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
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <asm/io.h>

#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/ctype.h>
#include <asm/uaccess.h>

#include "base_types.h"
#include "os_util.h"
#include "sys_io.h"

#include "de_model.h"
#include "de_ver_def.h"
#include "hma_alloc.h"

#ifdef USE_KDRV_CODES_FOR_M23
#include "de_kapi.h"
#include "de_def.h"
#include "de_prm_def.h"
#include "de_hal_def.h"
#include "de_cfg.h"
#include "de_drv.h"

#include "de_cfg_m23.h"
#include "de_ipc_def_m23.h"
#include "de_int_def_m23.h"
#include "de_reg_def_m23.h"
#include "de_reg_m23.h"

#include "de_ipc_reg_m23.h"
#include "de_ctr_reg_m23.h"

//check values (SICDTV-10687)
#ifdef USE_CTOP_CODES_FOR_M23
#include "../sys/sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define USE_VIDEO_MCU_ROM_BASE_ADDR 0x50000000
#define USE_VIDEO_MCU_ROM_FW0_OFSET 0x00000000

/* FW0(MAIN) */
#define USE_VIDEO_MCU_ROM_FW_MAX_NUM 1

#define DE_REG_M23_NOTI_BUF_MAX		100
#define DE_REG_M23_NOTI_STR_SIZE	64

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_REG_M23_NOTI_BACKUP(_fmt, args...)	\
	{\
		char _de_io_str_buf[DE_REG_M23_NOTI_STR_SIZE];\
		DE_NOTI(_fmt, ##args);\
		snprintf(_de_io_str_buf, DE_REG_M23_NOTI_STR_SIZE, _fmt, ##args);\
		DE_REG_M23_BackupTraceDataBuf(_de_io_str_buf);\
	}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
#define NUM_OF_CVI_FIR_COEF 8
#define NUM_WIN_MAX	2

typedef struct {
	UINT32 sec;			///< sec
	UINT32 msec;		///< msec
	UINT32 usec;		///< usec
}
DE_REG_M23_NOTI_TIME_T;

typedef struct {
	DE_REG_M23_NOTI_TIME_T time;		///< time
	char str[DE_REG_M23_NOTI_STR_SIZE];	///< str
}
DE_REG_M23_NOTI_BUF_T;

typedef struct {
	LX_DE_SYSTEM_VERSION_T      system_info; // 0xDECAFE00 + 1:ASIC,2:FPGA
	LX_DE_IPC_SYSTEM_MODEL_T  	model;		// STB, HD/FHD panel type info.
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu0;   // MCU0 firmware
	LX_DE_IPC_SYSTEM_MEM_T		de_svp_m0;	// M0 SVP(FRM)
	LX_DE_IPC_SYSTEM_MEM_T		de_svp_m1;	// M1 SVP(FRM)
	LX_DE_IPC_SYSTEM_MEM_T		de_svp_m2;	// M2 SVP(FRM)

	LX_DE_IPC_SYSTEM_MEM_T		de_nsvp_m1;	// M1 non SVP(DNNSQM, DNNSR)
	LX_DE_IPC_SYSTEM_MEM_T		de_nsvp_m2;	// M2 non SVP(DNNSQM, DNNSR)
	LX_DE_IPC_SYSTEM_MEM_T		de_vt_m1;	// M1 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_vt_m2;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		de_hdr;		// dolby lut

	LX_DE_IPC_SYSTEM_MEM_T		be_fpp;		// M0 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_frc0;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_frc1;	// M2 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_frc2;	// M1 BUS
	LX_DE_IPC_SYSTEM_MEM_T		be_wcg;   	// WCG LUT
	LX_DE_IPC_SYSTEM_MEM_T		fpp_info;   //
	LX_DE_IPC_SYSTEM_MEM_T		vdec_pool_0; // vdec dpb address
	LX_DE_IPC_SYSTEM_MEM_T		vdec_pool_1; // vdec dpb address

	FW_SHARED_MEM_INFO_T		shared_mem_info;	// video delay

	LX_DE_IPC_SYSTEM_MEM_T		pe_db; // tnr,scl,sr
	LX_DE_IPC_SYSTEM_MEM_T		pe_hdr; // hdr10

	LX_DE_IPC_SYSTEM_MEM_T		fw_dnn;    // fw dnn
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu1;   // MCU1 firmware(DNN-SR)
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu2;   // MCU2 firmware(IPU)(face detection)
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu3;   // MCU3 firmware(LNE)(2k to 4k)
	LX_DE_IPC_SYSTEM_MEM_T		fw_shared; // fw shared
	LX_DE_IPC_SYSTEM_MEM_T		fw_mcu4;   // MCU4 firmware(LNE)(4k to 4k)

	LX_DE_IPC_SYSTEM_MEM_T		be_led;   	// LED LUT
	LX_DE_IPC_SYSTEM_MEM_T		be_phdr;   	// post HDR/OLED data
	LX_DE_IPC_SYSTEM_MEM_T		be_chipinfo;// Chip Info

	LX_DE_IPC_SYSTEM_MEM_T		lne_pool; // lne

	LX_DE_IPC_SYSTEM_MEM_T		de_dbg_m1; // M1 dbg
	LX_DE_IPC_SYSTEM_MEM_T		de_dbg_m2; // M2 dbg
}
DE_REG_M23_IPC_SYSTEM_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/
int DE_REG_M23_CviMap(LX_DE_WIN_ID_T win_id, LX_DE_IN_SRC_T in_port, UINT32 port_num);

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

DE_IPC_REG_M23_T gDE_IPC_M23;
volatile UINT32 *gDE_MUTE_M23 = NULL;//VSD_SHP:SHP_FSW_CTRL_03:0xC900D8FC
volatile LX_DE_FW_STATUS_REG_T *gDE_FW_STATUS_M23 = NULL;//0xC902E328
volatile LX_DE_VDEC_IPC_REG_T *gDE_VDEC_M23[4];

LX_DE_IN_SRC_T g_WinsrcMap_M23[NUM_WIN_MAX] = { LX_DE_IN_SRC_MVI,	LX_DE_IN_SRC_MVI};
UINT32 g_WinsrcPort_M23[NUM_WIN_MAX] = { 0, 0};
UINT32 g_HdmiPort_M23[NUM_WIN_MAX] = { 0, };
UINT32 g_QuadWin_M23  = 0;
LX_DE_OPER_CONFIG_T g_SrcOperType_M23 = LX_DE_OPER_ONE_WIN;
LX_DE_SUB_OPER_CONFIG_T	g_SrcSubOperType_M23 = LX_DE_SUB_OPER_OFF;
UINT16 g_SrcOperCtrlFlag_M23 = 0;
UINT16 g_SrcSubOperCtrlFlag_M23 = 0;
LX_DE_DISPLAY_MIRROR_T	g_Display_mirror_M23 = LX_DE_DIS_MIRROR_OFF;
UINT32                  g_Zero_delay_mode_M23 = 0;

static phys_addr_t bt_paddr_m0 = 0;
//static phys_addr_t vr_paddr_m0 = 0;
static phys_addr_t vtg_paddr_m0 = 0, vtg_paddr_m1 = 0;
static phys_addr_t dbg_paddr_m0 = 0;

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
static void _set_tag_info(void);
static int DE_REG_M23_ClearTraceDataBuf(void);
static int DE_REG_M23_BackupTraceDataBuf(char *data);
static int DE_REG_M23_ViewTraceDataBuf(void);
static void _print_tag_info(void *tag_info, UINT32 tag_size);

LX_MEMCFG_T de_reg_m23_getmeminfo(char* str);
int DE_REG_M23_SetClockGate(CTOP_PQE_CG_M23_MODULE mod, BOOLEAN onOff);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static DE_REG_M23_IPC_SYSTEM_T  g_Mem_Info = { 0, };
static LX_DE_MEM_SYS_INFO_T   g_Mem_Sys_Info = { 0, };
static DE_REG_M23_NOTI_BUF_T _g_de_reg_m23_buf[DE_REG_M23_NOTI_BUF_MAX];

static LX_DE_VIDEO_DELAY_INFO_MEM_T *lpAddr_win_update = NULL;

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
/**
 * @callgraph
 * @callergraph
 *
 * @brief Initialize Reigerter Physical Address to Virtual Address and Make Shadow Register
 *
 * @return RET_OK(0)
 */
int DE_REG_M23_InitPHY2VIRT(void)
{
	int ret = RET_OK;

	memset(&g_Mem_Info, 0, sizeof(DE_REG_M23_IPC_SYSTEM_T));

	gDE_IPC_M23.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_M23A0_T));
	gDE_IPC_M23.phys.addr  = (volatile UINT32 *)ioremap(DE_IPC_REG_M23_BASE, sizeof(DE_IPC_REG_M23A0_T));
	gDE_VDEC_M23[0] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_M23_BASE + 0x00, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_M23[1] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_M23_BASE + 0x40, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_M23[2] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_M23_BASE + 0x80, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_M23[3] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_M23_BASE + 0xC0, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_MUTE_M23 = (volatile UINT32 *)ioremap(DE_MUTE_M23_BASE, sizeof(UINT32));//VSD_SHP:SHP_FSW_CTRL_03:0xCC4628FC
	gDE_FW_STATUS_M23 = (volatile LX_DE_FW_STATUS_REG_T *)ioremap(DE_FW_STATUS_M23_BASE, sizeof(LX_DE_FW_STATUS_REG_T));//0xCC482228

	DE_REG_M23_ClearTraceDataBuf();
	_set_tag_info();

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Free memory alocated in Shadow Register
 *
 * @return RET_OK(0)
 */
int DE_REG_M23_FreePHY2VIRT(void)
{
	if (gDE_IPC_M23.shdw.addr) OS_Free((void *)gDE_IPC_M23.shdw.addr);
	if (gDE_IPC_M23.phys.addr) iounmap((void *)gDE_IPC_M23.phys.addr);
	if (gDE_VDEC_M23[0]) iounmap((void *)gDE_VDEC_M23[0]);
	if (gDE_VDEC_M23[1]) iounmap((void *)gDE_VDEC_M23[1]);
	if (gDE_VDEC_M23[2]) iounmap((void *)gDE_VDEC_M23[2]);
	if (gDE_VDEC_M23[3]) iounmap((void *)gDE_VDEC_M23[3]);
	if (gDE_MUTE_M23) iounmap((void *)gDE_MUTE_M23);
	if (gDE_FW_STATUS_M23) iounmap((void *)gDE_FW_STATUS_M23);

	return RET_OK;
}

 /**
 * @callgraph
 * @callergraph
 *
 * @brief Get Status of Interrupt which is one of either MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param pStatus [OUT] status pointer of Interrupt
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_M23_GetStatusReg(UINT32 mcu_id,           \
                            VIDEO_IPC_TYPE_T ipcType,\
                            UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
		case VIDEO_DMA_MCU :
		case VIDEO_JPG_MCU :
		case VIDEO_WEL_MCU :
		case VIDEO_WER_MCU :
		case VIDEO_GPW_CPU :
			DE_IPC_M23_RdFL(int_intr_status);
			*pStatus = DE_IPC_M23_Rd(int_intr_status);
			break;
		case VIDEO_IPC_CPU :
		case VIDEO_DMA_CPU :
		case VIDEO_JPG_CPU :
		case VIDEO_WEL_CPU :
		case VIDEO_WER_CPU :
			DE_IPC_M23_RdFL(ext_intr_status);
			*pStatus = DE_IPC_M23_Rd(ext_intr_status);
			break;
		default :
			BREAK_WRONG(ipcType);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make inerrupt status for watch dog either happen or clear
 *
 * @param turnOn [IN] determine to turn On or Off
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_WDG_M23_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn)
{
	if (turnOn) {
		DE_IPC_M23_FLWf(ext_intr_event, wdg_interrupt_event, 1);
	} else {
		DE_IPC_M23_FLWf(ext_intr_clear, wdg_interrupt_clear, 1);
	}

	return RET_OK;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make interrupt be happen according to ipcType which is either of MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param turnOn  [IN] maket Interrupt enable or clear
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_M23_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn)
{
	int ret = RET_OK;

	turnOn &= 0x1;
	switch (ipcType) {
		case VIDEO_IPC_MCU :
			if (turnOn) {
				DE_IPC_M23_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_IPC_CPU :
			if (turnOn) {
				DE_IPC_M23_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_MCU :
			if (turnOn) {
				DE_IPC_M23_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_CPU :
			if (turnOn) {
				DE_IPC_M23_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_MCU :
			if (turnOn) {
				DE_IPC_M23_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_CPU :
			if (turnOn) {
				DE_IPC_M23_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_MCU :
			if (turnOn) {
				DE_IPC_M23_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_CPU :
			if (turnOn) {
				DE_IPC_M23_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_MCU :
			if (turnOn) {
				DE_IPC_M23_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_CPU :
			if (turnOn) {
				DE_IPC_M23_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_MCU :
			if (turnOn) {
				DE_IPC_M23_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_CPU :
			if (turnOn) {
				DE_IPC_M23_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_M23_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		default :
			BREAK_WRONG(ipcType);
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make interrupt be happen according to ipcType which is either of MCU or CPU
 *
 * @param ipcType [IN] one of either MCU and CPU
 * @param turnOn  [IN] maket Interrupt enable or clear
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_IPC_M23_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
			DE_IPC_M23_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_IPC_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DMA_MCU :
			DE_IPC_M23_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DMA_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_JPG_MCU :
			DE_IPC_M23_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_JPG_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_USB_MCU :
			DE_IPC_M23_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_USB_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WEL_MCU :
			DE_IPC_M23_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WEL_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WER_MCU :
			DE_IPC_M23_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WER_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DHDR_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_DHDR_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DELAY_CPU:
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_CB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_GPS_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_GPS_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_GPW_CPU :
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_GPW_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_AMZ_CPU:
			DE_IPC_M23_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_AMZ_INTERRUPT_ARM_BIT, 1));
			break;
		default :
			BREAK_WRONG(ipcType);
			break;
	}
	return ret;
}

int DE_REG_M23_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status)
{
	int ret = RET_OK;
	UINT32 data;
	UINT32 i = win_id;

	if (gDE_MUTE_M23==NULL)	return RET_ERROR;
	data = *gDE_MUTE_M23;
	*mute_status = (UINT16)((data >> (16 * i)) & 0xFFFF);

	return ret;
}

int DE_REG_M23_CheckFwStatus(UINT32 win_id, void *status)
{
	int ret = RET_OK;
	LX_DE_FW_STATUS_REG_T *dst = (LX_DE_FW_STATUS_REG_T *)status;

	if (gDE_FW_STATUS_M23==NULL)	return RET_ERROR;
	if (status==NULL)	return RET_ERROR;
	memcpy(dst, (const void *)gDE_FW_STATUS_M23, sizeof(LX_DE_FW_STATUS_REG_T));
	return ret;
}

int DE_REG_M23_SetFrRate(DE_DPLL_CLK_T dclk)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;

	return ret;
}

BOOLEAN DE_REG_M23_CheckIrq4Vsync(UINT32 mcu_id)
{
	int ret;
	M23A0_INTR_CPU_FLAG_T intr_flag_cpu;
	M23A0_IMX_CTRL_INTR_REG_T imx_intr_reg;
	M23A0_HDR_CTRL_INTR_CPU_REG_T hdr_intr_reg;
	UINT32 videoIntrDe;
	BOOLEAN vsyncIrq = 0;

	do {
		vsyncIrq = 0;
		ret = DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_FUNC, &videoIntrDe);
		if (ret) break;

		intr_flag_cpu.udata32 = videoIntrDe;

		if (intr_flag_cpu.intr_imx_mcu_cpu)
		{
			vsyncIrq = 0;
			videoIntrDe = 0;
			ret = DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_IMX, &videoIntrDe);
			if (ret) break;
			imx_intr_reg.udata32 = videoIntrDe;
			if(!imx_intr_reg.intr_i5_intr_pulse) break;
			vsyncIrq = 1;
		}
		if (intr_flag_cpu.intr_hdr_mcu_cpu)
		{
			vsyncIrq = 0;
			videoIntrDe = 0;
			ret = DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_HDR, &videoIntrDe);
			if (ret) break;
			hdr_intr_reg.udata32 = videoIntrDe;
			if(!hdr_intr_reg.intr_i5_intr_pulse) break;
			vsyncIrq = 1;
		}
		if (intr_flag_cpu.intr_cvi_mcu_cpu)
		{
			vsyncIrq = 0;
			videoIntrDe = 0;
			ret = DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_CVI, &videoIntrDe);
			if (ret) break;
		}
	} while (0);
	return vsyncIrq;
}

int DE_REG_M23_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pVideoIrqStatus);
		switch (intrType) {
			case VIDEO_INTR_TYPE_CVI :
				break;
			case VIDEO_INTR_TYPE_IMX :
				break;
			case VIDEO_INTR_TYPE_ND1 :
				break;
			case VIDEO_INTR_TYPE_HDR :
				break;
			case VIDEO_INTR_TYPE_GSC :
				break;
			case VIDEO_INTR_TYPE_VSD :
				break;
			case VIDEO_INTR_TYPE_CCO :
				break;
			case VIDEO_INTR_TYPE_SUB :
				break;
			case VIDEO_INTR_TYPE_FUNC :
				DE_IPC_M23_RdFL(intr_cpu_flag);
				*pVideoIrqStatus = DE_IPC_M23_Rd(intr_cpu_flag);
				break;
			default :
				BREAK_WRONG(intrType);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief copy frame buffer of certain block size and position.
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams,LX_DE_CVI_RW_PREW_FRAME_T *prewInfo)
{
	int ret = RET_OK;

	return ret;
}


/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_CviMap(LX_DE_WIN_ID_T win_id, LX_DE_IN_SRC_T in_port, UINT32 port_num)
{
	int ret = RET_OK;
	UINT32 sel_cvi[2] = {0, 0};
	UINT32 sel_clk[2] = {0, 0};

	do {
		sel_cvi[0] = CVI_NONE_M23;
		sel_cvi[1] = CVI_NONE_M23;
		sel_clk[0] = CLK_NONE_M23;
		sel_clk[1] = CLK_NONE_M23;

		switch(win_id)
		{
			case LX_DE_WIN_MAIN:
			case LX_DE_WIN_1:
			case LX_DE_WIN_2:
			case LX_DE_WIN_3:
				if(in_port == LX_DE_IN_SRC_CVBS || \
						in_port == LX_DE_IN_SRC_ATV || \
						in_port == LX_DE_IN_SRC_SCART)
				{
					sel_cvi[0] = CVI_CVD_M23;
					sel_clk[0] = CLK_CVD_M23;
				}
				if(in_port == LX_DE_IN_SRC_YPBPR || \
						in_port == LX_DE_IN_SRC_VGA)
				{
					sel_cvi[0] = CVI_ADC_M23;
					sel_clk[0] = CLK_ADC_M23;
				}
				if(in_port == LX_DE_IN_SRC_HDMI)
				{
					g_HdmiPort_M23[win_id] = port_num;  // assign for resume from instanr boot !!!
					switch(port_num)
					{
						case HDMI_M23_PORT_0:
							sel_cvi[0] = CVI_HDMI_M23_A;
							sel_cvi[1] = CVI_HDMI_M23_A;
							sel_clk[0] = CLK_HDA_M23;
							sel_clk[1] = CLK_HDA_M23;
							break;
						case HDMI_M23_PORT_1:
							sel_cvi[0] = CVI_HDMI_M23_B;
							sel_cvi[1] = CVI_HDMI_M23_B;
							sel_clk[0] = CLK_HDB_M23;
							sel_clk[1] = CLK_HDB_M23;
							break;
						case HDMI_M23_PORT_2:
							sel_cvi[0] = CVI_HDMI_M23_C;
							sel_cvi[1] = CVI_HDMI_M23_C;
							sel_clk[0] = CLK_HDC_M23;
							sel_clk[1] = CLK_HDC_M23;
							break;
						case HDMI_M23_PORT_3:
							sel_cvi[0] = CVI_HDMI_M23_D;
							sel_cvi[1] = CVI_HDMI_M23_D;
							sel_clk[0] = CLK_HDD_M23;
							sel_clk[1] = CLK_HDD_M23;
							break;
						case HDMI_M23_PORT_DSC:
							sel_cvi[0] = CVI_HDMI_M23_DSC;
							sel_cvi[1] = CVI_HDMI_M23_DSC;
							sel_clk[0] = CLK_DSC_M23;
							sel_clk[1] = CLK_DSC_M23;
							break;
						default:
							sel_cvi[0] = CVI_HDMI_M23_A;
							sel_cvi[1] = CVI_HDMI_M23_A;
							sel_clk[0] = CLK_HDA_M23;
							sel_clk[1] = CLK_HDA_M23;
							DE_ERROR("undefined hdmi port [%d]\n", port_num);
							break;
					}
				}
				break;
			default:
				break;
		}

		if(in_port == LX_DE_IN_SRC_NONE) break;
		if(in_port >= LX_DE_IN_SRC_MVI)  break;

#ifdef USE_CTOP_CODES_FOR_M23

#if 0
M23_CRG_SUB_Register_Manual.xlsx
CVI(cvi_syn)

Clock Selection
0 => core660_clk (662.5MHz)
1 => core660_d2 (331.25MHz)
2 => phy1_hdmi_link_clk (660.0MHz)
3 => phy2_hdmi_link_clk (660.0MHz)
4 => phy3_hdmi_link_clk (660.0MHz)
5 => phy4_hdmi_link_clk (660.0MHz)
6 => cvi_cvd54_d2 (27.0MHz)

#define M23_A0_SCRG_CTRL_CVI_BASE 0xCC6A0000
SCRG_CTRL_CVI_REG_M23A0_T *SCRG_CTRL_CVI;// scrg_ctrl_cvi_m23a0_reg.h
#endif

		CTOP_CTRL_M23Ax_RdFL(SCRG_CTRL_CVI, crg_cvi04);//0xCC6A0010
		switch(win_id)
		{
		case LX_DE_WIN_MAIN:
			CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_CVI, crg_cvi04, reg_cvi0_clk_sel, sel_clk[0]);
			break;
		case LX_DE_WIN_2:
			CTOP_CTRL_M23Ax_Wr01(SCRG_CTRL_CVI, crg_cvi04, reg_cvi1_clk_sel, sel_clk[0]);
			break;
		default :
			break;
		}
		CTOP_CTRL_M23Ax_WrFL(SCRG_CTRL_CVI, crg_cvi04);
#endif
	} while(0);

	DE_NOTI("sel_cvi[%d] sel_clk[%d]", sel_cvi[0], sel_clk[0]);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_WIN_ID_T win_id = LX_DE_WIN_MAIN;
	LX_DE_IN_SRC_T in_port = LX_DE_IN_SRC_MVI;
	UINT32 srcPort = 0;

	do {
		CHECK_KNULL(pstParams);

		win_id  = pstParams->win_id;
		in_port = pstParams->inputSrc;
		srcPort = pstParams->inputResv;

		ret = DE_REG_M23_CviMap(win_id, in_port, srcPort);

		if(win_id < NUM_WIN_MAX)
		{
			g_WinsrcMap_M23[win_id] = in_port;
			g_WinsrcPort_M23[win_id] = srcPort;
		}
		DE_PRINT("Src map (NONE(0)/VGA(1)/YPBPR(2)/ATV(3)/CVD(4)/SCART(5)/HDMI(6)/MVI(7)/CPU(8))");
		DE_PRINT("  => win[%d] src[%d] port[%d]", win_id, in_port, srcPort);
	} while(0);

	return ret;
}

int DE_REG_M23_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	return 0;
}

int DE_REG_M23_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	return 0;
}

int DE_REG_M23_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	return 0;
}

int DE_REG_M23_GPIO_Init(void)
{
	return 0;
}

int DE_REG_M23_HDMI_Init(void)
{
	return 0;
}

int DE_REG_M23_LVDS_Init(void)
{
	return 0;
}

int DE_REG_M23_MISC_Init(void)
{
	return 0;
}

int DE_REG_M23_OSD_Init(void)
{
	return 0;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set uart for MCU or CPU
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_Uart0_Switch(int whichUart)
{
	int ret = RET_OK;

#ifdef USE_CTOP_CODES_FOR_M23
#ifdef USE_DE_SWITCH_UART
	DE_NOTI("UART[%d]", whichUart);

#if 0
M23_CTOP_SYN_Register_Manual.xlsx
WOC_SYN

Main IO Mux - UART #0 0xF3515108
reg_pad_uart0_rxd_mux_sel 7:4 0x0
reg_pad_uart0_txd_mux_sel 3:0 0x0
Main UART Mux WOC_SYN_07 0xF351201C ==> 0xC851201C main_uart_sel0 3:0

Main IO Mux - UART #1 0xCE522110
reg_pad_uart1_txd_mux_sel 27:24 0x1
reg_pad_uart1_rxd_mux_sel 23:20 0x1
Main UART Mux WOC_SYN_06 0xF3512018 ==> 0xC8512018 main_uart_sel1 3:0

Main IO Mux - UART #2 0xC6153104
reg_pad_gpio19_mux_sel 23:20 0x2
reg_pad_gpio20_mux_sel 19:16 0x2
Main UART Mux WOC_SYN_05 0xF3512014 ==> 0xC8512014 main_uart_sel2 3:0

[0x2] : CPU #0
[0x3] : CPU #1
[0x4] : CPU #2
[0x5] : VDEC
[0x6] : PQE MXU #0
[0x7] : TE
[0x9] : MICOM #1
[0xA] : AUD
[0xB] : HDMI

#define M23_A0_CPU_BND_CTRL_WOC_BASE             0xC8512000
#define M23_A0_CPU_BND_CTRL_WOC_TYPE             MICOM_BND_CTRL_WOC_REG_M23A0_T
MICOM_BND_CTRL_WOC_REG_M23A0_T *CPU_BND_CTRL_WOC;// micom_bnd_ctrl_woc_m23a0_reg.h

#define M23_A0_MICOM_BND_CTRL_WOC_BASE           0xF3512000
#define M23_A0_MICOM_BND_CTRL_WOC_TYPE           MICOM_BND_CTRL_WOC_REG_M23A0_T
MICOM_BND_CTRL_WOC_REG_M23A0_T *MICOM_BND_CTRL_WOC;// micom_bnd_ctrl_woc_m23a0_reg.h
#endif

//	CTOP_CTRL_M23Ax_RdFL(CPU_BND_CTRL_WOC, woc_syn_05);// UART2
//	CTOP_CTRL_M23Ax_RdFL(CPU_BND_CTRL_WOC, woc_syn_06);// UART1
	CTOP_CTRL_M23Ax_RdFL(CPU_BND_CTRL_WOC, woc_syn_07);// UART0
	switch (whichUart)
	{
		case 0 :
//				CTOP_CTRL_M23Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_05, reg_main_uart_sel2, 2); // UART2 = cpu0
//				CTOP_CTRL_M23Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_06, reg_main_uart_sel1, 2); // UART1 = cpu0
				CTOP_CTRL_M23Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_07, reg_main_uart_sel0, 2); // UART0 = cpu0
			break;
		case 1 :
//				CTOP_CTRL_M23Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_05, reg_main_uart_sel2, 6); // UART2 = mcu0
//				CTOP_CTRL_M23Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_06, reg_main_uart_sel1, 6); // UART1 = mcu0
				CTOP_CTRL_M23Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_07, reg_main_uart_sel0, 6); // UART0 = mcu0
			break;
		case 2 :
		default :
			break;
	}
//	CTOP_CTRL_M23Ax_WrFL(CPU_BND_CTRL_WOC, woc_syn_05);// UART2
//	CTOP_CTRL_M23Ax_WrFL(CPU_BND_CTRL_WOC, woc_syn_06);// UART1
	CTOP_CTRL_M23Ax_WrFL(CPU_BND_CTRL_WOC, woc_syn_07);// UART0
#endif
#endif
	return ret;
}

int DE_REG_M23_FW_DumpStatus(void)
{
	int ret = RET_OK;
	UINT32 *p_pqe_debug_info = NULL;
	UINT32 i;
	UINT32 size = 16;

	DE_NOTI("CPU->MCU[ 0x%08X ]\n", DTVSOC_IPC_FROM_CPU_M23_BASE);
	p_pqe_debug_info = (UINT32 *)ioremap(DTVSOC_IPC_FROM_CPU_M23_BASE, sizeof(UINT32) * size);
	for(i=0;i<size;i++)
	{
		DE_NOTI("[%02d] 0x%08X\n", i, p_pqe_debug_info[i]);
	}
	DE_NOTI("MCU->CPU[ 0x%08X ]\n", DTVSOC_IPC_FROM_MCU_M23_BASE);
	if(p_pqe_debug_info) iounmap(p_pqe_debug_info);

	p_pqe_debug_info = (UINT32 *)ioremap(DTVSOC_IPC_FROM_MCU_M23_BASE, sizeof(UINT32) * size);
	for(i=0;i<size;i++)
	{
		DE_NOTI("[%02d] 0x%08X\n", i, p_pqe_debug_info[i]);
	}

	if(p_pqe_debug_info) iounmap(p_pqe_debug_info);

	return ret;
}

static int DE_REG_M23_ClearTraceDataBuf(void)
{
	memset(_g_de_reg_m23_buf, 0, sizeof(DE_REG_M23_NOTI_BUF_T)*DE_REG_M23_NOTI_BUF_MAX);
	return RET_OK;
}

static int DE_REG_M23_BackupTraceDataBuf(char *data)
{
	UINT32 i;
	char *p_str;
	DE_REG_M23_NOTI_TIME_T *p_time;
	static UINT32 cnt = 0;

	if (!data)	return RET_OK;

	if(cnt>=DE_REG_M23_NOTI_BUF_MAX)	cnt = 0;

	p_str = _g_de_reg_m23_buf[cnt].str;
	p_time = &(_g_de_reg_m23_buf[cnt].time);
	OS_GetCurrentTicks(&(p_time->sec), &(p_time->msec), &(p_time->usec));
	memset(p_str, 0, DE_REG_M23_NOTI_STR_SIZE);

	for(i=0;i<DE_REG_M23_NOTI_STR_SIZE;i++)
	{
		p_str[i] = data[i];
		if(data[i] == 0) break;
	}

	cnt++;

	return RET_OK;
}

static int DE_REG_M23_ViewTraceDataBuf(void)
{
	UINT32 i;
	char *p_str;
	DE_REG_M23_NOTI_TIME_T *p_time;

	for (i=0; i<DE_REG_M23_NOTI_BUF_MAX; i++)
	{
		p_time = &(_g_de_reg_m23_buf[i].time);
		if(p_time->sec==0 && p_time->msec==0 && p_time->usec==0)	break;
		p_str = _g_de_reg_m23_buf[i].str;
		printk("[%02d][%06d.%03d%03d] %s",i,p_time->sec,p_time->msec,p_time->usec,p_str);
	}

	return RET_OK;
}

int DE_REG_M23_ViewInfo(int type)
{
	int ret = RET_OK;

	if (type == 0)
	{
		ret = DE_REG_M23_ViewTraceDataBuf();
		_print_tag_info(&g_Mem_Info,sizeof(DE_REG_M23_IPC_SYSTEM_T));
	}

	return ret;
}

LX_MEMCFG_T de_reg_m23_getmeminfo(char* str)
{
	LX_MEMCFG_T meminfo = {.name = NULL,.base = 0,.size = 0};

	if (!strncasecmp(str, "vdec_pool_0", strlen("vdec_pool_0"))) {
		meminfo.base = g_Mem_Info.vdec_pool_0.base;
		meminfo.size = g_Mem_Info.vdec_pool_0.size;
	}
	else if (!strncasecmp(str, "vdec_pool_1", strlen("vdec_pool_1"))) {
		meminfo.base = g_Mem_Info.vdec_pool_1.base;
		meminfo.size = g_Mem_Info.vdec_pool_1.size;
	}
	else if (!strncasecmp(str, "lne_pool", strlen("lne_pool"))) {
		meminfo.base = g_Mem_Info.lne_pool.base;
		meminfo.size = g_Mem_Info.lne_pool.size;
	}

	return meminfo;
}

static void _print_tag_info(void *tag_info, UINT32 tag_size)
{
	DE_REG_M23_IPC_SYSTEM_T *p = (DE_REG_M23_IPC_SYSTEM_T *)tag_info;

	if (!p)
	{
		DE_NOTI("no info\n");
		return;
	}

	#define SIZE_MB(a)	  (a/1024/1024)
	#define SIZE_KB(a)	  (a/1024)
	DE_NOTI("######################################\n");
	DE_NOTI("tag_size  = %d (max:%d)\n", tag_size, DTVSOC_IPC_TOTAL_SIZE);
	DE_NOTI("system_info[0x%08x] model[0x%08x]\n", p->system_info.u32Data, p->model.u32Data);
	DE_NOTI("fw_mcu0   = 0x%08x, %4dMB\n",p->fw_mcu0.base  ,SIZE_MB(p->fw_mcu0.size));
	DE_NOTI("de_svp_m0 = 0x%08x, %4dMB\n",p->de_svp_m0.base,SIZE_MB(p->de_svp_m0.size));
	DE_NOTI("de_svp_m1 = 0x%08x, %4dMB\n",p->de_svp_m1.base,SIZE_MB(p->de_svp_m1.size));
	DE_NOTI("de_svp_m2 = 0x%08x, %4dMB\n",p->de_svp_m2.base,SIZE_MB(p->de_svp_m2.size));
	DE_NOTI("de_nsvp_m1= 0x%08x, %4dMB\n",p->de_nsvp_m1.base,SIZE_MB(p->de_nsvp_m1.size));
	DE_NOTI("de_nsvp_m2= 0x%08x, %4dMB\n",p->de_nsvp_m2.base,SIZE_MB(p->de_nsvp_m2.size));
	DE_NOTI("de_vt_m1  = 0x%08x, %4dMB\n",p->de_vt_m1.base ,SIZE_MB(p->de_vt_m1.size));
	DE_NOTI("de_vt_m2  = 0x%08x, %4dMB\n",p->de_vt_m2.base ,SIZE_MB(p->de_vt_m2.size));
	DE_NOTI("de_hdr    = 0x%08x, %4dKB\n",p->de_hdr.base   ,SIZE_KB(p->de_hdr.size));
	DE_NOTI("be_fpp    = 0x%08x, %4dMB\n",p->be_fpp.base   ,SIZE_MB(p->be_fpp.size));
	DE_NOTI("be_frc0   = 0x%08x, %4dMB\n",p->be_frc0.base  ,SIZE_MB(p->be_frc0.size));
	DE_NOTI("be_frc1   = 0x%08x, %4dMB\n",p->be_frc1.base  ,SIZE_MB(p->be_frc1.size));
	DE_NOTI("be_frc2   = 0x%08x, %4dMB\n",p->be_frc2.base  ,SIZE_MB(p->be_frc2.size));
	DE_NOTI("be_wcg    = 0x%08x, %4dKB\n",p->be_wcg.base   ,SIZE_KB(p->be_wcg.size));
	DE_NOTI("fpp_info  = 0x%08x, %4dKB\n",p->fpp_info.base ,SIZE_KB(p->fpp_info.size));
	DE_NOTI("vdec_0    = 0x%08x, %4dMB\n",p->vdec_pool_0.base,SIZE_MB(p->vdec_pool_0.size));
	DE_NOTI("vdec_1    = 0x%08x, %4dMB\n",p->vdec_pool_1.base,SIZE_MB(p->vdec_pool_1.size));
	DE_NOTI("pe_db     = 0x%08x, %4dMB\n",p->pe_db.base  ,SIZE_MB(p->pe_db.size));
	DE_NOTI("pe_hdr    = 0x%08x, %4dMB\n",p->pe_hdr.base ,SIZE_MB(p->pe_hdr.size));
	DE_NOTI("fw_dnn    = 0x%08x, %4dMB\n",p->fw_dnn.base ,SIZE_MB(p->fw_dnn.size));
	DE_NOTI("fw_mcu1   = 0x%08x, %4dMB\n",p->fw_mcu1.base,SIZE_MB(p->fw_mcu1.size));
	DE_NOTI("fw_mcu2   = 0x%08x, %4dMB\n",p->fw_mcu2.base,SIZE_MB(p->fw_mcu2.size));
	DE_NOTI("fw_mcu3   = 0x%08x, %4dMB\n",p->fw_mcu3.base,SIZE_MB(p->fw_mcu3.size));
	DE_NOTI("fw_shared = 0x%08x, %4dMB\n",p->fw_shared.base,SIZE_MB(p->fw_shared.size));
	DE_NOTI("fw_mcu4   = 0x%08x, %4dMB\n",p->fw_mcu4.base,SIZE_MB(p->fw_mcu4.size));
	DE_NOTI("be_led    = 0x%08x, %4dKB\n",p->be_led.base   ,SIZE_KB(p->be_led.size));
	DE_NOTI("be_phdr   = 0x%08x, %4dKB\n",p->be_phdr.base  ,SIZE_KB(p->be_phdr.size));
	DE_NOTI("chipinfo  = 0x%08x, %4dMB\n",p->be_chipinfo.base,SIZE_MB(p->be_chipinfo.size));
	DE_NOTI("lne_pool  = 0x%08x, %4dMB\n",p->lne_pool.base,SIZE_MB(p->lne_pool.size));
	DE_NOTI("de_dbg_m1 = 0x%08x, %4dMB\n",p->de_dbg_m1.base,SIZE_MB(p->de_dbg_m1.size));
	DE_NOTI("de_dbg_m2 = 0x%08x, %4dMB\n",p->de_dbg_m2.base,SIZE_MB(p->de_dbg_m2.size));
	DE_NOTI("panel_type       = %d\n",p->model.panel_type);
	DE_NOTI("set_type         = %d\n",p->model.set_type);
	DE_NOTI("panel_maker      = %d\n",p->model.panel_maker);
	DE_NOTI("panel_resolution = %d\n",p->model.panel_resolution);
	DE_NOTI("panel_frame_rate = %d\n",p->model.panel_frame_rate);
	DE_NOTI("external_chip    = %d\n",p->model.external_chip);
	DE_NOTI("tcon_Scramble    = %d\n",p->model.tcon_Scramble);
	DE_NOTI("panel_carry_over = %d\n",p->model.panel_carry_over);
	DE_NOTI("vx1_byte         = %d\n",p->model.vx1_byte);
	DE_NOTI("sys_time         = 0x%08x, %4dKB\n",p->shared_mem_info.sys_time.base ,SIZE_KB(p->shared_mem_info.sys_time.size));
	DE_NOTI("sys_time_diff    = 0x%08x, %4dKB\n",p->shared_mem_info.sys_time_diff.base ,SIZE_KB(p->shared_mem_info.sys_time_diff.size));
	DE_NOTI("video_delay_info = 0x%08x, %4dKB\n",p->shared_mem_info.video_delay_info.base ,SIZE_KB(p->shared_mem_info.video_delay_info.size));
	DE_NOTI("de_gps           = 0x%08x, %4dKB\n",p->shared_mem_info.de_gps.base ,SIZE_KB(p->shared_mem_info.de_gps.size));
	DE_NOTI("######################################\n");
}

static void _resume_tag_info(void)
{
	UINT32 						*pTagBase = NULL;
	UINT32 tag_size = 0;
	DE_REG_M23_IPC_SYSTEM_T		fw_tag_info;

	if (sizeof(DE_REG_M23_IPC_SYSTEM_T) < DTVSOC_IPC_TOTAL_SIZE)
	{
		tag_size = sizeof(DE_REG_M23_IPC_SYSTEM_T);
	}
	else
	{
		tag_size = DTVSOC_IPC_TOTAL_SIZE;
	}

	memcpy(&fw_tag_info, &g_Mem_Info, tag_size);

	// tagging magic , fw base and frame base
	pTagBase = (UINT32*)ioremap(DE_IPC_GEN_M23_BASE, tag_size);
	if(pTagBase)
	{
		memcpy(pTagBase, &fw_tag_info, tag_size);
		wmb();
		_print_tag_info(&fw_tag_info, tag_size);
		iounmap((void*)pTagBase);
	}

}

static void _backup_mem_sys_info(DE_REG_M23_IPC_SYSTEM_T *tag_info)
{
	LX_DE_MEM_SYS_INFO_T *p = &g_Mem_Sys_Info;

	if (!tag_info)	return;

	p->de_prew.base      = tag_info->de_svp_m0.base;
	p->de_prew.size      = tag_info->de_svp_m0.size;
	p->de_frm_m1.base    = tag_info->de_svp_m1.base;
	p->de_frm_m1.size    = tag_info->de_svp_m1.size;
	p->de_frm_m2.base    = tag_info->de_svp_m2.base;
	p->de_frm_m2.size    = tag_info->de_svp_m2.size;
	p->de_vt_m1.base     = tag_info->de_vt_m1.base;
	p->de_vt_m1.size     = tag_info->de_vt_m1.size;
	p->de_vt_m2.base     = tag_info->de_vt_m2.base;
	p->de_vt_m2.size     = tag_info->de_vt_m2.size;
	p->de_hdr.base       = tag_info->de_hdr.base;
	p->de_hdr.size       = tag_info->de_hdr.size;
	p->vdec_pool_0.base  = tag_info->vdec_pool_0.base;
	p->vdec_pool_0.size  = tag_info->vdec_pool_0.size;
	p->vdec_pool_1.base  = tag_info->vdec_pool_1.base;
	p->vdec_pool_1.size  = tag_info->vdec_pool_1.size;
	p->de_gps.base       = tag_info->shared_mem_info.de_gps.base;
	p->de_gps.size       = tag_info->shared_mem_info.de_gps.size;
	p->de_gps_crc.base   = 0;//not support
	p->de_gps_crc.size   = 0;//not support
}

static void _set_tag_info(void)
{
#define SYSTEM_MAGIC_WORD           0xDECAFE
	UINT32						opt = 0;
	DE_REG_M23_IPC_SYSTEM_T		fw_tag_info;
	UINT64 hma_addr = 0;
	UINT32 hma_size = 0;
	UINT32 tag_size = 0;

	do {
		if (sizeof(DE_REG_M23_IPC_SYSTEM_T) < DTVSOC_IPC_TOTAL_SIZE)
		{
			tag_size = sizeof(DE_REG_M23_IPC_SYSTEM_T);
		}
		else
		{
			tag_size = DTVSOC_IPC_TOTAL_SIZE;
		}

		de_cfg_m23_get_hw_opt(&opt);

		memset(&fw_tag_info, 0, tag_size);
		fw_tag_info.system_info.magic_word = SYSTEM_MAGIC_WORD;

#ifdef USE_VIDEO_FOR_FPGA
		fw_tag_info.system_info.asic = 2/*1:ASIC,2:FPGA*/;
#else
		fw_tag_info.system_info.asic = 1/*1:ASIC,2:FPGA*/;
#endif
		if ( lx_chip_rev() >= LX_CHIP_REV(M23,A1) ) {
			fw_tag_info.system_info.chip_version = 1; // A0:0, A1:1
		}
		fw_tag_info.model.u32Data  = opt;

		fw_tag_info.fw_mcu0.base   = g_fw_mcu0.base;
		fw_tag_info.fw_mcu0.size   = g_fw_mcu0.size;
#ifdef USE_VIDEO_FOR_FPGA
		fw_tag_info.de_svp_m0.base = 0;
		fw_tag_info.de_svp_m0.size = 0;
#else
		fw_tag_info.de_svp_m0.base = g_de_svp_m0.base;
		fw_tag_info.de_svp_m0.size = g_de_svp_m0.size;
#endif

		fw_tag_info.de_svp_m1.base = g_de_svp_m1.base;
		fw_tag_info.de_svp_m1.size = g_de_svp_m1.size;
		fw_tag_info.de_svp_m2.base = g_de_svp_m2.base;
		fw_tag_info.de_svp_m2.size = g_de_svp_m2.size;
		fw_tag_info.de_nsvp_m1.base = g_de_nsvp_m1.base;
		fw_tag_info.de_nsvp_m1.size = g_de_nsvp_m1.size;
		fw_tag_info.de_nsvp_m2.base = g_de_nsvp_m2.base;
		fw_tag_info.de_nsvp_m2.size = g_de_nsvp_m2.size;
		fw_tag_info.de_vt_m1.base  = g_de_vt_m1.base;
		fw_tag_info.de_vt_m1.size  = g_de_vt_m1.size;
		fw_tag_info.de_vt_m2.base  = g_de_vt_m2.base;
		fw_tag_info.de_vt_m2.size  = g_de_vt_m2.size;

		fw_tag_info.de_hdr.base    = g_de_hdr.base;
		fw_tag_info.de_hdr.size    = g_de_hdr.size;

		fw_tag_info.be_fpp.base    = g_be_fpp.base;
		fw_tag_info.be_fpp.size    = g_be_fpp.size;
		fw_tag_info.be_frc0.base   = g_be_frc0.base;
		fw_tag_info.be_frc0.size   = g_be_frc0.size;
		fw_tag_info.be_frc1.base   = g_be_frc1.base;
		fw_tag_info.be_frc1.size   = g_be_frc1.size;
		fw_tag_info.be_frc2.base   = g_be_frc2.base;
		fw_tag_info.be_frc2.size   = g_be_frc2.size;
		fw_tag_info.be_wcg.base    = g_be_wcg.base;
		fw_tag_info.be_wcg.size    = g_be_wcg.size;
		fw_tag_info.be_led.base    = g_be_led.base;
		fw_tag_info.be_led.size    = g_be_led.size;
		fw_tag_info.be_phdr.base   = g_be_phdr.base;
		fw_tag_info.be_phdr.size   = g_be_phdr.size;
		fw_tag_info.be_chipinfo.base = g_chipinfo.base;
		fw_tag_info.be_chipinfo.size = g_chipinfo.size;

		fw_tag_info.pe_db.base     = g_pe_db.base;
		fw_tag_info.pe_db.size     = g_pe_db.size;
		fw_tag_info.pe_hdr.base    = g_pe_hdr.base;
		fw_tag_info.pe_hdr.size    = g_pe_hdr.size;

		fw_tag_info.fw_dnn.base    = g_fw_dnn.base;
		fw_tag_info.fw_dnn.size    = g_fw_dnn.size;
		fw_tag_info.fw_mcu1.base   = g_fw_mcu1.base;
		fw_tag_info.fw_mcu1.size   = g_fw_mcu1.size;
		fw_tag_info.fw_mcu2.base   = g_fw_mcu2.base;
		fw_tag_info.fw_mcu2.size   = g_fw_mcu2.size;
		fw_tag_info.fw_mcu3.base   = g_fw_mcu3.base;
		fw_tag_info.fw_mcu3.size   = g_fw_mcu3.size;
		fw_tag_info.fw_shared.base = g_fw_shared.base;
		fw_tag_info.fw_shared.size = g_fw_shared.size;
		fw_tag_info.fw_mcu4.base   = g_fw_mcu4.base;
		fw_tag_info.fw_mcu4.size   = g_fw_mcu4.size;

		fw_tag_info.de_dbg_m1.base = g_de_dbg_m1.base;
		fw_tag_info.de_dbg_m1.size = g_de_dbg_m1.size;
		fw_tag_info.de_dbg_m2.base = g_de_dbg_m2.base;
		fw_tag_info.de_dbg_m2.size = g_de_dbg_m2.size;

		fw_tag_info.fpp_info.base  = g_fw_shared.base + VIDEO_M23_FW_SHARED_OFST_FPP;
		fw_tag_info.fpp_info.size  = VIDEO_M23_FW_SHARED_SIZE_FPP;

		fw_tag_info.shared_mem_info.video_delay_info.base = g_fw_shared.base + VIDEO_M23_FW_SHARED_OFST_DLY;
		fw_tag_info.shared_mem_info.video_delay_info.size = VIDEO_M23_FW_SHARED_SIZE_DLY;

		fw_tag_info.shared_mem_info.de_gps.base = g_fw_shared.base + VIDEO_M23_FW_SHARED_OFST_GPS;
		fw_tag_info.shared_mem_info.de_gps.size = VIDEO_M23_FW_SHARED_SIZE_GPS;

		if ( 0 == hma_pool_info ("pqe-lne", (phys_addr_t *)&hma_addr, &hma_size) )
		{
			fw_tag_info.lne_pool.base = (UINT32)(hma_addr & 0xFFFFFFFF);
			fw_tag_info.lne_pool.size = hma_size;
		}

		do {
			UINT64 pool_base;
			UINT32 pool_size;
			UINT64 vdec_base[4] = {0,0,0,0};
			UINT32 vdec_size[4] = {0,0,0,0};
			UINT32 i = 0, valid_i = 0, min_i = 0, max_i = 0;
			UINT64 pool_start, pool_end;
			const char *vdec_pool_str_table[] = {"vpb","vcma","vdec","cpb"};

			for (i=0; i<4; i++) {
				if ( 0 == hma_pool_info (vdec_pool_str_table[i], (phys_addr_t *)&pool_base, &pool_size)) {
					if (pool_base > 0 && pool_size > 0) {
						DE_REG_M23_NOTI_BACKUP("[%d]%-5s:[%d]0x%08x,%dMB\n",i,vdec_pool_str_table[i],valid_i,(UINT32)(pool_base & 0xFFFFFFFF),pool_size>>20);
						vdec_base[valid_i] = pool_base;
						vdec_size[valid_i] = pool_size;
						valid_i++;
					}
				}
			}

			if (valid_i == 0) {
				DE_REG_M23_NOTI_BACKUP("no valid vdec_pool : skip\n");
				break;
			}

			if (valid_i > 1) {
				for (i = 1; i < valid_i; i++) {
					if (vdec_base[min_i] > vdec_base[i]) {
						min_i = i;
					}
					if (vdec_base[max_i] < vdec_base[i]) {
						max_i = i;
					}
				}
			}

			pool_start = vdec_base[min_i];
			pool_end = vdec_base[max_i] + vdec_size[max_i];

			hma_addr = pool_start;
			hma_size = (pool_end > pool_start)? (pool_end - pool_start):0;

			DE_REG_M23_NOTI_BACKUP("vdec_pool:0x%08x ~ 0x%08x (%dMB)\n",(UINT32)(pool_start & 0xFFFFFFFF),(UINT32)(pool_end & 0xFFFFFFFF),hma_size>>20);

			fw_tag_info.vdec_pool_0.base = (UINT32)(hma_addr & 0xFFFFFFFF);
			fw_tag_info.vdec_pool_0.size = hma_size;

			lpAddr_win_update	= (LX_DE_VIDEO_DELAY_INFO_MEM_T *)vmap_phys(fw_tag_info.shared_mem_info.video_delay_info.base,  fw_tag_info.shared_mem_info.video_delay_info.size);
		} while(0);

		memcpy(&g_Mem_Info, &fw_tag_info, tag_size);
		_backup_mem_sys_info(&fw_tag_info);
	}while(0);
}

int DE_REG_M23_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char						*lpAddr = NULL;
	LX_MEMCFG_T					*pFwMem = NULL;
	BOOLEAN						run_stall = 0;
	UINT32						fwBaseAddr;
	UINT32 						fwSize;
	UINT32						fwBaseOfst;

	do {
		CHECK_KNULL(pstParams);

		DE_REG_M23_NOTI_BACKUP("fw_dl start(fw:%d)(cfg:%d)(size:%d)\n",pstParams->inx,pstParams->cfg,pstParams->size)

		#if 0	//not used
		if (pstParams->cfg==DE_FW_CFG_STOP_FIRMWARE)
		{
			if (pstParams->inx==0)
			{
				DE_IPC_M23_Wr(ext_intr_enable,0x0);
				DE_IPC_M23_WrFL(ext_intr_enable);
				DE_IPC_M23_Wr(int_intr_enable,0x0);
				DE_IPC_M23_WrFL(int_intr_enable);

				DE_IPC_M23_RdFL(set_reg_ctrl0);
				DE_IPC_M23_Wr01(set_reg_ctrl0, p_debug_enable, 1);
				DE_IPC_M23_Wr01(set_reg_ctrl0, soft_reset, 1);
				DE_IPC_M23_Wr01(set_reg_ctrl0, run_stall, 1);
				DE_IPC_M23_WrFL(set_reg_ctrl0);

				DE_IPC_M23_Wr(ext_intr_enable,0x0);
				DE_IPC_M23_WrFL(ext_intr_enable);
				DE_IPC_M23_Wr(int_intr_enable,0x0);
				DE_IPC_M23_WrFL(int_intr_enable);

				DE_REG_M23_NOTI_BACKUP("fw_dl skip (stall on, reset)\n");
			}
			break;
		}
		#endif

		switch (pstParams->inx)
		{
			case 0 :
				pFwMem = &g_fw_mcu0;
				fwBaseOfst = USE_VIDEO_MCU_ROM_FW0_OFSET;
				break;
			case 1 :
			case 2 :
			case 3 :
			case 4 :
			default:
				pFwMem = NULL;
				break;
		}

		if (pFwMem==NULL)	{DE_REG_M23_NOTI_BACKUP("fw_dl not support(fw:%d)\n",pstParams->inx);break;}
		if (!pFwMem->base)	{DE_REG_M23_NOTI_BACKUP("fw_dl skip(base0)(fw:%d)\n",pstParams->inx);break;}
		if (!pFwMem->size)	{DE_REG_M23_NOTI_BACKUP("fw_dl skip(size0)(fw:%d)\n",pstParams->inx);break;}

		switch (pstParams->inx)
		{
			case 0 :
				DE_IPC_M23_RdFL(set_reg_ctrl0);
				DE_IPC_M23_Rd01(set_reg_ctrl0, run_stall, run_stall);

				// do not check run_stall status for re-download
				//if (!run_stall) break;
				DE_IPC_M23_Wr01(set_reg_ctrl0, run_stall, 1);
				// removed DE_IPC_M23_Wr01(set_reg_ctrl0, mcu_sw_reset, 0);
				DE_IPC_M23_WrFL(set_reg_ctrl0);
				break;
			case 1 :
			default:
				break;
		}

		if (pstParams->inx==0)	_resume_tag_info();

		do {
			fwBaseAddr = pFwMem->base;
			fwBaseOfst = GET_RDUP(fwBaseOfst, 4);
			fwSize = pstParams->size + fwBaseOfst;
			fwSize  = GET_RDUP(fwSize, 4);

			DE_REG_M23_NOTI_BACKUP("fw_dl load(fw%d)(addr:0x%08x+0x%x)(size:%d)\n",pstParams->inx,fwBaseAddr,fwBaseOfst,fwSize);

			if (pFwMem->size < fwSize)
			{
				DE_REG_M23_NOTI_BACKUP("fw_dl skip loading(abnormal size)\n");
				break;
			}

			if (pstParams->cfg==DE_FW_CFG_CPY_TO_DDR_SKIP)
			{
				DE_REG_M23_NOTI_BACKUP("fw_dl skip loading(run fw)\n");
				break;
			}

			lpAddr	= (char *)vmap_phys(fwBaseAddr, fwSize);

			CHECK_KNULL(lpAddr);
			if (pstParams->cfg==DE_FW_CFG_COPY_BIN_TO_DDR)
			{
				struct file *vsc_filp = (struct file *)pstParams->pData;
				vsc_filp->f_pos = 0;
				ret = kernel_read(vsc_filp, (char*)((uintptr_t)lpAddr + (uintptr_t)fwBaseOfst),pstParams->size,&vsc_filp->f_pos);//vfs_read(legacy)
				DE_REG_M23_NOTI_BACKUP("fw_dl kernel_read ret(%d)\n",ret);
				ret = (ret<0)? RET_ERROR:RET_OK;
			}
			else if (pstParams->cfg==DE_FW_CFG_COPY_USR_TO_DDR)
			{
				ret = copy_from_user((char*)((uintptr_t)lpAddr + (uintptr_t)fwBaseOfst), pstParams->pData, pstParams->size);
				DE_REG_M23_NOTI_BACKUP("fw_dl copy_from_user ret(%d)\n",ret);
			}
			else
			{
				memcpy((char*)((uintptr_t)lpAddr + (uintptr_t)fwBaseOfst), pstParams->pData, pstParams->size);
			}
			wmb();
			if (lpAddr) vunmap_phys((void*)lpAddr);
		} while(0);

		switch (pstParams->inx)
		{
			case 0 :
				//if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
				DE_IPC_M23_FLWr(srom_boot_map1, fwBaseAddr);
				DE_IPC_M23_FLWr(srom_boot_map2, fwBaseAddr);
				DE_IPC_M23_Wr01(set_reg_ctrl0, start_vector_sel, 0);
				// removed DE_IPC_M23_Wr01(set_reg_ctrl0, mcu_sw_reset, 1);

				msleep(1); // wait ddr to ddr transition
				DE_IPC_M23_Wr01(set_reg_ctrl0, p_debug_enable, 1);
				DE_IPC_M23_Wr01(set_reg_ctrl0, run_stall, 0);
				DE_IPC_M23_WrFL(set_reg_ctrl0);
				break;
			case 1 :
			case 2 :
			case 3 :
			case 4 :
			default :
				break;
		}

		DE_REG_M23_NOTI_BACKUP("fw_dl done(fw:%d)\n",pstParams->inx);

	} while (0);

	return ret;
}

int DE_REG_M23_FW_GetMaxNum(UINT32 *pMaxNum)
{
	if (!pMaxNum)	return RET_ERROR;

	if ( lx_chip_rev() >= LX_CHIP_REV(M23,A0) )
	{
		*pMaxNum = USE_VIDEO_MCU_ROM_FW_MAX_NUM;
	}
	else
	{
		return RET_ERROR;
	}

	return RET_OK;
}

int DE_REG_M23_FW_Verify(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char						*lpAddr = NULL;
	LX_MEMCFG_T					*pFwMem = NULL;
	BOOLEAN						run_stall = 0;
	UINT32						fwBaseAddr;
	UINT32 						fwSize;
	UINT32                      i;
	UINT32                      mismatch_count = 0;
	char temp;

	do {
		CHECK_KNULL(pstParams);

		DE_PRINT("Verify start\n");

		DE_IPC_M23_RdFL(set_reg_ctrl0);
		DE_IPC_M23_Rd01(set_reg_ctrl0, run_stall, run_stall);
		DE_IPC_M23_Wr01(set_reg_ctrl0, run_stall, 1);
		DE_IPC_M23_WrFL(set_reg_ctrl0);

		pFwMem = &g_fw_mcu0;

		CHECK_KNULL(pFwMem);

		fwBaseAddr = pFwMem->base;
		fwSize     = pFwMem->size;
		if (fwSize <  pstParams->size) fwSize =  pstParams->size;
		fwSize  = GET_RDUP(fwSize, 4);
		lpAddr	= (char *)vmap_phys((fwBaseAddr+USE_VIDEO_MCU_ROM_FW0_OFSET), pstParams->size);

		CHECK_KNULL(lpAddr);

		for(i=0;i<pstParams->size;i++)
		{
			temp = lpAddr[i];
			rmb();
			if(temp != pstParams->pData[i])
			{
				mismatch_count++;
				if(mismatch_count <= 4)
				{
					DE_ERROR("[%d]  : origin 0x%02x , read 0x%02x\n", i, pstParams->pData[i], temp);
				}
			}
		}

		DE_IPC_M23_RdFL(set_reg_ctrl0);
		DE_IPC_M23_Rd01(set_reg_ctrl0, run_stall, run_stall);
		DE_IPC_M23_Wr01(set_reg_ctrl0, run_stall, 0);
		DE_IPC_M23_WrFL(set_reg_ctrl0);

		if(mismatch_count) ret = RET_ERROR;

		DE_PRINT("Verify done.  base[0x%08x] size[%d] mismatch count [%d]\n",\
				fwBaseAddr, fwSize, mismatch_count);
		if (lpAddr) vunmap_phys((void*)lpAddr);
	} while(0);

	return ret;
}

int DE_REG_M23_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetEdgeCrop(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

	return ret;
}

BOOLEAN DE_REG_M23_IPCisAlive(void)
{
	BOOLEAN isFwDownloaded = FALSE;
	DE_IPC_M23_FLRf(int_intr_enable, ipc_interrupt_enable_mcu, isFwDownloaded);

	return GET_BITS(isFwDownloaded, VIDEO_IPC_INTERRUPT_ARM_BIT, 1);
}

int DE_REG_M23_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = g_fw_shared.base + VIDEO_M23_FW_SHARED_OFST_VTM;
	} while (0);

	return ret;
}

int DE_REG_M23_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address    = g_de_vt_m2.base;
		pstParams->y_frame[0] = g_de_vt_m2.base;
		pstParams->c_frame[0] = g_de_vt_m2.base;
	} while (0);

	return ret;
}

int DE_REG_M23_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = g_fw_shared.base + VIDEO_M23_FW_SHARED_OFST_VTV; // base of VTV shared mem
	} while (0);

	return ret;
}

int DE_REG_M23_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * control vsync interrupt from de hardware
 */
int DE_REG_M23_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en)
{
	int ret = RET_OK;

	return ret;
}

/**
 * get irq number
 */
int DE_REG_M23_GetIrqNum(UINT32 mcu_id, UINT32 *ipc_irq_num, UINT32 *sync_irq_num)
{
	switch(mcu_id)
	{
		case 0:
			*ipc_irq_num  = M23_IRQ_IPC_BCPU;
			*sync_irq_num = M23_IRQ_DE_BCPU;
			break;
		case 1:
			break;
		default:
			return RET_ERROR;
			break;
	}
	return RET_OK;
}

/**
 * set debug data
 */
int DE_REG_M23_SetDebug(LX_DE_SET_DBG_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->config_type) {
			case LX_DE_CONFIG_TYPE_ALL :
			case LX_DE_CONFIG_TYPE_DISPLAY_MIRROR:
				g_Display_mirror_M23 = pstParams->display_mirror;
				break;
			default :
				break;
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SYS_STATUS_ALL :
			case LX_DE_SYS_STATUS_DISPALY_MIRROR:
				pstParams->display_mirror = g_Display_mirror_M23;
				break;
			default :
				break;
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SRC_STATUS_ALL :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_M23[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_M23[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB]	 = g_WinsrcMap_M23[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_M23[LX_DE_WIN_SUB];

				pstParams->operType= g_SrcOperType_M23;
				pstParams->operCtrlFlag = g_SrcOperCtrlFlag_M23;

				pstParams->subOperType =  g_SrcSubOperType_M23;
				pstParams->subOperCtrlFlag = g_SrcSubOperCtrlFlag_M23;
				break;
			case LX_DE_SRC_STATUS_INPUT_SRC :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_M23[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_M23[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB] = g_WinsrcMap_M23[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_M23[LX_DE_WIN_SUB];
				break;
			case LX_DE_SRC_STATUS_OPER :
				pstParams->operType  = g_SrcOperType_M23;
				pstParams->operCtrlFlag = g_SrcOperCtrlFlag_M23;
				break;

			case LX_DE_SRC_STATUS_SUB_OPER :
				pstParams->subOperType =  g_SrcSubOperType_M23;
				pstParams->subOperCtrlFlag = g_SrcSubOperCtrlFlag_M23;
				break;

			case LX_DE_SRC_STATUS_VDEC_INFO :
				{
					UINT32 frame_rate_residual;
					UINT32 frame_rate_div;
					UINT32 framerate;
					UINT32 vdec_port;
					UINT32 scan;
					volatile LX_DE_VDEC_IPC_REG_T *p_vdec_ipc_reg;

					vdec_port = pstParams->inSrcPort[LX_DE_WIN_MAIN];
					if(vdec_port > 3)
					{
						DE_ERROR("invalid vdec port");
						vdec_port = 0;
					}

					p_vdec_ipc_reg = gDE_VDEC_M23[vdec_port];
					scan = p_vdec_ipc_reg->display_info.display_mode;

					frame_rate_residual	= p_vdec_ipc_reg->frame_rate.frame_rate_residual;
					frame_rate_div		= (p_vdec_ipc_reg->frame_rate.frame_rate_div > 0)?p_vdec_ipc_reg->frame_rate.frame_rate_div:1;
					framerate			= (frame_rate_residual * 100)/frame_rate_div;

					pstParams->vdecInfo.h_size = p_vdec_ipc_reg->picture_size.width;
					pstParams->vdecInfo.v_size = p_vdec_ipc_reg->picture_size.height;
					pstParams->vdecInfo.h_start = 0;
					pstParams->vdecInfo.v_start = 0;
					pstParams->vdecInfo.isProg = (scan==3)?1:0;
					pstParams->vdecInfo.v_freq = framerate;
					pstParams->vdecInfo.svp = p_vdec_ipc_reg->display_info.svp;
					pstParams->vdecInfo.par_width  = p_vdec_ipc_reg->par.par_width;
					pstParams->vdecInfo.par_height = p_vdec_ipc_reg->par.par_height;
					pstParams->vdecInfo.afd = p_vdec_ipc_reg->frame_idx.active_format_desc;

					if(pstParams->win_id == 1)
					{
						vdec_port = pstParams->inSrcPort[LX_DE_WIN_SUB];
						vdec_port = vdec_port>0?1:0;
						p_vdec_ipc_reg = gDE_VDEC_M23[vdec_port];
						pstParams->vdecInfo.par_width  = p_vdec_ipc_reg->par.par_width;
						pstParams->vdecInfo.par_height = p_vdec_ipc_reg->par.par_height;
						pstParams->vdecInfo.afd = p_vdec_ipc_reg->frame_idx.active_format_desc;
						pstParams->vdecInfo.h_size = p_vdec_ipc_reg->picture_size.width;
						pstParams->vdecInfo.v_size = p_vdec_ipc_reg->picture_size.height;
					}

					/*DE_NOTI("port->%d : h/v[%d/%d] scan[%d] fr[%d]", vdec_port, \
						pstParams->vdecInfo.h_size, pstParams->vdecInfo.v_size, \
						pstParams->vdecInfo.isProg, pstParams->vdecInfo.v_freq);*/
				}
				break;

			case LX_DE_SRC_STATUS_MAX :
			default :
				BREAK_WRONG(pstParams->status_type);
		}
	} while (0);

	return ret;


}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_OPER_CONFIG_T	type = LX_DE_OPER_ONE_WIN;
	UINT16 flag = 0;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_OPER_ONE_WIN :
				type = LX_DE_OPER_ONE_WIN;
				break;

			case LX_DE_OPER_TWO_WIN :
				if(pstParams->multiCtrl != FALSE)		type = LX_DE_OPER_TWO_WIN;
				flag = pstParams->multiCtrl;
				break;
			case LX_DE_OPER_3D :
				if(pstParams->ctrl3D.run_mode != LX_DE_3D_RUNMODE_OFF && pstParams->ctrl3D.run_mode != LX_DE_3D_RUNMODE_MAX)
				{
					type = LX_DE_OPER_3D;
					flag = pstParams->ctrl3D.in_img_fmt;
				}
				break;

			case LX_DE_OPER_UD :
				if(pstParams->udCtrl != LX_DE_UD_OFF && pstParams->udCtrl != LX_DE_UD_MAX)
				{
					type = LX_DE_OPER_UD;
					flag = pstParams->udCtrl;
				}
				break;

			case LX_DE_OPER_VENC :
			case LX_DE_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}

		g_SrcOperType_M23 = type;
		g_SrcOperCtrlFlag_M23 = flag;
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Set Information from which source is comming
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT16 flag = 0;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_SUB_OPER_OFF :
				g_SrcSubOperType_M23 = LX_DE_SUB_OPER_OFF;
				break;
			case LX_DE_SUB_OPER_CAPTURE:
				g_SrcSubOperType_M23 = LX_DE_SUB_OPER_CAPTURE;
				flag = pstParams->capture_enable;
				break;
			case LX_DE_SUB_OPER_VENC:
				g_SrcSubOperType_M23 = LX_DE_SUB_OPER_VENC;
				flag = pstParams->vencCtrl.bOnOff;
				break;
			case LX_DE_SUB_OPER_SCART_OUT:
				g_SrcSubOperType_M23 = LX_DE_SUB_OPER_SCART_OUT;
				flag = 1;
				break;
			case LX_DE_SUB_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}
	} while (0);

	g_SrcSubOperCtrlFlag_M23 = flag;
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get fir coefficient for cvi
 *
 * @param arg [IN] address of buffer to be carried
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir)
{
	int ret = RET_OK;
	int i = 0;
	// CVI FIR coefficient for Y - 11 Tap,Cbcr - 11 Tap
	UINT16 coef_FIR_Y_Normal[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_Y_Double[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_Y_Quad[]   = {64, 56, 34, 12, 0, -6, 0, 0};	// 55 >> 56 --> sum 254 >> 256
	UINT16 coef_FIR_M23_CVD_CbCr_Normal[] = {160, 49, -1, 0, 0, 0};// CVI FIR Filter for 1 pixel & 422
	UINT16 coef_FIR_CbCr_Normal[] = {128, 74, 0, -11, 0, 1};// CVI FIR Filter for 1 pixel & 422
	UINT16 coef_FIR_CbCr_Double[] = {160, 0, 49, 0, -1, 0};	// 55 >> 56 --> sum 254 >> 256
	UINT16 coef_FIR_CbCr_Quad[] = {64, 56, 34, 12, 0, -6};

	do {
		CHECK_KNULL(pstParams);

		fir->cvi_channel = pstParams->cvi_channel;

		switch (pstParams->sampling) {
			case LX_DE_CVI_NORMAL_SAMPLING:
				fir->isEnable = TRUE;
				for (i=0; i<NUM_OF_CVI_FIR_COEF; i++) {
					fir->fir_coef[i] = coef_FIR_Y_Normal[i];

					if (i<(NUM_OF_CVI_FIR_COEF-2)) {
						if (pstParams->cvi_input_src == LX_DE_CVI_SRC_ATV || pstParams->cvi_input_src == LX_DE_CVI_SRC_CVBS)
							fir->fir_coef_CbCr[i] = coef_FIR_M23_CVD_CbCr_Normal[i];
						else
							fir->fir_coef_CbCr[i] = coef_FIR_CbCr_Normal[i];
					}
				}
				break;

			case LX_DE_CVI_DOUBLE_SAMPLING:
				fir->isEnable = TRUE;
				for (i=0; i<NUM_OF_CVI_FIR_COEF; i++) {
					fir->fir_coef[i] = coef_FIR_Y_Double[i];
					if (i<(NUM_OF_CVI_FIR_COEF-2))
						fir->fir_coef_CbCr[i] = coef_FIR_CbCr_Double[i];
				}
				break;

			case LX_DE_CVI_QUAD_SAMPLING:
				fir->isEnable = TRUE;
				for (i=0; i<NUM_OF_CVI_FIR_COEF; i++) {
					fir->fir_coef[i] = coef_FIR_Y_Quad[i];
					if (i<(NUM_OF_CVI_FIR_COEF-2))
						fir->fir_coef_CbCr[i] = coef_FIR_CbCr_Quad[i];
				}
				break;

			default:
				BREAK_WRONG(pstParams->sampling);
		}
	} while (0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set hdmi in-port for cvi
 *
 * @param arg [IN] hdmi port num
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams)
{
	int ret = RET_OK;

	g_HdmiPort_M23[pstParams->win_id] = pstParams->port_num;  // assign from vp_kadp
	DE_TRACE("win-hdmi map [%d / %d]", pstParams->win_id, pstParams->port_num);

	return ret;
}

int DE_REG_M23_GetCapacity(LX_DE_CAPACITY_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_GetLocalMute(UINT32 *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_SetMemByCma(char* mem_name)
{
	int ret = RET_OK;
	UINT32 base_addr = 0;
	int alloc_size = 0;
	enum hma_pool_type pool_type;
	LX_MEMCFG_T *p_mem;

	if (strcmp(mem_name, "de-dbgbuf") == 0)
	{
		#if 0	//not used
		if (g_de_dbg_m1.base && g_de_dbg_m1.size)
		{
			alloc_size = g_de_dbg_m1.size;
			base_addr  = g_de_dbg_m1.base;
			if(hma_pool_register_type("debug0",base_addr,alloc_size,CMA_POOL) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("register: debug0 base[0x%08X] size = %dKB\n", base_addr, alloc_size/1024);
		}
		if (g_de_dbg_m2.base && g_de_dbg_m2.size)
		{
			alloc_size = g_de_dbg_m2.size;
			base_addr  = g_de_dbg_m2.base;
			if(hma_pool_register_type("debug1",base_addr,alloc_size,CMA_POOL) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("register: debug1 base[0x%08X] size = %dKB\n", base_addr, alloc_size/1024);
		}
		#endif
	}
	#if 0	//not used
	else if(strcmp(mem_name, "de-dbgbuf-off") == 0)
	{
		hma_pool_unregister("debug0");
		DE_NOTI("unregister: debug0\n");
		hma_pool_unregister("debug1");
		DE_NOTI("unregister: debug1\n");
	}
	#endif
	else if(strcmp(mem_name, "de-btbuf") == 0)
	{
		#if 0	//not used
		if (g_de_svp_m1.base)
		{
			alloc_size = g_de_svp_m1.size;
			base_addr  = g_de_svp_m1.base;
			if (hma_pool_register_type("de-btbuf-m0", base_addr, alloc_size, CMA_POOL) < 0)
			{
			     ret = RET_ERROR;
			}
			DE_NOTI("g_de_svp_m1 base[0x%08X]  BT m0 buffer size = %dMB", base_addr, alloc_size/1024/1024);
			alloc_size = g_de_svp_m2.size;
			base_addr  = g_de_svp_m2.base;
			if (hma_pool_register_type("de-btbuf-m1", base_addr, alloc_size, CMA_POOL) < 0)
			{
			     ret = RET_ERROR;
			}
			DE_NOTI("g_de_svp_m2 base[0x%08X]  BT m1 buffer size = %dMB", base_addr, alloc_size/1024/1024);

			if(m23_de_debug_mem)
			{
				DE_NOTI("pre-alloc %dMB@%s for debug\n", alloc_size/1024/1024, mem_name);
			    hma_alloc(mem_name,  alloc_size, (1<<20));
			}
		}
		#endif
	}
	else if(strcmp(mem_name, "de-hdrbuf0") == 0)
	{
		if(g_de_hdr.base)
		{
			alloc_size = g_de_hdr.size;
			base_addr  = g_de_hdr.base;
			if(hma_pool_register_type("de-hdrbuf0",base_addr,alloc_size,HMA_POOL) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("g_de_hdr base[0x%08X] HDR buffer size = %dKB", base_addr, alloc_size/1024);
		}
	}
	else if(strcmp(mem_name, "de-vtgbuffer") == 0)
	{
		p_mem = &g_de_vt_m1;
		if (p_mem->base != 0 && p_mem->size > 0)
		{
			const char *pool_name = "de-vt-m0";
			pool_type = CMA_POOL;
			if (RET_OK == de_cfg_check_force_hma_pool(pool_name,pool_type,p_mem->base,p_mem->size))
			{
				pool_type = HMA_POOL;
			}

			if (hma_pool_register_type(pool_name,p_mem->base,p_mem->size,pool_type) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("%s base: 0x%08x, size: %d kB, type: %d(%s)\n",pool_name,p_mem->base,p_mem->size>>10,pool_type,(pool_type)? "cma":"hma");
		}

		p_mem = &g_de_vt_m2;
		if (p_mem->base != 0 && p_mem->size > 0)
		{
			const char *pool_name = "de-vt-m1";
			pool_type = CMA_POOL;
			if (RET_OK == de_cfg_check_force_hma_pool(pool_name,pool_type,p_mem->base,p_mem->size))
			{
				pool_type = HMA_POOL;
			}

			if (hma_pool_register_type(pool_name,p_mem->base,p_mem->size,pool_type) < 0)
			{
				ret = RET_ERROR;
			}
			DE_NOTI("%s base: 0x%08x, size: %d kB, type: %d(%s)\n",pool_name,p_mem->base,p_mem->size>>10,pool_type,(pool_type)? "cma":"hma");
		}
	}

	return ret;
}

int DE_REG_M23_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag)
{
	int ret = RET_OK;
	int size_m0,size_m1;
	int free_m0;

	if(strcmp(mem_name, "de-dbgbuf") == 0)
	{
		size_m0 = g_de_dbg_m1.size;

		if(flag)
		{
			hma_pool_status("debug0", hma_pool_status_free_size, &free_m0);
			DE_NOTI("debug0 = %dMB(%dMB)\n", size_m0>>20, free_m0>>20);

			if (dbg_paddr_m0 == 0 && free_m0 > 0)
			{
				if (size_m0 > free_m0)	size_m0 = free_m0;
				dbg_paddr_m0 = hma_alloc("debug0", size_m0, (1<<14));//align:16k
				DE_NOTI("hma_alloc debug0 = %dMB\n", size_m0>>20);
			}
		}
		else
		{
			if (dbg_paddr_m0 != 0)
			{
				hma_free("debug0", dbg_paddr_m0);
				DE_NOTI("hma_free debug0\n");
				dbg_paddr_m0 = 0;
			}
		}
	}
	else if(strcmp(mem_name, "de-vrbuf") == 0)
	{
		#if 0	//not used (SICDTV-13880)
		size_m0 = 60*1024*1024;

		if(flag)
		{
			LX_DE_SET_DELAY_BUFFER_T *pBuf_info = info;
			if(!pBuf_info)  { return -1; }
			/* hma alloc */
			if(vr_paddr_m0 != 0) { return -1; }
			vr_paddr_m0 = hma_alloc("debug0", size_m0, (1<<14));//align:16k
			if(vr_paddr_m0 == 0) { return -2; }
			DE_NOTI("hma_alloc: debug0 size = %dKB\n", size_m0/1024);

			pBuf_info->pool_size[0] = size_m0;
			pBuf_info->pool_base[0] = vr_paddr_m0;
			DE_NOTI("use shared-pool(from %s) : start = 0x%08X, size = %dMB", \
				"debug0", (UINT32)pBuf_info->pool_base[0], size_m0/1024/1024);
		}
		else
		{
			if(vr_paddr_m0 != 0)
			{
				hma_free("debug0", vr_paddr_m0);
				DE_NOTI("hma_free: debug0\n");
				DE_NOTI("free shared-pool(%s) : start = 0x%08X", \
					"debug0", (UINT32)vr_paddr_m0);
				vr_paddr_m0 = 0;
			}
		}
		#endif
	}
	else if(strcmp(mem_name, "de-btbuf") == 0)
	{
		if(flag)
		{
			LX_DE_SET_DELAY_BUFFER_T *pBuf_info = info;
			char *pool_name;
			if(!pBuf_info)  { return -1; }

#ifdef USE_VIDEO_FOR_FPGA
			size_m0 = g_de_svp_m0.size;
			pool_name = g_de_svp_m0.name;

			if(bt_paddr_m0 == 0) {
				bt_paddr_m0 = g_de_svp_m0.base;
			}
#else
			size_m0 = g_de_vdec_shared_size;
			pool_name = "vdec_shared";

			if(bt_paddr_m0 == 0) {
				bt_paddr_m0 = hma_alloc(pool_name, size_m0, (1<<14));//align:16k
			}
#endif
			pBuf_info->pool_size[0] = size_m0;
			pBuf_info->pool_base[0] = bt_paddr_m0;
			g_Mem_Sys_Info.vdec_pool_0.size = pBuf_info->pool_size[0];
			g_Mem_Sys_Info.vdec_pool_0.base = bt_paddr_m0;
			DE_NOTI("use shared-pool(from %s) : start = 0x%08X, size = %dMB", \
				pool_name, (UINT32)pBuf_info->pool_base[0], size_m0/1024/1024);

			if(bt_paddr_m0 == 0) { return -3; }
		}
		else
		{
			if(bt_paddr_m0 != 0)
			{
				DE_NOTI("free shared-pool : start = 0x%08X", (UINT32)bt_paddr_m0);
#ifdef USE_VIDEO_FOR_FPGA
#else
				hma_free("vdec_shared", bt_paddr_m0);
#endif
				bt_paddr_m0 = 0;
			}
		}
	}
	else if(strcmp(mem_name, "de-hdrbuf") == 0)
	{

	}
	else if(strcmp(mem_name, "de-vtgbuffer") == 0)
	{
		size_m0 = g_de_vt_m1_cma_size;
		size_m1 = g_de_vt_m2_cma_size;

		if(flag)
		{
			/* hma alloc */
			if(vtg_paddr_m0 != 0) { return -1; }
			vtg_paddr_m0 = hma_alloc("de-vt-m0", count*size_m0, (1<<14));//align:16k
			if(vtg_paddr_m0 == 0) { return -2; }
			vtg_paddr_m1 = hma_alloc("de-vt-m1", count*size_m1, (1<<14));//align:16k
			if(vtg_paddr_m1 == 0) { return -2; }
		}
		else
		{
			if(vtg_paddr_m0 != 0)
			{
				hma_free("de-vt-m0", vtg_paddr_m0);
				hma_free("de-vt-m1", vtg_paddr_m1);
				vtg_paddr_m0 = 0;
				vtg_paddr_m1 = 0;
			}
		}
		DE_NOTI("gVTG %s : start = 0x%08X/0x%08X, size = %dMB/%dMB", flag?"alloc":"free", \
			g_de_vt_m1.base, g_de_vt_m2.base,\
			count*size_m0/1024/1024, count*size_m1/1024/1024);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set multi window information
 *
 * @param arg [IN] control param
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetMultiWin(UINT32 *pstParams)
{
	int ret = RET_OK;

	g_QuadWin_M23 = (*pstParams==4)?TRUE:FALSE;

	DE_NOTI("multi window control for quad [%d]", *pstParams);

	return ret;
}

int DE_REG_M23_SetClockGate(CTOP_PQE_CG_M23_MODULE mod, BOOLEAN onOff)
{
	int ret = RET_OK;

	return ret;
}

//#define ADD_CLOCK_GATING
int DE_REG_M23_SetClockPath(BOOLEAN onOff)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_M23_GetLowDelayClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	*pstParams = g_Zero_delay_mode_M23;

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief set ctop clock for zero delay
 *
 * @param arg [IN] control param
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_SetLowDelayClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	ret = DE_REG_M23_SetClockPath((BOOLEAN)*pstParams);

	g_Zero_delay_mode_M23 = *pstParams; // 0:OFF, 1:5V_HPD, 2:CVI_INTR

	DE_NOTI("g_Zero_delay_mode_M23 = %d  (0:OFF, 1:5V_HPD, 2:CVI_INTR)", g_Zero_delay_mode_M23);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get shared mem for mmap
 *
 * @param arg [IN] page_offset, mem_info(start/end/size)
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_GetSharedMem(UINT32 page_offset, UINT32 **mem_info)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(mem_info);

		*mem_info[0] = g_fw_shared.base;
		*mem_info[1] = g_fw_shared.base + g_fw_shared.size;
		*mem_info[2] = g_fw_shared.size;

		DE_NOTI("base/end/size = 0x%08x/0x%08x/%d", *mem_info[0], *mem_info[1], *mem_info[2]/1024);
	} while(0);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief pre initialize before mem init
 *
 * @param eClk [IN]
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int DE_REG_M23_PreInit(void)
{
	return RET_OK;
}

int DE_REG_M23_GetFPPInfo(UINT32 *start_address)
{
	int ret = RET_OK;

	*start_address = g_fw_shared.base + VIDEO_M23_FW_SHARED_OFST_FPP;

	DE_NOTI(" start_address = 0x%08x , size = 0x%08x", *start_address, VIDEO_M23_FW_SHARED_SIZE_FPP);

	return ret;
}

int DE_REG_M23_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams)
{
	int ret = RET_OK;

	if(!pstParams) return RET_ERROR;

	memcpy(pstParams, &g_Mem_Sys_Info, sizeof(LX_DE_MEM_SYS_INFO_T));

	// for SVP (de_frm_m1 info is used for M1 svp in tz)
	//pstParams->de_frm_m1.base = pstParams->de_frm_m2.base;
	//pstParams->de_frm_m1.size = pstParams->de_frm_m2.size;

	return ret;
}

int DE_REG_M23_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f)
{
	int ret = RET_OK;
	UINT32 *lpAddr = NULL;
	UINT32 phys = g_Mem_Info.fpp_info.base + VIDEO_M23_FW_SHARED_OFST_FPP_DNN;// fpp_info.base + 32*1024
	// M23 phys = ?
	lpAddr	= (UINT32 *)vmap_phys(phys, 4 * 6);

	if (!lpAddr)
	{
		DE_ERROR("vmap fail");
		return RET_ERROR;
	}

	*a = lpAddr[0];
	*b = lpAddr[1];
	*c = lpAddr[2];
	*d = lpAddr[3];
	*e = lpAddr[4];
	*f = lpAddr[5];

//	DE_NOTI("phys = 0x%08X", phys);

	if (lpAddr) vunmap_phys(lpAddr);

	return ret;
}

int DE_REG_M23_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_MEM_T *pstParams)
{
	int ret = RET_OK;
	LX_DE_VIDEO_DELAY_INFO_T *lpAddr = NULL;
	LX_DE_VIDEO_DELAY_INFO_T *p;

	if(!pstParams) return RET_ERROR;
	if(g_Mem_Info.shared_mem_info.video_delay_info.base == 0 || g_Mem_Info.shared_mem_info.video_delay_info.size == 0) return RET_ERROR;

	//lpAddr	= (LX_DE_VIDEO_DELAY_INFO_T *)vmap_phys(g_Mem_Info.shared_mem_info.video_delay_info.base,  g_Mem_Info.shared_mem_info.video_delay_info.size);
	if(lpAddr_win_update==NULL)
	{
		return RET_ERROR;
	}
	p = (LX_DE_VIDEO_DELAY_INFO_T *)pstParams;
	p->win_id = lpAddr_win_update->owin_sync.win_id;
	p->delay = lpAddr_win_update->owin_sync.delay;
	p->rect.x = lpAddr_win_update->owin_sync.rect.x;
	p->rect.y = lpAddr_win_update->owin_sync.rect.y;
	p->rect.w = lpAddr_win_update->owin_sync.rect.w;
	p->rect.h = lpAddr_win_update->owin_sync.rect.h;

	if (lpAddr) vunmap_phys((void*)lpAddr);

	return ret;
}

#endif
/**  @} */
