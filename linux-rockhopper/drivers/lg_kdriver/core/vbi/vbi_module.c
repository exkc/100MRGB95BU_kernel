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
 *	VBI module control Drivers linux module
 *
 *  author      won.hur (won.hur@lge.com)
 *  version		1.0
 *  date
 *  note		Additional information.
 *
 *  @addtogroup lg115x_VBI
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
#include <linux/timer.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <linux/interrupt.h>

#include "vbi_kapi.h"

#include "vbi_module.h"
#include "vbi_drv.h"
#include "vbi_hw.h"
#include "vbi_data.h"

#include "os_util.h"

#include "../be/video_status_keeper.h"
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
int (*VBI_CheckVline625)(void);
int (*VBI_CheckAnalogCP)(void);

int (*VBI_TTX_HWInitialize)(void);
int (*VBI_TTX_SetInputFormat)(eVBIDataType type);
int (*VBI_TTX_SetInterrupt)(int on_off);
int (*VBI_TTX_ParsingVBIData)(sHeaderData *data);
int (*VBI_TTX_PutVBIData)(sHeaderData *data);
int (*VBI_TTX_SetInterruptClear)(void);
int (*VBI_TTX_Enable_VPS_Slicer)(BOOLEAN Enable);
int (*VBI_TTX_Set_TT_Slicer_Mode)(unsigned int mode);
int (*VBI_TTX_CheckOnLine318)(int mode);
int (*VBI_TTX_SetTypeLine318)(int onoff);
int (*VBI_TTX_SetVBILPF)(int onoff);
int (*VBI_TTX_DebugPrintMode)(int mode);

int (*VBI_CC_HWInitialize)(void);
int (*VBI_CC_SetInputFormat)(eVBIDataType type);
int (*VBI_CC_SetInterrupt)(int on_off);
int (*VBI_CC_ParsingVBIData)(unsigned int *packet);
int (*VBI_CC_SetInterruptClear)(void);
int (*VBI_CC_DebugPrintMode)(int mode);
#ifdef	KDRV_CONFIG_PM
int (*VBI_CC_RunSuspend)(void);
int (*VBI_CC_RunResume)(void);
int (*VBI_TTX_RunSuspend)(void);
int (*VBI_TTX_RunResume)(void);
#endif
int VBI_TTX_InterruptFunc(unsigned int status);
int VBI_CC_InterruptFunc(unsigned int status);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_VBI_INIT_MODE_T gVBIInitiateMode;
extern LX_VBI_INIT_MODE_T gVBIEnabledMode;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
//static BOOLEAN IS_VBI_INTERRUPT_REGISTERED	= false;

BOOLEAN ENABLE_ANALOGCC	= false;
BOOLEAN ENABLE_ANALOGTTX	= false;

static BOOLEAN gEnableLineFollowOnCCData = 1;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
void _VBI_TTX_InterruptRoutine(struct tasklet_struct *t);
DECLARE_TASKLET(VBI_TTX_ProcessData , _VBI_TTX_InterruptRoutine);
void _VBI_CC_InterruptRoutine(struct tasklet_struct *t);
DECLARE_TASKLET(VBI_CC_ProcessData , _VBI_CC_InterruptRoutine);
#else
void _VBI_TTX_InterruptRoutine(unsigned long unused);
DECLARE_TASKLET(VBI_TTX_ProcessData , _VBI_TTX_InterruptRoutine , 0);
void _VBI_CC_InterruptRoutine(unsigned long unused);
DECLARE_TASKLET(VBI_CC_ProcessData , _VBI_CC_InterruptRoutine , 0);
#endif
//static irqreturn_t VBI_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs);

static int __VBI_TTX_InitChipRev(void);
static int __VBI_CC_InitChipRev(void);

static int _VBI_FollowOnCCLine(int count, unsigned int *packet_array);
static int _VBI_CC_CountLineNumber(int line_number,int line_data,unsigned int *raw_line_number_count,unsigned int *line_number_count);
static int _VBI_CC_SelectLineNumber(unsigned int *raw_line_number_count,unsigned int *line_number_count, unsigned int *raw_line_number_sum, unsigned int *max_line_number);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static int gEnablePrintResultofLineDetect = 0;


/*========================================================================================
	Implementation Group
========================================================================================*/

/**
* VBI TTX Module Chip revision converter
*
* @param void
* @return int
*/

static int __VBI_TTX_InitChipRev(void)
{
	int ret = RET_OK;

	VBI_PRINT("VBI TTX chip revision is set to E60 A0\n");
	VBI_TTX_HWInitialize	    = TTX_Hal_HWInitialize;
	VBI_TTX_SetInputFormat	    = TTX_Hal_SetInputFormat;
	VBI_TTX_SetInterrupt	    = TTX_Hal_SetInterrupt;
	VBI_TTX_SetInterruptClear	= TTX_Hal_SetInterruptClear;
	VBI_TTX_ParsingVBIData	    = TTX_Hal_ParsingVBIData;
	VBI_TTX_PutVBIData		    = TTX_Hal_PutVBIData;
	VBI_TTX_SetVBILPF	        = TTX_Hal_SetVBILPF;
	VBI_TTX_CheckOnLine318	    = TTX_Hal_CheckOnLine318;
	VBI_TTX_SetTypeLine318	    = TTX_Hal_SetTypeLine318;
	VBI_TTX_Enable_VPS_Slicer   = TTX_Hal_Enable_VPS_Slicer;
	VBI_TTX_Set_TT_Slicer_Mode  = TTX_Hal_Set_TT_Slicer_Mode;
	VBI_TTX_DebugPrintMode		= TTX_Hal_DebugPrintMode;
	VBI_CheckVline625			= TTX_Hal_CheckVline625;
	VBI_CheckAnalogCP			= TTX_Hal_CheckAnalogCP;
#ifdef	KDRV_CONFIG_PM
	VBI_TTX_RunSuspend  		= TTX_Hal_RunSuspend;
	VBI_TTX_RunResume	    	= TTX_Hal_RunResume;
#endif

	return ret;
}



/**
* VBI TTX Module initialize
*
* @param void
* @return int
*/
int VBI_TTX_Initialize(void)
{
	int ret = RET_ERROR;
	__VBI_CC_InitChipRev();
    __VBI_TTX_InitChipRev();

	ret = VBI_TTX_HWInitialize();
	if(ret < 0) {
#ifdef INCLUDE_KDRV_BE
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_VBI, VBI_SKEEPER_VBI_MODULE_ERROR_STATUS, __L__);
#endif
		return -1;
	};

	VBI_TTX_SetInputFormat(eDisable);
	VBI_TTX_InitDataMemory();

	VBI_TTX_SetInputFormat(CURRENT_TTX);
	VBI_TTX_InterruptControl(ON);

	ENABLE_ANALOGTTX	= true;

	ret = RET_OK;

#if 0
	if(!IS_VBI_INTERRUPT_REGISTERED){
		if(lx_chip_rev() >= LX_CHIP_REV( H14,A0)){
			VBI_PRINT("VBI TTX Interrupt registering to H14 Ax\n");
			ret = request_irq(H14_IRQ_CVD_BCPU, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}
		else if(lx_chip_rev() >= LX_CHIP_REV( M14,B0)){
			VBI_PRINT("VBI TTX Interrupt registering to M14 Bx\n");
			ret = request_irq(M14_B0_IRQ_DE_IDS_CVD, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}
		else if(lx_chip_rev() >= LX_CHIP_REV( M14,A0)){
			VBI_PRINT("VBI TTX Interrupt registering to M14 Ax\n");
			ret = request_irq(M14_A0_IRQ_CVD_BCPU, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}
		else if(lx_chip_rev() >= LX_CHIP_REV( H13,A0)){
			VBI_PRINT("VBI TTX Interrupt registering to H13... \n");
			ret = request_irq(H13_IRQ_CVD_BCPU, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}

		if(ret) VBI_ERROR("ERROR! VBI Interrupt(request_irq) has failed! VBI will not work properly!\n");
		else VBI_PRINT("VBI TTX Interrupt register succeed!\n");

		IS_VBI_INTERRUPT_REGISTERED = true;
	}
#endif

	gVBIInitiateMode = LX_VBI_INIT_PAL;

	return ret;
}


/**
* VBI interrupt control
*
* @parm void
* @return int
*/
int VBI_TTX_InterruptControl(int onoff)
{
	int ret = RET_ERROR;

    VBI_TTX_SetInterrupt(onoff);
    ret = RET_OK;

	return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
void _VBI_TTX_InterruptRoutine(struct tasklet_struct *t)
#else
void _VBI_TTX_InterruptRoutine(unsigned long unused)
#endif
{
    //int ret = RET_OK;
	sHeaderData data;

	if(VBI_TTX_ParsingVBIData(&data) >= 0)
		VBI_TTX_PutVBIData(&data);
}



static int __VBI_CC_InitChipRev(void)
{
	int ret = RET_OK;

	VBI_PRINT("VBI CC Chip revision is set to E60 A0\n");
	VBI_CC_HWInitialize		    = CC_Hal_HWInitialize;
	VBI_CC_SetInputFormat	    = CC_Hal_SetInputFormat;
	VBI_CC_SetInterrupt		    = CC_Hal_SetInterrupt;
	VBI_CC_SetInterruptClear	= CC_Hal_SetInterruptClear;
	VBI_CC_ParsingVBIData   	= CC_Hal_ParsingVBIData;
	VBI_CC_DebugPrintMode		= CC_Hal_DebugPrintMode;
	VBI_CheckVline625			= CC_Hal_CheckVline625;
	VBI_CheckAnalogCP			= CC_Hal_CheckAnalogCP;
#ifdef	KDRV_CONFIG_PM
	VBI_CC_RunSuspend		    = CC_Hal_RunSuspend;
	VBI_CC_RunResume		    = CC_Hal_RunResume;
#endif

	return ret;
}



int VBI_CC_Initialize(void)
{
    int ret = RET_ERROR;

	__VBI_TTX_InitChipRev();
	__VBI_CC_InitChipRev();

	ret = VBI_CC_HWInitialize();
	if(ret < 0) {
		VBI_ERROR("VBI_CC_HWInitialize failed!\n");
#ifdef INCLUDE_KDRV_BE
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_VBI, VBI_SKEEPER_VBI_MODULE_ERROR_STATUS, __L__);
#endif
		return -1;
	}

	VBI_CC_SetInputFormat(eDisable);
	VBI_CC_InitDataMemory();

	VBI_CC_SetInputFormat(eClosedCaptionUS);

	ENABLE_ANALOGCC	= true;

	ret = RET_OK;

#if 0
	if(!IS_VBI_INTERRUPT_REGISTERED){
		if(lx_chip_rev() >= LX_CHIP_REV( H14,A0)){
			VBI_PRINT("VBI CC Interrupt registering to H14 Ax\n");
			ret = request_irq(H14_IRQ_CVD_BCPU, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}
		else if(lx_chip_rev() >= LX_CHIP_REV( M14,B0)){
			VBI_PRINT("VBI CC Interrupt registering to M14 Bx\n");
			ret = request_irq(M14_B0_IRQ_DE_IDS_CVD, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}
		else if(lx_chip_rev() >= LX_CHIP_REV( M14,A0)){
			VBI_PRINT("VBI CC Interrupt registering to M14 Ax\n");
			ret = request_irq(M14_A0_IRQ_CVD_BCPU, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}
		else if(lx_chip_rev() >= LX_CHIP_REV( H13,A0)){
			VBI_PRINT("VBI CC Interrupt registering to H13... \n");
			ret = request_irq(H13_IRQ_CVD_BCPU, (irq_handler_t)VBI_IRQ_Handler, 0, "CVD", NULL);
		}

		if(ret) VBI_ERROR("ERROR! VBI Interrupt(request_irq) has failed! VBI will not work properly!\n");
		else VBI_PRINT("VBI CC Interrupt register succeed!\n");

		IS_VBI_INTERRUPT_REGISTERED = true;
	}
#endif

	gVBIInitiateMode = LX_VBI_INIT_NTSC;

    return ret;
}

/**
* VBI interrupt service routine
*
* @param void
* @return int
*/
int VBI_TTX_InterruptFunc(unsigned int status)
{
    int ret = RET_OK;

	tasklet_schedule(&VBI_TTX_ProcessData);
	// interrupt already cleared in cvd_module.c
	//VBI_TTX_SetInterruptClear();

	return ret;
}


int VBI_CC_InterruptControl(int onoff)
{
    int ret = RET_OK;

    VBI_CC_SetInterrupt(onoff);

    return ret;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 5, 0))
void _VBI_CC_InterruptRoutine(struct tasklet_struct *t)
#else
void _VBI_CC_InterruptRoutine(unsigned long unused)
#endif
{
	int ret = RET_ERROR;
	int loop_count;

	static unsigned int data_array[6] = {0,};

    if ( gEnableLineFollowOnCCData > 0 )
	{
		ret = VBI_CC_ParsingVBIData(data_array);

		if(ret >= 1)
			_VBI_FollowOnCCLine(ret, data_array);
	}
	else
    {
		ret = VBI_CC_ParsingVBIData(data_array);

		for(loop_count=0;loop_count<ret;loop_count++)
		{
			/* VBI_CC_PutVBIData ???? size ?? 1 ?? ?? ??!
			 * ??? buffer? ?? overflow ?? ??? ??!
			 * ?? ??? size? ?? 1? ??? ?! */
			VBI_CC_PutVBIData(&data_array[loop_count], 1);
    	}
	}
}

/**
* VBI interrupt service routine
*
* @param void
* @return int
*/

int VBI_CC_InterruptFunc(unsigned int status)
{
	tasklet_schedule(&VBI_CC_ProcessData);
	// interrupt already cleared in cvd_module.c
	//VBI_CC_SetInterruptClear();
	return 0;
}

int VBI_CC_SetPrintResultOfLineDetect(int onoff)
{
	if(onoff>0) gEnablePrintResultofLineDetect = 1;
	else gEnablePrintResultofLineDetect = 0;

	return 0;
}

#if 0
static irqreturn_t VBI_IRQ_Handler(int irq, void *dev_id, struct pt_regs *regs)
{
	UINT32 cvd_int_status = 0;
	UINT32 vbi_int_status = 0;

	/* Step 1 : Get interrupt status */
	if( lx_chip_rev() >= LX_CHIP_REV( H14, A0))
	{
		CVD_H14Ax_RdFL(cvd_intr1_intr0);
		cvd_int_status = CVD_H14Ax_Rd(cvd_intr1_intr0);

		CVD_H14Ax_RdFL(cvd_intr1_intr1);
		vbi_int_status = CVD_H14Ax_Rd(cvd_intr1_intr1);

		VBI_INTR_PRINT("VBI ISR : intr0[0x%08x] intr1[0x%08x]\n", cvd_int_status, vbi_int_status);

		if((vbi_int_status & H14A0_VBI_INTERRUPT_MASK) )
		{
			if(ENABLE_ANALOGCC){
				VBI_CC_InterruptFunc(vbi_int_status);
			}

			if(ENABLE_ANALOGTTX){
				VBI_TTX_InterruptFunc(vbi_int_status);
			}
		}

		CVD_H14Ax_Wr(cvd_intr1_clear0, cvd_int_status);
		CVD_H14Ax_Wr(cvd_intr1_clear1, vbi_int_status);

		CVD_H14Ax_WrFL(cvd_intr1_clear0);
		CVD_H14Ax_WrFL(cvd_intr1_clear1);
	}
	else if( lx_chip_rev() >= LX_CHIP_REV( M14, B0))
	{
		CVD_M14Bx_RdFL(cvd_intr1_intr0);
		cvd_int_status = CVD_M14Bx_Rd(cvd_intr1_intr0);

		CVD_M14Bx_RdFL(cvd_intr1_intr1);
		vbi_int_status = CVD_M14Bx_Rd(cvd_intr1_intr1);

		VBI_INTR_PRINT("VBI ISR : intr0[0x%08x] intr1[0x%08x]\n", cvd_int_status, vbi_int_status);

		if(vbi_int_status & M14B0_VBI_INTERRUPT_MASK)
		{
			if(ENABLE_ANALOGCC){
				VBI_CC_InterruptFunc(vbi_int_status);
			}

			if(ENABLE_ANALOGTTX){
				VBI_TTX_InterruptFunc(vbi_int_status);
			}

		}

		CVD_M14Bx_Wr(cvd_intr1_clear0, cvd_int_status);
		CVD_M14Bx_Wr(cvd_intr1_clear1, vbi_int_status);

		CVD_M14Bx_WrFL(cvd_intr1_clear0);
		CVD_M14Bx_WrFL(cvd_intr1_clear1);

	}
	else if( lx_chip_rev() >= LX_CHIP_REV( M14, A0))
	{
		CVD_M14Ax_RdFL(cvd_intr1_intr0);
		cvd_int_status = CVD_M14Ax_Rd(cvd_intr1_intr0);

		CVD_M14Ax_RdFL(cvd_intr1_intr1);
		vbi_int_status = CVD_M14Ax_Rd(cvd_intr1_intr1);

		VBI_INTR_PRINT("VBI ISR : intr0[0x%08x] intr1[0x%08x]\n", cvd_int_status, vbi_int_status);

		if(vbi_int_status & M14A0_VBI_INTERRUPT_MASK)
		{
			if(ENABLE_ANALOGCC){
				VBI_CC_InterruptFunc(vbi_int_status);
			}

			if(ENABLE_ANALOGTTX){
				VBI_TTX_InterruptFunc(vbi_int_status);
			}
		}

		CVD_M14Ax_Wr(cvd_intr1_clear0, cvd_int_status);
		CVD_M14Ax_Wr(cvd_intr1_clear1, vbi_int_status);

		CVD_M14Ax_WrFL(cvd_intr1_clear0);
		CVD_M14Ax_WrFL(cvd_intr1_clear1);
	}
	else if( lx_chip_rev() >= LX_CHIP_REV( H13, B0))
	{
		CVD_H13Bx_RdFL(cvd_intr1_intr0);
		cvd_int_status = CVD_H13Bx_Rd(cvd_intr1_intr0);

		CVD_H13Bx_RdFL(cvd_intr1_intr1);
		vbi_int_status = CVD_H13Bx_Rd(cvd_intr1_intr1);

		VBI_INTR_PRINT("VBI ISR : intr0[0x%08x] intr1[0x%08x]\n", cvd_int_status, vbi_int_status);

		if(vbi_int_status & H13A0_VBI_INTERRUPT_MASK)
		{
			if(ENABLE_ANALOGCC){
				VBI_CC_InterruptFunc(vbi_int_status);
			}

			if(ENABLE_ANALOGTTX){
				VBI_TTX_InterruptFunc(vbi_int_status);
			}
		}


		CVD_H13Bx_Wr(cvd_intr1_clear0, cvd_int_status);
		CVD_H13Bx_Wr(cvd_intr1_clear1, vbi_int_status);

		CVD_H13Bx_WrFL(cvd_intr1_clear0);
		CVD_H13Bx_WrFL(cvd_intr1_clear1);
	}
	else if( lx_chip_rev() >= LX_CHIP_REV( H13, A0))
	{
		CVD_H13Ax_RdFL(cvd_intr1_intr0);
		cvd_int_status = CVD_H13Ax_Rd(cvd_intr1_intr0);

		CVD_H13Ax_RdFL(cvd_intr1_intr1);
		vbi_int_status = CVD_H13Ax_Rd(cvd_intr1_intr1);

		VBI_INTR_PRINT("VBI ISR : intr0[0x%08x] intr1[0x%08x]\n", cvd_int_status, vbi_int_status);

		if(vbi_int_status & H13A0_VBI_INTERRUPT_MASK)
		{
			if(ENABLE_ANALOGCC){
				VBI_CC_InterruptFunc(vbi_int_status);
			}

			if(ENABLE_ANALOGTTX){
				VBI_TTX_InterruptFunc(vbi_int_status);
			}
		}

		CVD_H13Ax_Wr(cvd_intr1_clear0, cvd_int_status);
		CVD_H13Ax_Wr(cvd_intr1_clear1, vbi_int_status);

		CVD_H13Ax_WrFL(cvd_intr1_clear0);
		CVD_H13Ax_WrFL(cvd_intr1_clear1);

	}
	else{
		VBI_ERROR("WARNING! Unknown chip revision at VBI IRQ!\n");
		// Add statement for other chip version
	}

	return IRQ_HANDLED;
}
#endif

int VBI_TOP_UnInitialize(void)
{
	int ret = RET_OK;

#if 0
	if(IS_VBI_INTERRUPT_REGISTERED){
		if(lx_chip_rev() >= LX_CHIP_REV( H14,A0))
			free_irq(H14_IRQ_CVD_BCPU, NULL);
		else if(lx_chip_rev() >= LX_CHIP_REV( M14,B0))
			free_irq(M14_B0_IRQ_DE_IDS_CVD, NULL);
		else if(lx_chip_rev() >= LX_CHIP_REV( M14,A0))
			free_irq(M14_A0_IRQ_CVD_BCPU, NULL);
		else if(lx_chip_rev() >= LX_CHIP_REV( H13,A0))
			free_irq(H13_IRQ_CVD_BCPU, NULL);

		IS_VBI_INTERRUPT_REGISTERED = false;
	}
#endif

	return ret;
}

int VBI_SetLogmPrint(unsigned long arg)
{
	int ret = RET_ERROR;
	LX_VBI_LOGM_SETTING_T stParams;

	do{
		/* Step 1. Copy data from application */
		ret = copy_from_user(&stParams, (LX_VBI_LOGM_SETTING_T *)arg, sizeof(LX_VBI_LOGM_SETTING_T));
		if (ret) break;

		/* Step 2. Check validty of logLevel, whether it is in the LOGM Level*/
		if( /*(stParams.logLevel < 0)|| */ (stParams.logLevel >= LX_LOGM_LEVEL_MAX)){
			VBI_ERROR("Unknown LOGM Level[%d]\n", stParams.logLevel);
#ifdef INCLUDE_KDRV_BE
			(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_VBI, VBI_SKEEPER_VBI_MODULE_ERROR_STATUS, __L__);
#endif
			ret = RET_ERROR;
			break;
		}

		/* Step 3. Operate Logm Setting */
		if(stParams.onOff){
			OS_DEBUG_EnableModuleByIndex  ( g_vbi_debug_fd, stParams.logLevel, DBG_COLOR_NONE );
			VBI_INFO("VBI LOGM Enabled for LogLevel[%d]\n", stParams.logLevel);
		}
		else{
			OS_DEBUG_DisableModuleByIndex ( g_vbi_debug_fd, stParams.logLevel);
			VBI_INFO("VBI LOGM disabled for LogLevel[%d]\n", stParams.logLevel);
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int VBI_Module_Resume(LX_VBI_INIT_MODE_T mode, int isrOnOff)
{
	int ret = RET_ERROR;

	VBI_PRINT("[%s:%d] Called with mode[%d], isrOnOff[%d]\n", __F__, __L__, mode, isrOnOff);

	if(mode == LX_VBI_INIT_NONE){
		VBI_PRINT("[%s:%d] Nothing to resume because, it was not initiated before suspend\n", __F__, __L__);
		return RET_OK;
	}

#ifdef KDRV_CONFIG_PM
	do{
		/* Resume Initial setting & Interrupt setting */
		if(mode == LX_VBI_INIT_NTSC){
			VBI_PRINT("[%s:%d] ReInitiating VBI to previous mode to [NTSC]\n", __F__, __L__);
			ret = VBI_CC_RunResume();

			if(ret<0) {
				VBI_PRINT("[%s:%d] Error! Could not Re-Init. Ret was [%d]\n", __F__, __L__, ret);
				break;
			}

			if(isrOnOff){
				VBI_PRINT("[%s:%d] Re-Activating VBI ISR to [NTSC]\n", __F__, __L__);
				ret =  VBI_CC_SetInterrupt(isrOnOff);
			}

			if(ret<0) {
				VBI_PRINT("[%s:%d] Error! Could not Re-Activate ISR. Ret was [%d]\n", __F__, __L__, ret);
				break;
			}
		}
		else if(mode == LX_VBI_INIT_PAL){
			VBI_PRINT("[%s:%d] ReInitiating VBI to previous mode to [PAL/SECAM]\n", __F__, __L__);
			ret = VBI_TTX_RunResume();

			if(ret<0) {
				VBI_PRINT("[%s:%d] Error! Could not Re-Init. Ret was [%d]\n", __F__, __L__, ret);
				break;
			}

			if(isrOnOff){
				VBI_PRINT("[%s:%d] Re-Activating VBI ISR to [PAL/SECAM]\n", __F__, __L__);
				ret =  VBI_TTX_SetInterrupt(isrOnOff);
			}

			if(ret<0) {
				VBI_PRINT("[%s:%d] Error! Could not Re-Activate ISR. Ret was [%d]\n", __F__, __L__, ret);
				break;
			}

		}
		else{
			VBI_PRINT("[%s:%d] Warning! Unknown previous mode type[%d]. Maybe snapshot memory curruption\n", __F__, __L__, mode);
			ret = RET_ERROR;
			break;
		}


	}while(0);
#endif

	if(ret<0) VBI_PRINT("[%s:%d] VBI Resume failed\n", __F__, __L__);
	else VBI_PRINT("[%s:%d] finished job OK!\n", __F__, __L__);

	return ret;
}

int VBI_Empty_Function_void(void)
{
	VBI_ERROR("Warning! VBI function called without Chip-initialization\n");
	return 0;
}

int VBI_Empty_Function_int(int empty)
{
	VBI_ERROR("Warning! VBI function called without Chip-initialization\n");
	return 0;
}

int VBI_Empty_Function_bool(BOOLEAN empty)
{
	VBI_ERROR("Warning! VBI function called without Chip-initialization\n");
	return 0;
}

static int _VBI_FollowOnCCLine(int count, unsigned int *packet_array)
{
	int line_number;
	int line_data;
	int loop_count;

	static unsigned int line_number_count[3] ={0,} ;
	static unsigned int raw_line_number_count[3] ={0,};
	static unsigned int raw_line_number_sum[3] ={0,};
	static unsigned int prev_cc_int_time = 0;
	unsigned int curr_cc_int_time;
	static unsigned int max_line_number = 21;

	curr_cc_int_time = jiffies_to_msecs(jiffies);	// get current time

	for(loop_count=0;loop_count<count;loop_count++)
	{
		line_number = (packet_array[loop_count]&0xFFC00000) >> 22;
		line_data = (packet_array[loop_count]&0x0000FFFF);

		_VBI_CC_CountLineNumber(line_number, line_data, raw_line_number_count, line_number_count);

		// Select most frequent CC line number for CC slicing
		if( (curr_cc_int_time - prev_cc_int_time ) > 500)
		{
			prev_cc_int_time = jiffies_to_msecs(jiffies);	// get current time
			_VBI_CC_SelectLineNumber(raw_line_number_count, line_number_count, raw_line_number_sum, &max_line_number);
		}

		if( (max_line_number == 18) && ( (line_number == 18) || (line_number ==281)) )
		{
			if(raw_line_number_sum[0] > 6)
				VBI_CC_PutVBIData(&packet_array[loop_count] , 1);
		}
		else if( (max_line_number == 21) && ( (line_number == 21) || (line_number ==284)) )
		{
			if(raw_line_number_sum[1] > 6)
				VBI_CC_PutVBIData(&packet_array[loop_count] , 1);
		}
		else if ( (max_line_number == 22) && ( (line_number == 22) || (line_number ==285)) )
		{
			if(raw_line_number_sum[2] > 6)
				VBI_CC_PutVBIData(&packet_array[loop_count] , 1);
		}
		else
		{
			VBI_DEBUG("garbage CC packet???\n");
		}
	}

	return RET_OK;
}

static int _VBI_CC_CountLineNumber(int line_number,int line_data,unsigned int *raw_line_number_count,unsigned int *line_number_count)
{
	int parity_valid_flag = 0;

	parity_valid_flag = VBI_CC_CheckDataParity(line_data);

	if(parity_valid_flag == 0)
		VBI_DEBUG("Parity Error !!!! [%d], [0x%x]\n", line_number, line_data);

	//if(line_data == 0x8080) CC_PRINT("Data on line [%d] is [0x8080]\n", line_number);

	if((line_number == 18) || (line_number == 281))
	{
		raw_line_number_count[0]++;
		if((line_data != 0x8080)&&(parity_valid_flag == 1)) line_number_count[0] ++;
	}
	else if((line_number == 21) || (line_number ==284))
	{
		raw_line_number_count[1]++;
		if((line_data != 0x8080)&&(parity_valid_flag == 1))line_number_count[1] ++;
	}
	else if((line_number == 22) || (line_number ==285))
	{
		raw_line_number_count[2]++;
		if((line_data != 0x8080) &&(parity_valid_flag == 1))line_number_count[2] ++;
	}
	else
	{
		VBI_DEBUG("ERROR BAD LINE NUMBER [%d]\n", line_number);
	}

	return RET_OK;
}

static int _VBI_CC_SelectLineNumber(unsigned int *raw_line_number_count,unsigned int *line_number_count, unsigned int *raw_line_number_sum, unsigned int *max_line_number)
{
	unsigned int max_value = 0;
	unsigned int raw_max_value = 0;

	static unsigned int prev_max_line_number = 21;
	static unsigned int curr_max_line_number = 21;

	unsigned int line_number_sum[3] ={0,} ;

	memcpy(raw_line_number_sum, raw_line_number_count, sizeof(unsigned int)*3 );
	memset(raw_line_number_count, 0, sizeof(unsigned int)* 3);
	memcpy(line_number_sum, line_number_count, sizeof(unsigned int)*3);
	memset(line_number_count, 0, sizeof(unsigned int)* 3);

	max_value = 0;
	raw_max_value = 0;

	VBI_DEBUG("LINE18[%d], LINE21[%d], LINE22[%d]\n", line_number_sum[0], line_number_sum[1], line_number_sum[2]);

	if(raw_line_number_sum[0] > ((raw_line_number_sum[1])*3) )
	{
		curr_max_line_number = 18;
		*max_line_number = curr_max_line_number;
		max_value = line_number_sum[0];
		raw_max_value = raw_line_number_sum[0];
	}
	else if(raw_line_number_sum[0] >= ((raw_line_number_sum[1]>>2)+(raw_line_number_sum[1]>>3)) )
	{
		VBI_DEBUG("Difficuilt line selection #1...\n");
		if(	line_number_sum[0] > line_number_sum[1])
		{

			if(raw_line_number_sum[0] >= VALID_LOWER_RANGE_OF_CC_LINE )
			{
				curr_max_line_number = 18;
				if(prev_max_line_number == curr_max_line_number)
					*max_line_number = curr_max_line_number;
				max_value = line_number_sum[0];
				raw_max_value = raw_line_number_sum[0];
			}
			else if(raw_line_number_sum[1] >= VALID_LOWER_RANGE_OF_CC_LINE)
			{
				curr_max_line_number = 21;
				if(prev_max_line_number == curr_max_line_number)
					*max_line_number = curr_max_line_number;
				max_value = line_number_sum[1];
				raw_max_value = raw_line_number_sum[1];
			}
			else
			{
				VBI_DEBUG(" State 1 : use previous...\n");
				// ?? ???쿡?? ??~ ?Ǻ?; ?????ϳ?, ????° ???????? ?Ǻ?; '?Ͽ? ???? ????: d?صд?.
				if(raw_line_number_sum[0] >= raw_line_number_sum[1])
				{
					max_value = line_number_sum[0];
					raw_max_value = raw_line_number_sum[0];
				}
				else
				{
					max_value = line_number_sum[1];
					raw_max_value = raw_line_number_sum[1];
				}
			}
		}
		else if(line_number_sum[0] < line_number_sum[1])
		{

			if(raw_line_number_sum[1] >= VALID_LOWER_RANGE_OF_CC_LINE )
			{
				curr_max_line_number = 21;
				if(prev_max_line_number == curr_max_line_number)
					*max_line_number = curr_max_line_number;
				max_value = line_number_sum[1];
				raw_max_value = raw_line_number_sum[1];
			}
			else
			{
				VBI_DEBUG(" State 1 : use previous...\n");
				if(raw_line_number_sum[1] >= raw_line_number_sum[0])
				{
					max_value = line_number_sum[1];
					raw_max_value = raw_line_number_sum[1];
				}
				else
				{
					max_value = line_number_sum[0];
					raw_max_value = raw_line_number_sum[0];
				}
			}
		}
		else
		{
			VBI_DEBUG(" State 1 : use previous...\n");
			if(raw_line_number_sum[0] >= raw_line_number_sum[1])
			{
				raw_max_value = raw_line_number_sum[0];
				max_value = line_number_sum[0];
			}
			else
			{
				raw_max_value = raw_line_number_sum[1];
				max_value = line_number_sum[1];
			}
		}
	}
	else
	{
		curr_max_line_number = 21;
		*max_line_number = curr_max_line_number;
		max_value = line_number_sum[1];
		raw_max_value = raw_line_number_sum[1];
	}

	if(raw_line_number_sum[2] > (raw_max_value*3))
	{
		curr_max_line_number = 22;
		*max_line_number = curr_max_line_number;
		max_value = line_number_sum[2];
		raw_max_value = raw_line_number_sum[2];
	}
	else if(raw_line_number_sum[2] >= ((raw_max_value>>2)+(raw_max_value>>3)) )
	{
		VBI_DEBUG("Difficuilt line selection #2...\n");
		if(line_number_sum[2] > max_value)
		{
			if(raw_line_number_sum[2] >= VALID_LOWER_RANGE_OF_CC_LINE)
			{
				curr_max_line_number = 22;
				if(prev_max_line_number == curr_max_line_number)
					*max_line_number = curr_max_line_number;
				max_value = line_number_sum[2];
				raw_max_value = raw_line_number_sum[2];
			}
			else if(raw_max_value >= VALID_LOWER_RANGE_OF_CC_LINE)
			{
				VBI_DEBUG(" State 2 : use previous...\n");
				// do nothing...
			}
			else
			{
				// do nothing...
				VBI_DEBUG(" State 2 : use previous...\n");
			}
		}
		else if(line_number_sum[2] < max_value)
		{
			// do nothing
			VBI_DEBUG(" State 2 : use previous...\n");
		}
		else
		{
			// do nothing
			VBI_DEBUG(" State 2 : use previous...\n");
		}
	}
	else
	{
		// do nothing
		VBI_DEBUG(" State 2 : use previous...\n");
	}

	if(gEnablePrintResultofLineDetect>0)
	{
		CC_PRINT("Vote value : 18:[%d], 21:[%d], 22:[%d]\n", line_number_sum[0], line_number_sum[1], line_number_sum[2]);
		CC_PRINT("RAW Vote value : 18:[%d], 21:[%d], 22:[%d]\n", raw_line_number_sum[0], raw_line_number_sum[1], raw_line_number_sum[2]);
		CC_PRINT("Max Line Number = [%d], curr = [%d], prev = [%d]\n", *max_line_number, curr_max_line_number, prev_max_line_number);
	}

	prev_max_line_number = curr_max_line_number;;

	return RET_OK;
}
/** @} */
