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
 *  @author		wonsik.do
 *  @version	1.0
 *  @date		2010-11-16
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/signal.h>
#include <linux/semaphore.h>

#include "o20/os/linux_irqs.h"

#include "afe_drv.h"

#include "os_util.h"
//#include "hdmi_phy_reg.h"

#include "afe_cfg.h"

#include "cvd_module.h"
#ifdef INCLUDE_L9_CHIP_KDRV
#endif
//#include "pe_dcm.h"
#include "de_cvd_reg.h"

#include "o26/afe/cvd_hw_o26a0.h"

#include "o24/afe/cvd_hw_o24a0.h"

#include "m23/afe/cvd_hw_m23a0.h"

#include "o22/afe/cvd_hw_o22a0.h"

#include "e60/afe/cvd_hw_e60a0.h"

#include "o20/afe/cvd_hw_o20a0.h"

#include "m19/afe/cvd_hw_m19a0.h"

#include "o18/afe/cvd_hw_o18a0.h"

#include "cvd_hal.h"
#include "cvd_task.h"
#include "cvd_control.h"

#include <asm/io.h>
#include <linux/slab.h>

#include "hma_alloc.h"

#include "afe_kwrap.h"

#ifdef INCLUDE_KDRV_PQE_PM
#include "pqe_pm_drv.h"
#endif
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#undef USE_AFE_KDRV_FOR_M14
#undef USE_AFE_KDRV_FOR_H15
#undef USE_AFE_KDRV_FOR_M16

#ifdef INCLUDE_O26_CHIP_KDRV
#define USE_AFE_KDRV_FOR_O26
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#define USE_AFE_KDRV_FOR_O24
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#define USE_AFE_KDRV_FOR_M23
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#define USE_AFE_KDRV_FOR_O22
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#define USE_AFE_KDRV_FOR_E60
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
#define USE_AFE_KDRV_FOR_O20
#endif

#define	MAINCVD_TIMEOUT	150	// 1000 msec
#define	L9_CVD_TIMEOUT	50	// 1000 msec


#define ENABLE_CVD_THREAD				///<< Must define this to make CVD driver work.
//#undef ENABLE_CVD_THREAD
#define CVD_THREAD_VSYNC_CONTROL	1 	///<< CVD Thread is wakeup by CVD vsync


#define CVD_STATE_TRANSITION_MAX	15

#define ENABLE_CVD_STATE_TRANSITION_LIMIT 1
#define ENABLE_CVD_INTERRUPT_CONTROL 0

#define CVD_FC_FOR_SECAM_LOW	190
#define CVD_FC_FOR_SECAM_HIGH	240
#define CVD_FC_FOR_PALCN_LOW	170
#define CVD_FC_FOR_PALCN_HIGH	220
//#define CVD_KERNEL_DEBUG

//#define DCRESTORE_ACCUM_WIDTH_INITIAL			0x25

// Workaround for chroma lost on brasil streams : 20120202

// moved to cvd_hw.h
//#define L9_FAST_3DCOMB_WORKAROUND

// Workaround for stable AGC on weak RF signal
//#define CVD_AGC_PEAK_CONTROL_WORKAROUND
//#define L9_ADAPTIVE_AGC_PEAK_NOMINAL_CONTROL
#define AGC_PEAK_NOMINAL_INITIAL_VALUE	0x30
#define AGC_PEAK_NOMINAL_DEFAULT_VALUE	0x0a

#define USE_REGISTER_VALUE_FOR_SYNC_STATES
/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_KDRV_DEMOD
extern int DEMOD_ANALOG_Set_ClampingCtrl(UINT8 clampCount, UINT16 stepsize);
#endif

extern int VBI_CC_InterruptFunc(unsigned int status);
extern int VBI_TTX_InterruptFunc(unsigned int status);
extern int TTX_Hal_SetInterrupt(int on_off);

int CVD_Vsync_Interrupt(void);
LX_AFE_VIDEO_SYSTEM_T CVD_Get_Color_System(void);
int CVD_Set_Burst_Gate_12(int burst1_start, int burst1_end, int burst2_start, int burst2_end);
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern LX_CVD_REG_T *pVportRegCfg;

extern CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_O26A0;
extern CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_O24A0;
extern CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_M23A0;
extern CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_O22A0;
extern CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_E60A0;
extern CVD_COLOR_SYSTEM_ARRAY_3CS_T g_SetColorSystem_3CS_O20A0;

extern BOOLEAN ENABLE_ANALOGCC;
extern BOOLEAN ENABLE_ANALOGTTX;

extern UINT32 g_CVD_WA_Low_Burst_ATV_Noise;
extern UINT32 g_CVD_Soft_Reset_WA_for_HLock_Error;
extern UINT32 g_CVD_Adaptive_Burst_WA_for_SECAM;
extern UINT32 g_O26_CVD_HW_DRV_REV;
extern UINT32 g_O24_CVD_HW_DRV_REV;
extern UINT32 g_M23_CVD_HW_DRV_REV;
extern UINT32 g_O22_CVD_HW_DRV_REV;
extern UINT32 g_E60_CVD_HW_DRV_REV;
extern UINT32 g_O20_CVD_HW_DRV_REV;
extern UINT32 g_CVD_No_Burst_SECAM_WA;	//191114 : WA for no burst signal not to determined to SECAM
extern UINT32 g_CVD_Low_Burst_PAL_WA;	//191202 : WA for low burst PAL signal not to go into noburst mode

extern LX_AFE_CVD_SOURCE_ATTRIBUTE_T _g_kwrap_cvd_source_attribute;
extern LX_AFE_CVD_INPUT_PORT_T _g_kwrap_cvd_input_port;

extern BOOLEAN g_CVD_CMA_POOL;
extern BOOLEAN g_CVD_USE_TE_SHARED_POOL;
/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
//CVD_SET_SYSTEM_3CS_T (*pSetColorSystem_3CS)[CVD_STATE_VideoNotReady];
CVD_COLOR_SYSTEM_ARRAY_3CS_T *pSetColorSystem_3CS;

volatile DE_CVD_REG_T __iomem *gpRegCVD;
volatile DE_CVD_REG_T __iomem *gpRealRegCVD;

// H13A0 CVD Register Access
#ifdef INCLUDE_L9_CHIP_KDRV
#endif


BOOLEAN gCVDInitStatus = FALSE;

BOOLEAN gCVD_2d_mode = FALSE;
//UINT8 	gEnable_Monitor_3DCOMB_State = 0;

//spinlock_t 	cvd_lock;
//ULONG		cvd_irq_flags = 0;

#ifdef ENABLE_CVD_THREAD
struct task_struct	*stCVD_Thread;
//long	gPid_cvd_thread = -1;

static int		gForce_thread_sleep = 1;
static int		gCVD_thread_running = 0;
int		gWait_return = -1;

DECLARE_WAIT_QUEUE_HEAD(WaitQueue_CVD);
#endif
#ifdef	KDRV_CONFIG_PM
typedef	struct{
	BOOLEAN CVDInitStatus;
	LX_AFE_CVD_SELECT_T SelectMainSub;
}S_AFE_PM_DATA;

//S_AFE_PM_DATA *gAfePmData;
#endif

//CVD_AGC_PEAK_CONTROL_T	g_CVD_AGC_Peak_Control;

CVD_STATUS_3CS_T	g_CVD_Status_3CS = {0,};

//LX_AFE_CVD_SUPPORT_COLOR_SYSTEM_T	g_CVD_Color_System_Support = LX_COLOR_SYSTEM_MULTI;
//int		gAutoProgramming	= 0;
CVD_PATTERN_DETECTION_T g_CVD_Pattern_Detection_t ;

BOOLEAN IS_CVD_INTERRUPT_REGISTERED	= false;
UINT32 g_CVD_HW_DRV_REV = 0;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
#ifdef CVD_AGC_PEAK_CONTROL_WORKAROUND		//disabled
static int CVD_Adaptive_AGC_Peak_Control(CVD_AGC_PEAK_CONTROL_T *pCVD_AGC_Peak_Control );
#endif

//static int MainCVD_Thread(void *data);
static int MainCVD_Thread_Vsync_Ctrl(void *data);

static int CVD_Get_No_Signal_Flag(void);
//static int CVD_Get_Chromalock_Flag(void);

static int CVD_Get_Vline_625_Reg(void);	// Read user forced vline 625 value
//void (*CVD_Program_Color_System_PreJob)(CVD_SET_SYSTEM_MAIN_T *pSet_system_t);
//static int CVD_Init_Global_Params(void);

static int CVD_Get_Reg_States_Detail(LX_AFE_CVD_STATES_DETAIL_T	*pcvd_states_detail_t);
//static int CVD_Set_Color_System_3CS(CVD_STATE_T cvd_next_state);
//static int CVD_Set_ycsep_Blend(int blend);
//static int CVD_Set_clampagc_updn(int updn_value);
//static int CVD_Set_dc_clamp_mode(int mode);

static irqreturn_t CVD_IRQ_Handler(int irq, void *dev_id);
static int CVD_SetInterruptClear(UINT32 interrupt_clear_mask);
static int CVD_Init_Buffer(void);
static int CVD_AllocFree_Buffer(int flag);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
#ifdef CVD_AGC_PEAK_CONTROL_WORKAROUND		//disabled
static UINT32	g_AGC_Peak_Nominal_Value = AGC_PEAK_NOMINAL_DEFAULT_VALUE;
#endif

CVD_ADAPTIVE_PEAK_NOMINAL_CONTROL_T g_CVD_AGC_Peak_Nominal_Control ;

static	int CVD_Set_Initial_Color_System(void);
static char cvd_mem_pool[32];
/*========================================================================================
	Implementation Group
========================================================================================*/
#ifdef INCLUDE_KDRV_PQE_PM
static int CVD_PQE_PM_RuntimeCallback(int action);

static struct pqe_pm_config g_pqe_pm_cfg =
{
    .name = "afe_pm",
    .opt = PQE_PM_OPT_MONITOR,
    .order = 0,
    .callback = CVD_PQE_PM_RuntimeCallback,
};

static int g_pqe_pm_id = -1;

static int CVD_PQE_PM_RuntimeCallback(int pqe_pm_action)
{
	if(gCVDInitStatus == FALSE)
	{
		AFE_PRINT("%s :  before Initial setting\n", __func__);
		return 0;
	}

    if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_PREPARE)
    {
		AFE_PRINT("[SUSPEND_PREPARE] disable interrupt\n");
		CVD_SetVsyncInterrupt(0);	//Disable CVD Vsync Interrupt
		CVD_SetUnlockInterrupt(0);
		TTX_Hal_SetInterrupt(0);
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND)
    {
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_SUSPEND_COMPLETED)
    {
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_PREPARE)
    {
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME)
    {
    }
    else if (pqe_pm_action == PQE_PM_DEVICE_RESUME_COMPLETED)
    {
		AFE_PRINT("[RESUME_COMPLETED] enable interrupt\n");
		CVD_SetVsyncInterrupt(1);	//Enable CVD Vsync Interrupt
    }
    else
    {
        // not supported action
    }

    return RET_OK;
}

#endif

static int CVD_Set_Buffer_Base_Addr(phys_addr_t cvd_paddr)
{
	int ret = RET_OK;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Set_Buffer_Base_Addr(cvd_paddr);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Set_Buffer_Base_Addr(cvd_paddr);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Set_Buffer_Base_Addr(cvd_paddr);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Set_Buffer_Base_Addr(cvd_paddr);
	} else
#endif
	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_PQ_Mode(LX_AFE_CVD_PQ_MODE_T cvd_pq_mode)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Set_PQ_Mode(cvd_pq_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Set_PQ_Mode(cvd_pq_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Set_PQ_Mode(cvd_pq_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Set_PQ_Mode(cvd_pq_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Set_PQ_Mode(cvd_pq_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Set_PQ_Mode(cvd_pq_mode);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

#if 0
int CVD_Set_for_Tunning(BOOLEAN bEnable)
{
	int ret = RET_OK;

	return ret;
}
#endif

int CVD_Power_Down(LX_AFE_CVD_SELECT_T select_main_sub, BOOLEAN PowerOnOFF)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Power_Down(select_main_sub, PowerOnOFF);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Power_Down(select_main_sub, PowerOnOFF);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Power_Down(select_main_sub, PowerOnOFF);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Power_Down(select_main_sub, PowerOnOFF);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Power_Down(select_main_sub, PowerOnOFF);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Power_Down(select_main_sub, PowerOnOFF);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_Source_Type(LX_AFE_CVD_SET_INPUT_T	cvd_input_info)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Set_Source_Type(cvd_input_info);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Set_Source_Type(cvd_input_info);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Set_Source_Type(cvd_input_info);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Set_Source_Type(cvd_input_info);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Set_Source_Type(cvd_input_info);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Set_Source_Type(cvd_input_info);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Clamp_Current_Control(UINT8 value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Clamp_Current_Control(value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Clamp_Current_Control(value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Clamp_Current_Control(value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Clamp_Current_Control(value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Clamp_Current_Control(value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Clamp_Current_Control(value);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_Scart_Overlay(BOOLEAN bEnable)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Scart_Overlay(bEnable);

	return ret;
}

int CVD_Reg_Init(LX_AFE_CVD_SELECT_T select_main_sub)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		g_CVD_HW_DRV_REV = g_O26_CVD_HW_DRV_REV;
		CVD_O26Ax_Reg_Init(select_main_sub);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		g_CVD_HW_DRV_REV = g_O24_CVD_HW_DRV_REV;
		CVD_O24Ax_Reg_Init(select_main_sub);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		g_CVD_HW_DRV_REV = g_M23_CVD_HW_DRV_REV;
		CVD_M23Ax_Reg_Init(select_main_sub);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		g_CVD_HW_DRV_REV = g_O22_CVD_HW_DRV_REV;
		CVD_O22Ax_Reg_Init(select_main_sub);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		g_CVD_HW_DRV_REV = g_E60_CVD_HW_DRV_REV;
		CVD_E60Ax_Reg_Init(select_main_sub);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		g_CVD_HW_DRV_REV = g_O20_CVD_HW_DRV_REV;
		CVD_O20Ax_Reg_Init(select_main_sub);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Get_Scart_AR(LX_AFE_SCART_AR_INFO_T	*pScart_ar_param)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Get_Scart_AR(pScart_ar_param);

	return ret;
}

int CVD_Vport_Reg_Read(LX_AFE_REG_RW_T *pReg_addr_data_t)
{
	int ret = RET_OK;

	UINT32 value;
	void *recvAddr;
	void *currAddr;
	UINT32 nextValue;
	uintptr_t dBit;
	uintptr_t wBit;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	do {
		recvAddr = (void *)(uintptr_t)pReg_addr_data_t->addr;
		/*
		   if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DE_BASE;
		   else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		 */

		recvAddr += (uintptr_t)gpRealRegCVD;

	currAddr = recvAddr;
	currAddr = (void *)((uintptr_t)currAddr >> 2);
	currAddr = (void *)((uintptr_t)currAddr << 2);
	value = REG_RD(currAddr);
	if (currAddr == recvAddr) break;
	nextValue = REG_RD(currAddr+4);
	dBit = ((uintptr_t)recvAddr - (uintptr_t)currAddr)<<3;
	wBit = (32 - dBit);
	value  = GET_BITS(value, dBit, wBit);
	value += GET_PVAL(nextValue, wBit, dBit);

	} while (0);
	pReg_addr_data_t->data = value;

	return ret;
}

int CVD_Vport_Reg_Write(LX_AFE_REG_RW_T *pReg_addr_data_t)
{
	int ret = RET_OK;

	UINT32 value;
	void *recvAddr;
	void *currAddr;
	UINT32 currValue;
	UINT32 nextValue;
	uintptr_t dBit;
	uintptr_t wBit;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	do {
		recvAddr = (void *)(uintptr_t)pReg_addr_data_t->addr;
		value = pReg_addr_data_t->data;
		/*
		   if		(recvAddr <= 0x2000) recvAddr += DTVSOC_DE_BASE;
		   else if (recvAddr <= 0xffff) recvAddr += DTVSOC_VIRT_PL301_BASE;
		 */

		recvAddr += (uintptr_t)gpRealRegCVD;

		currAddr = recvAddr;
		currAddr = (void *)((uintptr_t)currAddr >> 2);
		currAddr = (void *)((uintptr_t)currAddr << 2);
		if (currAddr == recvAddr) {
			REG_WD(recvAddr, value);
			break;
		}
		currValue = REG_RD(currAddr);
		nextValue = REG_RD((currAddr+4));
		dBit = ((uintptr_t)recvAddr - (uintptr_t)currAddr)<<3;
		wBit = (32 - dBit);
		currValue  = GET_BITS(currValue ,0	  ,dBit);
		currValue += GET_PVAL(value		,dBit ,wBit);
		nextValue  = GET_PVAL(nextValue ,dBit ,wBit);
		nextValue += GET_BITS(value		,0	  ,dBit);
		REG_WD(currAddr		,currValue);
		REG_WD((currAddr+4) ,nextValue);
	} while (0);

	return ret;
}

int CVD_Get_FB_Status(LX_AFE_SCART_MODE_T *pScart_fb_mode)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Get_FB_Status(pScart_fb_mode);

	return ret;
}

static int CVD_Get_No_Signal_Flag(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_No_Signal_Flag();

	return ret;
}

int CVD_Get_HLock_Flag(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_HLock_Flag();

	return ret;
}

int CVD_Get_VLock_Flag(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_VLock_Flag();

	return ret;
}

int CVD_Get_Vline_625_Flag(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Vline_625_Flag();

	return ret;
}

#if 0
static int CVD_Get_Chromalock_Flag(void)
{
	int ret;

	ret = CVD_Hal_Get_Chromalock_Flag();

	return ret;
}
#endif

int CVD_Get_Noise_Status(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Noise_Status();

	return ret;
}

int CVD_Channel_Power_Control(UINT32 on_off)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	if(on_off)
	{
		ret = CVD_AllocFree_Buffer(1);

		if(ret < 0)
		{
			AFE_ERROR("!!! CVD CMA Alloc Failed !!! : %d\n", ret);

			return RET_ERROR;
		}
	}


#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Channel_Power_Control(on_off);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Channel_Power_Control(on_off);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Channel_Power_Control(on_off);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Channel_Power_Control(on_off);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Channel_Power_Control(on_off);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Channel_Power_Control(on_off);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	if(on_off == 0)
	{
		ret = CVD_AllocFree_Buffer(0);

		if(ret < 0)
		{
			AFE_ERROR("!!! CVD CMA Free Failed !!! %d\n", ret);
			return ret;
		}
	}

	return ret;
}

int CVD_Bypass_Control(LX_AFE_CVD_BYPASS_CONTROL_T *cvd_bypass_control_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Bypass_Control(cvd_bypass_control_t);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Bypass_Control(cvd_bypass_control_t);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Bypass_Control(cvd_bypass_control_t);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Bypass_Control(cvd_bypass_control_t);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Bypass_Control(cvd_bypass_control_t);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Bypass_Control(cvd_bypass_control_t);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Get_Vline_625_Reg(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Vline_625_Reg();

	return ret;
}

int CVD_Set_Hstate_Max(UINT32	hstate_max_value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Hstate_Max(hstate_max_value);

	return ret;
}

int CVD_Get_Crunky_Status(LX_AFE_CVD_CK_T *pCK_Detection_t)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Crunky_Status(pCK_Detection_t);

	return ret;
}

int CVD_Set_Scart_FB_En(int fb_en_ctrl)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Scart_FB_En(fb_en_ctrl);

	return ret;
}

int CVD_OnOff_VDAC(BOOLEAN bonoff)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_OnOff_VDAC(bonoff);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_OnOff_VDAC(bonoff);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_OnOff_VDAC(bonoff);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_OnOff_VDAC(bonoff);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_OnOff_VDAC(bonoff);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_OnOff_VDAC(bonoff);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

#if 0
int CVD_Task_3cdetect(void)
{
	int ret = RET_OK;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Task_3cdetect();
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Task_3cdetect();
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Task_3cdetect();
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Task_3cdetect();
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Task_3cdetect();
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Task_3cdetect();
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}
#endif

/* Test Code for H13B0 */
#if 0
int CVD_Channel_Change_Control(BOOLEAN bATV_Channel_Change)
{
	int ret = RET_OK;

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}
#endif

int CVD_VDAC_mute_control(int enable)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	return ret;
}

#if 0
int CVD_Init_Global_Params(void)
{
	int ret = RET_OK;

	return ret;
}

int CVD_Set_Color_System_3CS(CVD_STATE_T cvd_next_state)
{
	int ret = RET_OK;

#ifdef USE_AFE_KDRV_FOR_O18
	if (lx_chip_rev() >= LX_CHIP_REV(O18, A0))
	{
		CVD_O18Ax_Set_Color_System_3CS(cvd_next_state);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}
#endif

static int CVD_Get_Reg_States_Detail(LX_AFE_CVD_STATES_DETAIL_T	*pcvd_states_detail_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_ColorBar_Detector(&pcvd_states_detail_t->colorbar_diff, &pcvd_states_detail_t->colorbar_75_100);

	CVD_Hal_Get_Reg_States_Detail(pcvd_states_detail_t);

	return ret;
}

int CVD_Set_Internal_Demod_Mode(BOOLEAN bInternal_Demod)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		CVD_O26Ax_Set_Internal_Demod_Mode(bInternal_Demod);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		CVD_O24Ax_Set_Internal_Demod_Mode(bInternal_Demod);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		CVD_M23Ax_Set_Internal_Demod_Mode(bInternal_Demod);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		CVD_O22Ax_Set_Internal_Demod_Mode(bInternal_Demod);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		CVD_E60Ax_Set_Internal_Demod_Mode(bInternal_Demod);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		CVD_O20Ax_Set_Internal_Demod_Mode(bInternal_Demod);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_Blue_Mode(int blue)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Blue_Mode(blue);

	return ret;
}

int CVD_OnOff_DMD_DAC(BOOLEAN bonoff)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26

	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24

	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23

	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22

	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60

	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20

	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_Blend_Ratio(int value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Blend_Ratio(value);

	return ret;
}

int CVD_Set_Vsync_Enhance(int system)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Vsync_Enhance(system);

	return ret;
}

int CVD_Set_Hsync_Enhance(int enable)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_Hsync_Enhance(enable);

	return ret;
}

static int Cvd_Interrupt_Register(void)
{
	int ret = 0;

	if(!IS_CVD_INTERRUPT_REGISTERED){

		if(0)	{ /* do nothing */ }
#ifdef USE_AFE_KDRV_FOR_O26
		else if(lx_chip_rev() >= LX_CHIP_REV( O26,A0))
		{
			AFE_PRINT("CVD Interrupt registering to O26 Ax\n");
			ret = request_irq(O26_IRQ_INTR_CVI_VBI_CPU, (irq_handler_t)CVD_IRQ_Handler, 0, "CVD", NULL);
		}
#endif

#ifdef USE_AFE_KDRV_FOR_O24
		else if(lx_chip_rev() >= LX_CHIP_REV( O24,A0))
		{
			AFE_PRINT("CVD Interrupt registering to O24 Ax\n");
			ret = request_irq(O24_IRQ_INTR_CVI_VBI_CPU, (irq_handler_t)CVD_IRQ_Handler, 0, "CVD", NULL);
		}
#endif

#ifdef USE_AFE_KDRV_FOR_M23
		else if(lx_chip_rev() >= LX_CHIP_REV( M23,A0))
		{
			AFE_PRINT("CVD Interrupt registering to M23 Ax\n");
			ret = request_irq(M23_IRQ_INTR_CVI_VBI_CPU, (irq_handler_t)CVD_IRQ_Handler, 0, "CVD", NULL);
		}
#endif

#ifdef USE_AFE_KDRV_FOR_O22
		else if(lx_chip_rev() >= LX_CHIP_REV( O22,A0))
		{
			AFE_PRINT("CVD Interrupt registering to O22 Ax\n");
			ret = request_irq(O22_IRQ_INTR_CVI_CPU_VBI, (irq_handler_t)CVD_IRQ_Handler, 0, "CVD", NULL);
		}
#endif

#ifdef USE_AFE_KDRV_FOR_E60
		else if(lx_chip_rev() >= LX_CHIP_REV( E60,A0))
		{
			AFE_PRINT("CVD Interrupt registering to E60 Ax\n");
			ret = request_irq(E60_IRQ_INTR_VBI, (irq_handler_t)CVD_IRQ_Handler, 0, "CVD", NULL);
		}
#endif

#ifdef USE_AFE_KDRV_FOR_O20
		else if(lx_chip_rev() >= LX_CHIP_REV( O20,A0))
		{
			AFE_PRINT("CVD Interrupt registering to O20 Ax\n");
			ret = request_irq(O20_IRQ_INTR_CVD, (irq_handler_t)CVD_IRQ_Handler, 0, "CVD", NULL);
		}
#endif

		else
		{
			ret = -1;
		}

		if(ret)
			AFE_ERROR("ERROR! CVD Interrupt(request_irq) has failed! CVD will not work properly!\n");
		else
			AFE_PRINT("CVD Interrupt register succeed!\n");

		IS_CVD_INTERRUPT_REGISTERED = true;
	}

	return ret;
}

/* CVD_Init 	: Initialize CVD registers to default value
					: Enables Kenel_threads(CVD main & CHB)
					: Enable CVD Interrupt 						*/
int CVD_Init(LX_AFE_CVD_SELECT_T select_main_sub)
{
	int ret;

	ret	= 0;

	if(gCVDInitStatus == TRUE)
	{
		AFE_PRINT("%s already initialized ... \n",__func__);
		return 0;
	}

#ifdef	KDRV_CONFIG_PM
//	gAfePmData = (S_AFE_PM_DATA *)kmalloc(sizeof(S_AFE_PM_DATA) , GFP_KERNEL);
//	gAfePmData->CVDInitStatus = FALSE;
//	gAfePmData->SelectMainSub = select_main_sub;
#endif

	if(select_main_sub != LX_CVD_MAIN)
		return -1;

//	AFE_PRINT("gRegCfg [0x%x]\n", pVportRegCfg->vport_reg_base_addr);

	/*-----------------------------------------------------------------------------------
	 * [H15/H14/H13/M14] CVD Register Base Address configuration
	 *----------------------------------------------------------------------------------*/

	gpRealRegCVD = (volatile DE_CVD_REG_T __iomem *)ioremap(pVportRegCfg->vport_reg_base_addr , pVportRegCfg->vport_reg_size);
	if(gpRealRegCVD == NULL)
	{
		printk("ERROR : can't allocate for register\n");
		return -1;
	}
	gpRegCVD = (volatile DE_CVD_REG_T __iomem *)kmalloc(sizeof(DE_CVD_REG_T), GFP_ATOMIC);
	if(gpRegCVD == NULL)
	{
		printk("ERROR : can't allocate for shadow register\n");
		return -1;
	}
	//spin_lock_init(&cvd_lock);
	/*
	   CVD_DEBUG("Real [0x%x], Reg [0x%x]\n", gpRealRegCVD_H13Ax, gpRegCVD_H13Ax);
	   {
	   UINT32 readAddr;
	   UINT32  j;
	   for(j =0x0;j<0x200;j+=4)
	   {
	   readAddr = (UINT32)gpRealRegCVD_H13Ax + j;
	   CVD_DEBUG("Offset[0x%x], Real [0x%x]=value[0x%x]\n", j,  readAddr, REG_RD(readAddr) );
	   }
	   }
	 */
	CVD_Reg_RdFL(top_001);
	AFE_PRINT("%s : CVD Version : 0x%x\n",__func__, CVD_Reg_Rd(top_001));

	CVD_Init_Buffer();

	CVD_Init_Global_Params();

	CVD_Init_ColorSystem_Params();

	gCVDInitStatus = TRUE;

	/* M14 Latchup debug */
	CVD_Channel_Power_Control(0);

	// no use for O22 : done by boot code
	CVD_Power_Down(LX_CVD_MAIN, FALSE);

	CVD_Reg_Init(LX_CVD_MAIN);

	//Init Register to NTSC Mode
	CVD_Set_Initial_Color_System();

#ifdef CVD_CH42_SKIP_WORKAROUND
	CVD_Clamp_Current_Control(0x3);
#endif

//	CVD_SW_Reset(LX_CVD_MAIN);

#ifdef ENABLE_CVD_THREAD

#if CVD_THREAD_VSYNC_CONTROL
	stCVD_Thread = kthread_create( MainCVD_Thread_Vsync_Ctrl, (void*)NULL, "cvd_thread");
#else
	stCVD_Thread = kthread_create( MainCVD_Thread, (void*)NULL, "cvd_thread");
#endif

	if(stCVD_Thread)
	{
		wake_up_process(stCVD_Thread);
		//gCVD_thread_running = 1;
		AFE_PRINT("CVD Thread [%d]\n", stCVD_Thread->pid);
	}
	else
	{
		AFE_ERROR("CVD Thread Already Created\n");
	}

#endif

	Cvd_Interrupt_Register();

	CVD_SetVsyncInterrupt(1);	//Enable CVD Vsync Interrupt

	// No sub CVD
//	CVD_Power_Down(LX_CVD_SUB, FALSE);

    if (lx_chip() >= LX_CHIP_M23)
    {
#ifdef INCLUDE_KDRV_PQE_PM
        g_pqe_pm_id = pqe_pm_register(&g_pqe_pm_cfg);

        if (g_pqe_pm_id < 0)
        {
            AFE_ERROR("pqe_pm register error\n");
            return -1;
        }

#endif
    }
    else
    {
        // add something if necessary
    }

	return 0;
}

void CVD_UnInit(void)
{
	if(gCVDInitStatus)
	{
		if(IS_CVD_INTERRUPT_REGISTERED){
			if(0)
			{
				/* do nothing */
			}
#ifdef USE_AFE_KDRV_FOR_O26
			else if(lx_chip_rev() >= LX_CHIP_REV( O26,A0))
			{
				free_irq(O26_IRQ_INTR_CVI_VBI_CPU, NULL);
			}
#endif

#ifdef USE_AFE_KDRV_FOR_O24
			else if(lx_chip_rev() >= LX_CHIP_REV( O24,A0))
			{
				free_irq(O24_IRQ_INTR_CVI_VBI_CPU, NULL);
			}
#endif

#ifdef USE_AFE_KDRV_FOR_M23
			else if(lx_chip_rev() >= LX_CHIP_REV( M23,A0))
			{
				free_irq(M23_IRQ_INTR_CVI_VBI_CPU, NULL);
			}
#endif

#ifdef USE_AFE_KDRV_FOR_O22
			else if(lx_chip_rev() >= LX_CHIP_REV( O22,A0))
			{
				free_irq(O22_IRQ_INTR_CVI_CPU_VBI, NULL);
			}
#endif

#ifdef USE_AFE_KDRV_FOR_E60
			else if(lx_chip_rev() >= LX_CHIP_REV( E60,A0))
			{
				free_irq(E60_IRQ_INTR_VBI, NULL);
			}
#endif

#ifdef USE_AFE_KDRV_FOR_O20
			else if(lx_chip_rev() >= LX_CHIP_REV( O20,A0))
			{
				free_irq(O20_IRQ_INTR_CVD, NULL);
			}
#endif
			else
			{
				/* unknown chip */
			}

			IS_CVD_INTERRUPT_REGISTERED = false;
		}
		gCVDInitStatus = FALSE;

		//CMA free, pdb down
		CVD_Channel_Power_Control(0);

#ifdef	KDRV_CONFIG_PM
//		kfree(gAfePmData);
#endif
	}

}


int CVD_Set_NTSC_Only(LX_AFE_VIDEO_SYSTEM_INFO_T system_info)
{

	if(system_info.cvd_video_system == LX_COLOR_SYSTEM_NTSC_M)
	{
		AFE_PRINT("############ Setting NTSC ONLY MODE ##################\n");
		g_CVD_Status_3CS.cvd_ntsc_only_mode = TRUE;
	}
	else
		g_CVD_Status_3CS.cvd_ntsc_only_mode = FALSE;

	return 0;
}

#if 0
static int MainCVD_Thread(void *data)	// not used
{
	while(1)
	{
		CVD_THREAD_DEBUG("gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);
		if(gForce_thread_sleep > 0)
		{
			CVD_THREAD_DEBUG("User force sleep CVD Thread\n");
			//gForce_thread_sleep = 0;
			gCVD_thread_running = 0;
			CVD_THREAD_DEBUG("CVD Sleep : gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);

			wait_event_interruptible(WaitQueue_CVD , gCVD_thread_running != 0);
			//interruptible_sleep_on(&WaitQueue_CVD);

			// added : in case CVD power off/on h/v unlock sometimes do not occur.
			g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoReadyToDetect;
			//	g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
			//	g_CVD_Status_3CS.cvd_prev_color_system  = CVD_STATE_VideoNotReady;

//			gCVD_thread_running = 1;
			CVD_THREAD_DEBUG("CVD Wakeup : gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);
			//gWait_return = wait_event_interruptible(WaitQueue_CVD, gForce_thread_sleep>0);
		}

		CVD_Task_3cdetect();

		OS_MsecSleep(L9_CVD_TIMEOUT);
	}

	return 0;
}
#endif

int CVD_Start_Timer(unsigned long arg)
{
#ifdef ENABLE_CVD_THREAD

#if CVD_THREAD_VSYNC_CONTROL
	if(gForce_thread_sleep)
	{
		// added : in case CVD power off/on h/v unlock sometimes do not occur.
		g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoReadyToDetect;

		gForce_thread_sleep = 0;
		CVD_DEBUG("Starting CVD Thread\n");
	}
	else
		CVD_DEBUG("CVD Thread already running !!! : gForce_thread_sleep[%d], gCVD_thread_running[%d] \n", gForce_thread_sleep, gCVD_thread_running);
#else // not used
	if(gForce_thread_sleep)
	{
		CVD_DEBUG("CVD Thread forced sleep, but re-starting thread !!!\n");
	}

	gForce_thread_sleep = 0;
	gCVD_thread_running = 1;
	wake_up_interruptible(&WaitQueue_CVD);
	CVD_DEBUG("Starting CVD Thread\n");
#endif

#endif
	return 0;
}

int CVD_Stop_Timer(unsigned long arg)
{
#ifdef ENABLE_CVD_THREAD
		CVD_DEBUG("Stopping CVD Thread\n");
		gForce_thread_sleep = 1;

	return 0;
#endif
}

static int MainCVD_Thread_Vsync_Ctrl(void *data)
{
#ifdef ENABLE_CVD_THREAD
	while(1)
	{
		gCVD_thread_running = 0;
		//interruptible_sleep_on(&WaitQueue_CVD);
		wait_event_interruptible(WaitQueue_CVD , gCVD_thread_running != 0 );
//		gCVD_thread_running = 1;

		CVD_Task_3cdetect();
	}
#endif
	return 0;
}

int CVD_Vsync_Interrupt(void)
{
#ifdef ENABLE_CVD_THREAD
	static int vsync_intr_count = 0;

	if(gForce_thread_sleep == 0)
		vsync_intr_count++;
	else
	{
		CVD_THREAD_DEBUG("CVD Thread Sleeping ~~\n");
		return 0;
	}

	if(vsync_intr_count > 2)	// 20msec *3 = 60msec, 16.7msec *3 = 50msec
	{
		if( gCVD_thread_running == 0 )
		{
			AFE_TRACE("Wake Up CVD Thread !!!\n");
			vsync_intr_count = 0;
			gCVD_thread_running = 1;
			wake_up_interruptible(&WaitQueue_CVD);
		}
		else
			CVD_THREAD_DEBUG("Previous CVD Thread not finished !!!\n");
	}
#endif
	return 0;
}

static int CVD_Unlock_Interrupt(UINT32 interrupt_status)
{
	if(interrupt_status & NOSIGNAL_INTERRUPT_MASK)
		g_CVD_Status_3CS.no_signal_intr = 1;
	if(interrupt_status & HUNLOCK_INTERRUPT_MASK)
		g_CVD_Status_3CS.h_unlock_intr = 1;
	if(interrupt_status & VUNLOCK_INTERRUPT_MASK)
		g_CVD_Status_3CS.v_unlock_intr = 1;

	CVD_SetUnlockInterrupt(0);

	return 0;
}

static irqreturn_t CVD_IRQ_Handler(int irq, void *dev_id)
{
	UINT32 cvd_int_status = 0;
	UINT32 vbi_int_status = 0;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	/* Step 1 : Get interrupt status */
	CVD_Reg_RdFL(cvd_intr1_intr0);
	cvd_int_status = CVD_Reg_Rd(cvd_intr1_intr0);

	CVD_Reg_RdFL(cvd_intr1_intr1);
	vbi_int_status = CVD_Reg_Rd(cvd_intr1_intr1);

	AFE_TRACE("CVD ISR : intr0[0x%08x] intr1[0x%08x]\n", cvd_int_status, vbi_int_status);

	if((vbi_int_status & VBI_INTERRUPT_MASK) )
	{
		if(ENABLE_ANALOGCC){
			VBI_CC_InterruptFunc(vbi_int_status);
		}

		if(ENABLE_ANALOGTTX){
			VBI_TTX_InterruptFunc(vbi_int_status);
		}
	}

	if((cvd_int_status & VSYNC_INTERRUPT_MASK) )
	{
		CVD_Vsync_Interrupt();
	}

	if((cvd_int_status & UNLOCK_INTERRUPT_MASK) )
	{
		CVD_Unlock_Interrupt(cvd_int_status);
	}

	CVD_Reg_Wr(cvd_intr1_clear0, cvd_int_status);
	CVD_Reg_Wr(cvd_intr1_clear1, vbi_int_status);

	CVD_Reg_WrFL(cvd_intr1_clear0);
	CVD_Reg_WrFL(cvd_intr1_clear1);

	return IRQ_HANDLED;
}

static int CVD_SetInterruptClear(UINT32 interrupt_clear_mask)
{
	int ret = 0;
	UINT32 cvd_intr1_clear;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Reg_RdFL(cvd_intr1_clear0);
	cvd_intr1_clear = CVD_Reg_Rd(cvd_intr1_clear0);
	CVD_Reg_Wr(cvd_intr1_clear0, (cvd_intr1_clear |= interrupt_clear_mask ));
	CVD_Reg_WrFL(cvd_intr1_clear0);

	return ret;
}

int CVD_SetVsyncInterrupt(int on_off)
{
	int ret = 0;

	UINT32 cvd_intr1_en;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Reg_RdFL(cvd_intr1_enable0);
	cvd_intr1_en = CVD_Reg_Rd(cvd_intr1_enable0);
	if(on_off)
		CVD_Reg_Wr(cvd_intr1_enable0, (cvd_intr1_en |= VSYNC_INTERRUPT_MASK));
	else
		CVD_Reg_Wr(cvd_intr1_enable0, (cvd_intr1_en &= ~VSYNC_INTERRUPT_MASK));
	CVD_Reg_WrFL(cvd_intr1_enable0);

	if(on_off == 0)
		CVD_SetInterruptClear(VSYNC_INTERRUPT_MASK);

	return ret;
}

int CVD_SetUnlockInterrupt(int on_off)
{
	int ret = 0;

	UINT32 cvd_intr1_en;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Reg_RdFL(cvd_intr1_enable0);
	cvd_intr1_en = CVD_Reg_Rd(cvd_intr1_enable0);
	if(on_off)
		CVD_Reg_Wr(cvd_intr1_enable0, (cvd_intr1_en |= UNLOCK_INTERRUPT_MASK));
	else
		CVD_Reg_Wr(cvd_intr1_enable0, (cvd_intr1_en &= ~UNLOCK_INTERRUPT_MASK));
	CVD_Reg_WrFL(cvd_intr1_enable0);

	if(on_off == 0)
		CVD_SetInterruptClear(UNLOCK_INTERRUPT_MASK);

	return ret;
}

int CVD_Program_Color_System(LX_AFE_CVD_PROGRAM_COLOR_SYSTEM_T program_color_system_t)
{

	if(program_color_system_t.color_system >= LX_NON_STANDARD ) return -1;

	CVD_Set_Color_System_3CS((CVD_STATE_T)program_color_system_t.color_system);

	CVD_DEBUG("CVD Main : Program Color System to [%d]\n", program_color_system_t.color_system);

	return 0;
}

#ifdef	KDRV_CONFIG_PM
int CVD_RunSuspend(void)
{
	LX_AFE_CVD_SET_INPUT_T	cvd_input_info = { LX_CVD_MAX_NUM, LX_CVD_INPUT_SOURCE_NUM, LX_AFE_CVBS_NONE, LX_AFE_CVBS_NONE, LX_CVD_INPUT_SOURCE_ATTRIBUTE_NUM} ;
	/*
	if (!gAfePmData->CVDInitStatus)
		return 0;
		*/
	AFE_PRINT("%s : attr[%d],port[%d]\n", __func__ , _g_kwrap_cvd_source_attribute, _g_kwrap_cvd_input_port);

	if(gCVDInitStatus == FALSE)
	{
		AFE_PRINT("CVD Suspending before Initial setting\n");
		return 0;
	}
	AFE_PRINT(" CVD Suspending ... : port setting to initial \n");
	CVD_Set_Source_Type_Control(cvd_input_info);

	CVD_SetVsyncInterrupt(0);	//Disable CVD Vsync Interrupt
	CVD_SetUnlockInterrupt(0);

//	CVD_Channel_Power_Control(0);	// 160718 : to reduce resume time

	return 0;
}

int CVD_RunResume(void)
{
	int ret = 0;
	/*
	if (!gAfePmData->CVDInitStatus)
		return 0;
		*/
	if(gCVDInitStatus == FALSE)
	{
		AFE_PRINT("CVD resuming before Initial setting\n");
		return 0;
	}

	CVD_Init_Global_Params();

	//Initialize CVD semaphore
	//OS_InitMutex(&g_CVD_Sema, OS_SEM_ATTR_DEFAULT);

	/* M14 Latchup debug */
	CVD_Channel_Power_Control(0);

	CVD_Power_Down(LX_CVD_MAIN, FALSE);

	CVD_Reg_Init(LX_CVD_MAIN);

	//Init Register to NTSC Mode
	CVD_Set_Initial_Color_System();

#ifdef CVD_CH42_SKIP_WORKAROUND
	CVD_Clamp_Current_Control(0x3);
#endif

	CVD_SetVsyncInterrupt(1);	//Enable CVD Vsync Interrupt

	CVD_Power_Down(LX_CVD_SUB, FALSE);

	AFE_PRINT("start kwrap cvd resuming attr[%d],port[%d]\n", _g_kwrap_cvd_source_attribute, _g_kwrap_cvd_input_port);

	if( (_g_kwrap_cvd_source_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_NUM) || (_g_kwrap_cvd_input_port == LX_AFE_CVBS_NONE))
	{
        return 0;
	}

	ret = afe_kwrap_cvd_connectmodule(_g_kwrap_cvd_source_attribute, _g_kwrap_cvd_input_port);

	return ret;
}

#endif


int CVD_Set_SW_3DCOMB_Control(unsigned long arg)
{
	return 0;
}

int CVD_Set_Source_Type_Control(LX_AFE_CVD_SET_INPUT_T	cvd_input_info)
{

	static LX_AFE_CVD_SET_INPUT_T	prev_cvd_input_info = { LX_CVD_MAX_NUM, LX_CVD_INPUT_SOURCE_NUM, LX_AFE_CVBS_NONE, LX_AFE_CVBS_NONE, LX_CVD_INPUT_SOURCE_ATTRIBUTE_NUM} ;

	//AFE_PRINT("Entered CVD_Set_Source_Type_Control\n");

	if( (cvd_input_info.cvd_main_sub == prev_cvd_input_info.cvd_main_sub) && (cvd_input_info.cvd_input_source_type == prev_cvd_input_info.cvd_input_source_type) && (cvd_input_info.cvbs_input_port == prev_cvd_input_info.cvbs_input_port) && (cvd_input_info.cvd_input_source_attribute == prev_cvd_input_info.cvd_input_source_attribute))  // Same Input Setting.
	{
		AFE_PRINT("CVD Set Source Type to Same Port !!!!????\n");
		return 0;
	}
	else
		memcpy (&prev_cvd_input_info, &cvd_input_info, sizeof(LX_AFE_CVD_SET_INPUT_T)) ;	// Save Current Port Settings.

	CVD_Set_Source_Type(cvd_input_info);

	//		AFE_PRINT("Main CVD input\n");
	if(cvd_input_info.cvd_input_source_attribute == LX_CVD_INPUT_SOURCE_ATTRIBUTE_RF)
	{
		CVD_DEBUG("CVD : RF Input Mode\n");
		g_CVD_Status_3CS.in_rf_mode = TRUE;
	}
	else
	{
		CVD_DEBUG("CVD : AV Input Mode\n");
		g_CVD_Status_3CS.in_rf_mode = FALSE;
	}

//	g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoNotReady;
//	g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
//	g_CVD_Status_3CS.cvd_prev_color_system  = CVD_STATE_VideoNotReady;		//121228 Added
	g_CVD_Status_3CS.port_change_detected = TRUE;

	return 0;

}

int CVD_Get_States_Detail(LX_AFE_CVD_STATES_DETAIL_T	*pcvd_states_detail_t)
{
	//UINT32 status_reg;

	CVD_Get_Reg_States_Detail(pcvd_states_detail_t);

	pcvd_states_detail_t->MainCVD_State = g_CVD_Status_3CS.cvd_color_system;
	pcvd_states_detail_t->Current_State = g_CVD_Status_3CS.cvd_color_system;
	pcvd_states_detail_t->Next_State = g_CVD_Status_3CS.cvd_next_state;


	pcvd_states_detail_t->CVD_Color_System = g_CVD_Status_3CS.cvd_color_system;
	pcvd_states_detail_t->CS0_Color_System = g_CVD_Status_3CS.cs0_color_system;
	pcvd_states_detail_t->CS1_Color_System = g_CVD_Status_3CS.cs1_color_system;
	pcvd_states_detail_t->color_system_support = g_CVD_Status_3CS.color_system_support;

	pcvd_states_detail_t->motion_diff = g_CVD_Pattern_Detection_t.global_motion_diff;
	pcvd_states_detail_t->pattern_found = g_CVD_Pattern_Detection_t.pattern_found;
	pcvd_states_detail_t->static_pattern_found = g_CVD_Pattern_Detection_t.static_pattern_found;
	pcvd_states_detail_t->tunning_mode	= g_CVD_Status_3CS.in_atv_tunning;
	pcvd_states_detail_t->lock_stable_count	= g_CVD_Status_3CS.cvd_lock_stable_count;
	pcvd_states_detail_t->no_signal_count	= g_CVD_Status_3CS.cvd_no_signal_count;
	pcvd_states_detail_t->black_level	= g_CVD_Status_3CS.cvd_black_level;

	return 0;
}


int CVD_Test_Program(LX_AFE_CVD_TEST_PARAM_T *stCVD_Test_Param)
{
	int ret = 0;

	switch(stCVD_Test_Param->item_to_test)
	{
		case CVD_TEST_ENABLE_3DCOMB_STATE_PRINT:
			break;
		case CVD_TEST_HSTATEMAX_WRITE:
			CVD_Set_Hstate_Max(stCVD_Test_Param->hstate_max_value);
			break;
		case CVD_TEST_AGC_PEAK_NOMINAL:
			/*
			g_CVD_AGC_Peak_Control.bEnable = 			stCVD_Test_Param->agc_peak_enable;
			g_CVD_AGC_Peak_Control.white_ratio_th = 	stCVD_Test_Param->agc_pean_white_ratio_th;
			g_CVD_AGC_Peak_Control.white_frame_max_th = stCVD_Test_Param->agc_pean_white_frame_max_th;
			g_CVD_AGC_Peak_Control.white_frame_on = 	stCVD_Test_Param->agc_pean_white_frame_on;
			g_CVD_AGC_Peak_Control.white_frame_off = 	stCVD_Test_Param->agc_pean_white_frame_off;
			g_CVD_AGC_Peak_Control.print_en = 			stCVD_Test_Param->agc_pean_print_en;
			g_CVD_AGC_Peak_Nominal_Control.bEnable 				= stCVD_Test_Param->agc_peak_enable ;
			g_CVD_AGC_Peak_Nominal_Control.tnr_x_avg_t_th 		= stCVD_Test_Param->agc_peak_x_avg_t_th;
			g_CVD_AGC_Peak_Nominal_Control.tnr_x_avg_s_th 		= stCVD_Test_Param->agc_peak_x_avg_s_th;
			g_CVD_AGC_Peak_Nominal_Control.tpd_s_status_th 		= stCVD_Test_Param->agc_peak_s_staus_th;
			g_CVD_AGC_Peak_Nominal_Control.pattern_frame_max_th = stCVD_Test_Param->agc_peak_white_frame_max_th ;
			g_CVD_AGC_Peak_Nominal_Control.pattern_frame_on 	= stCVD_Test_Param->agc_peak_white_frame_on ;
			g_CVD_AGC_Peak_Nominal_Control.pattern_frame_off 	= stCVD_Test_Param->agc_peak_white_frame_off ;
			g_CVD_AGC_Peak_Nominal_Control.noise_th			 	= stCVD_Test_Param->agc_peak_noise_th ;
			g_CVD_AGC_Peak_Nominal_Control.print_en 			= stCVD_Test_Param->agc_peak_print_en ;
			*/
			break;
		case CVD_TEST_STABLE_SYNC_MODE:
				CVD_Hal_Enable_Stable_Sync_Mode(stCVD_Test_Param->stable_sync_value);		//for RF nosignal (dcrestore_lpf_en ON)
			break;
		case CVD_TEST_COMB2D_ONLY:
			break;
		case CVD_TEST_ADEMOD_TYPE:
			{
				BOOLEAN bInternal_Demod;

				if ( stCVD_Test_Param->internal_demod_type )
					bInternal_Demod = TRUE;
				else
					bInternal_Demod = FALSE;

				CVD_Set_Internal_Demod_Mode(bInternal_Demod);
			}
			break;
		case CVD_TEST_BLUE_MODE:
			{
				CVD_Set_Blue_Mode(stCVD_Test_Param->blue_mode_enable);
			}
			break;
		case CVD_TEST_DMD_OUT:
			{
				CVD_OnOff_DMD_DAC(stCVD_Test_Param->dmd_out_enable);
			}
			break;
		case CVD_TEST_SCART_RGB:
			{
				CVD_Set_Scart_FB_En(stCVD_Test_Param->fb_en);
				CVD_Set_Blend_Ratio(stCVD_Test_Param->blend_ratio);
			}
			break;
		case CVD_TEST_HSYNC_ENHANCE:
			{
				CVD_Set_Hsync_Enhance(stCVD_Test_Param->hsync_enhance_value);
			}
			break;
		case CVD_TEST_VSYNC_ENHANCE:
			{
				CVD_Set_Vsync_Enhance(stCVD_Test_Param->vsync_enhance_value);
			}
			break;
		case CVD_TEST_YCSEP:
			{
				CVD_Set_ycsep_Blend(stCVD_Test_Param->ycsep_blend_value);
			}
			break;
		case CVD_TEST_CLAMP_UPDN:
			{
				CVD_Set_clampagc_updn(stCVD_Test_Param->clamp_updn_value);
			}
			break;
		case CVD_TEST_DC_CLAMP_MODE:
			{
				CVD_Set_dc_clamp_mode(stCVD_Test_Param->dc_clamp_mode_value);
			}
			break;
		case CVD_TEST_ABB_CLAMP_PARAM:
			{
				if ( ( ( lx_chip_rev() < LX_CHIP_REV( H14, A0 ) ) && ( lx_chip_rev() >= LX_CHIP_REV( M14, B0 )) )  \
						|| (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M16)) || (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17)))
				{
					AFE_PRINT("ABB Clamp Parameter Setting : clamp_count[0x%x], clamp_step_size[0x%x]\n", \
							stCVD_Test_Param->abb_clamp_count, stCVD_Test_Param->abb_clamp_step );
#ifdef INCLUDE_KDRV_DEMOD
					ret = DEMOD_ANALOG_Set_ClampingCtrl((UINT8)stCVD_Test_Param->abb_clamp_count, (UINT16)stCVD_Test_Param->abb_clamp_step);
#endif
				}
			}
			break;
		case CVD_TEST_WORKAROUND_CONTROL:
			{
				if(stCVD_Test_Param->workaround_number == 1)
				{
					if(stCVD_Test_Param->workaround_on_off == 1)
						g_CVD_WA_Low_Burst_ATV_Noise = 1;
					else
						g_CVD_WA_Low_Burst_ATV_Noise = 0;

					AFE_PRINT("g_CVD_WA_Low_Burst_ATV_Noise : [%d]\n", g_CVD_WA_Low_Burst_ATV_Noise);
				}
				else if(stCVD_Test_Param->workaround_number == 2)
				{
					if(stCVD_Test_Param->workaround_on_off == 1)
						g_CVD_Soft_Reset_WA_for_HLock_Error = 1;
					else
						g_CVD_Soft_Reset_WA_for_HLock_Error = 0;

					AFE_PRINT("g_CVD_Soft_Reset_WA_for_HLock_Error : [%d]\n", g_CVD_Soft_Reset_WA_for_HLock_Error);
				}
				else if(stCVD_Test_Param->workaround_number == 3)
				{
					if(stCVD_Test_Param->workaround_on_off == 1)
						g_CVD_Adaptive_Burst_WA_for_SECAM = 1;
					else
						g_CVD_Adaptive_Burst_WA_for_SECAM = 0;

					AFE_PRINT("g_CVD_Adaptive_Burst_WA_for_SECAM : [%d]\n", g_CVD_Adaptive_Burst_WA_for_SECAM);
				}
				else if(stCVD_Test_Param->workaround_number == 4)
				{
					if(stCVD_Test_Param->workaround_on_off == 1)
						g_CVD_No_Burst_SECAM_WA = 1;
					else
						g_CVD_No_Burst_SECAM_WA = 0;

					AFE_PRINT("g_CVD_No_Burst_SECAM_WA : [%d]\n", g_CVD_No_Burst_SECAM_WA);
				}
				else if(stCVD_Test_Param->workaround_number == 5)
				{
					if(stCVD_Test_Param->workaround_on_off == 1)
						g_CVD_Low_Burst_PAL_WA = 1;
					else
						g_CVD_Low_Burst_PAL_WA = 0;

					AFE_PRINT("g_CVD_Low_Burst_PAL_WA : [%d]\n", g_CVD_Low_Burst_PAL_WA);
				}
			}
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}

void CVD_Get_Timing_Info(LX_AFE_CVD_TIMING_INFO_T	*ptiming_info)
{
	CVD_STATE_T	cvd_state;

	cvd_state = g_CVD_Status_3CS.cvd_color_system;

	switch(cvd_state)
	{
		case CVD_STATE_NTSC:
			ptiming_info->cvd_standard = LX_NTSC_M;
			ptiming_info->u16_VFreq = 599;
			break;
		case CVD_STATE_NTSC443:
			ptiming_info->cvd_standard = LX_NTSC_443;
			ptiming_info->u16_VFreq = 599;
			break;
		case CVD_STATE_PALi:
			ptiming_info->cvd_standard = LX_PAL_BG;
			ptiming_info->u16_VFreq = 500;
			break;
		case CVD_STATE_PALm:
			ptiming_info->cvd_standard = LX_PAL_M;
			ptiming_info->u16_VFreq = 599;
			break;
		case CVD_STATE_PALCn:
			ptiming_info->cvd_standard = LX_PAL_CN;
			ptiming_info->u16_VFreq = 500;
			break;
		case CVD_STATE_PAL60:
			ptiming_info->cvd_standard = LX_PAL_60;
			ptiming_info->u16_VFreq = 599;
			break;
		case CVD_STATE_SECAM:
			ptiming_info->cvd_standard = LX_SECAM;
			ptiming_info->u16_VFreq = 500;
			break;
		default:
			ptiming_info->cvd_standard = LX_NON_STANDARD;//gogosing
			if (CVD_Get_Vline_625_Reg())	// 625 line : 50Hz System
				ptiming_info->u16_VFreq = 500;
			else
				ptiming_info->u16_VFreq = 599;
			break;
	}

	if( g_CVD_Status_3CS.vline_625_stable )		// stable 50Hz
		ptiming_info->u16_VFreq_Stable = 500;
	else
		ptiming_info->u16_VFreq_Stable = 599;

	ptiming_info->cvd_lock_stable_count = g_CVD_Status_3CS.cvd_lock_stable_count;
	ptiming_info->cvd_no_signal_count = g_CVD_Status_3CS.cvd_no_signal_count;
	/*
	//Instead of reading input VFreq., read forced VFreq. of CVD to determine CVD's running VFreq.
	//if (CVD_Get_Vline_625_Flag())	// 625 line : 50Hz System
	if (CVD_Get_Vline_625_Reg())	// 625 line : 50Hz System
			ptiming_info->u16_VFreq = 500;
	else
			ptiming_info->u16_VFreq = 599;
			*/

	return;
}

int CVD_Get_States(LX_AFE_CVD_STATES_INFO_T	*pcvd_states_info)
{
	//UINT32 status_reg;

#ifdef USE_REGISTER_VALUE_FOR_SYNC_STATES
	/* Returns Current Sync Register values(NOT the status of CVD thread) */

	pcvd_states_info->cvd_status =0;

	if(CVD_Get_No_Signal_Flag())
	{
		//110414 No_Signal_Flag is not working well
		pcvd_states_info->cvd_status |= LX_NO_SIGNAL;
		//		CVD_ClampAGC_OnOff(0); // agc off on No signal for ch42 no signal workaround
	}
	if(CVD_Get_HLock_Flag())
		pcvd_states_info->cvd_status |= LX_HLOCK;
	if(CVD_Get_VLock_Flag())
		pcvd_states_info->cvd_status |= LX_VLOCK;
	if(g_CVD_Status_3CS.cvd_chromalock_flag)
		pcvd_states_info->cvd_status |= LX_CHROMALOCK;
	if(g_CVD_Status_3CS.cvd_pal_flag)
		pcvd_states_info->cvd_status |= LX_PAL_DETECTED;
	if(g_CVD_Status_3CS.cvd_secam_flag)
		pcvd_states_info->cvd_status |= LX_SECAM_DETECTED;
	if(CVD_Get_Vline_625_Flag())
		pcvd_states_info->cvd_status |= LX_625LINES_DETECTED;
	if(g_CVD_Status_3CS.cs0_secam_flag)
		pcvd_states_info->cvd_status |= LX_CS0_SECAM_DETECTED;
	if(g_CVD_Status_3CS.cs0_pal_flag)
		pcvd_states_info->cvd_status |= LX_CS0_PAL_DETECTED;
	if(g_CVD_Status_3CS.cs0_chromalock_flag)
		pcvd_states_info->cvd_status |= LX_CS0_CHROMALOCK;
	if(CVD_Get_HNon_Standard_Flag())
		pcvd_states_info->cvd_status |= LX_HNON_STANDARD;
	if(CVD_Get_VNon_Standard_Flag())
		pcvd_states_info->cvd_status |= LX_VNON_STANDARD;
#else
	/* Returns Sync Status of CVD thread */
	if(g_CVD_Status_3CS.cvd_color_system < CVD_STATE_VideoNotReady)
		pcvd_states_info->cvd_status = LX_HLOCK|LX_VLOCK;
	else
		pcvd_states_info->cvd_status = LX_NO_SIGNAL;

#endif

	return 0;
}

int CVD_Set_Color_System(LX_AFE_VIDEO_SYSTEM_INFO_T system_info)
{
	if(system_info.cvd_video_system <= LX_COLOR_SYSTEM_MULTI)
	{
		g_CVD_Status_3CS.color_system_support = system_info.cvd_video_system;
		CVD_DEBUG("### Setting Color System to [0x%x] ###\n", g_CVD_Status_3CS.color_system_support);
	}
	else
	{
		CVD_DEBUG("### Invalid Color System [%d] ###\n", system_info.cvd_video_system);
		return -1;
	}

	return 0;
}

/**
 * @brief Initialize Color System Related Registers to NTSC System
 *
 * @return
 */
int CVD_Set_Initial_Color_System(void)
{

	g_CVD_Status_3CS.noisy_signal_detected = 0;
	g_CVD_Status_3CS.no_color_detected = 0;

	g_CVD_Status_3CS.cvd_color_system = CVD_STATE_VideoNotReady;
	g_CVD_Status_3CS.cvd_next_state = CVD_STATE_VideoNotReady;
	g_CVD_Status_3CS.cvd_prev_color_system = CVD_STATE_VideoNotReady;

	g_CVD_Status_3CS.in_atv_tunning = 0;

	if(g_CVD_Status_3CS.color_system_support == 0)	//for resume restore previous color system
		g_CVD_Status_3CS.color_system_support =  LX_COLOR_SYSTEM_MULTI;

	g_CVD_Status_3CS.in_rf_mode = FALSE;
	g_CVD_Status_3CS.prev_av_rf_mode = TRUE;
	g_CVD_Status_3CS.port_change_detected = FALSE;
	g_CVD_Status_3CS.cvd_ntsc_only_mode = FALSE;
	g_CVD_Status_3CS.cvd_lock_stable_count = 0;
	g_CVD_Status_3CS.cvd_no_signal_count = 0;

	g_CVD_Status_3CS.cvd_black_level = LX_AFE_CVD_BLACK_LEVEL_AUTO;
	g_CVD_Status_3CS.vline_625_stable = 1;
	//Init Register to NTSC Mode
	CVD_Program_Color_System_Main_Multi(&pSetColorSystem_3CS->Color_System_Params[CVD_STATE_NTSC]);
	CVD_Program_Color_System_CS(CVD_SEL_CS_CS0, &pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PAL60]);
	CVD_Program_Color_System_CS(CVD_SEL_CS_CS1, &pSetColorSystem_3CS->Color_System_Params[CVD_STATE_PALm]);

	//added 141003 ATV white noise after DC on
	CVD_Set_PQ_Mode(LX_CVD_PQ_NTSC_M_RF);

	AFE_PRINT("CVD Init Color System Ended : 18111400\n");

	return 0;

}

/**
 * @brief Set CVD Black Level
 *
 * @return
 */
int CVD_Set_Black_Level(LX_AFE_CVD_BLACK_LEVEL_T cvd_black_level)
{

	g_CVD_Status_3CS.cvd_black_level = cvd_black_level;

	return 0;

}

int CVD_Set_Use_Internal_Demod(BOOLEAN bInternal_Mode)
{
	CVD_DEBUG("%s entered :  %d \n",__func__, bInternal_Mode);


	if(bInternal_Mode)
	{
		g_CVD_Status_3CS.use_internal_demod = 1;
	}
	else
	{
		g_CVD_Status_3CS.use_internal_demod = 0;
	}

	return 0;
}

int CVD_Set_ycsep_Blend(int blend)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_ycsep_Blend(blend);

	return ret;
}

int CVD_Set_clampagc_updn(int updn_value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_clampagc_updn(updn_value);

	return ret;
}

int CVD_Set_dc_clamp_mode(int mode)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Set_dc_clamp_mode(mode);

	return ret;
}

int CVD_Get_HNon_Standard_Flag(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_HNon_Standard_Flag();

	return ret;
}

int CVD_Get_VNon_Standard_Flag(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_VNon_Standard_Flag();

	return ret;
}

int CVD_Black_Level_Control(LX_AFE_CVD_BLACK_LEVEL_T black_level, LX_AFE_CVD_SOURCE_ATTRIBUTE_T rf_av_mode)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		ret = CVD_O26Ax_Black_Level_Control(black_level, rf_av_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		ret = CVD_O24Ax_Black_Level_Control(black_level, rf_av_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		ret = CVD_M23Ax_Black_Level_Control(black_level, rf_av_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		ret = CVD_O22Ax_Black_Level_Control(black_level, rf_av_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		ret = CVD_E60Ax_Black_Level_Control(black_level, rf_av_mode);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		ret = CVD_O20Ax_Black_Level_Control(black_level, rf_av_mode);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Update_Status_Regs(CVD_STATUS_3CS_T	*pCVD_Status_3CS)
{
	int ret= RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Update_Status_Regs(pCVD_Status_3CS);

	return ret;
}

int CVD_Fast_Vline_625_Using_Vdetec_Vcount(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Fast_Vline_625_Using_Vdetec_Vcount();

	return ret;
}

int CVD_agc_half_en_control(int enable) //gogosing agc
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_agc_half_en_control(enable);

	return ret;
}

int CVD_Program_Color_System_Main_Multi(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Program_Color_System_Main_Multi(pSet_system_t);

	return ret;
}

int CVD_Program_Color_System_CS(CVD_SELECT_CDETECT_T cs_sel, CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Program_Color_System_CS(cs_sel, pSet_system_t);

	return ret;
}

int CVD_swrst_CS(CVD_SELECT_CDETECT_T cs_sel)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_swrst_CS(cs_sel);

	return ret;
}

int CVD_Reset_hdct(int enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Reset_hdct(enable);

	return ret;
}

int CVD_Force_Color_Kill(UINT8 color_kill_enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Force_Color_Kill(color_kill_enable);

	return ret;
}

int CVD_Set_Hstate_Fixed(UINT32	value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Hstate_Fixed(value);

	return ret;
}

int CVD_Set_CVD_CAGC(UINT8 state,CVD_SET_SYSTEM_3CS_T *pSet_system_t, CVD_STATE_T	color_system)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_CVD_CAGC(state, pSet_system_t, color_system);

	return ret;
}

int CVD_Enable_LPF_en(int enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Enable_LPF_en(enable);

	return ret;
}

int CVD_Set_for_Field_Detect_Mode(UINT32 mode)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_for_Field_Detect_Mode(mode);

	return ret;
}

int CVD_Burst_Gate_Control(UINT32	gate_start, UINT32 gate_end)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Burst_Gate_Control(gate_start, gate_end);

	return ret;
}

int CVD_OnOff_Chromalock_Ckill(BOOLEAN bonoff)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_OnOff_Chromalock_Ckill(bonoff);

	return ret;
}

int CVD_Set_for_Burst_Gate_End_On_Noisy(UINT8 original_value, UINT32 Enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_for_Burst_Gate_End_On_Noisy(original_value, Enable);

	return ret;
}

int CVD_Set_Cpump_Auto_Stip_Noisy_Value(int value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Cpump_Auto_Stip_Noisy_Value(value);

	return ret;
}

int CVD_AGC_Bypass(int Bypass_Enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_AGC_Bypass(Bypass_Enable);

	return ret;
}

int CVD_Reset_cdct(int enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Reset_cdct(enable);

	return ret;
}

int CVD_3DComb_Workaround(int step)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_3DComb_Workaround(step);

	return ret;
}

int CVD_Set_PE_Param_Flag(int signal_lock, int color_system, int rf_av_mode, int write_done)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_PE_Param_Flag(signal_lock, color_system, rf_av_mode, write_done);

	return ret;
}

int CVD_Hstart_Position_Compensator(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Hstart_Position_Compensator(pSet_system_t);

	return ret;
}

int CVD_Set_Nosignal_Vactive_Params(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Nosignal_Vactive_Params();

	return ret;
}

int	CVD_Read_VCR_Detected(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Read_VCR_Detected();

	return ret;
}

int CVD_Get_Global_Motion_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Global_Motion_Value();

	return ret;
}

int CVD_Get_Hstate_Max(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Hstate_Max();

	return ret;
}

UINT32 CVD_Differential_Status_Cdto_Inc_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Differential_Status_Cdto_Inc_Value();

	return ret;
}

UINT32 CVD_Read_Cordic_Freq_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Read_Cordic_Freq_Value();

	return ret;
}

int CVD_Init_Level_Detector(CVD_STATE_T color_system)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Init_Level_Detector(color_system);

	return ret;
}

int CVD_Program_Color_System_Size(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Program_Color_System_Size(pSet_system_t);

	return ret;
}

int CVD_Program_Color_System_Size_md(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Program_Color_System_Size_md(pSet_system_t);

	return ret;
}

int CVD_Get_comb2d_only(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_comb2d_only();

	return ret;
}

int CVD_Get_CVD_Burst_Mag_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_CVD_Burst_Mag_Value();

	return ret;
}

int CVD_Set_Motion_Expand(int enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Motion_Expand(enable);

	return ret;
}

int CVD_Set_CCR(int ccr_value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_CCR(ccr_value);

	return ret;
}

UINT8 CVD_Get_CVD_Burst_Mag_Flag(CVD_STATE_T	color_system)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_CVD_Burst_Mag_Flag(color_system);

	return ret;
}

int CVD_Get_CAGC_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_CAGC_Value();

	return ret;
}

int CVD_Set_CAGC_Value(UINT32 cagc_value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_CAGC_Value(cagc_value);

	return ret;
}

int CVD_Get_Hue_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Hue_Value();

	return ret;
}

int CVD_Set_Hue_Value(int value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Hue_Value(value);

	return ret;
}

int CVD_Set_SCART_CSC(int black_level)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_SCART_CSC(black_level);

	return ret;
}

int CVD_Get_SECAM_Flag_CS0(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_SECAM_Flag_CS0();

	return ret;
}

int CVD_Reset_vdct(int enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Reset_vdct(enable);

	return ret;
}

int CVD_Set_AGC_Peak_En(int enable)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_AGC_Peak_En(enable);

	return ret;
}

int CVD_Get_AGC_Peak_En_Value(void)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_AGC_Peak_En_Value();

	return ret;
}

int CVD_Program_Color_System_PreJob(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Program_Color_System_PreJob(pSet_system_t);

	return ret;
}

int CVD_Program_Color_System_PostJob(CVD_SET_SYSTEM_3CS_T *pSet_system_t)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	CVD_Hal_Program_Color_System_PostJob(pSet_system_t);

	return ret;
}

int CVD_Get_PE0_Motion_Value(int *p_tnr_x_avg_t, int *p_tnr_x_avg_s, int *p_tpd_s_status)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		ret = CVD_O26Ax_Get_PE0_Motion_Value(p_tnr_x_avg_t, p_tnr_x_avg_s, p_tpd_s_status);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		ret = CVD_O24Ax_Get_PE0_Motion_Value(p_tnr_x_avg_t, p_tnr_x_avg_s, p_tpd_s_status);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		ret = CVD_M23Ax_Get_PE0_Motion_Value(p_tnr_x_avg_t, p_tnr_x_avg_s, p_tpd_s_status);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		ret = CVD_O22Ax_Get_PE0_Motion_Value(p_tnr_x_avg_t, p_tnr_x_avg_s, p_tpd_s_status);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		ret = CVD_E60Ax_Get_PE0_Motion_Value(p_tnr_x_avg_t, p_tnr_x_avg_s, p_tpd_s_status);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		ret = CVD_O20Ax_Get_PE0_Motion_Value(p_tnr_x_avg_t, p_tnr_x_avg_s, p_tpd_s_status);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_PE_Params(CVD_REG_PARAM_T	*pCVD_PE_Param_t, UINT32 size, LX_AFE_CVD_PQ_MODE_T cvd_pq_mode)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_PE_Params(pCVD_PE_Param_t, size, cvd_pq_mode);

	return ret;
}

int CVD_Set_dcrestore_accum_width(int value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	AFE_PRINT("%s entered :  [0x%x] \n",__func__, value);

	ret = CVD_Hal_Set_dcrestore_accum_width(value);

	return ret;
}

int CVD_Set_Noise_Threshold(int value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Noise_Threshold(value);

	return ret;
}

int CVD_Get_ColorBar_Level(UINT8 *Composite_Level)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_ColorBar_Level(Composite_Level);

	return ret;
}

int CVD_Set_ColorBar_Params(int enable)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_ColorBar_Params(enable);

	return ret;
}

int CVD_Init_ColorSystem_Params(void)
{
	int ret = RET_OK;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		pSetColorSystem_3CS = &g_SetColorSystem_3CS_O26A0;
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		pSetColorSystem_3CS = &g_SetColorSystem_3CS_O24A0;
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		pSetColorSystem_3CS = &g_SetColorSystem_3CS_M23A0;
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		pSetColorSystem_3CS = &g_SetColorSystem_3CS_O22A0;
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		pSetColorSystem_3CS = &g_SetColorSystem_3CS_E60A0;
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		pSetColorSystem_3CS = &g_SetColorSystem_3CS_O20A0;
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Get_HDTO_difference(void)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_HDTO_difference();

	return ret;
}

int CVD_Set_CVD_Saturation_Value(UINT32 saturation_value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_CVD_Saturation_Value(saturation_value);

	return ret;
}

int CVD_vf_nstd_control(unsigned int value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_vf_nstd_control(value);

	return ret;
}

int CVD_Set_HNon_Standard_Threshold(int value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_HNon_Standard_Threshold(value);

	return ret;
}

LX_AFE_VIDEO_SYSTEM_T CVD_Get_Color_System(void)
{
	LX_AFE_VIDEO_SYSTEM_T	cvd_standard;

	switch(g_CVD_Status_3CS.cvd_color_system)
	{
		case CVD_STATE_NTSC:
			cvd_standard = LX_NTSC_M;
			break;
		case CVD_STATE_NTSC443:
			cvd_standard = LX_NTSC_443;
			break;
		case CVD_STATE_PALi:
			cvd_standard = LX_PAL_BG;
			break;
		case CVD_STATE_PALm:
			cvd_standard = LX_PAL_M;
			break;
		case CVD_STATE_PALCn:
			cvd_standard = LX_PAL_CN;
			break;
		case CVD_STATE_PAL60:
			cvd_standard = LX_PAL_60;
			break;
		case CVD_STATE_SECAM:
			cvd_standard = LX_SECAM;
			break;
		default:
			cvd_standard = LX_NON_STANDARD;
			break;
	}

	return cvd_standard;

}

int CVD_Set_force_vcr(int value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_force_vcr(value);

	return ret;
}

int CVD_Set_vcr_auto_switch_en(int value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_vcr_auto_switch_en(value);

	return ret;
}

int CVD_Set_Cpump_Auto_Stip_Mode(int value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Cpump_Auto_Stip_Mode(value);

	return ret;
}

int CVD_CVD_Soft_Reset(void)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_CVD_Soft_Reset();

	return ret;
}

int CVD_Get_AFE_CVBS_status(UINT8 *cvbs_icon_value, UINT8 *cvbs_pdb_value, UINT8 *cvbs_cp_value, UINT8 *cvbs_insel_value, UINT8 *cvbs_pdbm_value)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		ret = CVD_O26Ax_Get_AFE_CVBS_status(cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		ret = CVD_O24Ax_Get_AFE_CVBS_status(cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		ret = CVD_M23Ax_Get_AFE_CVBS_status(cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		ret = CVD_O22Ax_Get_AFE_CVBS_status(cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		ret = CVD_E60Ax_Get_AFE_CVBS_status(cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		ret = CVD_O20Ax_Get_AFE_CVBS_status(cvbs_icon_value, cvbs_pdb_value, cvbs_cp_value, cvbs_insel_value, cvbs_pdbm_value);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}

int CVD_Set_Burst_Gate_12(int burst1_start, int burst1_end, int burst2_start, int burst2_end)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Set_Burst_Gate_12(burst1_start, burst1_end, burst2_start, burst2_end);

	return ret;
}

int CVD_Get_Burst_Mag_12(int *pBurst1_mag, int *pBurst2_mag)
{
	int ret = RET_OK;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Get_Burst_Mag_12(pBurst1_mag, pBurst2_mag);

	return ret;
}

int CVD_Cordic_Gate_Control(UINT32	gate_start, UINT32 gate_end)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_Cordic_Gate_Control(gate_start, gate_end);

	return ret;
}

int CVD_Set_Clockgating(int value)
{
	int ret = RET_OK;

	CVD_Hal_Set_Clockgating(value);

	return ret;
}
static int CVD_Init_Buffer(void)
{
	int ret = RET_OK;

	unsigned int phy_buffer_base = 0, phy_buffer_size;

	if(g_CVD_USE_TE_SHARED_POOL)
	{
		strncpy(cvd_mem_pool ,"te_shared", sizeof("te_shared")+1);
		AFE_PRINT("cvd using %s\n", cvd_mem_pool);
	}
	else if (gpCvdMemCfg->memory_base)
	{
		enum hma_pool_type pool_type;
		phy_buffer_base = gpCvdMemCfg->memory_base;
		phy_buffer_size = gpCvdMemCfg->memory_size;

		if(g_CVD_CMA_POOL)
			pool_type = CMA_POOL;
		else 
			pool_type = HMA_POOL;

		strncpy(cvd_mem_pool ,"cvd_3dcomb_buf", sizeof("cvd_3dcomb_buf")+1);

		AFE_PRINT("Cvd buffer memory type : %d ,pool : %s\n", pool_type , cvd_mem_pool);

		if (hma_pool_register_type(cvd_mem_pool, phy_buffer_base, phy_buffer_size, pool_type) < 0)
		{
			AFE_PRINT("gpCvdMemCfg hma register failed !!!\n");
			gCVD_2d_mode = TRUE;
			ret = RET_ERROR;
		}
		AFE_PRINT("gpCvdMemCfg base[0x%08X]  CVD buffer size = %dKB\n", phy_buffer_base, phy_buffer_size/1024);
	}
	else
	{
		AFE_PRINT("gpCvdMemCfg base[0x%08X] !!!\n", phy_buffer_base);
		gCVD_2d_mode = TRUE;
		ret = RET_ERROR;
	}

	return ret;
}

static int CVD_AllocFree_Buffer(int flag)
{
	int ret = RET_OK;
	static phys_addr_t cvd_paddr = 0;
	unsigned int phy_buffer_size = 0;

	AFE_PRINT("cvd %s \n", flag?"alloc":"free");

	if(flag)
	{
		phy_buffer_size = gpCvdMemCfg->memory_size;
		/* hma alloc */
		if(cvd_paddr != 0) {
			AFE_PRINT("%s already allocated\n", cvd_mem_pool);
			return 0; 
		}
		cvd_paddr = hma_alloc_user(cvd_mem_pool, phy_buffer_size, (1<<12), "cvd_3dcomb_buf");
		AFE_PRINT("cvd alloc addr : 0x%llx\n", cvd_paddr);
		if(cvd_paddr == 0) {
			AFE_ERROR("%s hma alloc failed !!!\n", cvd_mem_pool);
			gCVD_2d_mode = TRUE;
			}
		else
			gCVD_2d_mode = FALSE;

		if(g_CVD_USE_TE_SHARED_POOL)
			ret = CVD_Set_Buffer_Base_Addr(cvd_paddr);
	}
	else
	{
		if (g_CVD_CMA_POOL)
		{
			if(cvd_paddr != 0)
			{
				hma_free(cvd_mem_pool, cvd_paddr);
				cvd_paddr = 0;
			}
			else
				AFE_PRINT("CVD CMA not allocated\n");
		}
	}
	AFE_PRINT("CVD %s done : start = 0x%8x, size = %dKB", flag?"alloc":"free", \
			(UINT32)cvd_paddr, phy_buffer_size/1024);

	return ret;
}

#ifdef INCLUDE_KDRV_PE
int CVD_SetPqModeToDdr(volatile UINT32 *p_ddr_reg)
{
	int ret;

	// enable download cvd pq before cvd driver initialize.
	/*
	if(gCVDInitStatus == FALSE)
		return RET_ERROR;
		*/

#ifdef USE_AFE_KDRV_FOR_O26
	if (lx_chip_rev() >= LX_CHIP_REV(O26, A0))
	{
		ret = CVD_O26Ax_SetPqModeToDdr(p_ddr_reg);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O24
	if (lx_chip_rev() >= LX_CHIP_REV(O24, A0))
	{
		ret = CVD_O24Ax_SetPqModeToDdr(p_ddr_reg);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_M23
	if (lx_chip_rev() >= LX_CHIP_REV(M23, A0))
	{
		ret = CVD_M23Ax_SetPqModeToDdr(p_ddr_reg);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O22
	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0))
	{
		ret = CVD_O22Ax_SetPqModeToDdr(p_ddr_reg);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_E60
	if (lx_chip_rev() >= LX_CHIP_REV(E60, A0))
	{
		ret = CVD_E60Ax_SetPqModeToDdr(p_ddr_reg);
	} else
#endif

#ifdef USE_AFE_KDRV_FOR_O20
	if (lx_chip_rev() >= LX_CHIP_REV(O20, A0))
	{
		ret = CVD_O20Ax_SetPqModeToDdr(p_ddr_reg);
	} else
#endif

	{
		ret = RET_ERROR;	// Unkown chip revision
	}

	return ret;
}
#endif

int CVD_chromalock_level_control(unsigned int value)
{
	int ret;

	if(gCVDInitStatus == FALSE)
		return RET_ERROR;

	ret = CVD_Hal_chromalock_level_control(value);

	return ret;
}

EXPORT_SYMBOL(CVD_Get_Color_System);
#ifdef INCLUDE_KDRV_PE
EXPORT_SYMBOL(CVD_SetPqModeToDdr);
#endif
