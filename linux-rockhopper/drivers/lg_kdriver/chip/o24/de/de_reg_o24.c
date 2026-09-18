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

#ifdef USE_KDRV_CODES_FOR_O24
#include "de_kapi.h"
#include "de_def.h"
#include "de_prm_def.h"
#include "de_hal_def.h"
#include "de_cfg.h"
#include "de_drv.h"
#include "vsc_fw.h"

#include "de_cfg_o24.h"
#include "de_ipc_def_o24.h"
#include "de_int_def_o24.h"
#include "de_reg_def_o24.h"
#include "de_reg_o24.h"

#include "de_ipc_reg_o24.h"
#include "de_ctr_reg_o24.h"

//check values (SICDTV-10687)
#ifdef USE_CTOP_CODES_FOR_O24
#include "../sys/sys_regs.h"
#endif

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define USE_VIDEO_MCU_ROM_BASE_ADDR 0x50000000

/* fw0,fw1 */
#define USE_VIDEO_MCU_FW_MAX_NUM    2

#define DE_REG_O24_NOTI_BUF_MAX     100
#define DE_REG_O24_NOTI_STR_SIZE    64

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_REG_O24_NOTI_BACKUP(_fmt, args...)	\
	{\
		char _de_io_str_buf[DE_REG_O24_NOTI_STR_SIZE];\
		DE_NOTI(_fmt, ##args);\
		snprintf(_de_io_str_buf, DE_REG_O24_NOTI_STR_SIZE, _fmt, ##args);\
		DE_REG_O24_BackupTraceDataBuf(_de_io_str_buf);\
	}

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
#define NUM_OF_CVI_FIR_COEF 8
#define NUM_WIN_MAX	5

typedef struct {
	UINT32 sec;			///< sec
	UINT32 msec;		///< msec
	UINT32 usec;		///< usec
}
DE_REG_O24_NOTI_TIME_T;

typedef struct {
	DE_REG_O24_NOTI_TIME_T time;		///< time
	char str[DE_REG_O24_NOTI_STR_SIZE];	///< str
}
DE_REG_O24_NOTI_BUF_T;

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
DE_REG_O24_IPC_SYSTEM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC820D00 RW 0x0000_0000
	UINT32 height                 :14;//(13:0) active h (0 ~ 16383)
	UINT32 width                  :14;//(27:14) active w (0 ~ 16383)
	UINT32 vdisp_instance_number  :4; //(31:27) vdisp_instance_number
	};
}
DE_REG_O24_IPC_DAR_INFO_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC820D04 RW 0x0000_0000
	UINT32 par_height              :14;//(13:0) pixel aspect ratio of height (0 ~ 16383)
	UINT32 par_width               :14;//(27:14) pixel aspect ratio of width (0 ~ 16383)
	UINT32 active_format_desc      :4; //(31:27) active_format_desc 0:invalid, 1~f: MPEG2/H.264 AFD
	};
}
DE_REG_O24_IPC_DAR_INFO_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC820D08 RW 0x0000_0000
	UINT32 v_freq                  :16;//(15:0) v_freq : hz x 100 (if i input, x 2 is calculated)
	UINT32 svp                     :1; //(16) 0:nosvp,1:svp
	UINT32 display_mode            :2; //(18:17) Display Mode	01 : Top Field Display	10 : Bottom Field Dipslay	11 : Frame Display
	UINT32 reserved                :13;//(31:19) reserved
	};
}
DE_REG_O24_IPC_DAR_INFO_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC820D0C RW 0x0000_0000
	UINT32 reserved                :32;//(31:0) reserved
	};
}
DE_REG_O24_IPC_DAR_INFO_3_T;

typedef struct {
	DE_REG_O24_IPC_DAR_INFO_0_T info_0;
	DE_REG_O24_IPC_DAR_INFO_1_T info_1;
	DE_REG_O24_IPC_DAR_INFO_2_T info_2;
	DE_REG_O24_IPC_DAR_INFO_3_T info_3;
}
DE_REG_O24_IPC_DAR_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0C0000 RW 0x0000_0000
	UINT32 tx_locked_id                     :32;	//(31:0,RW,0x0000_0000) //to which access permission is granted For Scatter-Gather, txSrcAddr should be the first field that DMA engine will read
	};
}REG_MCU_EDMA_TX_LOCKED_ID_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0C0004 RW 0x0000_0000
	UINT32 tx_src_addr                      :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_MCU_EDMA_TX_SRC_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0C0008 RW 0x0000_0000
	UINT32 tx_dst_addr                      :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_MCU_EDMA_TX_DST_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0C000C RW 0x0000_0000
	UINT32 tx_nxt_addr                      :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_MCU_EDMA_TX_NXT_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0C0010 RW 0x0000_0000
	UINT32 tx_length                        :32;	//(31:0,RW,0x0000_0000) //
	};
}REG_MCU_EDMA_TX_LENGTH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC0C0014 RW/RO 0x0000_0000
	UINT32 tx_start                         :1;	//(0,RW,0x00) //triggerring a transaction when a writing one happens on this register. This address is shared between registers; txStart, txBusy a write goes on txStart, a read return txBusy
	UINT32 tx_dir                           :3;	//(3:1,RW,0x00) //direction of the traction (portA: DDR, portB : In-bound PIF)	000 := Port A -> Port A	001  = Port A -> Port B	010  = Port B -> Port A	011  = Port B -> Port B	100  = Pattern -> Port A	101  = Pattern -> Port B
	UINT32 tx_nxt_dir                       :1;	//(4,RW,0x00) //Indicating which port the next descriptor exists 0: Port A, 1: Port B
	UINT32 resvd0                           :3;
	UINT32 tx_done                          :1;	//(8,RO,0x00) //A DMA transaction completes not a read-only register could be written if and only if txState == IDLE_STATE
	UINT32 tx_locked                        :1;	//(9,RO,0x00) //indicating whether DMA engine is locked, txLockedID is valid if and if only while this is high
	UINT32 tx_switch_en                     :1;	//(10,RW,0x00) //Endian-switching is enabled when this is high
	UINT32 resvd1                           :1;
	UINT32 tx_atomic_size                   :2;	//(13:12,RW,0x00) //Atomic size for endian switching
	UINT32 resvd2                           :18;
	};
}REG_MCU_EDMA_EDMA_CTRL_T;

typedef struct {
	REG_MCU_EDMA_TX_LOCKED_ID_T   tx_locked_id;//0xCC0C0000
	REG_MCU_EDMA_TX_SRC_ADDR_T     tx_src_addr;//0xCC0C0004
	REG_MCU_EDMA_TX_DST_ADDR_T     tx_dst_addr;//0xCC0C0008
	REG_MCU_EDMA_TX_NXT_ADDR_T     tx_nxt_addr;//0xCC0C000C
	REG_MCU_EDMA_TX_LENGTH_T         tx_length;//0xCC0C0010
	REG_MCU_EDMA_EDMA_CTRL_T         edma_ctrl;//0xCC0C0014
}DE_MCU_EDMA_REG_O24_T;

typedef struct {
	UINT32    load;//0x0
	UINT32   value;//0x4
	UINT32 control;//0x8
	UINT32 int_clr;//0xC
} DE_REG_O24_WDOG_T;

typedef struct {
	UINT32 trace_0;//0xCC421400
	UINT32 trace_1;//0xCC421404
	UINT32 trace_2;//0xCC421408
	UINT32 trace_3;//0xCC42140C
} DE_REG_O24_FMC_VERI_T;

typedef struct {
	UINT32 trace_4;//0xCC8A0200
	UINT32 trace_5;//0xCC8A0204
	UINT32 trace_6;//0xCC8A0208
	UINT32 trace_7;//0xCC8A020C
} DE_REG_O24_ME1_VERI_T;

typedef struct {
	UINT32 trace_8;//0xCCC91100
	UINT32 trace_9;//0xCCC91104
	UINT32 trace_10;//0xCCC91108
	UINT32 trace_11;//0xCCC9110C
} DE_REG_O24_ND1_VERI_T;

typedef struct {
	UINT32 exception;//0xCC820D3C
	UINT32 no_touch[3];//0xCC820D40~0xCC820D48
	UINT32 exception1;//0xCC820D4C
} DE_REG_O24_IMX_VERI_15_T;

typedef struct {
	UINT32 dbg_githash;  //0xCC4E0200
	UINT32 dbg_timestamp;//0xCC4E0204
	UINT32 dbg_pc;       //0xCC4E0208
	UINT32 dbg_exccause; //0xCC4E020C
} DE_REG_O24_FMS_VERI_T;

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/
int DE_REG_O24_CviMap(LX_DE_WIN_ID_T win_id, LX_DE_IN_SRC_T in_port, UINT32 port_num);
int de_reg_o24_fwload_register(struct vsc_fw_load *load);
LX_MEMCFG_T de_reg_o24_getmeminfo(char* str);
int DE_REG_O24_SetClockGate(CTOP_PQE_CG_O24_MODULE mod, BOOLEAN onOff);

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/
DE_IPC_REG_O24_T gDE_IPC_O24;
volatile UINT32 *gDE_MUTE_O24[2] = {NULL, NULL};//REG_VSD_SHP_SHP_FSW_CTRL_03_T shp_fsw_ctrl_03;	//0xCCA228FC
volatile LX_DE_FW_STATUS_REG_T *gDE_FW_STATUS_O24 = NULL;//REG_CCO_VERI_SYS_VERI_10_T video_delay_sts0;	//0xCC862328
volatile LX_DE_VDEC_IPC_REG_T *gDE_VDEC_O24[LX_DE_WIN_MAX];
volatile DE_REG_O24_IPC_DAR_INFO_T *gDE_DAR_INFO_O24[2] = {NULL, NULL};
volatile LX_DE_DDR_MVI_T *gDE_DDR_MVI_O24 = NULL;
volatile DE_MCU_EDMA_REG_O24_T *gDE_MCU_EDMA_O24 = NULL;
volatile DE_REG_O24_WDOG_T *gDE_MCU_WDOG0_O24 = NULL;
volatile DE_REG_O24_WDOG_T *gDE_MCU_WDOG1_O24 = NULL;
volatile DE_REG_O24_FMC_VERI_T *gDE_FMC_VERI_O24 = NULL;
volatile DE_REG_O24_ME1_VERI_T *gDE_ME1_VERI_O24 = NULL;
volatile DE_REG_O24_ND1_VERI_T *gDE_ND1_VERI_O24 = NULL;
volatile DE_REG_O24_IMX_VERI_15_T *gDE_IMX_VERI_15_O24 = NULL;
volatile DE_REG_O24_FMS_VERI_T *gDE_FMS_VERI_O24 = NULL;

LX_DE_IN_SRC_T g_WinsrcMap_O24[NUM_WIN_MAX] = { LX_DE_IN_SRC_MVI,	LX_DE_IN_SRC_MVI};
UINT32 g_WinsrcPort_O24[NUM_WIN_MAX] = { 0, 0};
UINT32 g_HdmiPort_O24[NUM_WIN_MAX] = { 0, };
UINT32 g_QuadWin_O24  = 0;
LX_DE_OPER_CONFIG_T g_SrcOperType_O24 = LX_DE_OPER_ONE_WIN;
LX_DE_SUB_OPER_CONFIG_T	g_SrcSubOperType_O24 = LX_DE_SUB_OPER_OFF;
UINT16 g_SrcOperCtrlFlag_O24 = 0;
UINT16 g_SrcSubOperCtrlFlag_O24 = 0;
LX_DE_DISPLAY_MIRROR_T	g_Display_mirror_O24 = LX_DE_DIS_MIRROR_OFF;
UINT32                  g_Zero_delay_mode_O24 = 0;

static phys_addr_t bt_paddr_m0 = 0;
static phys_addr_t vr_paddr_m0 = 0, vr_paddr_m1 = 0;;
static phys_addr_t vtg_paddr_m0 = 0, vtg_paddr_m1 = 0;
static phys_addr_t dbg_paddr_m0 = 0, dbg_paddr_m1 = 0;;

static UINT32 _g_de_reg_o24_mvi_magic = 0;

static struct vsc_fw_load_param _g_de_reg_o24_fw_load_p[] = {
	[0] = {
		.name = "pqefw0_o24",
		.idx = 0,
		.hma_pool = "debug0",
		.hma_size = 4*1024*1024,
	},
	[1] = {
		.name = "pqefw1_o24",
		.idx = 1,
		.hma_pool = "debug1",
		.hma_size = 4*1024*1024,
	}
};

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/
int DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus);
static void _set_tag_info(void);
static int DE_REG_O24_ClearTraceDataBuf(void);
static int DE_REG_O24_BackupTraceDataBuf(char *data);
static int DE_REG_O24_ViewTraceDataBuf(void);
static void _print_status_info(void);
static void _print_tag_info(void *tag_info, UINT32 tag_size);

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static DE_REG_O24_IPC_SYSTEM_T  g_Mem_Info = { 0, };
static LX_DE_MEM_SYS_INFO_T   g_Mem_Sys_Info = { 0, };
static DE_REG_O24_NOTI_BUF_T _g_de_reg_o24_buf[DE_REG_O24_NOTI_BUF_MAX];
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
int DE_REG_O24_InitPHY2VIRT(void)
{
	int ret = RET_OK;

	gDE_IPC_O24.shdw.addr  = (UINT32 *)OS_KMalloc(sizeof(DE_IPC_REG_O24A0_T));
	gDE_IPC_O24.phys.addr  = (volatile UINT32 *)ioremap(DE_IPC_REG_O24_BASE, sizeof(DE_IPC_REG_O24A0_T));
	gDE_VDEC_O24[0] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O24_BASE + 0x00, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_O24[1] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O24_BASE + 0x40, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_O24[2] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O24_BASE + 0x80, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_VDEC_O24[3] = (volatile LX_DE_VDEC_IPC_REG_T *)ioremap(DE_VDEC_O24_BASE + 0xC0, sizeof(LX_DE_VDEC_IPC_REG_T));
	gDE_MUTE_O24[0] = (volatile UINT32 *)ioremap(DE_MUTE_O24_BASE, sizeof(UINT32));//REG_VSD_SHP_SHP_FSW_CTRL_03_T mute_info_w1_w0;	//0xCCA228FC
	gDE_MUTE_O24[1] = (volatile UINT32 *)ioremap(DE_MUTE_O24_BASE - 4, sizeof(UINT32));// REG_VSD_SHP_SHP_FSW_CTRL_02_T          mute_info_w3_w2; //0xCCA228F8
	gDE_FW_STATUS_O24 = (volatile LX_DE_FW_STATUS_REG_T *)ioremap(DE_FW_STATUS_O24_BASE, sizeof(LX_DE_FW_STATUS_REG_T));//REG_CCO_VERI_SYS_VERI_10_T video_delay_sts0;	//0xCC862328
	gDE_DAR_INFO_O24[0] = (volatile DE_REG_O24_IPC_DAR_INFO_T *)ioremap(DE_FW_DARINFO_O24_BASE, sizeof(DE_REG_O24_IPC_DAR_INFO_T));
	gDE_DAR_INFO_O24[1] = (volatile DE_REG_O24_IPC_DAR_INFO_T *)ioremap((DE_FW_DARINFO_O24_BASE+sizeof(DE_REG_O24_IPC_DAR_INFO_T)), sizeof(DE_REG_O24_IPC_DAR_INFO_T));
	gDE_DDR_MVI_O24 = (volatile LX_DE_DDR_MVI_T *)vmap_phys((g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_MVI), sizeof(LX_DE_DDR_MVI_T));
	gDE_MCU_EDMA_O24 = (volatile DE_MCU_EDMA_REG_O24_T *)ioremap(DE_MCU_EDMA_O24_BASE, sizeof(DE_MCU_EDMA_REG_O24_T));
	gDE_MCU_WDOG0_O24 = (volatile DE_REG_O24_WDOG_T *)ioremap(DE_MCU_WDOG0_O24_BASE, sizeof(DE_REG_O24_WDOG_T));
	gDE_MCU_WDOG1_O24 = (volatile DE_REG_O24_WDOG_T *)ioremap(DE_MCU_WDOG1_O24_BASE, sizeof(DE_REG_O24_WDOG_T));
	gDE_FMC_VERI_O24 = (volatile DE_REG_O24_FMC_VERI_T *)ioremap(DE_FMC_VERI_O24_BASE, sizeof(DE_REG_O24_FMC_VERI_T));
	gDE_ME1_VERI_O24 = (volatile DE_REG_O24_ME1_VERI_T *)ioremap(DE_ME1_VERI_O24_BASE, sizeof(DE_REG_O24_ME1_VERI_T));
	gDE_ND1_VERI_O24 = (volatile DE_REG_O24_ND1_VERI_T *)ioremap(DE_ND1_VERI_O24_BASE, sizeof(DE_REG_O24_ND1_VERI_T));
	gDE_IMX_VERI_15_O24 = (volatile DE_REG_O24_IMX_VERI_15_T *)ioremap(DE_IMX_VERI_15_O24_BASE, sizeof(DE_REG_O24_IMX_VERI_15_T));
	gDE_FMS_VERI_O24 = (volatile DE_REG_O24_FMS_VERI_T *)ioremap(DE_FMS_VERI_O24_BASE, sizeof(DE_REG_O24_FMS_VERI_T));
	DE_NOTI("ioremap wdog 0:0x%08x,1:0x%08x.\n",DE_MCU_WDOG0_O24_BASE,DE_MCU_WDOG1_O24_BASE);

	DE_REG_O24_ClearTraceDataBuf();
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
int DE_REG_O24_FreePHY2VIRT(void)
{
	if (gDE_IPC_O24.shdw.addr) OS_Free((void *)gDE_IPC_O24.shdw.addr);
	if (gDE_IPC_O24.phys.addr) iounmap((void *)gDE_IPC_O24.phys.addr);
	if (gDE_VDEC_O24[0]) iounmap((void *)gDE_VDEC_O24[0]);
	if (gDE_VDEC_O24[1]) iounmap((void *)gDE_VDEC_O24[1]);
	if (gDE_VDEC_O24[2]) iounmap((void *)gDE_VDEC_O24[2]);
	if (gDE_VDEC_O24[3]) iounmap((void *)gDE_VDEC_O24[3]);
	if (gDE_MUTE_O24[0]) {iounmap((void *)gDE_MUTE_O24[0]);iounmap((void *)gDE_MUTE_O24[1]);}
	if (gDE_FW_STATUS_O24) iounmap((void *)gDE_FW_STATUS_O24);
	if (gDE_DAR_INFO_O24[0]) {iounmap((void *)gDE_DAR_INFO_O24[0]);iounmap((void *)gDE_DAR_INFO_O24[1]);}
	if (gDE_DDR_MVI_O24) vunmap_phys((void*)gDE_DDR_MVI_O24);
	if (gDE_MCU_EDMA_O24) iounmap((void *)gDE_MCU_EDMA_O24);
	if (gDE_MCU_WDOG0_O24) iounmap((void *)gDE_MCU_WDOG0_O24);
	if (gDE_MCU_WDOG1_O24) iounmap((void *)gDE_MCU_WDOG1_O24);
	if (gDE_FMC_VERI_O24) iounmap((void *)gDE_FMC_VERI_O24);
	if (gDE_ME1_VERI_O24) iounmap((void *)gDE_ME1_VERI_O24);
	if (gDE_ND1_VERI_O24) iounmap((void *)gDE_ND1_VERI_O24);
	if (gDE_IMX_VERI_15_O24) iounmap((void *)gDE_IMX_VERI_15_O24);
	if (gDE_FMS_VERI_O24) iounmap((void *)gDE_FMS_VERI_O24);

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
int DE_IPC_O24_GetStatusReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
		case VIDEO_DMA_MCU :
		case VIDEO_JPG_MCU :
		case VIDEO_WEL_MCU :
		case VIDEO_WER_MCU :
			DE_IPC_O24_RdFL(int_intr_status);
			*pStatus = DE_IPC_O24_Rd(int_intr_status);
			break;
		case VIDEO_IPC_CPU :
		case VIDEO_DMA_CPU :
		case VIDEO_JPG_CPU :
		case VIDEO_WEL_CPU :
		case VIDEO_WER_CPU :
			DE_IPC_O24_RdFL(ext_intr_status);
			*pStatus = DE_IPC_O24_Rd(ext_intr_status);
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
int DE_WDG_O24_WakeUpReg(UINT32 mcu_id, BOOLEAN turnOn)
{
	unsigned int rd_data;
	switch(mcu_id)
	{
		case 0:
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event, wdg_interrupt_event, 1);
			} else {
				DE_IPC_O24_FLWf(ext_intr_enable, wdg_interrupt_enable, 0);
				DE_IPC_O24_FLWf(ext_intr_clear, wdg_interrupt_clear, 1);
			}
		break;
		case 1:
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event, wdg_interrupt_event_mcu1, 1);
			} else {			
				DE_IPC_O24_FLWf(ext_intr_enable, wdg_interrupt_enable_mcu1, 0);
				DE_IPC_O24_FLWf(ext_intr_clear, wdg_interrupt_clear_mcu1, 1);
			}
			break;
		default:
			break;
	}
	DE_IPC_O24_RdFL(ext_intr_enable);
	rd_data = DE_IPC_O24_Rd(ext_intr_enable);
	DE_NOTI("ext_intr_enable = 0x%08x", rd_data);

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
int DE_IPC_O24_WakeUpReg(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, BOOLEAN turnOn)
{
	int ret = RET_OK;

	turnOn &= 0x1;
	switch (ipcType) {
		case VIDEO_IPC_MCU :
			if (turnOn) {
				DE_IPC_O24_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_IPC_CPU :
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_MCU :
			if (turnOn) {
				DE_IPC_O24_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_DMA_CPU :
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_MCU :
			if (turnOn) {
				DE_IPC_O24_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_JPG_CPU :
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_MCU :
			if (turnOn) {
				DE_IPC_O24_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_USB_CPU :
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_MCU :
			if (turnOn) {
				DE_IPC_O24_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WEL_CPU :
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(ext_intr_clear,\
						ipc_interrupt_clear_arm,\
						GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_MCU :
			if (turnOn) {
				DE_IPC_O24_FLWf(int_intr_event,\
						ipc_interrupt_event_mcu,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(int_intr_clear,\
						ipc_interrupt_clear_mcu,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			}
			break;
		case VIDEO_WER_CPU :
			if (turnOn) {
				DE_IPC_O24_FLWf(ext_intr_event,\
						ipc_interrupt_event_arm,\
						GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			} else {
				DE_IPC_O24_FLWf(ext_intr_clear,\
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
int DE_IPC_O24_ClearStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	switch (ipcType) {
		case VIDEO_IPC_MCU :
			DE_IPC_O24_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_IPC_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_IPC_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DMA_MCU :
			DE_IPC_O24_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DMA_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_DMA_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_JPG_MCU :
			DE_IPC_O24_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_JPG_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_JPG_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_USB_MCU :
			DE_IPC_O24_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_USB_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_USB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WEL_MCU :
			DE_IPC_O24_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WEL_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_WEL_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WER_MCU :
			DE_IPC_O24_FLWf(int_intr_clear,\
					ipc_interrupt_clear_mcu,\
					GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_WER_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_WER_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DHDR_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_DHDR_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_DELAY_CPU:
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_CB_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_GPS_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_GPS_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_GPW_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_GPW_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_AMZ_CPU:
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_AMZ_INTERRUPT_ARM_BIT, 1));
			break;
		case VIDEO_LED_CPU :
			DE_IPC_O24_FLWf(ext_intr_clear,\
					ipc_interrupt_clear_arm,\
					GET_PMSK(VIDEO_LED_INTERRUPT_ARM_BIT, 1));
			break;
		default :
			BREAK_WRONG(ipcType);
			break;
	}
	return ret;
}

int DE_IPC_O24_CleanupStatus(UINT32 mcu_id)
{
	DE_IPC_O24_FLWf(ext_intr_clear,\
		ipc_interrupt_clear_arm,\
		VIDEO_UNUSED_INTERRUPT_ARM_MASK);
	return 0;
}

int DE_REG_O24_CheckMuteStatus(UINT32 win_id, UINT32 *mute_status)
{
	int ret = RET_OK;
	UINT32 data;
	UINT32 i = win_id;

	if (gDE_MUTE_O24[0]==NULL)	return RET_ERROR;

	if(i < 2)
		data = *gDE_MUTE_O24[0];
	else
		data = *gDE_MUTE_O24[1];

	*mute_status = (UINT16)((data >> (16 * i)) & 0xFFFF);

	return ret;
}

int DE_REG_O24_CheckFwStatus(UINT32 win_id, void *status)
{
	int ret = RET_OK;
	LX_DE_FW_STATUS_REG_T *dst = (LX_DE_FW_STATUS_REG_T *)status;

	if (gDE_FW_STATUS_O24==NULL)	return RET_ERROR;
	if (status==NULL)	return RET_ERROR;
	memcpy(dst, (const void *)gDE_FW_STATUS_O24, sizeof(LX_DE_FW_STATUS_REG_T));
	return ret;
}

int DE_REG_O24_SetFrRate(DE_DPLL_CLK_T dclk)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetBgColor(LX_DE_COLOR_T *pBackColor)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetWinBlank(LX_DE_SET_WIN_BLANK_T *pWinBlank)
{
	int ret = RET_OK;

	return ret;
}

BOOLEAN DE_REG_O24_CheckIrq4Vsync(UINT32 mcu_id)
{
	int ret;
	O24A0_INTR_CPU_FLAG_T intr_flag_cpu;
	O24A0_IMX_CTRL_INTR_REG_T imx_intr_reg;
	O24A0_HDR_CTRL_INTR_CPU_REG_T hdr_intr_reg;
	UINT32 videoIntrDe;
	BOOLEAN vsyncIrq = 0;

	do {
		vsyncIrq = 0;
		ret = DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_FUNC, &videoIntrDe);
		if (ret) break;

		intr_flag_cpu.udata32 = videoIntrDe;

		if (intr_flag_cpu.imx_mcu_intr_cpu)
		{
			vsyncIrq = 0;
			videoIntrDe = 0;
			ret = DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_IMX, &videoIntrDe);
			if (ret) break;
			imx_intr_reg.udata32 = videoIntrDe;
			if(!imx_intr_reg.intr_i5_intr_pulse) break;
			vsyncIrq = 1;
		}
		if (intr_flag_cpu.hdr_mcu_intr_cpu)
		{
			vsyncIrq = 0;
			videoIntrDe = 0;
			ret = DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_HDR, &videoIntrDe);
			if (ret) break;
			hdr_intr_reg.udata32 = videoIntrDe;
			if(!hdr_intr_reg.intr_i5_intr_pulse) break;
			vsyncIrq = 1;
		}
		if (intr_flag_cpu.cvi_mcu_intr_cpu)
		{
			vsyncIrq = 0;
			videoIntrDe = 0;
			ret = DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_CVI, &videoIntrDe);
			if (ret) break;
		}
	} while (0);
	return vsyncIrq;
}

int DE_REG_O24_UpdateVideoIrqStatus(VIDEO_INTR_TYPE_T intrType, UINT32 *pVideoIrqStatus)
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
				DE_IPC_O24_RdFL(intr_cpu_flag);
				*pVideoIrqStatus = DE_IPC_O24_Rd(intr_cpu_flag);
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
int DE_REG_O24_SetCviVideoFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams)
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
int DE_REG_O24_SetCviRWFrameBuffer(LX_DE_CVI_RW_VIDEO_FRAME_T *pstParams,LX_DE_CVI_RW_PREW_FRAME_T *prewInfo)
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
int DE_REG_O24_CviMap(LX_DE_WIN_ID_T win_id, LX_DE_IN_SRC_T in_port, UINT32 port_num)
{
	int ret = RET_OK;
	UINT32 sel_cvi[2] = {0, 0};
	UINT32 sel_clk[2] = {0, 0};

	do {
		sel_cvi[0] = CVI_NONE_O24;
		sel_cvi[1] = CVI_NONE_O24;
		sel_clk[0] = CLK_NONE_O24;
		sel_clk[1] = CLK_NONE_O24;

		switch(win_id)
		{
			case LX_DE_WIN_MAIN:
			case LX_DE_WIN_1:
			case LX_DE_WIN_2:
			case LX_DE_WIN_3:
			case LX_DE_WIN_4:
			case LX_DE_WIN_MAX:
				if(in_port == LX_DE_IN_SRC_CVBS || \
						in_port == LX_DE_IN_SRC_ATV || \
						in_port == LX_DE_IN_SRC_SCART)
				{
					sel_cvi[0] = CVI_CVD_O24;
					sel_clk[0] = CLK_CVD_O24;
				}
				if(in_port == LX_DE_IN_SRC_YPBPR || \
						in_port == LX_DE_IN_SRC_VGA)
				{
					sel_cvi[0] = CVI_ADC_O24;
					sel_clk[0] = CLK_ADC_O24;
				}
				if(in_port == LX_DE_IN_SRC_HDMI)
				{
					g_HdmiPort_O24[win_id] = port_num;  // assign for resume from instanr boot !!!
					switch(port_num)
					{
						case HDMI_O24_PORT_0:
							sel_cvi[0] = CVI_HDMI_O24_A;
							sel_cvi[1] = CVI_HDMI_O24_A;
							sel_clk[0] = CLK_HDA_O24;
							sel_clk[1] = CLK_HDA_O24;
							break;
						case HDMI_O24_PORT_1:
							sel_cvi[0] = CVI_HDMI_O24_B;
							sel_cvi[1] = CVI_HDMI_O24_B;
							sel_clk[0] = CLK_HDB_O24;
							sel_clk[1] = CLK_HDB_O24;
							break;
						case HDMI_O24_PORT_2:
							sel_cvi[0] = CVI_HDMI_O24_C;
							sel_cvi[1] = CVI_HDMI_O24_C;
							sel_clk[0] = CLK_HDC_O24;
							sel_clk[1] = CLK_HDC_O24;
							break;
						case HDMI_O24_PORT_3:
							sel_cvi[0] = CVI_HDMI_O24_D;
							sel_cvi[1] = CVI_HDMI_O24_D;
							sel_clk[0] = CLK_HDD_O24;
							sel_clk[1] = CLK_HDD_O24;
							break;
						case HDMI_O24_PORT_DSC:
							sel_cvi[0] = CVI_HDMI_O24_DSC;
							sel_cvi[1] = CVI_HDMI_O24_DSC;
							sel_clk[0] = CLK_DSC_O24;
							sel_clk[1] = CLK_DSC_O24;
							break;
						default:
							sel_cvi[0] = CVI_HDMI_O24_A;
							sel_cvi[1] = CVI_HDMI_O24_A;
							sel_clk[0] = CLK_HDA_O24;
							sel_clk[1] = CLK_HDA_O24;
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

#ifdef USE_CTOP_CODES_FOR_O24

#if 0
O24_CRG_SUB_Register_Manual.xlsx
CVI(cvi_syn)

18:16	reg_cvi4_clk_sel
14:12	reg_cvi3_clk_sel
10:8	reg_cvi2_clk_sel
6:4		reg_cvi1_clk_sel
2:0		reg_cvi0_clk_sel

Clock Selection
0 => core600_clk (600MHz)
1 => core600_d2 (300MHz)
2 => hdmirx_prt1_tmdsqp_clk (444MHz)
3 => hdmirx_prt2_tmdsqp_clk (444MHz)
4 => hdmirx_prt3_tmdsqp_clk (444MHz)
5 => hdmirx_prt4_tmdsqp_clk (444MHz)
6 => cvi_cvd54_d2 (27MHz)

#define O24_A0_SCRG_CTRL_CVI_BASE 0xCCCD0000
SCRG_CTRL_CVI_REG_O24A0_T *SCRG_CTRL_CVI;// scrg_ctrl_cvi_o24a0_reg.h
#endif

#if 0
sel_cvi[0] : see following enum

typedef enum {
	CVI_HDMI_O24_DSC = 0,
	CVI_HDMI_O24_A = 2,
	CVI_HDMI_O24_B,
	CVI_HDMI_O24_C,
	CVI_HDMI_O24_D = 5,
	CVI_CVD_O24,
	CVI_ADC_O24,
	CVI_NONE_O24     = 0xFF
} CVI_DATA_IN_SEL_O24;
#endif

		CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_CVI, crg_cvi4);//0xCCCD0010
		switch(win_id)
		{
		case LX_DE_WIN_MAIN:
			CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_CVI, crg_cvi4, reg_cvi0_clk_sel, sel_clk[0]);
			if(!g_QuadWin_O24) { // reserved for 8k path (in case of o24 8k model, it use 0/2/3/4)
				CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_CVI, crg_cvi4, reg_cvi1_clk_sel, sel_clk[0]);
			}
			break;
		case LX_DE_WIN_1:
		case LX_DE_WIN_2:
			CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_CVI, crg_cvi4, reg_cvi2_clk_sel, sel_clk[0]);
			break;
		case LX_DE_WIN_3:
			CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_CVI, crg_cvi4, reg_cvi4_clk_sel, sel_clk[0]);
			break;
		case LX_DE_WIN_4:
			CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_CVI, crg_cvi4, reg_cvi1_clk_sel, sel_clk[0]);
			break;
		case LX_DE_WIN_MAX:

			break;

		default :
			break;
		}
		CTOP_CTRL_O24Ax_WrFL(SCRG_CTRL_CVI, crg_cvi4);
#endif
	} while(0);

	DE_NOTI("win_id[%d]: sel_cvi[%d] sel_clk[%d]", win_id, sel_cvi[0], sel_clk[0]);

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
int DE_REG_O24_SetWinPortSrc(LX_DE_INPUT_CFG_T *pstParams)
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

		ret = DE_REG_O24_CviMap(win_id, in_port, srcPort);

		if(win_id < NUM_WIN_MAX)
		{
			g_WinsrcMap_O24[win_id] = in_port;
			g_WinsrcPort_O24[win_id] = srcPort;
		}
		DE_PRINT("Src map (NONE(0)/VGA(1)/YPBPR(2)/ATV(3)/CVD(4)/SCART(5)/HDMI(6)/MVI(7)/CPU(8))");
		DE_PRINT("  => win[%d] src[%d] port[%d]", win_id, in_port, srcPort);
	} while(0);

	return ret;
}

int DE_REG_O24_SetCviSrcType(LX_DE_CVI_SRC_TYPE_T *pstParams)
{
	return 0;
}

int DE_REG_O24_Init(LX_DE_PANEL_TYPE_T *pstParams)
{
	return 0;
}

int DE_REG_O24_SetVcs(LX_DE_VCS_IPC_T *pstParams)
{
	return 0;
}

int DE_REG_O24_GPIO_Init(void)
{
	return 0;
}

int DE_REG_O24_HDMI_Init(void)
{
	return 0;
}

int DE_REG_O24_LVDS_Init(void)
{
	return 0;
}

int DE_REG_O24_MISC_Init(void)
{
	return 0;
}

int DE_REG_O24_OSD_Init(void)
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
int DE_REG_O24_Uart0_Switch(int whichUart)
{
	int ret = RET_OK;

#ifdef USE_CTOP_CODES_FOR_O24
	DE_NOTI("UART[%d]\n", whichUart);

#if 0
O24_CTOP_SYN_Register_Manual.xlsx  ??????????
WOC_SYN
--------------------------------------------
Main IO Mux ??UART #0
0xC63F510C
reg_pad_uart0_rx_mux_sel 15:12 : 0x0
reg_pad_uart0_tx_mux_sel 11:8 : 0x1

Main UART Mux
0xC63F2020 main_uart_sel0 3:0
[0x0] : TZ
[0x2] : CPU #0
[0x3] : CPU #1
[0x4] : CPU #2
[0x5] : VDEC
[0x6] : PQE MXU #0
[0x7] : PQE MXU #1
[0x8] : TE
[0x9] : MICOM #0
[0xA] : MICOM #1
[0xB] : AUD
[0xC] : HDMI
[0xD] : DBB
[0xE] : DRAM
--------------------------------------------
Main IO Mux ??UART #1
0xC68A3114
reg_pad_uart1_rx_mux_sel 11:8 : 0x0
reg_pad_uart1_tx_mux_sel 7:4 : 0x0

Main UART Mux
0xC63F2024 main_uart_sel1 3:0
[0x0] : MICOM #0
[0x1] : TZ
[0x2] : CPU #0
[0x3] : CPU #1
[0x4] : CPU #2
[0x5] : VDEC
[0x6] : PQE MXU #0
[0x7] : PQE MXU #1
[0x8] : TE
[0xA] : MICOM #1
[0xB] : AUD
[0xC] : HDMI
[0xD] : DBB
[0xE] : DRAM
--------------------------------------------
Main IO Mux ??UART #2
0xCC972114
reg_pad_epi_gclk2_mux_sel 15:12 : 0x3
reg_pad_epi_mclk2_mux_sel 7:4 : 0x3

Main UART Mux
0xC63F2028 main_uart_sel2 3:0
[0x1] : TZ
[0x2] : CPU #0
[0x3] : CPU #1
[0x4] : CPU #2
[0x5] : VDEC
[0x6] : PQE MXU #0
[0x7] : PQE MXU #1
[0x8] : TE
[0x9] : MICOM #0
[0xA] : MICOM #1
[0xB] : AUD
[0xC] : HDMI
[0xD] : DBB
[0xE] : DRAM
--------------------------------------------
#define O24_A0_CPU_BND_CTRL_WOC_BASE             0xC8512000
#define O24_A0_CPU_BND_CTRL_WOC_TYPE             MICOM_BND_CTRL_WOC_REG_O24A0_T
MICOM_BND_CTRL_WOC_REG_O24A0_T *CPU_BND_CTRL_WOC;// micom_bnd_ctrl_woc_o24a0_reg.h
#endif

//	CTOP_CTRL_O24Ax_RdFL(CPU_BND_CTRL_WOC, woc_syn_07);// UART2
//	CTOP_CTRL_O24Ax_RdFL(CPU_BND_CTRL_WOC, woc_syn_06);// UART1
	CTOP_CTRL_O24Ax_RdFL(CPU_BND_CTRL_WOC, woc_syn_05);// UART0
	switch (whichUart)
	{
		case 0 :
//				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_07, reg_main_uart_sel2, 2); // UART2 = cpu0
//				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_06, reg_main_uart_sel1, 2); // UART1 = cpu0
				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_05, reg_main_uart_sel0, 2); // UART0 = cpu0
			break;
		case 1 :
//				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_07, reg_main_uart_sel2, 6); // UART2 = mcu0
//				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_06, reg_main_uart_sel1, 6); // UART1 = mcu0
				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_05, reg_main_uart_sel0, 6); // UART0 = mcu0
			break;
		case 2 :
				CTOP_CTRL_O24Ax_Wr01(CPU_BND_CTRL_WOC, woc_syn_05, reg_main_uart_sel0, 7); // UART0 = mcu1
			break;
		default :
			break;
	}
//	CTOP_CTRL_O24Ax_WrFL(CPU_BND_CTRL_WOC, woc_syn_07);// UART2
//	CTOP_CTRL_O24Ax_WrFL(CPU_BND_CTRL_WOC, woc_syn_06);// UART1
	CTOP_CTRL_O24Ax_WrFL(CPU_BND_CTRL_WOC, woc_syn_05);// UART0
#endif
	return ret;
}

int DE_REG_O24_FW_DumpStatus(void)
{
	int ret = RET_OK;
	UINT32 *p_pqe_debug_info = NULL;
	UINT32 i;
	UINT32 size = 16;

	DE_NOTI("CPU->MCU[ 0x%08X ]\n", DTVSOC_IPC_FROM_CPU_O24_BASE);
	p_pqe_debug_info = (UINT32 *)ioremap(DTVSOC_IPC_FROM_CPU_O24_BASE, sizeof(UINT32) * size);
	for(i=0;i<size;i+=4)
	{
		DE_NOTI("[%02d] 0x%08X 0x%08X 0x%08X 0x%08X\n",i,p_pqe_debug_info[i],p_pqe_debug_info[i+1],p_pqe_debug_info[i+2],p_pqe_debug_info[i+3]);
	}
	DE_NOTI("MCU->CPU[ 0x%08X ]\n", DTVSOC_IPC_FROM_MCU_O24_BASE);
	if(p_pqe_debug_info) iounmap(p_pqe_debug_info);

	p_pqe_debug_info = (UINT32 *)ioremap(DTVSOC_IPC_FROM_MCU_O24_BASE, sizeof(UINT32) * size);
	for(i=0;i<size;i+=4)
	{
		DE_NOTI("[%02d] 0x%08X 0x%08X 0x%08X 0x%08X\n",i,p_pqe_debug_info[i],p_pqe_debug_info[i+1],p_pqe_debug_info[i+2],p_pqe_debug_info[i+3]);
	}

	if(p_pqe_debug_info) iounmap(p_pqe_debug_info);

	_print_status_info();

	return ret;
}

static int DE_REG_O24_ClearTraceDataBuf(void)
{
	memset(_g_de_reg_o24_buf, 0, sizeof(DE_REG_O24_NOTI_BUF_T)*DE_REG_O24_NOTI_BUF_MAX);
	return RET_OK;
}

static int DE_REG_O24_BackupTraceDataBuf(char *data)
{
	UINT32 i;
	char *p_str;
	DE_REG_O24_NOTI_TIME_T *p_time;
	static UINT32 cnt = 0;

	if (!data)	return RET_OK;

	if(cnt>=DE_REG_O24_NOTI_BUF_MAX)	cnt = 0;

	p_str = _g_de_reg_o24_buf[cnt].str;
	p_time = &(_g_de_reg_o24_buf[cnt].time);
	OS_GetCurrentTicks(&(p_time->sec), &(p_time->msec), &(p_time->usec));
	memset(p_str, 0, DE_REG_O24_NOTI_STR_SIZE);

	for(i=0;i<DE_REG_O24_NOTI_STR_SIZE;i++)
	{
		p_str[i] = data[i];
		if(data[i] == 0) break;
	}

	cnt++;

	return RET_OK;
}

static int DE_REG_O24_ViewTraceDataBuf(void)
{
	UINT32 i;
	char *p_str;
	DE_REG_O24_NOTI_TIME_T *p_time;

	for (i=0; i<DE_REG_O24_NOTI_BUF_MAX; i++)
	{
		p_time = &(_g_de_reg_o24_buf[i].time);
		if(p_time->sec==0 && p_time->msec==0 && p_time->usec==0)	break;
		p_str = _g_de_reg_o24_buf[i].str;
		printk("[%02d][%06d.%03d%03d] %s",i,p_time->sec,p_time->msec,p_time->usec,p_str);
	}

	return RET_OK;
}

int DE_REG_O24_ViewInfo(int type)
{
	int ret = RET_OK;

	if (type == 0)
	{
		ret = DE_REG_O24_ViewTraceDataBuf();
		_print_tag_info(&g_Mem_Info,sizeof(DE_REG_O24_IPC_SYSTEM_T));
		_print_status_info();
	}

	return ret;
}

static void _print_status_info(void)
{
	UINT32 r[6];

	DE_IPC_O24_RdFL(pfault_status0);
	DE_IPC_O24_RdFL(pfault_status1);
	DE_IPC_O24_RdFL(pfault_status2);
	r[0] = DE_IPC_O24_Rd(pfault_status0);
	r[1] = DE_IPC_O24_Rd(pfault_status1);
	r[2] = DE_IPC_O24_Rd(pfault_status2);
	DE_NOTI("pfault_status:0x%08x,0x%08x,0x%08x\n",r[0],r[1],r[2]);

	if (gDE_FMC_VERI_O24) {
		r[0] = gDE_FMC_VERI_O24->trace_0;
		r[1] = gDE_FMC_VERI_O24->trace_1;
		r[2] = gDE_FMC_VERI_O24->trace_2;
		r[3] = gDE_FMC_VERI_O24->trace_3;
		DE_NOTI("tr0:0x%08x,0x%08x,0x%08x,0x%08x\n",r[0],r[1],r[2],r[3]);
	}

	if (gDE_ME1_VERI_O24) {
		r[0] = gDE_ME1_VERI_O24->trace_4;
		r[1] = gDE_ME1_VERI_O24->trace_5;
		r[2] = gDE_ME1_VERI_O24->trace_6;
		r[3] = gDE_ME1_VERI_O24->trace_7;
		DE_NOTI("tr4:0x%08x,0x%08x,0x%08x,0x%08x\n",r[0],r[1],r[2],r[3]);
	}

	if (gDE_ND1_VERI_O24) {
		r[0] = gDE_ND1_VERI_O24->trace_8;
		r[1] = gDE_ND1_VERI_O24->trace_9;
		r[2] = gDE_ND1_VERI_O24->trace_10;
		r[3] = gDE_ND1_VERI_O24->trace_11;
		DE_NOTI("tr8:0x%08x,0x%08x,0x%08x,0x%08x\n",r[0],r[1],r[2],r[3]);
	}

	if (gDE_IMX_VERI_15_O24 && gDE_FMS_VERI_O24) {
		r[0] = gDE_IMX_VERI_15_O24->exception;
		r[1] = gDE_IMX_VERI_15_O24->exception1;
		r[2] = gDE_FMS_VERI_O24->dbg_githash;
		r[3] = gDE_FMS_VERI_O24->dbg_timestamp;
		r[4] = gDE_FMS_VERI_O24->dbg_pc;
		r[5] = gDE_FMS_VERI_O24->dbg_exccause;
		DE_NOTI("exc:0x%08x,0x%08x,dbg:0x%08x,0x%08x,0x%08x,0x%08x\n",r[0],r[1],r[2],r[3],r[4],r[5]);
	}
}

static void _print_tag_info(void *tag_info, UINT32 tag_size)
{
	DE_REG_O24_IPC_SYSTEM_T *p = (DE_REG_O24_IPC_SYSTEM_T *)tag_info;

	if (!p)
	{
		DE_NOTI("no info\n");
		return;
	}

	#define SIZE_MB(a)	  (a/1024/1024)
	#define SIZE_KB(a)	  (a/1024)
	DE_NOTI("tag_size  = %d (max:%d)\n", tag_size, DTVSOC_IPC_TOTAL_SIZE);
	DE_NOTI("system_info[0x%08x] model[0x%08x]\n", p->system_info.u32Data, p->model.u32Data);
	if (p->fw_mcu0.size)     DE_NOTI("fw_mcu0    = 0x%08x, %4dMB\n",p->fw_mcu0.base,     SIZE_MB(p->fw_mcu0.size));
	if (p->de_svp_m0.size)   DE_NOTI("de_svp_m0  = 0x%08x, %4dMB\n",p->de_svp_m0.base,   SIZE_MB(p->de_svp_m0.size));
	if (p->de_svp_m1.size)   DE_NOTI("de_svp_m1  = 0x%08x, %4dMB\n",p->de_svp_m1.base,   SIZE_MB(p->de_svp_m1.size));
	if (p->de_svp_m2.size)   DE_NOTI("de_svp_m2  = 0x%08x, %4dMB\n",p->de_svp_m2.base,   SIZE_MB(p->de_svp_m2.size));
	if (p->de_nsvp_m1.size)  DE_NOTI("de_nsvp_m1 = 0x%08x, %4dMB\n",p->de_nsvp_m1.base,  SIZE_MB(p->de_nsvp_m1.size));
	if (p->de_nsvp_m2.size)  DE_NOTI("de_nsvp_m2 = 0x%08x, %4dMB\n",p->de_nsvp_m2.base,  SIZE_MB(p->de_nsvp_m2.size));
	if (p->de_vt_m1.size)    DE_NOTI("de_vt_m1   = 0x%08x, %4dMB\n",p->de_vt_m1.base,    SIZE_MB(p->de_vt_m1.size));
	if (p->de_vt_m2.size)    DE_NOTI("de_vt_m2   = 0x%08x, %4dMB\n",p->de_vt_m2.base,    SIZE_MB(p->de_vt_m2.size));
	if (p->de_hdr.size)      DE_NOTI("de_hdr     = 0x%08x, %4dKB\n",p->de_hdr.base,      SIZE_KB(p->de_hdr.size));
	if (p->be_fpp.size)      DE_NOTI("be_fpp     = 0x%08x, %4dMB\n",p->be_fpp.base,      SIZE_MB(p->be_fpp.size));
	if (p->be_frc0.size)     DE_NOTI("be_frc0    = 0x%08x, %4dMB\n",p->be_frc0.base,     SIZE_MB(p->be_frc0.size));
	if (p->be_frc1.size)     DE_NOTI("be_frc1    = 0x%08x, %4dMB\n",p->be_frc1.base,     SIZE_MB(p->be_frc1.size));
	if (p->be_frc2.size)     DE_NOTI("be_frc2    = 0x%08x, %4dMB\n",p->be_frc2.base,     SIZE_MB(p->be_frc2.size));
	if (p->be_wcg.size)      DE_NOTI("be_wcg     = 0x%08x, %4dKB\n",p->be_wcg.base,      SIZE_KB(p->be_wcg.size));
	if (p->fpp_info.size)    DE_NOTI("fpp_info   = 0x%08x, %4dKB\n",p->fpp_info.base,    SIZE_KB(p->fpp_info.size));
	if (p->vdec_pool_0.size) DE_NOTI("vdec_0     = 0x%08x, %4dMB\n",p->vdec_pool_0.base, SIZE_MB(p->vdec_pool_0.size));
	if (p->vdec_pool_1.size) DE_NOTI("vdec_1     = 0x%08x, %4dMB\n",p->vdec_pool_1.base, SIZE_MB(p->vdec_pool_1.size));
	if (p->pe_db.size)       DE_NOTI("pe_db      = 0x%08x, %4dMB\n",p->pe_db.base,       SIZE_MB(p->pe_db.size));
	if (p->pe_hdr.size)      DE_NOTI("pe_hdr     = 0x%08x, %4dMB\n",p->pe_hdr.base,      SIZE_MB(p->pe_hdr.size));
	if (p->fw_dnn.size)      DE_NOTI("fw_dnn     = 0x%08x, %4dMB\n",p->fw_dnn.base,      SIZE_MB(p->fw_dnn.size));
	if (p->fw_mcu1.size)     DE_NOTI("fw_mcu1    = 0x%08x, %4dMB\n",p->fw_mcu1.base,     SIZE_MB(p->fw_mcu1.size));
	if (p->fw_mcu2.size)     DE_NOTI("fw_mcu2    = 0x%08x, %4dMB\n",p->fw_mcu2.base,     SIZE_MB(p->fw_mcu2.size));
	if (p->fw_mcu3.size)     DE_NOTI("fw_mcu3    = 0x%08x, %4dMB\n",p->fw_mcu3.base,     SIZE_MB(p->fw_mcu3.size));
	if (p->fw_shared.size)   DE_NOTI("fw_shared  = 0x%08x, %4dMB\n",p->fw_shared.base,   SIZE_MB(p->fw_shared.size));
	if (p->fw_mcu4.size)     DE_NOTI("fw_mcu4    = 0x%08x, %4dMB\n",p->fw_mcu4.base,     SIZE_MB(p->fw_mcu4.size));
	if (p->be_led.size)      DE_NOTI("be_led     = 0x%08x, %4dKB\n",p->be_led.base,      SIZE_KB(p->be_led.size));
	if (p->be_phdr.size)     DE_NOTI("be_phdr    = 0x%08x, %4dKB\n",p->be_phdr.base,     SIZE_KB(p->be_phdr.size));
	if (p->be_chipinfo.size) DE_NOTI("chipinfo   = 0x%08x, %4dMB\n",p->be_chipinfo.base, SIZE_MB(p->be_chipinfo.size));
	if (p->lne_pool.size)    DE_NOTI("lne_pool   = 0x%08x, %4dMB\n",p->lne_pool.base,    SIZE_MB(p->lne_pool.size));
	if (p->de_dbg_m1.size)   DE_NOTI("de_dbg_m1  = 0x%08x, %4dMB\n",p->de_dbg_m1.base,   SIZE_MB(p->de_dbg_m1.size));
	if (p->de_dbg_m2.size)   DE_NOTI("de_dbg_m2  = 0x%08x, %4dMB\n",p->de_dbg_m2.base,   SIZE_MB(p->de_dbg_m2.size));
	if (p->shared_mem_info.sys_time.size)         DE_NOTI("sys_time   = 0x%08x, %4dKB\n",p->shared_mem_info.sys_time.base,         SIZE_KB(p->shared_mem_info.sys_time.size));
	if (p->shared_mem_info.sys_time_diff.size)    DE_NOTI("time_diff  = 0x%08x, %4dKB\n",p->shared_mem_info.sys_time_diff.base,    SIZE_KB(p->shared_mem_info.sys_time_diff.size));
	if (p->shared_mem_info.video_delay_info.size) DE_NOTI("delay_info = 0x%08x, %4dKB\n",p->shared_mem_info.video_delay_info.base, SIZE_KB(p->shared_mem_info.video_delay_info.size));
	if (p->shared_mem_info.de_gps.size)           DE_NOTI("de_gps     = 0x%08x, %4dKB\n",p->shared_mem_info.de_gps.base,           SIZE_KB(p->shared_mem_info.de_gps.size));
	DE_NOTI("panel:%d,set:%d,maker:%d,res:%d,frate:%d\n",p->model.panel_type,p->model.set_type,p->model.panel_maker,p->model.panel_resolution,p->model.panel_frame_rate);
	DE_NOTI("ext:%d,tcon:%d,carry:%d,vx1:%d\n",p->model.external_chip,p->model.tcon_Scramble,p->model.panel_carry_over,p->model.vx1_byte);
}

static void _resume_tag_info(void)
{
	UINT32 						*pTagBase = NULL;
	UINT32 tag_size = 0;
	DE_REG_O24_IPC_SYSTEM_T		fw_tag_info;

	if (sizeof(DE_REG_O24_IPC_SYSTEM_T) < DTVSOC_IPC_TOTAL_SIZE)
	{
		tag_size = sizeof(DE_REG_O24_IPC_SYSTEM_T);
	}
	else
	{
		tag_size = DTVSOC_IPC_TOTAL_SIZE;
	}

	memcpy(&fw_tag_info, &g_Mem_Info, tag_size);

	// tagging magic , fw base and frame base
	pTagBase = (UINT32*)ioremap(DE_IPC_GEN_O24_BASE, tag_size);
	if(pTagBase)
	{
		memcpy(pTagBase, &fw_tag_info, tag_size);
		wmb();
		_print_tag_info(&fw_tag_info, tag_size);
		iounmap((void*)pTagBase);
	}

}

static void _backup_mem_sys_info(DE_REG_O24_IPC_SYSTEM_T *tag_info)
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
	p->de_gps_crc.base   = 0;//tag_info->de_gps_crc.base;
	p->de_gps_crc.size   = 0;//tag_info->de_gps_crc.size;
}

static void _set_tag_info(void)
{
#define SYSTEM_MAGIC_WORD           0xDECAFE
	UINT32						opt = 0;
	DE_REG_O24_IPC_SYSTEM_T		fw_tag_info;
	UINT64 hma_addr = 0;
	UINT32 hma_size = 0;
	UINT32 tag_size = 0;

	do {
		if (sizeof(DE_REG_O24_IPC_SYSTEM_T) < DTVSOC_IPC_TOTAL_SIZE)
		{
			tag_size = sizeof(DE_REG_O24_IPC_SYSTEM_T);
		}
		else
		{
			tag_size = DTVSOC_IPC_TOTAL_SIZE;
		}

		de_cfg_o24_get_hw_opt(&opt);

		memset(&fw_tag_info, 0, tag_size);
		fw_tag_info.system_info.magic_word = SYSTEM_MAGIC_WORD;

#ifdef USE_VIDEO_FOR_FPGA
		fw_tag_info.system_info.asic = 2/*1:ASIC,2:FPGA*/;
#else
		fw_tag_info.system_info.asic = 1/*1:ASIC,2:FPGA*/;
#endif
		if ( lx_chip_rev() >= LX_CHIP_REV(O24,A1) ) {
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

		fw_tag_info.fpp_info.base  = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_FPP;
		fw_tag_info.fpp_info.size  = VIDEO_O24_FW_SHARED_SIZE_FPP;

		fw_tag_info.shared_mem_info.video_delay_info.base = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_DLY;
		fw_tag_info.shared_mem_info.video_delay_info.size = VIDEO_O24_FW_SHARED_SIZE_DLY;

		fw_tag_info.shared_mem_info.de_gps.base = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_GPS;
		fw_tag_info.shared_mem_info.de_gps.size = VIDEO_O24_FW_SHARED_SIZE_GPS;
		//fw_tag_info.de_gps_crc.base = fw_tag_info.shared_mem_info.de_gps.base + VIDEO_O24_FW_SHARED_SIZE_GPS - 8;
		//fw_tag_info.de_gps_crc.size = 8;

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
						DE_REG_O24_NOTI_BACKUP("[%d]%-5s:[%d]0x%08x,%dMB\n",i,vdec_pool_str_table[i],valid_i,(UINT32)(pool_base & 0xFFFFFFFF),pool_size>>20);
						vdec_base[valid_i] = pool_base;
						vdec_size[valid_i] = pool_size;
						valid_i++;
					}
				}
			}

			if (valid_i == 0) {
				DE_REG_O24_NOTI_BACKUP("no valid vdec_pool : skip\n");
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

			DE_REG_O24_NOTI_BACKUP("vdec_pool:0x%08x ~ 0x%08x (%dMB)\n",(UINT32)(pool_start & 0xFFFFFFFF),(UINT32)(pool_end & 0xFFFFFFFF),hma_size>>20);

			fw_tag_info.vdec_pool_0.base = (UINT32)(hma_addr & 0xFFFFFFFF);
			fw_tag_info.vdec_pool_0.size = hma_size;

			lpAddr_win_update	= (LX_DE_VIDEO_DELAY_INFO_MEM_T *)vmap_phys(fw_tag_info.shared_mem_info.video_delay_info.base,  fw_tag_info.shared_mem_info.video_delay_info.size);
		} while(0);

		memcpy(&g_Mem_Info, &fw_tag_info, tag_size);
		_backup_mem_sys_info(&fw_tag_info);
	}while(0);
}

#define DE_REG_O24_FLUSH_TIMEOUT_CNT  (50)
#define DE_REG_O24_FLUSH_TIMEOUT_OK   (2)
static int _de_reg_o24_chk_flush_rst_ctrl_status(void)
{
	int ret = RET_OK;
	O24A0_SET_REG_CTRL0_T set_reg_ctrl0;//0xCC080000
	UINT32 retry_cnt = 0, ok_cnt = 0;

	while (1) {
		#ifdef USE_VIDEO_FOR_FPGA
		msleep(100);
		#else
		msleep(1);
		#endif

		DE_IPC_O24_RdFL(set_reg_ctrl0);
		set_reg_ctrl0.udata32 = DE_IPC_O24_Rd(set_reg_ctrl0);
		if (set_reg_ctrl0.flush_rst_ctrl_status == 0) {
			ok_cnt++;
			//DE_NOTI("flush ok(retry:%d)\n",retry_cnt);
			if (ok_cnt >= DE_REG_O24_FLUSH_TIMEOUT_OK) {
				DE_REG_O24_NOTI_BACKUP("flush done(retry:%d)(%d)\n",retry_cnt,ok_cnt);
				break;
			}
		}

		if (retry_cnt >= DE_REG_O24_FLUSH_TIMEOUT_CNT) {
			DE_REG_O24_NOTI_BACKUP("flush time out(retry:%d)(%d)\n",retry_cnt,ok_cnt);
			ret = RET_TIMEOUT;
			break;
		}

		retry_cnt++;
	}

	return ret;
}

static int _de_reg_o24_mcu_stall_on(int idx)
{
	int is_2nd_try = 0;
	O24A0_SROM_BOOT_MAP1_T srom_boot_map1;//0xCC080028
	O24A0_SROM_BOOT_MAP3_T srom_boot_map3;//0xCC0800F4

	/* do idx 1 only (download order : fw1, fw0) */
	if (idx != 1) return 0;

	DE_IPC_O24_RdFL(srom_boot_map1);
	DE_IPC_O24_RdFL(srom_boot_map3);
	srom_boot_map1.udata32 = DE_IPC_O24_Rd(srom_boot_map1);
	srom_boot_map3.udata32 = DE_IPC_O24_Rd(srom_boot_map3);
	is_2nd_try = (srom_boot_map1.udata32 == 0x50000000 && srom_boot_map3.udata32 == 0x50000000)? 0:1;
	// DE_REG_O24_NOTI_BACKUP("is_2nd_try:%d(0x%08x)\n",is_2nd_try,srom_boot_map1.udata32);

	if (is_2nd_try) {
		DE_IPC_O24_FLWr(ext_intr_enable,0);
		DE_IPC_O24_FLWr(int_intr_enable,0);
		DE_IPC_O24_FLWr(intr_mcu_flag_en,0);
		DE_IPC_O24_FLWr(intr_cpu_flag_en,0);
		DE_IPC_O24_FLWr(intr_mcu1_flag_en,0);

		if (gDE_MCU_WDOG0_O24) {
			gDE_MCU_WDOG0_O24->int_clr = 0x1;
			gDE_MCU_WDOG0_O24->control = 0x0;
			// gDE_MCU_WDOG0_O24->load = 0xffffffff;
		}

		if (gDE_MCU_WDOG1_O24) {
			gDE_MCU_WDOG1_O24->int_clr = 0x1;
			gDE_MCU_WDOG1_O24->control = 0x0;
			// gDE_MCU_WDOG1_O24->load = 0xffffffff;
		}

		msleep(1);

		DE_IPC_O24_RdFL(set_reg_ctrl0);
		DE_IPC_O24_Wr01(set_reg_ctrl0,run_stall,1);
		DE_IPC_O24_Wr01(set_reg_ctrl0,run_stall1,1);
		DE_IPC_O24_WrFL(set_reg_ctrl0);
		msleep(1);

		DE_IPC_O24_RdFL(set_reg_ctrl0);
		DE_IPC_O24_Wr01(set_reg_ctrl0,soft_reset,1);
		DE_IPC_O24_WrFL(set_reg_ctrl0);
		DE_REG_O24_NOTI_BACKUP("wintr off,reset,stall:on\n");

		_de_reg_o24_chk_flush_rst_ctrl_status();
	}

	return 0;
}

static int _de_reg_o24_mcu_stall_off(int idx, UINT32 base)
{
	switch (idx)
	{
		case 0 :
			//if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
			DE_IPC_O24_FLWr(srom_boot_map1, base);
			DE_IPC_O24_FLWr(srom_boot_map2, base);
			DE_IPC_O24_RdFL(set_reg_ctrl0);
			DE_IPC_O24_Wr01(set_reg_ctrl0, start_vector_sel, 0);
			// removed DE_IPC_O24_Wr01(set_reg_ctrl0, mcu_sw_reset, 1);

			//msleep(1); // wait ddr to ddr transition
			DE_IPC_O24_Wr01(set_reg_ctrl0, p_debug_enable, 1);
			DE_IPC_O24_Wr01(set_reg_ctrl0, run_stall, 0);
			DE_IPC_O24_WrFL(set_reg_ctrl0);
			break;
		case 1 :
			//if (fwBaseAddr < USE_VIDEO_MCU_ROM_BASE_ADDR) BREAK_WRONG(fwBaseAddr);
			DE_IPC_O24_FLWr(srom_boot_map3, (base-0x400000));
			DE_IPC_O24_FLWr(srom_boot_map4, (base-0x400000));
			DE_IPC_O24_RdFL(set_reg_ctrl0);
			DE_IPC_O24_Wr01(set_reg_ctrl0, start_vector_sel1, 0);
			// removed DE_IPC_O24_Wr01(set_reg_ctrl0, mcu_sw_reset, 1);

			//msleep(1); // wait ddr to ddr transition
			DE_IPC_O24_Wr01(set_reg_ctrl0, p_debug_enable1, 1);
			DE_IPC_O24_Wr01(set_reg_ctrl0, run_stall1, 0);
			DE_IPC_O24_WrFL(set_reg_ctrl0);
			break;
		default :
			return -1;
	}

	DE_REG_O24_NOTI_BACKUP("stall off(fw%d)(0x%x)\n",idx,base);
	return 0;
}

static int _de_reg_o24_mcu_update_pc(struct vsc_fw_load_param *param)
{
	if (!param) {
		DE_ERROR("null param\n");
		return -1;
	}

	switch (param->idx)
	{
		case 0 :
			DE_IPC_O24_RdFL(pdebug_pc);
			param->pc = DE_IPC_O24_Rd(pdebug_pc);
			break;
		case 1 :
			DE_IPC_O24_RdFL(pdebug_pc1);
			param->pc = DE_IPC_O24_Rd(pdebug_pc1);
			break;
		default:
			return -1;
	}

	//DE_NOTI("fw%d pc:0x%08x\n",param->idx,param->pc);

	if (param->idx == 0) {
		struct vsc_fw_load_param *p0 = &_g_de_reg_o24_fw_load_p[0];
		struct vsc_fw_load_param *p1 = &_g_de_reg_o24_fw_load_p[1];
		DE_NOTI("pc : fw0:0x%08x, fw1:0x%08x\n",p0->pc,p1->pc);
	}

	return 0;
}

static int _de_reg_o24_mcu_update_exce(struct vsc_fw_load_param *param)
{
	if (!param) {
		DE_ERROR("null param\n");
		return -1;
	}

	if (!gDE_IMX_VERI_15_O24) {
		DE_ERROR("null reg\n");
		return -1;
	}

	if (param->idx == 0) {
		param->exce = gDE_IMX_VERI_15_O24->exception;
	}
	else if (param->idx == 1) {
		param->exce = gDE_IMX_VERI_15_O24->exception1;
	}
	else {
		DE_ERROR("wrong idx(%d)\n",param->idx);
		return -1;
	}

	DE_NOTI("exc%d:0x%08x\n",param->idx,param->exce);
	return 0;
}

static int _de_reg_o24_mcu_mem_cpy(UINT32 src, UINT32 dst, UINT32 size)
{
	REG_MCU_EDMA_EDMA_CTRL_T edma_ctrl;//0xCC0C0014

	DE_NOTI("src:0x%08x, dst:0x%08x, size:%d\n",src,dst,size);

	if (gDE_MCU_EDMA_O24 == NULL) {DE_ERROR("null gDE_MCU_EDMA_O24\n");return -1;}
	if (!src) {DE_ERROR("null src\n");return -1;}
	if (!dst) {DE_ERROR("null dst\n");return -1;}
	if (!size) {DE_ERROR("no size\n");return -1;}

	edma_ctrl.udata32 = gDE_MCU_EDMA_O24->edma_ctrl.udata32;
	if (edma_ctrl.tx_done == 0) DE_WARN("edma busy\n");

	gDE_MCU_EDMA_O24->tx_src_addr.udata32 = src;
	gDE_MCU_EDMA_O24->tx_dst_addr.udata32 = dst;
	gDE_MCU_EDMA_O24->tx_length.udata32 = size;
	edma_ctrl.tx_start = 1;
	gDE_MCU_EDMA_O24->edma_ctrl.udata32 = edma_ctrl.udata32;

	return 0;
}

static int _de_reg_o24_fwload_handler(struct vsc_fw_load_param *param, int action)
{
	int ret = 0;

	if (!param) {
		DE_ERROR("null param\n");
		return -1;
	}

	if (action == VSC_FW_LOAD_STOP) {
		DE_REG_O24_NOTI_BACKUP("stop(%s)(%d)\n",param->name,param->idx);
		_de_reg_o24_mcu_stall_on(param->idx);
	}
	else if (action == VSC_FW_LOAD_PREPARE) {
		DE_REG_O24_NOTI_BACKUP("prepare(%s)(%d)\n",param->name,param->idx);
		_de_reg_o24_mcu_stall_on(param->idx);
		if (param->idx == 0) {
			_resume_tag_info();
		}
	}
	else if (action == VSC_FW_LOAD_COMPLETE) {
		DE_REG_O24_NOTI_BACKUP("complete(%s)(%d)(0x%08x)\n",param->name,param->idx,param->rom_base);
		_de_reg_o24_mcu_stall_off(param->idx,param->rom_base);
	}
	else if (action == VSC_FW_MEM_CPY) {
		_de_reg_o24_mcu_mem_cpy(param->mem_src,param->mem_dst,param->mem_size);
	}
	else if (action == VSC_FW_UPDATE_PC) {
		_de_reg_o24_mcu_update_pc(param);
	}
	else if (action == VSC_FW_UPDATE_EXCE) {
		_de_reg_o24_mcu_update_exce(param);
	}

	if (action < VSC_FW_LOAD_MAX) {
		param->action = action;
	}

	return ret;
}

int de_reg_o24_fwload_register(struct vsc_fw_load *load)
{
	struct vsc_fw_load_param *p;

	if (!load) {
		DE_ERROR("null load\n");
		return -1;
	}

	load->handler = _de_reg_o24_fwload_handler;

	p = &_g_de_reg_o24_fw_load_p[0];
	p->secure = de_cfg_o24_is_mcu_se_map(p->idx);
	p->dst_base = (phys_addr_t)g_fw_mcu0.base;
	p->int_pool = g_m0_pqe_nsv.name;
	p->int_base = (phys_addr_t)g_m0_pqe_nsv.base;
	load->param[0] = p;

	p = &_g_de_reg_o24_fw_load_p[1];
	p->secure = de_cfg_o24_is_mcu_se_map(p->idx);
	p->dst_base = (phys_addr_t)g_fw_mcu1.base;
	p->int_pool = g_m1_pqe_nsv.name;
	p->int_base = (phys_addr_t)g_m1_pqe_nsv.base;
	load->param[1] = p;

	DE_REG_O24_NOTI_BACKUP("fwload_init done\n");

	return 0;
}

int DE_REG_O24_FW_Download(LX_DE_FW_DWLD_T *pstParams)
{
	int ret = RET_OK;
	char *lpAddr = NULL;
	LX_MEMCFG_T *pFwMem = NULL;
	UINT32 fwBaseAddr, fwSize, fwBaseOfst = 0;

	do {
		CHECK_KNULL(pstParams);

		DE_REG_O24_NOTI_BACKUP("fw_dl start(fw:%d)(cfg:%d)(size:%d)\n",pstParams->inx,pstParams->cfg,pstParams->size);

		switch (pstParams->inx)
		{
			case 0 :
				pFwMem = &g_fw_mcu0;
				break;
			case 1 :
				pFwMem = &g_fw_mcu1;
				break;
			case 2 :
			case 3 :
			case 4 :
			default:
				pFwMem = NULL;
				break;
		}

		if (pFwMem==NULL)	{DE_REG_O24_NOTI_BACKUP("fw_dl not support(fw:%d)\n",pstParams->inx);break;}
		if (!pFwMem->base)	{DE_REG_O24_NOTI_BACKUP("fw_dl skip(base0)(fw:%d)\n",pstParams->inx);break;}
		if (!pFwMem->size)	{DE_REG_O24_NOTI_BACKUP("fw_dl skip(size0)(fw:%d)\n",pstParams->inx);break;}

		_de_reg_o24_mcu_stall_on(pstParams->inx);

		if (pstParams->inx==0)	_resume_tag_info();

		do {
			fwBaseAddr = pFwMem->base;
			fwBaseOfst = GET_RDUP(fwBaseOfst, 4);
			fwSize = pstParams->size + fwBaseOfst;
			fwSize  = GET_RDUP(fwSize, 4);

			DE_REG_O24_NOTI_BACKUP("fw_dl load(fw%d)(addr:0x%08x+0x%x)(size:%d)\n",pstParams->inx,fwBaseAddr,fwBaseOfst,fwSize);

			if (pFwMem->size < fwSize)
			{
				DE_REG_O24_NOTI_BACKUP("fw_dl skip loading(abnormal size)\n");
				break;
			}

			if (pstParams->cfg==DE_FW_CFG_CPY_TO_DDR_SKIP)
			{
				DE_REG_O24_NOTI_BACKUP("fw_dl skip loading(run fw)\n");
				break;
			}

			lpAddr	= (char *)vmap_phys(fwBaseAddr, fwSize);

			CHECK_KNULL(lpAddr);
			if (pstParams->cfg==DE_FW_CFG_COPY_BIN_TO_DDR)
			{
				struct file *vsc_filp = (struct file *)pstParams->pData;
				vsc_filp->f_pos = 0;
				ret = kernel_read(vsc_filp, (char*)((uintptr_t)lpAddr + (uintptr_t)fwBaseOfst),pstParams->size,&vsc_filp->f_pos);//vfs_read(legacy)
				DE_REG_O24_NOTI_BACKUP("fw_dl kernel_read ret(%d)\n",ret);
				ret = (ret<0)? RET_ERROR:RET_OK;
			}
			else if (pstParams->cfg==DE_FW_CFG_COPY_USR_TO_DDR)
			{
				ret = copy_from_user((char*)((uintptr_t)lpAddr + (uintptr_t)fwBaseOfst), pstParams->pData, pstParams->size);
				DE_REG_O24_NOTI_BACKUP("fw_dl copy_from_user ret(%d)\n",ret);
			}
			else
			{
				memcpy((char*)((uintptr_t)lpAddr + (uintptr_t)fwBaseOfst), pstParams->pData, pstParams->size);
			}
			wmb();
			if (lpAddr) vunmap_phys((void*)lpAddr);
		} while(0);

		_de_reg_o24_mcu_stall_off(pstParams->inx,fwBaseAddr);

		DE_REG_O24_NOTI_BACKUP("fw_dl done(fw:%d)\n",pstParams->inx);

	} while (0);

	return ret;
}

int DE_REG_O24_FW_GetMaxNum(UINT32 *pMaxNum)
{
	if (!pMaxNum)	return RET_ERROR;

	if ( lx_chip_rev() >= LX_CHIP_REV(O24,A0) )
	{
		*pMaxNum = USE_VIDEO_MCU_FW_MAX_NUM;
	}
	else
	{
		return RET_ERROR;
	}

	return RET_OK;
}

int DE_REG_O24_SetCviFir(LX_DE_CVI_FIR_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetCviTpg(LX_DE_CVI_TPG_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetCviCsampleMode(LX_DE_CSAMPLE_MODE_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetEdgeCrop(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_ResetDE(BOOLEAN bReset)
{
	int ret = RET_OK;

	return ret;
}

BOOLEAN DE_REG_O24_IPCisAlive(void)
{
	BOOLEAN isFwDownloaded = FALSE;
	DE_IPC_O24_FLRf(int_intr_enable, ipc_interrupt_enable_mcu, isFwDownloaded);

	return GET_BITS(isFwDownloaded, VIDEO_IPC_INTERRUPT_ARM_BIT, 1);
}

int DE_REG_O24_SetUdMode(BOOLEAN *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_VTM;
	} while (0);

	return ret;
}

int DE_REG_O24_GetVTM(LX_DE_VTM_FRAME_INFO_T *pstParams)
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

int DE_REG_O24_SetGeneralCapturePath(LX_DE_GCP_INFO_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);
		pstParams->address = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_VTV; // base of VTV shared mem
	} while (0);

	return ret;
}

int DE_REG_O24_SelectMultiWinSrc(LX_DE_MULTI_WIN_SRC_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

/**
 * control vsync interrupt from de hardware
 */
int DE_REG_O24_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en)
{
	int ret = RET_OK;

	return ret;
}

/**
 * get irq number
 */
int DE_REG_O24_GetIrqNum(UINT32 mcu_id, UINT32 *ipc_irq_num, UINT32 *sync_irq_num)
{
	switch(mcu_id)
	{
		case 0:
			*ipc_irq_num  = O24_IRQ_IPC_BCPU;
			*sync_irq_num = O24_IRQ_DE_BCPU;
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
int DE_REG_O24_SetDebug(LX_DE_SET_DBG_T *pstParams)
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
int DE_REG_O24_SetInterfaceConfig(LX_DE_IF_CONFIG_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->config_type) {
			case LX_DE_CONFIG_TYPE_ALL :
			case LX_DE_CONFIG_TYPE_DISPLAY_MIRROR:
				g_Display_mirror_O24 = pstParams->display_mirror;
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
int DE_REG_O24_GetSystemStatus(LX_DE_SYS_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SYS_STATUS_ALL :
			case LX_DE_SYS_STATUS_DISPALY_MIRROR:
				pstParams->display_mirror = g_Display_mirror_O24;
				break;
			default :
				break;
		}
	} while (0);

	return ret;
}

static int DE_REG_O24_GetMviInfo_CheckValid(void)
{
	int ret = RET_OK;
#define DE_REG_O24_MVI_INFO_MAGIC	0xDECAFE

	if (gDE_DDR_MVI_O24 == NULL)	return RET_ERROR;

	if (_g_de_reg_o24_mvi_magic != DE_REG_O24_MVI_INFO_MAGIC)
	{
		rmb();
		_g_de_reg_o24_mvi_magic = gDE_DDR_MVI_O24->magic;
	}

	ret = (_g_de_reg_o24_mvi_magic == DE_REG_O24_MVI_INFO_MAGIC)? RET_OK:RET_ERROR;

	DE_TRACE_20("magic : 0x%08x (ret : %d)\n",_g_de_reg_o24_mvi_magic,ret);

	return ret;
}

static int DE_REG_O24_GetMviInfo_lagecy(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 frame_rate_residual;
	UINT32 frame_rate_div;
	UINT32 framerate;
	UINT32 vdec_port;
	UINT32 scan;
	volatile LX_DE_VDEC_IPC_REG_T *p_vdec_ipc_reg;
	if(pstParams->win_id > LX_DE_WIN_MAX) return -1;

	do {
		CHECK_KNULL(pstParams);

		vdec_port = pstParams->inSrcPort[LX_DE_WIN_MAIN];
		if(vdec_port > 3)
		{
			DE_ERROR("invalid vdec port");
			vdec_port = 0;
		}

		p_vdec_ipc_reg = gDE_VDEC_O24[vdec_port];
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
			p_vdec_ipc_reg = gDE_VDEC_O24[vdec_port];
			pstParams->vdecInfo.par_width  = p_vdec_ipc_reg->par.par_width;
			pstParams->vdecInfo.par_height = p_vdec_ipc_reg->par.par_height;
			pstParams->vdecInfo.afd = p_vdec_ipc_reg->frame_idx.active_format_desc;
			pstParams->vdecInfo.h_size = p_vdec_ipc_reg->picture_size.width;
			pstParams->vdecInfo.v_size = p_vdec_ipc_reg->picture_size.height;
		}
		else if(pstParams->win_id == 2 || pstParams->win_id == 3)//AVTASK-1334
		{
			UINT32 idx,ins_id;
			DE_REG_O24_IPC_DAR_INFO_T shdw;
			idx = (pstParams->win_id == 2)? 0:1;

			memcpy(&shdw,(const void *)gDE_DAR_INFO_O24[idx],sizeof(DE_REG_O24_IPC_DAR_INFO_T));
			ins_id = shdw.info_0.vdisp_instance_number;
			pstParams->vdecInfo.h_size = shdw.info_0.width;
			pstParams->vdecInfo.v_size = shdw.info_0.height;
			pstParams->vdecInfo.isProg = (shdw.info_2.display_mode==3)?1:0;
			pstParams->vdecInfo.v_freq = (pstParams->vdecInfo.isProg == 0)? (shdw.info_2.v_freq>>1):shdw.info_2.v_freq;//because of x2 in vp_kwrap_readtiminginfo_frm_vdec()
			pstParams->vdecInfo.svp = shdw.info_2.svp;
			pstParams->vdecInfo.par_width  = shdw.info_1.par_width;
			pstParams->vdecInfo.par_height = shdw.info_1.par_height;
			pstParams->vdecInfo.afd = shdw.info_1.active_format_desc;
			DE_TRACE_20("dar%d %d/%d 0:%d/%d/%d 1:%d/%d/%d 2:%d/%d/%d\n",\
				idx,pstParams->win_id,ins_id,shdw.info_0.vdisp_instance_number,shdw.info_0.width,shdw.info_0.height,\
				shdw.info_1.active_format_desc,shdw.info_1.par_width,shdw.info_1.par_height,\
				shdw.info_2.display_mode,shdw.info_2.svp,shdw.info_2.v_freq);
		}
		DE_TRACE_21("wid:%d: h/v:%d/%d, scan:%d, fr:%d, svp:%d, par:%d/%d/%d\n",\
			pstParams->win_id,pstParams->vdecInfo.h_size,pstParams->vdecInfo.v_size,pstParams->vdecInfo.isProg,pstParams->vdecInfo.v_freq,\
			pstParams->vdecInfo.svp,pstParams->vdecInfo.par_width,pstParams->vdecInfo.par_height,pstParams->vdecInfo.afd);
	} while (0);

	return ret;
}

static int DE_REG_O24_GetMviInfo(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;
	UINT32 vdec_port, path, win_id, ins_id;
	UINT32 frame_rate_residual, frame_rate_div, framerate, scan;
	LX_DE_VDEC_IPC_REG_T shdw;
	volatile LX_DE_VDEC_IPC_REG_T *phys;

	if (gDE_DDR_MVI_O24 == NULL)	return RET_ERROR;

	do {
		CHECK_KNULL(pstParams);

		win_id = pstParams->win_id;
		if (win_id > 3)	{DE_TRACE_21("not support wid(%d)\n",win_id);ret = RET_ERROR;break;}

		path = (win_id == 0)? 0:1;
		vdec_port = pstParams->inSrcPort[path];

		rmb();
		phys = &gDE_DDR_MVI_O24->mvi[win_id];
		shdw.frame_idx.udata32 = phys->frame_idx.udata32;
		shdw.display_info.udata32 = phys->display_info.udata32;
		shdw.frame_rate.udata32 = phys->frame_rate.udata32;
		shdw.picture_size.udata32 = phys->picture_size.udata32;
		shdw.par.udata32 = phys->par.udata32;

		ins_id = shdw.frame_idx.vdisp_instance_number;
		scan = shdw.display_info.display_mode;
		frame_rate_residual	= shdw.frame_rate.frame_rate_residual;
		frame_rate_div		= (shdw.frame_rate.frame_rate_div > 0)?shdw.frame_rate.frame_rate_div:1;
		framerate			= (frame_rate_residual * 100)/frame_rate_div;

		pstParams->vdecInfo.h_size = shdw.picture_size.width;
		pstParams->vdecInfo.v_size = shdw.picture_size.height;
		pstParams->vdecInfo.h_start = 0;
		pstParams->vdecInfo.v_start = 0;
		pstParams->vdecInfo.isProg = (scan==3)?1:0;
		pstParams->vdecInfo.v_freq = framerate;
		pstParams->vdecInfo.svp = shdw.display_info.svp;
		pstParams->vdecInfo.par_width  = shdw.par.par_width;
		pstParams->vdecInfo.par_height = shdw.par.par_height;
		pstParams->vdecInfo.afd = shdw.frame_idx.active_format_desc;

		DE_TRACE_21("w%d p%d ins%d size:%dx%d scan:%d fr:%d par:%dx%d afd:%d\n",win_id,vdec_port,ins_id,\
			pstParams->vdecInfo.h_size,pstParams->vdecInfo.v_size,pstParams->vdecInfo.isProg,pstParams->vdecInfo.v_freq,\
			pstParams->vdecInfo.par_width,pstParams->vdecInfo.par_height,pstParams->vdecInfo.afd);
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
int DE_REG_O24_GetSourceStatus(LX_DE_SRC_STATUS_T *pstParams)
{
	int ret = RET_OK;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->status_type) {
			case LX_DE_SRC_STATUS_ALL :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_O24[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_O24[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB]	 = g_WinsrcMap_O24[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_O24[LX_DE_WIN_SUB];

				pstParams->operType= g_SrcOperType_O24;
				pstParams->operCtrlFlag = g_SrcOperCtrlFlag_O24;

				pstParams->subOperType =  g_SrcSubOperType_O24;
				pstParams->subOperCtrlFlag = g_SrcSubOperCtrlFlag_O24;
				break;
			case LX_DE_SRC_STATUS_INPUT_SRC :
				pstParams->inSrc[LX_DE_WIN_MAIN] = g_WinsrcMap_O24[LX_DE_WIN_MAIN];
				pstParams->inSrcPort[LX_DE_WIN_MAIN] = g_WinsrcPort_O24[LX_DE_WIN_MAIN];
				pstParams->inSrc[LX_DE_WIN_SUB] = g_WinsrcMap_O24[LX_DE_WIN_SUB];
				pstParams->inSrcPort[LX_DE_WIN_SUB] = g_WinsrcPort_O24[LX_DE_WIN_SUB];
				break;
			case LX_DE_SRC_STATUS_OPER :
				pstParams->operType  = g_SrcOperType_O24;
				pstParams->operCtrlFlag = g_SrcOperCtrlFlag_O24;
				break;

			case LX_DE_SRC_STATUS_SUB_OPER :
				pstParams->subOperType =  g_SrcSubOperType_O24;
				pstParams->subOperCtrlFlag = g_SrcSubOperCtrlFlag_O24;
				break;

			case LX_DE_SRC_STATUS_VDEC_INFO :
				if (RET_OK == DE_REG_O24_GetMviInfo_CheckValid())
				{
					ret = DE_REG_O24_GetMviInfo(pstParams);
				}
				else
				{
					ret = DE_REG_O24_GetMviInfo_lagecy(pstParams);
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
int DE_REG_O24_SetOperation(LX_DE_OPERATION_CTRL_T *pstParams)
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

		g_SrcOperType_O24 = type;
		g_SrcOperCtrlFlag_O24 = flag;
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
int DE_REG_O24_SetSubOperation(LX_DE_SUB_OPERATION_CTRL_T *pstParams)
{
	int ret = RET_OK;
	UINT16 flag = 0;

	do {
		CHECK_KNULL(pstParams);

		switch (pstParams->operation) {
			case LX_DE_SUB_OPER_OFF :
				g_SrcSubOperType_O24 = LX_DE_SUB_OPER_OFF;
				break;
			case LX_DE_SUB_OPER_CAPTURE:
				g_SrcSubOperType_O24 = LX_DE_SUB_OPER_CAPTURE;
				flag = pstParams->capture_enable;
				break;
			case LX_DE_SUB_OPER_VENC:
				g_SrcSubOperType_O24 = LX_DE_SUB_OPER_VENC;
				flag = pstParams->vencCtrl.bOnOff;
				break;
			case LX_DE_SUB_OPER_SCART_OUT:
				g_SrcSubOperType_O24 = LX_DE_SUB_OPER_SCART_OUT;
				flag = 1;
				break;
			case LX_DE_SUB_OPER_MAX :
			default :
				BREAK_WRONG(pstParams->operation);
		}
	} while (0);

	g_SrcSubOperCtrlFlag_O24 = flag;
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
int DE_REG_O24_GetFIR(LX_DE_CVI_SRC_TYPE_T *pstParams, LX_DE_CVI_FIR_T *fir)
{
	int ret = RET_OK;
	int i = 0;
	// CVI FIR coefficient for Y - 11 Tap,Cbcr - 11 Tap
	UINT16 coef_FIR_Y_Normal[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_Y_Double[] = {256, 0, 0, 0, 0, 0, 0, 0};
	UINT16 coef_FIR_Y_Quad[]   = {64, 56, 34, 12, 0, -6, 0, 0};	// 55 >> 56 --> sum 254 >> 256
	UINT16 coef_FIR_O24_CVD_CbCr_Normal[] = {160, 49, -1, 0, 0, 0};// CVI FIR Filter for 1 pixel & 422
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
							fir->fir_coef_CbCr[i] = coef_FIR_O24_CVD_CbCr_Normal[i];
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
int DE_REG_O24_SetHdmiPort(LX_DE_HDMIPORT_T *pstParams)
{
	int ret = RET_OK;

	g_HdmiPort_O24[pstParams->win_id] = pstParams->port_num;  // assign from vp_kadp
	DE_TRACE("win-hdmi map [%d / %d]", pstParams->win_id, pstParams->port_num);

	return ret;
}

int DE_REG_O24_GetCapacity(LX_DE_CAPACITY_T *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_GetLocalMute(UINT32 *pstParams)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_SetMemByCma(char* mem_name)
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

			if(o24_de_debug_mem)
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
			DE_NOTI("%s base: 0x%08x, size: %d kB, type: %d(%s)\n",pool_name,p_mem->base,p_mem->size>>10,pool_type,(pool_type==HMA_POOL)? "hma":"cma");
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
			DE_NOTI("%s base: 0x%08x, size: %d kB, type: %d(%s)\n",pool_name,p_mem->base,p_mem->size>>10,pool_type,(pool_type==HMA_POOL)? "hma":"cma");
		}
	}

	return ret;
}

static int _g_de_reg_o24_vtvr_size_m0 = (25*1024*1024);
static int _g_de_reg_o24_vtvr_size_m1 = (50*1024*1024);
int DE_REG_O24_GetMemFromCma(char *mem_name, int count, void *info, BOOLEAN flag)
{
	int ret = RET_OK;
	int size_m0,size_m1;
	int free_m0,free_m1;

	if(strcmp(mem_name, "de-dbgbuf") == 0)
	{
		size_m0 = g_de_dbg_m1.size;
		size_m1 = g_de_dbg_m2.size;

		if(flag)
		{
			hma_pool_status("debug0", hma_pool_status_free_size, &free_m0);
			hma_pool_status("debug1", hma_pool_status_free_size, &free_m1);
			DE_NOTI("debug0 = %dMB(%dMB), debug1 = %dMB(%dMB)\n", size_m0>>20, free_m0>>20, size_m1>>20, free_m1>>20);

			if (dbg_paddr_m0 == 0 && free_m0 > 0)
			{
				if (size_m0 > free_m0)	size_m0 = free_m0;
				dbg_paddr_m0 = hma_alloc("debug0", size_m0, (1<<14));//align:16k
				DE_NOTI("hma_alloc debug0 = %dMB\n", size_m0>>20);
			}

			if (dbg_paddr_m1 == 0 && free_m1 > 0)
			{
				if (size_m1 > free_m1)	size_m1 = free_m1;
				dbg_paddr_m1 = hma_alloc("debug1", size_m1, (1<<14));//align:16k
				DE_NOTI("hma_alloc debug1 = %dMB\n", size_m1>>20);
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

			if (dbg_paddr_m1 != 0)
			{
				hma_free("debug1", dbg_paddr_m1);
				DE_NOTI("hma_free debug1\n");
				dbg_paddr_m1 = 0;
			}
		}
	}
	else if(strcmp(mem_name, "de-vtvrbuf") == 0)
	{
		size_m0 = _g_de_reg_o24_vtvr_size_m0;
		size_m1 = _g_de_reg_o24_vtvr_size_m1;

		//20240105, change vdec_shared to debug (AVTASK-1386)
		if(flag)
		{
			LX_DE_SET_DELAY_BUFFER_T *pBuf_info = info;
			if(!pBuf_info)  { return -1; }
			/* hma alloc */
			if(vr_paddr_m0 != 0) { return -1; }
			if(vr_paddr_m1 != 0) { return -1; }
			vr_paddr_m0 = hma_alloc("debug0", size_m0, (1<<14));//align:16k
			vr_paddr_m1 = hma_alloc("debug1", size_m1, (1<<14));//align:16k
			if(vr_paddr_m0 == 0) { return -2; }
			if(vr_paddr_m1 == 0) { return -2; }
			DE_NOTI("hma_alloc: de-vtvrbuf size_m0 = %dKB, size_m1 = %dKB\n", size_m0/1024, size_m1/1024);

			pBuf_info->pool_size[0] = size_m0;
			pBuf_info->pool_base[0] = vr_paddr_m0;
			pBuf_info->pool_size[1] = size_m1;
			pBuf_info->pool_base[1] = vr_paddr_m1;
			DE_NOTI("use pool(from %s) : start_m0 = 0x%08X, size = %dMB, start_m1 = 0x%08X, size = %dMB", \
				"debug0/debug1", (UINT32)pBuf_info->pool_base[0], size_m0/1024/1024, (UINT32)pBuf_info->pool_base[1], size_m1/1024/1024);
		}
		else
		{
			DE_NOTI("hma_free: de-vtvrbuf\n");

			if(vr_paddr_m0 != 0)
			{
				hma_free("debug0", vr_paddr_m0);
				DE_NOTI("free pool(%s) : 0x%08X","debug0",(UINT32)vr_paddr_m0);
				vr_paddr_m0 = 0;
			}

			if(vr_paddr_m1 != 0)
			{
				hma_free("debug1", vr_paddr_m1);
				DE_NOTI("free pool(%s) : 0x%08X","debug1",(UINT32)vr_paddr_m1);
				vr_paddr_m1 = 0;
			}
		}
	}
	else if(strcmp(mem_name, "de-btbuf") == 0)
	{
#ifdef USE_VIDEO_FOR_FPGA
		char *pool_name = g_de_svp_m0.name;
		size_m0 = g_de_svp_m0.size;
#else
		#ifdef BUILD_FEATURE_ddr_96bit
		char *pool_name = "pqe-bwb";
		size_m0 = g_de_pqe_bwb_size;
		#else
		char *pool_name = "vdec_shared";
		size_m0 = g_de_vdec_shared_size;
		#endif
#endif

		if(flag)
		{
			LX_DE_SET_DELAY_BUFFER_T *pBuf_info = info;
			if(!pBuf_info)  { return -1; }

			if(bt_paddr_m0 == 0) {
#ifdef USE_VIDEO_FOR_FPGA
				bt_paddr_m0 = g_de_svp_m0.base;
#else
				bt_paddr_m0 = hma_alloc_user(pool_name, size_m0, (1<<14), "de_frame_buf");//align:16k
#endif
			}

			pBuf_info->pool_size[0] = size_m0;
			pBuf_info->pool_base[0] = bt_paddr_m0;
			g_Mem_Sys_Info.vdec_pool_0.size = pBuf_info->pool_size[0];
			g_Mem_Sys_Info.vdec_pool_0.base = bt_paddr_m0;
			DE_NOTI("alloc pool(%s) : start = 0x%08X, size = %dMB", \
				pool_name, (UINT32)pBuf_info->pool_base[0], size_m0/1024/1024);

			if(bt_paddr_m0 == 0) { return -3; }
		}
		else
		{
			if(bt_paddr_m0 != 0)
			{
				DE_NOTI("free pool(%s) : start = 0x%08X",pool_name,(UINT32)bt_paddr_m0);
#ifdef USE_VIDEO_FOR_FPGA
#else
				hma_free(pool_name, bt_paddr_m0);
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

LX_MEMCFG_T de_reg_o24_getmeminfo(char* str)
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
	else if (!strncasecmp(str, "de-vtvrbuf", strlen("de-vtvrbuf"))) {
		if (strstr(str,"m1")) {
			meminfo.size = _g_de_reg_o24_vtvr_size_m1;
		}
		else {
			meminfo.size = _g_de_reg_o24_vtvr_size_m0;
		}
	}

	return meminfo;
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
int DE_REG_O24_SetMultiWin(UINT32 *pstParams)
{
	int ret = RET_OK;

	g_QuadWin_O24 = (*pstParams==4)?TRUE:FALSE;

	DE_NOTI("multi window control for quad [%d]", *pstParams);

	return ret;
}

int DE_REG_O24_SetClockGate(CTOP_PQE_CG_O24_MODULE mod, BOOLEAN onOff)
{
	int ret = RET_OK;

	return ret;
}

//#define ADD_CLOCK_GATING
int DE_REG_O24_SetClockPath(BOOLEAN onOff)
{
	int ret = RET_OK;

	return ret;
}

int DE_REG_O24_GetLowDelayClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	*pstParams = g_Zero_delay_mode_O24;

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
int DE_REG_O24_SetLowDelayClock(UINT32 *pstParams)
{
	int ret = RET_OK;

	ret = DE_REG_O24_SetClockPath((BOOLEAN)*pstParams);

	g_Zero_delay_mode_O24 = *pstParams; // 0:OFF, 1:5V_HPD, 2:CVI_INTR

	DE_NOTI("g_Zero_delay_mode_O24 = %d  (0:OFF, 1:5V_HPD, 2:CVI_INTR)", g_Zero_delay_mode_O24);

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
int DE_REG_O24_GetSharedMem(UINT32 page_offset, UINT32 **mem_info)
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
int DE_REG_O24_PreInit(void)
{
	return RET_OK;
}

int DE_REG_O24_GetFPPInfo(UINT32 *start_address)
{
	int ret = RET_OK;

	*start_address = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_FPP;

	DE_NOTI(" start_address = 0x%08x , size = 0x%08x", *start_address, VIDEO_O24_FW_SHARED_SIZE_FPP);

	return ret;
}

int DE_REG_O24_GetMEMInfo(LX_DE_MEM_SYS_INFO_T *pstParams)
{
	int ret = RET_OK;

	if(!pstParams) return RET_ERROR;

	memcpy(pstParams, &g_Mem_Sys_Info, sizeof(LX_DE_MEM_SYS_INFO_T));

	// for SVP (de_frm_m1 info is used for M1 svp in tz)
	//pstParams->de_frm_m1.base = pstParams->de_frm_m2.base;
	//pstParams->de_frm_m1.size = pstParams->de_frm_m2.size;

	return ret;
}

int DE_REG_O24_GetDNNStatus(UINT32 *a, UINT32 *b, UINT32 *c, UINT32 *d, UINT32 *e, UINT32 *f)
{
	int ret = RET_OK;
	UINT32 *lpAddr = NULL;
	UINT32 phys = g_Mem_Info.fpp_info.base + VIDEO_O24_FW_SHARED_OFST_FPP_DNN;// fpp_info.base + 32*1024
	// O24 phys = ?
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

int DE_REG_O24_GetVideoDelay(LX_DE_VIDEO_DELAY_INFO_MEM_T *pstParams)
{
	int ret = RET_OK, i;
	// LX_DE_VIDEO_DELAY_INFO_MEM_T *lpAddr = NULL;

	if(!pstParams) return RET_ERROR;

	if(g_Mem_Info.shared_mem_info.video_delay_info.base == 0 || g_Mem_Info.shared_mem_info.video_delay_info.size == 0) return RET_ERROR;
	//lpAddr	= (LX_DE_VIDEO_DELAY_INFO_MEM_T *)vmap_phys(g_Mem_Info.shared_mem_info.video_delay_info.base,  g_Mem_Info.shared_mem_info.video_delay_info.size);
	if(lpAddr_win_update== NULL)
	{
		return RET_ERROR;
	}
	for(i=0;i<LX_DE_WIN_MAX;i++) {
		memcpy(&pstParams->win[i], &lpAddr_win_update->win[i], sizeof(LX_DE_VIDEO_DELAY_INFO_T));
		//DE_NOTI("i:%d, win[%d] LX_DE_WIN_MAX[%d]", i, pstParams->win[i].win_id, LX_DE_WIN_MAX);
	}
	memcpy(&pstParams->owin_sync, &lpAddr_win_update->owin_sync, sizeof(LX_DE_VIDEO_DELAY_INFO_T));
	rmb();

	//if (lpAddr) vunmap_phys((void*)lpAddr);

	return ret;
}

int DE_REG_O24_FW_DownloadFromHead(LX_DE_FW_DWLD_T *pstParams)
{
	DE_NOTI("not support\n");
	return RET_OK;
}

int DE_REG_O24_FW_Verify(void)
{
	DE_NOTI("not support\n");
	return RET_OK;
}

int DE_REG_O24_GetInitData(LX_DE_IPC_INIT_DATA_T *pstParams)
{
	int ret = RET_OK;

	if (gDE_DDR_MVI_O24 == NULL) {DE_NOTI("gDE_DDR_MVI_O24 null\n");return RET_ERROR;}

	do {
		CHECK_KNULL(pstParams);
		memset((void *)gDE_DDR_MVI_O24,0,sizeof(LX_DE_DDR_MVI_T));
		wmb();

		pstParams->head.magic = 1;
		pstParams->head.idx_num = 1;

		pstParams->u[0].data = g_fw_shared.base + VIDEO_O24_FW_SHARED_OFST_MVI;
		pstParams->u[0].size = VIDEO_O24_FW_SHARED_SIZE_MVI;

		_g_de_reg_o24_mvi_magic = 0;
		DE_NOTI("%08x [0]%08x,%08x\n", pstParams->head.u32,pstParams->u[0].data,pstParams->u[0].size);
	} while(0);

	return ret;
}

int DE_REG_O24_GetHistoBufferRange(UINT32 *start,UINT32 *end)
{
	if(start == NULL || end == NULL)
		return -1;
	*start = g_de_svp_m2.base;
	*end = g_de_svp_m2.base + g_de_svp_m2.size;

	return 0;
}
#endif
/**  @} */
