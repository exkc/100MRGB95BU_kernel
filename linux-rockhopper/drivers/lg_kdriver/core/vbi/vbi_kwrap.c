/******************************************************************************
 *   DTV LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 *   COPYRIGHT(c) 1998-2010 by LG Electronics Inc.
 *
 *   All rights reserved. No part of this work covered by this copyright hereon
 *   may be reproduced, stored in a retrieval system, in any form
 *   or by any means, electronic, mechanical, photocopying, recording
 *   or otherwise, without the prior written  permission of LG Electronics.
 *****************************************************************************/


/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		won.hur (won.hur@lge.com)
 *  @version	1.0
 *  @date		2012-04-03
 *  @note		Additional information.
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
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <linux/io.h>
#include <linux/kthread.h>

#include "os_util.h"
#include "vbi_kapi.h"
#include "vbi_drv.h"
#include "vbi_module.h"
#include "vbi_data.h"
#include "vbi_hw.h"

#include "vbi_kwrap.h"
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
//#define VBI_LATCHUP_DEBUG 1	//temp. latchup debug
#undef VBI_LATCHUP_DEBUG

#define	TTX_SHMEM_MAGIC	0x564249		/* 'V','B','I'*/

#define VBI_VPS_PACKET_SIZE 15          /* Changing this value does not affect any HAL operation */
#define VBI_WSS_PACKET_SIZE 4           /* Changing this value does ont affect any HAL operation */
#define VBI_CGMS_PACKET_SIZE 10
#define VBI_TTX_PACKET_STACK_ALARM  300 /* Places a warning if units of TTX packets are over this value */

#define VBI_WSS_NO_INTERRUPT_THRESHOLD 10	/* Since this should run 50msec, thresdhold for 250msec is nessessary */

#define TT_DECRYPT_CORRECTED	0x80
#define TT_DECRYPT_INVALID		0xff

#define VBI_TTX_DEFAULT_HAMMING_CORRECT_ON	0

//from vbi_kadp
#define VBI_COPYPROTECTION_RAW_ANALOG_CP_FILTER_MAX_SIZE 	100
#define VBI_COPYPROTECTION_RAW_CGMS_FILTER_MAX_SIZE 	100
#define VBI_COPYPROTECTION_WSS_FILTER_MAX_SIZE 		30
#define VBI_COPYPROTECTION_RAW_WSS_FILTER_MAX_SIZE 100
/*----------------------------------------------------------------------------------------
	Macro Definition
----------------------------------------------------------------------------------------*/
#define VBI_DBG_PRINT           VBI_PRINT  //�ӽ� ���� ��ġ
#define TTX_DEBUG				VBI_PRINT
#define VBI_NOTI 				VBI_PRINT
#define TTX_ERROR				VBI_ERROR
#define TTX_TRACE_BEGIN()		TTX_PRINT("[ttx] %s:%d -- BEGIN\n", __F__, __L__)
#define TTX_TRACE_END()			TTX_PRINT("[ttx] %s:%d -- END\n", __F__, __L__ )
#define TTX_TRACE_MARK()		TTX_PRINT("[ttx] %s:%d -- TRACE !!!\n", __F__, __L__ )

#ifdef SEETV_BRINGUP
/* TTX device mutex */
#define TTX_INIT_LOCK()			g_ttx_ctx.dev_mtx = KADP_OSA_OpenSema("kadp-ttx-mtx", LX_OSA_GLOBAL_SEMA, 1);
#define TTX_LOCK()				(void)KADP_OSA_LockSema( g_ttx_ctx.dev_mtx, LX_OSA_INF_WAIT)
#define TTX_UNLOCK()			(void)KADP_OSA_UnlockSema( g_ttx_ctx.dev_mtx )

/* VBI module IOCTL call */
#define IOCTL_CALL(args...)  {ret=ioctl(args); if(ret<0) BREAK_WRONG_IOCTL(ret);}
#endif

/* VBI module KADAPTOR BREAK */
#define BREAK_WRONG(arg)			{if(gVBIBreakPrintOnOff >0){VBI_PRINT("[VBI] %s : Break wrong[%d]. Ret was [%d]\n", __F__, __L__,arg);} ret = RET_ERROR; break;}
#define BREAK_WRONG_IOCTL(arg)    	{if(gVBIBreakPrintOnOff >0){VBI_PRINT("[VBI] %s : Error in IOCTL call(%d). Ret was [%d]\n", __F__, __L__, arg);} break;}

/* VBI Task Disconnector */

/* VBI module Debug macros */
#define TTX_DEBUG_PRINT(fmt, args...)    {if(gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_TTX]>0) VBI_PRINT(fmt,##args);}
#define VPS_DEBUG_PRINT(fmt, args...)    {if(gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_VPS]>0) VBI_PRINT(fmt,##args);}
#define WSS_DEBUG_PRINT(fmt, args...)    {if(gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_WSS]>0) VBI_PRINT(fmt,##args);}
#define CC_DEBUG_PRINT(fmt, args...)     {if(gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CC]>0) VBI_PRINT(fmt,##args);}
#define CGMS_DEBUG_PRINT(fmt, args...)	 {if(gVBIDebugModeStatus.printMask[VBI_DEBUG_PRINT_CGMS]>0) VBI_PRINT(fmt,##args);}

/* VBI moduel open checker */
#define VBI_CHECK_DEVICE()				{if(0){\
											VBI_PRINT("[%s:%d] Error! VBI function was called without opening VBI device.\n", __F__, __L__);\
											return RET_ERROR;}}

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
int vbi_kwrap_ttx_create_file_pointer(void);
int vbi_kwrap_ttx_close_file_pointer(void);
int vbi_kwrap_ttx_close_data_file(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern int	gVBIInterruptControl;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
UINT8  g8VBIDebugInputLine[48];
UINT8  gPacket[48];
UINT8  gVBICopyProtectionDataID = 0;

BOOLEAN gIsVBIThreadCPAlive = FALSE;

static struct task_struct	*cp_Thread = NULL;

int g_vbi_logm_fd = -1;

UINT32	gVBIBreakPrintOnOff = 0;

#ifdef SEETV_BRINGUP
LX_TTX_CXT_T	g_ttx_ctx =
{
	.dev_fd 	= -1,		/* dev_fd should be initialized to -1 */
	.dev_mtx	= NULL,
	.dev_shmem	= NULL,
	._gMMapTTX	= 0,
	.pTTX_Parameter_t = NULL,
	.packet_buffer_t.pTTX_Packet_Buffer = NULL,
	.packet_buffer_t.TTX_Packet_Unit = 0,
	.gmmap_size = 0,
};
#endif

VBI_KWRAP_DEBUGGER_T gVBIDebugModeStatus =
{
    .out_file_status = VBI_FILE_POINTER_NONE,
    .in_file_status = VBI_FILE_POINTER_NONE,
	.dataProfile.full_count  = 0,
	.dataProfile.error_count = 0,
	.dataProfile.max_count_value  = 10000,
	.dataProfile.cc_dont_count_80 = 0,
};

int		gVBIWSSCopyProtectionFilterSize = 0;	// Initial value of WSS Copy Protection Filter length
int		gVBIWSSCopyProtectionFilterThreshold	= 0;

int		gVBIWSSCopyProtectionRAWFilterSize = 0;	// Initial value of WSS Copy Protection RAW Filter length
int		gVBIWSSCopyProtectionRAWFilterThreshold	= 0;

int		gVBICGMSCopyProtectionRAWFilterSize = 0;	// Initial value of CGMS Copy Protection RAW Filter length
int		gVBICGMSCopyProtectionRAWFilterThreshold	= 0;

int		gVBIAnalogCPCopyProtectionRAWFilterSize = 8;	// Initial value of AnalogCP Copy Protection RAW Filter length
int		gVBIAnalogCPCopyProtectionRAWFilterThreshold	= 0;

int		gVBICopyProtectionRawNoInterruptCount	= 3;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int _vbi_kwrap_get_mmap(void);
static int _vbi_kwrap_release_mmap(void);
static int _vbi_kwrap_release(void);
static int _vbi_kwrap_updatedataprofilter(int error);

static int _vbi_kwrap_ttx_enableinterrupt(void);
static int _vbi_kwrap_ttx_startslicer(void);
static int _vbi_kwrap_ttx_stopslicer(void);
static int _vbi_kwrap_ttx_disableinterrupt(void);
static int _vbi_kwrap_ttx_get_packets_from_file(LX_TTX_PACKET_TYPE_T **ttx_packet);
static int _vbi_kwrap_ttx_get_packets_from_mem(LX_TTX_PACKET_TYPE_T **ttx_packet, int packet_count);
static int _vbi_kwrap_ttx_check8to4hamming(UINT8 data);
static int _vbi_kwrap_ttx_correct_hamming_8_4(UINT8 *code);


static int _vbi_kwrap_cc_enableinterrupt(void);
static int _vbi_kwrap_cc_startslicer(void);
static int _vbi_kwrap_cc_stopslicer(void);
static int _vbi_kwrap_cc_disableinterrupt(void);
static int _vbi_kwrap_cc_correct_parity(UINT8 *data);
static int _vbi_kwrap_cc_checkparity(UINT8 data);

static int _vbi_kwrap_get_cp_data(UINT8 **packet, int *is_analog_cp_protected,int *is_analog_cp_Stable);
static int _vbi_kwrap_process_cp_data(UINT8 **packet);
static int _vbi_kwrap_ttx_unittest(LX_TTX_PACKET_TYPE_T **gptPB);
static int _vbi_kwrap_ttx_hammingcorrection(LX_TTX_PACKET_TYPE_T **gptPB);
static int _vbi_kwrap_ttx_dataprofilter(LX_TTX_PACKET_TYPE_T **gptPB);
static int _vbi_kwrap_ttx_data_file_dump(LX_TTX_PACKET_TYPE_T **gptPB);

static int _vbi_kwrap_cc_dataprofilter(LX_CC_DATA_T *packet);
static int _vbi_kwrap_calculate_cp_type(UINT8 **ppacket);

static int vbi_kwrap_ttx_get_status(LX_TTX_TYPE_T ttx_type, UINT32 *ttx_status);
static int vbi_kwrap_cp_dataflush_thread(void *data);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LX_TTX_PACKET_TYPE_T vbi_ttx_packet_t;


static UINT32	gVBIDebugMWUnitTestPointer 	  = 0;	// Used for TARA_MW_UNIT_TEST
static UINT32	gVBIDebugMWUnitTestSubPointer = 0;

static UINT8	gVBIWSSCopyProtectionFilter[VBI_COPYPROTECTION_WSS_FILTER_MAX_SIZE] = {0,};
static UINT8	gVBIWSSCopyProtectionRAWFilter[VBI_COPYPROTECTION_RAW_WSS_FILTER_MAX_SIZE] = {0,};
static UINT8	gVBICGMSCopyProtectionRAWFilter[VBI_COPYPROTECTION_RAW_CGMS_FILTER_MAX_SIZE] = {0,};
static UINT8	gVBIAnalogCPCopyProtectionRAWFilter[VBI_COPYPROTECTION_RAW_ANALOG_CP_FILTER_MAX_SIZE] = {0,};

//static char _gBitReverse[4] = {0x00, 0x10, 0x01, 0x11};
static LX_TTX_PACKET_TYPE_T _g_TTX_packet_for_UnitTest;

unsigned char gVBITeletextUnitTestSig[] = "ff ff ff ff ff ff  2 15 15 15 15 15 15 15 15 15 20 20 20 20 20 20 4c c7 20 54 45 4c 45 54 45 58 54 20 c4 e5 62 75 67 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff  2 49  4 9d  2 8f 20 20 20 4c 20 67 20 45 20 20 d3 20 49 20 43 20 20 20 c4 20 e5 20 62 20 75 20 67 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff c7 5e 20 20 20 20 20 20 20 20 20 20 20 20 20  7 9d 86 9d 85 9d  4 9d 83 9d  2 9d  1 9d 80 9d 20 20 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff  2 64 20 97 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 20 ff ff ff ff ff ff  2 73  7 20 20 20 20 20 31 b0 b0 ae ae ae ae ae ae ae ae ae ae ae ae ae ae 4c c7 20 57 c1 d9 20 20 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff  2 38  1 20 20 20 20 20 31 31 b0 ae ae ae ae ae ae ae ae ae ae ae ae ae ae 46 c1 d3 54 20 20 20 20 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff  2 2f  2 20 20 20 20 20 31 32 b0 ae ae ae ae ae ae ae ae ae ae ae ae ae ae d3 54 52 4f ce c7 20 20 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff  2 d0 83 20 20 20 20 20 31 b3 b0 ae ae ae ae ae ae ae ae ae ae ae ae ae ae d3 cd c1 52 54 20 20 20 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff  2 c7 86 20 20 20 20 20 31 34 b0 ae ae ae ae ae ae ae ae ae ae ae ae ae ae 46 49 c7 c8 54 49 ce c7 20 20 20 20 20 20 20 20 20 ff ff ff ff ff ff c7 c7 20 97 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 70 20 ";

UINT8 gVBI_TTX_Decrypt_Hamming1_Correction_Tab[256] =
{
	/*     0x0x            */
	0x01 | TT_DECRYPT_CORRECTED,  /* 00000000 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 00000001 -> 01000000 */
	0x01,                         /* 00000010 -> 10000001 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 00000011 -> 10100001 */

	TT_DECRYPT_INVALID,           /* 00000100 -> 01000000 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 00000101 -> 10100000 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 00000110 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 00000111 -> 01000001 */

	TT_DECRYPT_INVALID,           /* 00001000 -> 01000010 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 00001001 -> 10100010 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 00001010 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 00001011 -> 01000011 */

	0x0A | TT_DECRYPT_CORRECTED,  /* 00001100 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 00001101 -> 01000010 */
	TT_DECRYPT_INVALID,           /* 00001110 -> 01000011 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 00001111 -> 10100111 */

	/*     0x1x            */
	TT_DECRYPT_INVALID,           /* 00010000 -> 01000000 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 00010001 -> 10100000 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 00010010 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 00010011 -> 01000001 */

	0x00 | TT_DECRYPT_CORRECTED,  /* 00010100 -> 10100000 */
	0x00,                         /* 00010101 -> 10000000 */
	TT_DECRYPT_INVALID,           /* 00010110 -> 01000001 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 00010111 -> 10100000 */

	0x06 | TT_DECRYPT_CORRECTED,  /* 00011000 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 00011001 -> 01000010 */
	TT_DECRYPT_INVALID,           /* 00011010 -> 01000011 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 00011011 -> 10101011 */

	TT_DECRYPT_INVALID,           /* 00011100 -> 01000010 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 00011101 -> 10100000 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 00011110 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 00011111 -> 01000011 */

	/*     0x2x            */
	TT_DECRYPT_INVALID,           /* 00100000 -> 01000100 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 00100001 -> 10101100 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 00100010 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 00100011 -> 01000101 */

	0x04 | TT_DECRYPT_CORRECTED,  /* 00100100 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 00100101 -> 01000100 */
	TT_DECRYPT_INVALID,           /* 00100110 -> 01000101 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 00100111 -> 10100111 */

	0x06 | TT_DECRYPT_CORRECTED,  /* 00101000 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 00101001 -> 01000110 */
	TT_DECRYPT_INVALID,           /* 00101010 -> 01000111 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 00101011 -> 10100111 */

	TT_DECRYPT_INVALID,           /* 00101100 -> 01000110 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 00101101 -> 10100111 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 00101110 -> 10100111 */
	0x07,                         /* 00101111 -> 10000111 */

	/*     0x3x            */
	0x06 | TT_DECRYPT_CORRECTED,  /* 00110000 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 00110001 -> 01000100 */
	TT_DECRYPT_INVALID,           /* 00110010 -> 01000101 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 00110011 -> 10100101 */

	TT_DECRYPT_INVALID,           /* 00110100 -> 01000100 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 00110101 -> 10100000 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 00110110 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 00110111 -> 01000101 */

	0x06,                         /* 00111000 -> 10000110 */
	0x06 | TT_DECRYPT_CORRECTED,  /* 00111001 -> 10100110 */
	0x06 | TT_DECRYPT_CORRECTED,  /* 00111010 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 00111011 -> 01000111 */

	0x06 | TT_DECRYPT_CORRECTED,  /* 00111100 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 00111101 -> 01000110 */
	TT_DECRYPT_INVALID,           /* 00111110 -> 01000111 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 00111111 -> 10100111 */

	/*     0x4x            */
	TT_DECRYPT_INVALID,           /* 01000000 -> 01000000 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 01000001 -> 10100010 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 01000010 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 01000011 -> 01000001 */

	0x04 | TT_DECRYPT_CORRECTED,  /* 01000100 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 01000101 -> 01000000 */
	TT_DECRYPT_INVALID,           /* 01000110 -> 01000001 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 01000111 -> 10101001 */

	0x02 | TT_DECRYPT_CORRECTED,  /* 01001000 -> 10100010 */
	0x02,                         /* 01001001 -> 10000010 */
	TT_DECRYPT_INVALID,           /* 01001010 -> 01000011 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 01001011 -> 10100010 */

	TT_DECRYPT_INVALID,           /* 01001100 -> 01000010 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 01001101 -> 10100010 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 01001110 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 01001111 -> 01000011 */

	/*     0x5x            */
	0x08 | TT_DECRYPT_CORRECTED,  /* 01010000 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 01010001 -> 01000000 */
	TT_DECRYPT_INVALID,           /* 01010010 -> 01000001 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 01010011 -> 10100101 */

	TT_DECRYPT_INVALID,           /* 01010100 -> 01000000 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 01010101 -> 10100000 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 01010110 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 01010111 -> 01000001 */

	TT_DECRYPT_INVALID,           /* 01011000 -> 01000010 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 01011001 -> 10100010 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 01011010 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 01011011 -> 01000011 */

	0x03 | TT_DECRYPT_CORRECTED,  /* 01011100 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 01011101 -> 01000010 */
	0x03,                         /* 01011110 -> 10000011 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 01011111 -> 10100011 */

	/*     0x6x            */
	0x04 | TT_DECRYPT_CORRECTED,  /* 01100000 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 01100001 -> 01000100 */
	TT_DECRYPT_INVALID,           /* 01100010 -> 01000101 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 01100011 -> 10100101 */

	0x04,                         /* 01100100 -> 10000100 */
	0x04 | TT_DECRYPT_CORRECTED,  /* 01100101 -> 10100100 */
	0x04 | TT_DECRYPT_CORRECTED,  /* 01100110 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 01100111 -> 01000101 */

	TT_DECRYPT_INVALID,           /* 01101000 -> 01000110 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 01101001 -> 10100010 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 01101010 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 01101011 -> 01000111 */

	0x04 | TT_DECRYPT_CORRECTED,  /* 01101100 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 01101101 -> 01000110 */
	TT_DECRYPT_INVALID,           /* 01101110 -> 01000111 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 01101111 -> 10100111 */

	/*     0x7x            */
	TT_DECRYPT_INVALID,           /* 01110000 -> 01000100 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 01110001 -> 10100101 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 01110010 -> 10100101 */
	0x05,                         /* 01110011 -> 10000101 */

	0x04 | TT_DECRYPT_CORRECTED,  /* 01110100 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 01110101 -> 01000100 */
	TT_DECRYPT_INVALID,           /* 01110110 -> 01000101 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 01110111 -> 10100101 */

	0x06 | TT_DECRYPT_CORRECTED,  /* 01111000 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 01111001 -> 01000110 */
	TT_DECRYPT_INVALID,           /* 01111010 -> 01000111 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 01111011 -> 10100101 */

	TT_DECRYPT_INVALID,           /* 01111100 -> 01000110 */
	0x0E | TT_DECRYPT_CORRECTED,  /* 01111101 -> 10101110 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 01111110 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 01111111 -> 01000111 */

	/*     0x8x            */
	TT_DECRYPT_INVALID,           /* 10000000 -> 01001000 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 10000001 -> 10101100 */
	0x01 | TT_DECRYPT_CORRECTED,  /* 10000010 -> 10100001 */
	TT_DECRYPT_INVALID,           /* 10000011 -> 01001001 */

	0x0A | TT_DECRYPT_CORRECTED,  /* 10000100 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 10000101 -> 01001000 */
	TT_DECRYPT_INVALID,           /* 10000110 -> 01001001 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 10000111 -> 10101001 */

	0x0A | TT_DECRYPT_CORRECTED,  /* 10001000 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 10001001 -> 01001010 */
	TT_DECRYPT_INVALID,           /* 10001010 -> 01001011 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 10001011 -> 10101011 */

	0x0A,                         /* 10001100 -> 10001010 */
	0x0A | TT_DECRYPT_CORRECTED,  /* 10001101 -> 10101010 */
	0x0A | TT_DECRYPT_CORRECTED,  /* 10001110 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 10001111 -> 01001011 */

	/*     0x9x            */
	0x08 | TT_DECRYPT_CORRECTED,  /* 10010000 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 10010001 -> 01001000 */
	TT_DECRYPT_INVALID,           /* 10010010 -> 01001001 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 10010011 -> 10101011 */

	TT_DECRYPT_INVALID,           /* 10010100 -> 01001000 */
	0x00 | TT_DECRYPT_CORRECTED,  /* 10010101 -> 10100000 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 10010110 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 10010111 -> 01001001 */

	TT_DECRYPT_INVALID,           /* 10011000 -> 01001010 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 10011001 -> 10101011 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 10011010 -> 10101011 */
	0x0B,                         /* 10011011 -> 10001011 */

	0x0A | TT_DECRYPT_CORRECTED,  /* 10011100 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 10011101 -> 01001010 */
	TT_DECRYPT_INVALID,           /* 10011110 -> 01001011 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 10011111 -> 10101011 */

	/*     0xAx            */
	0x0C | TT_DECRYPT_CORRECTED,  /* 10100000 -> 10101100 */
	0x0C,                         /* 10100001 -> 10001100 */
	TT_DECRYPT_INVALID,           /* 10100010 -> 01001101 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 10100011 -> 10101100 */

	TT_DECRYPT_INVALID,           /* 10100100 -> 01001100 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 10100101 -> 10101100 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 10100110 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 10100111 -> 01001101 */

	TT_DECRYPT_INVALID,           /* 10101000 -> 01001110 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 10101001 -> 10101100 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 10101010 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 10101011 -> 01001111 */

	0x0A | TT_DECRYPT_CORRECTED,  /* 10101100 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 10101101 -> 01001110 */
	TT_DECRYPT_INVALID,           /* 10101110 -> 01001111 */
	0x07 | TT_DECRYPT_CORRECTED,  /* 10101111 -> 10100111 */

	/*     0xBx            */
	TT_DECRYPT_INVALID,           /* 10110000 -> 01001100 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 10110001 -> 10101100 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 10110010 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 10110011 -> 01001101 */

	0x0D | TT_DECRYPT_CORRECTED,  /* 10110100 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 10110101 -> 01001100 */
	0x0D,                         /* 10110110 -> 10001101 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 10110111 -> 10101101 */

	0x06 | TT_DECRYPT_CORRECTED,  /* 10111000 -> 10100110 */
	TT_DECRYPT_INVALID,           /* 10111001 -> 01001110 */
	TT_DECRYPT_INVALID,           /* 10111010 -> 01001111 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 10111011 -> 10101011 */

	TT_DECRYPT_INVALID,           /* 10111100 -> 01001110 */
	0x0E | TT_DECRYPT_CORRECTED,  /* 10111101 -> 10101110 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 10111110 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 10111111 -> 01001111 */

	/*     0xCx            */
	0x08 | TT_DECRYPT_CORRECTED,  /* 11000000 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 11000001 -> 01001000 */
	TT_DECRYPT_INVALID,           /* 11000010 -> 01001001 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 11000011 -> 10101001 */

	TT_DECRYPT_INVALID,           /* 11000100 -> 01001000 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 11000101 -> 10101001 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 11000110 -> 10101001 */
	0x09,                         /* 11000111 -> 10001001 */

	TT_DECRYPT_INVALID,           /* 11001000 -> 01001010 */
	0x02 | TT_DECRYPT_CORRECTED,  /* 11001001 -> 10100010 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 11001010 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 11001011 -> 01001011 */

	0x0A | TT_DECRYPT_CORRECTED,  /* 11001100 -> 10101010 */
	TT_DECRYPT_INVALID,           /* 11001101 -> 01001010 */
	TT_DECRYPT_INVALID,           /* 11001110 -> 01001011 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 11001111 -> 10101001 */

	/*     0xDx            */
	0x08,                         /* 11010000 -> 10001000 */
	0x08 | TT_DECRYPT_CORRECTED,  /* 11010001 -> 10101000 */
	0x08 | TT_DECRYPT_CORRECTED,  /* 11010010 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 11010011 -> 01001001 */

	0x08 | TT_DECRYPT_CORRECTED,  /* 11010100 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 11010101 -> 01001000 */
	TT_DECRYPT_INVALID,           /* 11010110 -> 01001001 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 11010111 -> 10101001 */

	0x08 | TT_DECRYPT_CORRECTED,  /* 11011000 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 11011001 -> 01001010 */
	TT_DECRYPT_INVALID,           /* 11011010 -> 01001011 */
	0x0B | TT_DECRYPT_CORRECTED,  /* 11011011 -> 10101011 */

	TT_DECRYPT_INVALID,           /* 11011100 -> 01001010 */
	0x0E | TT_DECRYPT_CORRECTED,  /* 11011101 -> 10101110 */
	0x03 | TT_DECRYPT_CORRECTED,  /* 11011110 -> 10100011 */
	TT_DECRYPT_INVALID,           /* 11011111 -> 01001011 */

	/*     0xEx            */
	TT_DECRYPT_INVALID,           /* 11100000 -> 01001100 */
	0x0C | TT_DECRYPT_CORRECTED,  /* 11100001 -> 10101100 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 11100010 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 11100011 -> 01001101 */

	0x04 | TT_DECRYPT_CORRECTED,  /* 11100100 -> 10100100 */
	TT_DECRYPT_INVALID,           /* 11100101 -> 01001100 */
	TT_DECRYPT_INVALID,           /* 11100110 -> 01001101 */
	0x09 | TT_DECRYPT_CORRECTED,  /* 11100111 -> 10101001 */

	0x0F | TT_DECRYPT_CORRECTED,  /* 11101000 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 11101001 -> 01001110 */
	0x0F,                         /* 11101010 -> 10001111 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 11101011 -> 10101111 */

	TT_DECRYPT_INVALID,           /* 11101100 -> 01001110 */
	0x0E | TT_DECRYPT_CORRECTED,  /* 11101101 -> 10101110 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 11101110 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 11101111 -> 01001111 */

	/*     0xFx            */
	0x08 | TT_DECRYPT_CORRECTED,  /* 11110000 -> 10101000 */
	TT_DECRYPT_INVALID,           /* 11110001 -> 01001100 */
	TT_DECRYPT_INVALID,           /* 11110010 -> 01001101 */
	0x05 | TT_DECRYPT_CORRECTED,  /* 11110011 -> 10100101 */

	TT_DECRYPT_INVALID,           /* 11110100 -> 01001100 */
	0x0E | TT_DECRYPT_CORRECTED,  /* 11110101 -> 10101110 */
	0x0D | TT_DECRYPT_CORRECTED,  /* 11110110 -> 10101101 */
	TT_DECRYPT_INVALID,           /* 11110111 -> 01001101 */

	TT_DECRYPT_INVALID,           /* 11111000 -> 01001110 */
	0x0E | TT_DECRYPT_CORRECTED,  /* 11111001 -> 10101110 */
	0x0F | TT_DECRYPT_CORRECTED,  /* 11111010 -> 10101111 */
	TT_DECRYPT_INVALID,           /* 11111011 -> 01001111 */

	0x0E | TT_DECRYPT_CORRECTED,  /* 11111100 -> 10101110 */
	0x0E,                         /* 11111101 -> 10001110 */
	TT_DECRYPT_INVALID,           /* 11111110 -> 01001111 */
	0x0E | TT_DECRYPT_CORRECTED   /* 11111111 -> 10101110 */
};

UINT8 gVBI_TTX_Encrypt_Hamming_Tab[16] =
{
	0x15,		//0x0
	0x02,		//0x1
	0x49,		//0x2
	0x5e,		//0x3
	0x64,		//0x4
	0x73,		//0x5
	0x38,		//0x6
	0x2f,		//0x7
	0xd0,		//0x8
	0xc7,		//0x9
	0x8c,		//0xa
	0x9b,		//0xb
	0xa1,		//0xc
	0xb6,		//0xd
	0xfd,		//0xe
	0xea		//0xf
};


/*========================================================================================
	Implementation Group
========================================================================================*/

#ifdef SEETV_BRINGUP
int vbi_kwrap_ttx_open(void)
{
	int 	dev_fd;
	int 	ret = RET_ERROR;

	KADP_InitSystem(); /* initialize kadp system if necessary */

    if(g_ttx_ctx.dev_fd >= 0) {
            TTX_PRINT("[VBI] %s : Ignore multiple initialization\n", __FILE__);
            return RET_OK;
    }

	TTX_INIT_LOCK();

	TTX_LOCK();
	TTX_TRACE_BEGIN();
    do{
        /* Step 1. Get shared mem space */
	    g_ttx_ctx.dev_shmem = KADP_OSA_OpenMemory( "kadp-ttx-shmem", sizeof(LX_TTX_SHMEM_T));
		if(g_ttx_ctx.dev_shmem == NULL) BREAK_WRONG(0);

	    LX_TTX_SHMEM_T* TTX_shmem = KADP_OSA_GetMemory( g_ttx_ctx.dev_shmem );
	    if(TTX_shmem == NULL) BREAK_WRONG(0);
	    if(TTX_shmem->magic != TTX_SHMEM_MAGIC) TTX_shmem->magic = TTX_SHMEM_MAGIC;
        
		/* Step 2. Open module */
	    dev_fd = open(  TTX_DEVICE, O_RDWR );
	    if(dev_fd < 0) BREAK_WRONG(dev_fd);
	    g_ttx_ctx.dev_fd = dev_fd;
        
		/* Step 3. Initiate module using IOCTL call */
	    ret=ioctl(g_ttx_ctx.dev_fd, VBI_TTX_IO_INIT); 
		
		/* Step 3-1. Disconnect all VBI main operation when Kdriver VBI opens fail */
		if(ret<0){
			TTX_PRINT("[VBI][%s:%d] : TTX Open failed due to IOCTL error or VBI Kdriver Init error. \n", __FILE__, __LINE__);
			break;
		}
		
		/* Step 4. Initiate Task Disconnectors */
		memset(g_ttx_ctx.taskDisconnect, 0, sizeof(g_ttx_ctx.taskDisconnect));
        
		/* Step 4. Initiate settings for debug flags */
        memset(gVBIDebugModeStatus.modeOnOff, 0, sizeof(gVBIDebugModeStatus.modeOnOff));
        memset(gVBIDebugModeStatus.printMask, 0, sizeof(gVBIDebugModeStatus.printMask));
       	gVBIDebugModeStatus.dataProfile.full_count  = 0;
		gVBIDebugModeStatus.dataProfile.error_count = 0;
		gVBIDebugModeStatus.dataProfile.max_count_value = 10000;
		gVBIDebugModeStatus.dataProfile.cc_dont_count_80 = 0;


        /* Step 5. Set global settings for MMAP */
	    g_ttx_ctx._gMMapTTX = 0;
	    g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
	    g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;

		/* Step 6. Turn On Debugger */
		/* Turn On HammError fixer */
		#if VBI_TTX_DEFAULT_HAMMING_CORRECT_ON
		gVBIDebugModeStatus.modeOnOff[ VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX] = 1;
		#endif
        ret = RET_OK;
    } while(0);

	TTX_TRACE_END();
	TTX_UNLOCK();
	
	return ret;
}
#endif
int vbi_kwrap_ttx_initializemodule(void)
{
	int	ret = RET_OK;

	VBI_PRINT("[%s] entered : [220106] \n", __func__);

//	VBI_PRINT("VBI TTX init\n");

	if(VBI_TTX_Initialize() < 0)
	{
		ret = RET_ERROR;
	}

	/* Step 3-1. Disconnect all VBI main operation when Kdriver VBI opens fail */
	if(ret<0){
		TTX_PRINT("[VBI][%s:%d] : TTX Open failed due to IOCTL error or VBI Kdriver Init error. \n", __FILE__, __LINE__);
		return RET_ERROR;
	}

	/* Step 4. Initiate Task Disconnectors */
//	memset(g_ttx_ctx.taskDisconnect, 0, sizeof(g_ttx_ctx.taskDisconnect));

	/* Step 4. Initiate settings for debug flags */
	memset(gVBIDebugModeStatus.modeOnOff, 0, sizeof(gVBIDebugModeStatus.modeOnOff));
	memset(gVBIDebugModeStatus.printMask, 0, sizeof(gVBIDebugModeStatus.printMask));
	gVBIDebugModeStatus.dataProfile.full_count  = 0;
	gVBIDebugModeStatus.dataProfile.error_count = 0;
	gVBIDebugModeStatus.dataProfile.max_count_value = 10000;
	gVBIDebugModeStatus.dataProfile.cc_dont_count_80 = 0;

	vbi_ttx_packet_t.pTTX_Packet_Buffer = NULL;
	vbi_ttx_packet_t.TTX_Packet_Unit = 0;
#ifdef SEETV_BRINGUP
	/* Step 5. Set global settings for MMAP */
	g_ttx_ctx._gMMapTTX = 0;
	g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
	g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;
#endif

	/* Step 6. Turn On Debugger */
	/* Turn On HammError fixer */
#if VBI_TTX_DEFAULT_HAMMING_CORRECT_ON
	gVBIDebugModeStatus.modeOnOff[ VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX] = 1;
#endif

	/* For VBI copy-protection filter : from HAL */
	vbi_kwrap_set_wsscopyprotectionrawfilter(10);
	vbi_kwrap_set_cgmscopyprotectionrawfilter(10);

	/* Step 7. create CP thread  */
	if(cp_Thread)
		VBI_PRINT("cp_Thread is already created.\n");
	else
	{
		cp_Thread = kthread_create( vbi_kwrap_cp_dataflush_thread, (void*)NULL, "cp_kwrap_thread");

		if(cp_Thread)
		{
			wake_up_process(cp_Thread);
			//gCVD_thread_running = 1;
			VBI_PRINT("CP TTX Kwrap Thread [%d] \n", cp_Thread->pid);
		}
		else
			VBI_PRINT("cp thread NOT created\n");
	}

	return ret;
}

int vbi_kwrap_ttx_enable(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

    do{
#ifdef SEETV_BRINGUP
	    ret = _vbi_kwrap_get_mmap();
        if(ret <0) BREAK_WRONG(ret);
#endif

	    ret = _vbi_kwrap_ttx_enableinterrupt();
	    if(ret <0) BREAK_WRONG(ret);

        ret = _vbi_kwrap_ttx_startslicer();
        if(ret <0) BREAK_WRONG(ret);

        ret = RET_OK;
    } while(0);

	return ret;
}


int vbi_kwrap_ttx_close(void)
{
	int ret = RET_ERROR;

#ifdef SEETV_BRINGUP
    TTX_LOCK();
	TTX_TRACE_BEGIN();

    do{
        if(g_ttx_ctx.dev_fd <0) {
                VBI_PRINT("[VBI] Module closed called even though module is not opened!\n");
                BREAK_WRONG(0);
        }

        ret = vbi_kwrap_ttx_disable();
	    if(ret <0) BREAK_WRONG(ret);

        ret = _vbi_kwrap_release();
        if(ret <0) BREAK_WRONG(ret);

		ret = close( g_ttx_ctx.dev_fd );
        if(ret <0) BREAK_WRONG(ret);

        g_ttx_ctx.dev_fd = -1;

		KADP_OSA_CloseMemory( g_ttx_ctx.dev_shmem );
    	
		/* 2013.07.31 won.hur : Will not close sema variable, due to latchup
		 * on situation where lock was called with out the lock */
		//KADP_OSA_CloseSema( g_ttx_ctx.dev_mtx );
		//g_ttx_ctx.dev_mtx 	= NULL;

		g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
		g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;

        ret = RET_OK;
    }while(0);

    TTX_TRACE_END();
	TTX_UNLOCK();
#endif

    return ret;
}

int vbi_kwrap_ttx_resetbuffer(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_ClearTTXMemory();

	return ret;
}


int vbi_kwrap_ttx_reset(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	//do nothing in ioctl
	return ret;
}

int vbi_kwrap_ttx_dbg_getdatacount(UINT8 bReset, unsigned int *data)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	do{
		if(VBI_get_buffer_ptr() == NULL){ BREAK_WRONG(0); }
		else {
			if(bReset){
				VBI_get_ttx_parameter_ptr()->TTX_Data_Count = 0;
			}
			else{
				*data = (unsigned int)VBI_get_ttx_parameter_ptr()->TTX_Data_Count;
			}
			ret = RET_OK;
		}
	} while(0);

	return ret;
}

int vbi_kwrap_ttx_reg_init(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_Initialize();

	return ret;
}

int vbi_kwrap_ttx_reset_wss(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_ClearWSSMemory();

	return ret;
}

int vbi_kwrap_ttx_reset_vps(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_ClearVPSMemory();

    return ret;
}


/* VBI module VPS main operation functon
 * This function should be called from the upper layer */
int vbi_kwrap_ttx_get_vps_packetstask(UINT8 **vps_packet)
{
	int ret = RET_ERROR;
    volatile UINT8 *packet = NULL;
    UINT32 ttx_status;

	/* Step 00. Check Disconnector */
	VBI_CHECK_DEVICE();

    do{
	    /* Step 01. Check whether MMAP is invalid.*/
        if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);

        /* Step 02. Check TTX status */
        vbi_kwrap_ttx_get_status(LX_TTX_TYPE_VPS, &ttx_status);
        if(!ttx_status) {VPS_DEBUG_PRINT("[VBI VPS : ttx status is on break status.\n"); ret = RET_OK; break;}

        /* Step 03. Get vps packet from memory.*/
        packet = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)VBI_get_ttx_parameter_ptr()->VPS_Offset);

        /* Debug option */
        VPS_DEBUG_PRINT("[VBI VPS : Got packet info from kernel. Addr[0x%p], *packet[0x%x]\n", packet, *packet);

        /* Debug option */
        VPS_DEBUG_PRINT("[VBI VPS][%15ph] \n", packet);

        /* Step 04. Check whether data is valid or not, this is to detect empty data */
        if(memcmp((void *)packet, (char[VBI_VPS_PACKET_SIZE]){0} , VBI_VPS_PACKET_SIZE) !=0)
        {
            VPS_DEBUG_PRINT("[VBI VPS] : Detected incoming VPS packets...\n");
            /* No need to deliver NO-SPEC data. So, delete(memset to 0) unnessessary parts */
#if 1
			memset((void*)packet, 0, 4);
            memset((void*)&packet[5], 0, 5);
#else
			{
				int i;
				for (i=0;i<4;i++)
					packet[i]=0;
				for (i=5;i<10;i++)
					packet[i]=0;
			}
#endif

            /* Transfer data to upper stage */
            *vps_packet = (void *)packet;

        }
        else{vps_packet = NULL; VPS_DEBUG_PRINT("[VBI VPS : Detected incoming VPS packet was NULL. Do not send above... .\n");}

        ret = RET_OK;

    } while(0);

	return ret;
}

int vbi_kwrap_checkvline625(void)
{
	int ret = RET_ERROR;

	/* Step 00. Check Disconnector */
	VBI_CHECK_DEVICE();

	ret = VBI_CheckVline625();

	return ret;
}

int vbi_kwrap_init_copyprotection_info(void)
{
	int ret = RET_ERROR;
	unsigned char gZeroCGMSData[12] = {0,};

	VBI_CHECK_DEVICE();

	VBI_PutCGMSData((sCGMS *)&gZeroCGMSData);

	return ret;
}

/* VBI module VPS main operation functon
 * This function should be called from the upper layer */
int vbi_kwrap_copyprotection_dataflusher_task(void)
{
	int ret = RET_ERROR;
	int is_analog_cp_protected = 0;
	int is_analog_cp_Stable = 0;
	volatile UINT8 *packet = NULL;
	static UINT8 there_was_no_valid_data;

	/* Step 00. Check Disconnector */
	VBI_CHECK_DEVICE();

	do{
		/* Step 01. Check whether MMAP is invalid.*/
		if(VBI_get_buffer_ptr() == NULL) break;

		_vbi_kwrap_get_cp_data((void *)&packet, &is_analog_cp_protected, &is_analog_cp_Stable);

		/* Step 03. Check data and send to buffer.. */
#if 1
		memset((void *)((uintptr_t)packet + (uintptr_t)10), 0, 5);	// Clear packet +10,11,12,13,14 for data delivery
#else
		{
			int i;
			for (i=10;i<15;i++)
				packet[i]=0;
		}
#endif

		if( (packet[0] != 0x00) || (packet[1] !=0xff) || (packet[2] != 0xff)) {
			CGMS_DEBUG_PRINT("[VBI CGMS] None cgms data found.\n");

			there_was_no_valid_data++;
			if(there_was_no_valid_data >= gVBICopyProtectionRawNoInterruptCount){
				CGMS_DEBUG_PRINT("[VBI CGMS] Reset USER CP data.\n");
#if 1
				memset((void *)((uintptr_t)packet + (uintptr_t)10), 0, 5);
#else
				{
					int i;
					for (i=10;i<15;i++)
						packet[i]=0;
				}
#endif
			}
		}
		else {
			there_was_no_valid_data = 0;

			_vbi_kwrap_process_cp_data((void *)&packet);
		}

		/* Step 04. Clear sliced data buffer */
#if 1
		memset((void *)packet, 0, VBI_CGMS_PACKET_SIZE);
#else
		{
			int i;
			for (i=0;i<VBI_CGMS_PACKET_SIZE;i++)
				packet[i]=0;
		}
#endif

		/* Copy Analog CP to buffer */
		if((is_analog_cp_protected != 0) &&(is_analog_cp_Stable <= gVBIAnalogCPCopyProtectionRAWFilterThreshold) ){
			packet[15] = 1;
		} else{
			packet[15] = 0;
		}

		/* Step 06. Set return value */
		ret = RET_OK;
   }while(0);

	return ret;
}

/* Get CopyProtection Info
 * Return value :
 * ret -1 : Return Error
 * ret  0 : No copy protection
 * ret  1 : CGMS TYPE 0
 * ret  2 : CGMS TYPE 1
 * ret  4 : CGMS TYPE 2
 * ret  8 : CGMS TYPE 3
 * ret 16 : WSS copy protection
 * ret 32 : Analog protection type 1
 * ret 64 : Analog protection type 2
 * ret 128 : Analog protection type 3
 */
LX_VBI_CP_TYPE_T vbi_kwrap_get_copyprotection_info(UINT32 *cgms_packet)
{
	static LX_VBI_CP_TYPE_T prev_cpinfo = LX_VBI_CP_TYPE_NONE;
	LX_VBI_CP_TYPE_T ret = RET_ERROR;
	volatile UINT8 *packet = NULL;

#ifndef VBI_LATCHUP_DEBUG
#if 1
	UINT8 pre_data[4];
#else
	UINT32 pre_data[4];
#endif
	/* Step 00. Check Disconnector */
	VBI_CHECK_DEVICE();

	do
	{
		/* Step 01. Check whether MMAP is invalid.*/
		if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);

		/* Step 02. Get CGMS packet from memory.*/
        packet = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)VBI_get_ttx_parameter_ptr()->CGMS_Offset);

#if 0
		/* Step 04. Send catched data up-above */
		//*cgms_packet = (UINT32)(*((UINT32 *)(packet + 1)));
		pre_data[0] = packet[11];
		pre_data[1] = packet[12];
		pre_data[2] = packet[13];
		pre_data[3] = packet[14];
		memcpy((void *)cgms_packet, (void *)&pre_data, sizeof(UINT32));

		CGMS_DEBUG_PRINT("%s:%d cgms[0x%x]\n", __func__, __LINE__, *cgms_packet);
#else
		//CGMS_DEBUG_PRINT("%s:%d p0[0x%x]p1[0x%x]p2[0x%x]p3[0x%x]p4[0x%x]\n", __func__, __LINE__,*(packet+(uintptr_t)10), *(packet+(uintptr_t)11), *(packet+(uintptr_t)12), *(packet+(uintptr_t)13), *(packet+(uintptr_t)14));
		CGMS_DEBUG_PRINT("%s:%d p10[%5ph]\n", __func__, __LINE__, (packet+(uintptr_t)10) );
//		memcpy((void *)&pre_data[0], (void *)&packet[8], sizeof(UINT32));
//		memcpy((void *)&pre_data[1], (void *)&packet[12], sizeof(UINT32));
//		pre_data[0] = packet[8];
//		pre_data[1] = packet[12];
//
		pre_data[0] = packet[11];
		pre_data[1] = packet[12];
		pre_data[2] = packet[13];
		pre_data[3] = packet[14];

		//*cgms_packet = (pre_data[0] >> 24) | ( (pre_data[1] << 8) & 0xFFFFFF00);
		memcpy((void *)cgms_packet, (void *)&pre_data, sizeof(UINT32));
		CGMS_DEBUG_PRINT("%s:%d cgms[0x%x]\n", __func__, __LINE__, *cgms_packet);
#endif

		/* Step 06. Data analysis. Calculate return value to send above... */
		ret = _vbi_kwrap_calculate_cp_type((void *)&packet);

		CGMS_DEBUG_PRINT("[VBI CGMS] Return Value : [0x%08x]\n", ret);
		CGMS_DEBUG_PRINT("[VBI CGMS] buffer data : [%10ph]\n", (packet+(uintptr_t)10) );

		if(ret != prev_cpinfo)
		{
			VBI_NOTI("cp type change [0x%x]=>[0x%x]\n", prev_cpinfo, ret);
			prev_cpinfo = ret;
		}

   }while(0);
#else
	*cgms_packet = 0;

	ret = 0;
#endif

	return ret;
}


/* VBI module WSS main operation functon
 * This function should be called from the upper layer */
int vbi_kwrap_ttx_get_wss_packetstask(UINT8 **wss_packet)
{
	int ret = RET_ERROR;
    volatile UINT8 *packet = NULL;
	static UINT8 previous_packet[16];
    static UINT8 previous_wss_id;
	static UINT32 wss_unstable_count;
	volatile UINT8 *wss_id = 0;
	UINT32 ttx_status;

	/* Step 00. Check Disconnector */
	VBI_CHECK_DEVICE();

	do{
		/* Step 01. Check whether MMAP is invalid.*/
		if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);

		/* Step 02. Check TTX status */
		vbi_kwrap_ttx_get_status(LX_TTX_TYPE_WSS, &ttx_status);
		if(!ttx_status) {VBI_DEBUG("[VBI WSS : ttx status is on break status.\n"); ret = RET_OK; break;}


        /* Step 03. Get WSS packet from memory.*/
        packet = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)VBI_get_ttx_parameter_ptr()->WSS_Offset);

		/* Step 03-2. Get WSS ID from memory */
		wss_id = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)VBI_get_ttx_parameter_ptr()->WSS_Offset + (uintptr_t)4);

		WSS_DEBUG_PRINT("[VBI WSS] Got WSS info from kernel : packet[0x%p] *packet[%16ph] *wss_id[0x%x] \n", packet, packet, *wss_id);

        /* Step 04. Check whether data is valid or not, this is to detect no-interrupt-data */
        if((*wss_id) != (previous_wss_id)){
			previous_wss_id = *wss_id;
			wss_unstable_count = 0;
		}
		else {
			wss_unstable_count++;
			if(wss_unstable_count >=0xFFFFFFFE) wss_unstable_count = 1 + VBI_WSS_NO_INTERRUPT_THRESHOLD;	// protection code for massive no-interrupt
			WSS_DEBUG_PRINT("[VBI WSS] Incoming No WSS packet(There was no interrupt from KDRV). Unstable count is [%d] (current/previous [%x]/[%x] \n", (int)wss_unstable_count, *wss_id, previous_wss_id);
		}

		/* Step 05. Send up packet */
		if(wss_unstable_count == VBI_WSS_NO_INTERRUPT_THRESHOLD) 
		{
			WSS_DEBUG_PRINT("[VBI WSS] Reset WSS packet. Unstable count is [%d] *packet[%16ph]\n", (int)wss_unstable_count, packet);
			// add to reset wss buffer ,when wss packet read done
			vbi_kwrap_ttx_reset_wss();
			*wss_packet = (void*)packet;
			memcpy((void*)previous_packet, (void*)packet, 16);
		}
		else if((wss_unstable_count == 0)|| ( wss_unstable_count > VBI_WSS_NO_INTERRUPT_THRESHOLD) ) {
			*wss_packet = (void*)packet;
			memcpy((void*)previous_packet, (void*)packet, 16);
		}
		else {
			memcpy((void*)packet, (void*)previous_packet, 16);
			*wss_packet = (void*)packet;
		}

        /* Debug option */
        WSS_DEBUG_PRINT("[VBI WSS] Sent up WSS data was : [0x%x]\n", **(wss_packet) );

        ret = RET_OK;
   }while(0);

	return ret;
}



int vbi_kwrap_ttx_get_parameter_offset(UINT32 *parameter_offset)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	//do nothing in ioctl
	//
	return ret;
}


/* VBI module TTX main operation functon
 * This function should be called from the upper layer */
int vbi_kwrap_ttx_get_ttx_packetstask(LX_TTX_PACKET_TYPE_T **ttx_packet, int packet_count)
{
    int ret = RET_ERROR;

    static LX_TTX_PACKET_TYPE_T *gptPB;

	/* Step 0. Check Disconnector */
	VBI_CHECK_DEVICE();

	do{
		/* Step 0-1. Check whether MMAP is invalid.*/
		if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);

		/* Step 1. Get packets... */
		if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_TARA_UNIT_TEST]>0){
			_vbi_kwrap_ttx_unittest(&gptPB);
		}
		else if( _vbi_kwrap_ttx_get_packets_from_file(&gptPB) == RET_ERROR) 
			_vbi_kwrap_ttx_get_packets_from_mem(&gptPB, packet_count);

		/* Step 2. Check whether TTX packet address is valid or not */
        if(gptPB == NULL) {
               *ttx_packet = gptPB;
               TTX_DEBUG_PRINT("[VBI TTX] Failed to get MMAP DDR address for TTX.\n"); break;
        }

        /* Step 3. Check amount of packet, and warn if there ain't any... */
        if(gptPB->TTX_Packet_Unit == 0) { TTX_DEBUG_PRINT("[VBI TTX] No TTX data to read. Packet unit was zero.\n"); }

        /* Step 4. Check data stack, and place a warning if stack size was over the limit */
        if(gptPB->TTX_Packet_Unit > VBI_TTX_PACKET_STACK_ALARM) {
                TTX_DEBUG_PRINT("[VBI TTX] Warning! Large amount of stacked data in TTX buffer [%d]\n", gptPB->TTX_Packet_Unit);}

		/* ETC 1. Debug option : Fix hamming error */
		if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_ENABLE_HAMM_ERROR_FIX]){
			_vbi_kwrap_ttx_hammingcorrection(&gptPB);
		}

		/* ETC 2. Error proFilter */
		if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter]){
			_vbi_kwrap_ttx_dataprofilter(&gptPB);
		}

#ifdef SEETV_BRINGUP
		/* ETC 3. Debug mode for capturing sliced data to file */
        if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DUMP_TO_FILE]>0){
			_vbi_kwrap_ttx_data_file_dump(&gptPB);
        }
#endif


        /* Step 5. Send Packets */
        *ttx_packet = gptPB;

        ret = RET_OK;
    }while(0);

	return ret;
}


int vbi_kwrap_ttx_enable_vps_slicer(BOOLEAN bEnable)
{

	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_Enable_VPS_Slicer(bEnable);

	return ret;
}

int vbi_kwrap_ttx_set_tt_slicer_mode(unsigned int slicer_mode)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_Set_TT_Slicer_Mode(slicer_mode);

	return ret;
}


#ifdef SEETV_BRINGUP
int vbi_kwrap_cc_open(void)
{
	int 	dev_fd;
	int 	ret = RET_ERROR;

    if(g_ttx_ctx.dev_fd >= 0) {
	printf("%s:%d\n", __func__, __LINE__);
            TTX_PRINT("[VBI] %s : Ignore multiple initialization\n", __FILE__);
            return RET_OK;
    }

	TTX_INIT_LOCK();

	TTX_LOCK();
	TTX_TRACE_BEGIN();

    do{
        /* Step 0. Get shared mem space */
	    g_ttx_ctx.dev_shmem = KADP_OSA_OpenMemory( "kadp-ttx-shmem", sizeof(LX_TTX_SHMEM_T));
	    if(g_ttx_ctx.dev_shmem == NULL) BREAK_WRONG(0);

	    LX_TTX_SHMEM_T* TTX_shmem = KADP_OSA_GetMemory( g_ttx_ctx.dev_shmem );
	    if(TTX_shmem == NULL) BREAK_WRONG(0);

	    if(TTX_shmem->magic != TTX_SHMEM_MAGIC) TTX_shmem->magic = TTX_SHMEM_MAGIC;

	    /* Step 1. Open module */
        dev_fd = open( TTX_DEVICE, O_RDWR );
	    if(dev_fd < 0) BREAK_WRONG(dev_fd);

        g_ttx_ctx.dev_fd = dev_fd;

        /* Step 2. Initiate module using IOCTL call */
		ret=ioctl(g_ttx_ctx.dev_fd, VBI_CC_IO_INIT); 
		
		/* Step 3-1. Disconnect all VBI main operation when Kdriver VBI opens fail */
		if(ret<0){
			TTX_PRINT("[VBI][%s:%d] : CC Open failed due to IOCTL error or VBI Kdriver Init error. \n", __FILE__, __LINE__);
			printf("[VBI][%s:%d] : CC Open failed due to IOCTL error or VBI Kdriver Init error. \n", __FILE__, __LINE__);
			break;
		}

		/* Step 3. Initiate settings for debug flags */
        memset(gVBIDebugModeStatus.modeOnOff, 0, sizeof(gVBIDebugModeStatus.modeOnOff));
        memset(gVBIDebugModeStatus.printMask, 0, sizeof(gVBIDebugModeStatus.printMask));


        /* Step 4. Set global settings for MMAP */
	    g_ttx_ctx._gMMapTTX = 0;
	    g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
	    g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;

    }while(0);

	TTX_TRACE_END();
	TTX_UNLOCK();

	printf("%s:%d\n", __func__, __LINE__);
	return ret;
}
#endif

int vbi_kwrap_cc_initializemodule(void)
{
	int	ret = RET_OK;

	VBI_PRINT("[%s] entered : [220106] \n", __func__);

	VBI_PRINT("VBI CC init\n");

	if(VBI_CC_Initialize() < 0)
	{
		ret = RET_ERROR;
	}

	/* Step 3-1. Disconnect all VBI main operation when Kdriver VBI opens fail */
	if(ret<0){
		TTX_PRINT("[VBI][%s:%d] : TTX Open failed due to IOCTL error or VBI Kdriver Init error. \n", __FILE__, __LINE__);
	}

	/* Step 3. Initiate settings for debug flags */
	memset(gVBIDebugModeStatus.modeOnOff, 0, sizeof(gVBIDebugModeStatus.modeOnOff));
	memset(gVBIDebugModeStatus.printMask, 0, sizeof(gVBIDebugModeStatus.printMask));

	vbi_ttx_packet_t.pTTX_Packet_Buffer = NULL;
	vbi_ttx_packet_t.TTX_Packet_Unit = 0;
#ifdef SEETV_BRINGUP
	/* Step 5. Set global settings for MMAP */
	g_ttx_ctx._gMMapTTX = 0;
	g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
	g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;
#endif

	/* For VBI copy-protection filter : from HAL */
	vbi_kwrap_set_wsscopyprotectionrawfilter(10);
	vbi_kwrap_set_cgmscopyprotectionrawfilter(10);

	/* Step 6. create CP thread  */
	if(cp_Thread)
		VBI_PRINT("cp_Thread is already created.\n");
	else {
		cp_Thread = kthread_create( vbi_kwrap_cp_dataflush_thread, (void*)NULL, "cp_kwrap_thread");

		if(cp_Thread)
		{
			wake_up_process(cp_Thread);
			//gCVD_thread_running = 1;
			VBI_PRINT("CP CC Kwrap Thread [%d] \n", cp_Thread->pid);
		}
		else
			VBI_PRINT("cp thread NOT created\n");
	}

	return ret;
}

int vbi_kwrap_cc_enable(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

    do{
#ifdef SEETV_BRINGUP
	    ret = _vbi_kwrap_get_mmap();
        if(ret <0) BREAK_WRONG(ret);
#endif

        ret = _vbi_kwrap_cc_enableinterrupt();
	    if(ret <0) BREAK_WRONG(ret);

        ret = _vbi_kwrap_cc_startslicer();
	    if(ret <0) BREAK_WRONG(ret);

        ret = RET_OK;
    }while(0);

	return ret;
}

int vbi_kwrap_cc_disable(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

    do{
        ret = _vbi_kwrap_cc_stopslicer();
	    if(ret <0) BREAK_WRONG(ret);

	    ret = _vbi_kwrap_cc_disableinterrupt();
	    if(ret <0) BREAK_WRONG(ret);

        ret = RET_OK;
    }while(0);

    return ret;
}

int vbi_kwrap_cc_close(void)
{
	int ret = RET_ERROR;

    do{
	    ret = vbi_kwrap_cc_disable();
        if(ret <0) BREAK_WRONG(ret);

		ret = _vbi_kwrap_release();
        if(ret <0) BREAK_WRONG(ret);

		vbi_ttx_packet_t.pTTX_Packet_Buffer = NULL;
		vbi_ttx_packet_t.TTX_Packet_Unit = 0;
#ifdef SEETV_BRINGUP
		ret = close( g_ttx_ctx.dev_fd );
        if(ret <0) BREAK_WRONG(ret);

        g_ttx_ctx.dev_fd = -1;

		g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
		g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;

		KADP_OSA_CloseMemory( g_ttx_ctx.dev_shmem );
#endif
    	
		/* 2013.07.31 won.hur : Will not close sema variable, due to latchup
		 * on situation where lock was called with out the lock */
		//KADP_OSA_CloseSema( g_ttx_ctx.dev_mtx );
	    //g_ttx_ctx.dev_mtx 	= NULL;

        ret = RET_OK;
    }while(0);

	return ret;
}

int vbi_kwrap_cc_resetbuffer(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_CC_SetVBIBufferClear();

	return ret;
}

int vbi_kwrap_cc_reset(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

//do nothing in ioctl
	return ret;
}

int vbi_kwrap_cc_reg_init(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_CC_Initialize();

	return ret;
}

int vbi_kwrap_cc_get_packet_count(UINT32 *count)
{
	int ret = RET_OK;

	VBI_CHECK_DEVICE();

	*count = VBI_CC_GetVBIBufferInform();

	return ret;
}


/* This function grabs CC data from kernel */
int vbi_kwrap_cc_get_cc_datatask(LX_CC_DATA_T *pCC_Data_Buffer)
{
	int ret = RET_ERROR;
    LX_CC_DATA_T packet;

	/* Step 00. Check Disconnector */
	VBI_CHECK_DEVICE();

	do{
		/* Step 0-1. Check whether MMAP is invalid.*/
		if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);

		/* Step 1. Get a packet from kernel driver */
		ret = VBI_CC_GetVBIData((void *)&packet , 1);

		/* debug : Error proFilter */
		if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter]){
			if(packet.line_number > 0)
				_vbi_kwrap_cc_dataprofilter(&packet);
		}

        /* debug option : Fix parity error*/
        if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_FIX_CC_PARITY]>0) {
                _vbi_kwrap_cc_correct_parity(&packet.data1); }

        /* debug mode */
        CC_DEBUG_PRINT("[VBI CC] field[%x] D0[0x%x] D1[0x%x] \n", packet.field,\
                                                                (packet.data1),\
                                                                (packet.data2));
        /* Step 2. Copy data to upper layer */
        memcpy((void *)pCC_Data_Buffer, (void *)&packet, sizeof(LX_CC_DATA_T));

        ret = RET_OK;
    } while(0);

	return ret;
}


int vbi_kwrap_ttx_disableinterrupt(void)
{
	int ret = RET_ERROR;

	VBI_CHECK_DEVICE();

	ret = VBI_TTX_SetInterrupt(OFF);

	gVBIInterruptControl = 0;

	return ret;
}

int vbi_kwrap_ttx_disable(void)
{
	int ret = RET_ERROR;

   	VBI_CHECK_DEVICE();

	do{
	    ret = _vbi_kwrap_ttx_stopslicer();
        if(ret <0) BREAK_WRONG(ret);

        ret = _vbi_kwrap_ttx_disableinterrupt();
        if(ret <0) BREAK_WRONG(ret);

        ret = RET_OK;
    }while(0);

	return ret;
}

int vbi_kwrap_set_wsscopyprotectionrawfilter(int filterlength)
{
	int ret = RET_ERROR;
   	VBI_CHECK_DEVICE();


    do{
		if(filterlength >= VBI_COPYPROTECTION_RAW_WSS_FILTER_MAX_SIZE){
			break;
		}
		else{
			gVBIWSSCopyProtectionRAWFilterSize = filterlength;
		}
		ret = RET_OK;
    }while(0);

	return ret;
}

int vbi_kwrap_set_cgmscopyprotectionrawfilter(int filterlength)
{
	int ret = RET_ERROR;
   	VBI_CHECK_DEVICE();


    do{
		if(filterlength >= VBI_COPYPROTECTION_RAW_CGMS_FILTER_MAX_SIZE){
			break;
		}
		else{
			gVBICGMSCopyProtectionRAWFilterSize = filterlength;
		}
		ret = RET_OK;
    }while(0);

	return ret;
}

int vbi_kwrap_set_analogcpcopyprotectionrawfilter(int filterlength)
{
	int ret = RET_ERROR;
   	VBI_CHECK_DEVICE();


    do{
		if(filterlength >= VBI_COPYPROTECTION_RAW_ANALOG_CP_FILTER_MAX_SIZE){
			break;
		}
		else{
			gVBIAnalogCPCopyProtectionRAWFilterSize = filterlength;
		}
		ret = RET_OK;
    }while(0);

	return ret;
}

/*--------------------------------------------------------------------------------------------
   Static functions
--------------------------------------------------------------------------------------------*/


__attribute__((unused)) static int _vbi_kwrap_get_mmap(void)
{
	int ret = RET_ERROR;

	//gMMapTTX, gmmap_size, pTTX_Parameter_t
#ifdef SEETV_BRINGUP

    do{
        if(g_ttx_ctx._gMMapTTX != 0) {VBI_PRINT("[VBI] VBI MMAP Already MMaped!\n"); ret = RET_OK; break;}

		IOCTL_CALL(g_ttx_ctx.dev_fd, VBI_TTX_IOR_GET_MMAP_SIZE, &g_ttx_ctx.gmmap_size);

        if(g_ttx_ctx.gmmap_size == 0) {VBI_PRINT("[VBI] Error on getting MMap size. Size is zero"); BREAK_WRONG(0);}

        VBI_PRINT("[VBI] MMAP size is [0x%x]\n", g_ttx_ctx.gmmap_size);

		g_ttx_ctx._gMMapTTX = (UINT8 *)mmap(0, g_ttx_ctx.gmmap_size, PROT_READ|PROT_WRITE, MAP_SHARED, g_ttx_ctx.dev_fd, 0);

		VBI_PRINT("[VBI] gMMAPTTX is [0x%x]\n", (unsigned int)g_ttx_ctx._gMMapTTX);

		if(g_ttx_ctx._gMMapTTX == NULL) {
			VBI_ERROR("TTX device : Failed to MMAP !!! : size[0x%x]\n", g_ttx_ctx.gmmap_size);
			g_ttx_ctx._gMMapTTX = 0;
		    BREAK_WRONG(0);
		}

		if( lx_chip_rev( ) >= LX_CHIP_REV(H13,A0))
		{
        	g_ttx_ctx.pTTX_Parameter_t = (LX_TTX_PARAMETER_T *)((UINT32)g_ttx_ctx._gMMapTTX + (g_ttx_ctx.gmmap_size - 64 ));
		}
		else
		{
			g_ttx_ctx.pTTX_Parameter_t = (LX_TTX_PARAMETER_T *)((UINT32)g_ttx_ctx._gMMapTTX + (g_ttx_ctx.gmmap_size - 64 - 16));
		}

        ret = RET_OK;
    } while(0);
#endif

	return ret;
}


#ifdef SEETV_BRINGUP
int vbi_kwrap_ttx_open_data_file(void)
{
   int ret = RET_ERROR;

   do{
        /* Step 1. Check debug mode */
        if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_CATCH_FROM_FILE] <= 0) {ret = RET_OK; break;}

        /* Step 2. Search for file... */
        TTX_DEBUG_PRINT("[VBI TTX] Searching for input file... \n");

        /* Step 2-1. Is this the first time? YES */
        if(gVBIDebugModeStatus.in_file_status < VBI_FILE_POINTER_USB1) {
                /* USB1 position */
                TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb1/Drive1...\n");
				gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb1/Drive1/VBI_TTX_Data.txt", "r");
                if(gVBIDebugModeStatus.infile != NULL){
                        gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_USB1; ret = RET_OK; break; }

				/* USB1-9 opsition */
				TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb1/Drive9...\n");
				gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb1/Drive9/VBI_TTX_Data.txt", "r");
                if(gVBIDebugModeStatus.infile != NULL){
                        gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_USB1_9; ret = RET_OK; break; }

                /* USB2 position */
				TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb2/Drive1...\n");
                gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb2/Drive1/VBI_TTX_Data.txt", "r");
                if(gVBIDebugModeStatus.infile != NULL){
                        gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_USB2; ret = RET_OK; break; }

                /* USB3 position */
               	TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb3/Drive1...\n");
				gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb3/Drive1/VBI_TTX_Data.txt", "r");
                if(gVBIDebugModeStatus.infile != NULL){
                        gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_USB3; ret = RET_OK; break; }

                /* NFS position */
               	TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting NFS position...\n");
                gVBIDebugModeStatus.infile = fopen("./VBI_TTX_Data.txt", "r");
                if(gVBIDebugModeStatus.infile != NULL){
                        gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_NFS; ret = RET_OK; break; }
        }
        else{ /* Step 2-2. Is this the first time? NO! Then reset file pointer to initial state */
                /* First close existing file pointer */
                fclose(gVBIDebugModeStatus.infile);
                gVBIDebugModeStatus.infile = NULL;

                /* Reopen file pointer based on previous opened records... */
                switch(gVBIDebugModeStatus.in_file_status)
                {
                        case VBI_FILE_POINTER_USB1:
                                gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb1/Drive1/VBI_TTX_Data.txt", "r");
                                break;
						case VBI_FILE_POINTER_USB1_9:
                                gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb1/Drive9/VBI_TTX_Data.txt", "r");
                                break;
                        case VBI_FILE_POINTER_USB2:
                                gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb2/Drive1/VBI_TTX_Data.txt", "r");
                                break;
                        case VBI_FILE_POINTER_USB3:
                                gVBIDebugModeStatus.infile = fopen("/mnt/usb/usb3/Drive1/VBI_TTX_Data.txt", "r");
                                break;
                        case VBI_FILE_POINTER_NFS:
                                gVBIDebugModeStatus.infile = fopen("./VBI_TTX_Data.txt", "r");
                                break;
                        default:
                                gVBIDebugModeStatus.infile = NULL;
                }

                if(gVBIDebugModeStatus.infile != NULL) { ret = RET_OK; break; }
                else gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_ERROR;
        }

   }while(0);

   return ret;
}
#endif


int vbi_kwrap_ttx_create_file_pointer(void)
{
   int ret = RET_ERROR;

#ifdef SEETV_BRINGUP
   do{
        /* Step 1. Check debug mode & prevent reopening existing file pointer */
        if((gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DUMP_TO_FILE] > 0) | \
                                      (gVBIDebugModeStatus.out_file_status >= VBI_FILE_POINTER_USB1)) break;

        TTX_DEBUG_PRINT("[VBI TTX] File pointer create for data dump. Current mode[%d] ([0~2] None, [2~4] USB, [5] NFS) \n",gVBIDebugModeStatus.out_file_status);


        /* Step 2. Search for approperiate mount location */
        TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb1/Drive1...\n");
        gVBIDebugModeStatus.outfile = fopen("/mnt/usb/usb1/Drive1/VBI_TTX_Data.txt", "w");
        if(gVBIDebugModeStatus.outfile != NULL){
                //chmod("/mnt/usb/usb1/Drive1/VBI_TTX_Data.txt", 0777);
                gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_USB1; ret = RET_OK; break; }

		TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb1/Drive9...\n");
        gVBIDebugModeStatus.outfile = fopen("/mnt/usb/usb1/Drive9/VBI_TTX_Data.txt", "w");
        if(gVBIDebugModeStatus.outfile != NULL){
                //chmod("/mnt/usb/usb1/Drive1/VBI_TTX_Data.txt", 0777);
                gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_USB1_9; ret = RET_OK; break; }

        TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb2/Drive1...\n");
        gVBIDebugModeStatus.outfile = fopen("/mnt/usb/usb2/Drive1/VBI_TTX_Data.txt", "w");
        if(gVBIDebugModeStatus.outfile != NULL){
                //chmod("/mnt/usb/usb2/Drive1/VBI_TTX_Data.txt", 0777);
                gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_USB2; ret = RET_OK; break; }

        TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting /mnt/usb/usb3/Drive1...\n");
        gVBIDebugModeStatus.outfile = fopen("/mnt/usb/usb3/Drive1/VBI_TTX_Data.txt", "w");
        if(gVBIDebugModeStatus.outfile != NULL){
                //chmod("/mnt/usb/usb3/Drive1/VBI_TTX_Data.txt", 0777);
                gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_USB3; ret = RET_OK; break; }

        TTX_DEBUG_PRINT("[VBI TTX] Searching for valid mount location, attempting NFS position...\n");
        gVBIDebugModeStatus.outfile = fopen("./VBI_TTX_Data.txt", "w");
        if(gVBIDebugModeStatus.outfile != NULL){
                //chmod("./VBI_TTX_Data.txt", 0777);
                gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_NFS; ret = RET_OK; break; }

        /* Step 3. If file pointer failed on all mount cases, change flag to FAILED. */
        gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_FAILED;
    }while(0);

    if(ret == RET_OK) TTX_DEBUG_PRINT("[VBI TTX] File pointer mode changed to [%d] ([0~2] None, [2~5] USB, [6] NFS) \n",gVBIDebugModeStatus.out_file_status);
#endif
   return ret;
}


int vbi_kwrap_ttx_close_file_pointer(void)
{
   int ret = RET_ERROR;

#ifdef SEETV_BRINGUP
   do{
        /* Step 1. Check to prevent closing a file pointer that doesn't even exists */
        if(gVBIDebugModeStatus.out_file_status > VBI_FILE_POINTER_USB1) { ret = RET_OK; break; }

        TTX_DEBUG_PRINT("[VBI TTX] Closing file pointer used for data dump. Current mode[%d] ([0~2] None, [2~5] USB, [6] NFS) \n",gVBIDebugModeStatus.out_file_status);

        /* Step 2. Close approperiate mount location */
        fflush(gVBIDebugModeStatus.outfile);
		fclose(gVBIDebugModeStatus.outfile);
        gVBIDebugModeStatus.outfile = NULL;

        gVBIDebugModeStatus.out_file_status = VBI_FILE_POINTER_NONE;
        TTX_DEBUG_PRINT("[VBI TTX] File pointer mode changed to [%d] ([0~2] None, [2~5] USB, [6] NFS) \n",gVBIDebugModeStatus.out_file_status);
        ret = RET_OK;
    }while(0);
#endif

   return ret;
}

int vbi_kwrap_ttx_close_data_file(void)
{
   int ret = RET_ERROR;

#ifdef SEETV_BRINGUP
   do{
        /* Step 1. Check to prevent closing a file pointer that doesn't even exists */
        if(gVBIDebugModeStatus.in_file_status < VBI_FILE_POINTER_USB1) { ret = RET_OK; break; }

        TTX_DEBUG_PRINT("[VBI TTX] Closing data file used for debugging. Current mode[%d] ([0~2] None, [2~5] USB, [6] NFS) \n",gVBIDebugModeStatus.in_file_status);

        /* Step 2. Close approperiate mount location */
        fclose(gVBIDebugModeStatus.infile);
        gVBIDebugModeStatus.infile = NULL;

        gVBIDebugModeStatus.in_file_status = VBI_FILE_POINTER_NONE;
        TTX_DEBUG_PRINT("[VBI TTX] Data file mode changed to [%d] ([0~2] None, [2~5] USB, [6] NFS) \n",gVBIDebugModeStatus.out_file_status);
        ret = RET_OK;
    }while(0);
#endif

   return ret;
}


static int _vbi_kwrap_release_mmap(void)
{
	int ret = RET_ERROR;

#ifdef SEETV_BRINGUP
    do{
		if((UINT32)g_ttx_ctx._gMMapTTX == 0){
			TTX_PRINT("[%s:%d] Nothing to Unmmap.\n", __F__, __L__);
			ret = RET_OK;
			break;
		}

		munmap((void*)g_ttx_ctx._gMMapTTX, g_ttx_ctx.gmmap_size );
		g_ttx_ctx._gMMapTTX = 0;
		g_ttx_ctx.pTTX_Parameter_t = 0;
		ret = RET_OK;
    } while(0);

#endif
	return ret;
}


static int _vbi_kwrap_release(void)
{
	int ret = RET_ERROR;

    do{

	    ret = _vbi_kwrap_release_mmap();
        if(ret <0) 
		{
			BREAK_WRONG(ret);
		}

		//do nothing in ioctl


		ret = RET_OK;
    }while(0);


	return ret;
}


static int _vbi_kwrap_ttx_stopslicer(void)
{
	int ret = RET_OK;

	//do nothing in ioctl
	VBI_PRINT("VBI TTX Stop Slicer\n");

	return ret;
}

static int _vbi_kwrap_ttx_startslicer(void)
{
	int ret = RET_OK;

	//do nothing in ioctl
	VBI_PRINT("VBI TTX Slicer ON\n");

	return ret;

}

static int _vbi_kwrap_ttx_disableinterrupt(void)
{
	int ret = RET_ERROR;

	ret = VBI_TTX_SetInterrupt(OFF);

	gVBIInterruptControl = 0;

	return ret;
}


static int _vbi_kwrap_ttx_enableinterrupt(void)
{
	int ret = RET_ERROR;

	ret = VBI_TTX_SetInterrupt(ON);

	gVBIInterruptControl = 1;

	return ret;
}


static int vbi_kwrap_ttx_get_status(LX_TTX_TYPE_T ttx_type, UINT32 *ttx_status)
{
	int ret = RET_ERROR;

    do{
	    if(VBI_get_buffer_ptr() == NULL){ *ttx_status = 0; BREAK_WRONG(0); }
        else {
		    *ttx_status = VBI_get_ttx_parameter_ptr()->Status & ttx_type;
		    ret = RET_OK;
	    }
    }while(0);

	return ret;
}


static int _vbi_kwrap_ttx_get_packets_from_file(LX_TTX_PACKET_TYPE_T **ttx_packet)
{
    int ret = RET_ERROR;
#ifdef SEETV_BRINGUP
    int i, packetCounter=0;
    char packetFromFile[145];  // buffer for one line(48 bytes : 42 + 6)
    UINT32 byteBuffer1, byteBuffer2;

    do{
        /* Step 1. Break out if debug mode is not enabled */
        if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_CATCH_FROM_FILE] <= 0) break;

        /* Step 2. Check whether file pointer has been loaded or not. */
        if((gVBIDebugModeStatus.in_file_status <= VBI_FILE_POINTER_ERROR)| \
                        (gVBIDebugModeStatus.in_file_status >= VBI_FILE_POINTER_MAXNUM)) break;

        /* Step 3. Begin collecting data from file */
        if(fgets(packetFromFile, (145 * sizeof(char)), gVBIDebugModeStatus.infile) != NULL) {
               for(i=0; i<144; i+=3) {
                    byteBuffer1 = packetFromFile[i]>'9'   ? packetFromFile[i]-'A'+10   : packetFromFile[i]-'0';
                    byteBuffer2 = packetFromFile[i+1]>'9' ? packetFromFile[i+1]-'A'+10 : packetFromFile[i+1]-'0';

                    byteBuffer1 = byteBuffer1 & 0x0000000F;
                    byteBuffer2 = byteBuffer2 & 0x0000000F;

                    gPacket[packetCounter] = (byteBuffer1<<4)|byteBuffer2;
                    packetCounter++;
               }

            g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = (void *)&gPacket;
            g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 1;
        }
        else{
            vbi_kwrap_ttx_open_data_file();

            g_ttx_ctx.packet_buffer_t.pTTX_Packet_Buffer = NULL;
            g_ttx_ctx.packet_buffer_t.TTX_Packet_Unit = 0;
        }

        /* Step 4. Send data above... */
         *ttx_packet = &g_ttx_ctx.packet_buffer_t;

        ret = RET_OK;
    }while(0);
#endif

    return ret;
}

static int _vbi_kwrap_ttx_get_packets_from_mem(LX_TTX_PACKET_TYPE_T **ttx_packet, int packet_count)
{
	UINT32 CurGetIdx, CurPutIdx;
	int ret = RET_ERROR;

    do{
	    if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);

		CurGetIdx = VBI_get_ttx_parameter_ptr()->GetAddr;
		CurPutIdx = VBI_get_ttx_parameter_ptr()->PutAddr;

		TTX_DEBUG_PRINT("[VBI TTX] TTX GetAddr=[0x%x], PutAddr=[0x%x]\n", CurGetIdx, CurPutIdx);

		if(CurGetIdx == CurPutIdx) {                             ///< No Data to Read
			vbi_ttx_packet_t.pTTX_Packet_Buffer = NULL;
			vbi_ttx_packet_t.TTX_Packet_Unit = 0;
			*ttx_packet = &vbi_ttx_packet_t;
		}
		else if(CurGetIdx > CurPutIdx) ///< Read from CurGetIdx  to the End of Buffer
		{
			vbi_ttx_packet_t.pTTX_Packet_Buffer = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)CurGetIdx); ///< Address to get from
			if(packet_count == 0) 
			{
				vbi_ttx_packet_t.TTX_Packet_Unit = ((VBI_get_buffer_size() - 96) - CurGetIdx) / LX_TTX_PACKET_UNIT; ///< Data Size to get
				VBI_get_ttx_parameter_ptr()->GetAddr = 0; ///< Move GetAddr pointer to the beggining of TTX buffer
			}
			else if(packet_count > ( ((VBI_get_buffer_size() - 96) - CurGetIdx) / LX_TTX_PACKET_UNIT) )
			{
				vbi_ttx_packet_t.TTX_Packet_Unit = ((VBI_get_buffer_size() - 96) - CurGetIdx) / LX_TTX_PACKET_UNIT; ///< Data Size to get
				VBI_get_ttx_parameter_ptr()->GetAddr = 0; ///< Move GetAddr pointer to the beggining of TTX buffer
			}
			else	// read size is smaller than packet in buffer
			{
				vbi_ttx_packet_t.TTX_Packet_Unit = packet_count;
				VBI_get_ttx_parameter_ptr()->GetAddr += packet_count * LX_TTX_PACKET_UNIT;
			}
			*ttx_packet = &vbi_ttx_packet_t;
		}
		else//(CurGetIdx < CurPutIdx) ///< Read from CurGetIdx  to PutIdx
		{
			vbi_ttx_packet_t.pTTX_Packet_Buffer = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)CurGetIdx); ///< Address to get from
			if(packet_count == 0) 
			{
				vbi_ttx_packet_t.TTX_Packet_Unit = (CurPutIdx - CurGetIdx)/LX_TTX_PACKET_UNIT ; ///< Data Size to get
				VBI_get_ttx_parameter_ptr()->GetAddr = CurPutIdx; ///< Move GetAddr pointer to PutAddr pointer
			}
			else if(packet_count > ((CurPutIdx - CurGetIdx)/LX_TTX_PACKET_UNIT) )
			{
				vbi_ttx_packet_t.TTX_Packet_Unit = (CurPutIdx - CurGetIdx)/LX_TTX_PACKET_UNIT ; ///< Data Size to get
				VBI_get_ttx_parameter_ptr()->GetAddr = CurPutIdx; ///< Move GetAddr pointer to PutAddr pointer
			}
			else	// read size is smaller than packet in buffer
			{
				vbi_ttx_packet_t.TTX_Packet_Unit = packet_count;
				VBI_get_ttx_parameter_ptr()->GetAddr += packet_count * LX_TTX_PACKET_UNIT;
			}
			*ttx_packet = &vbi_ttx_packet_t;
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

static int _vbi_kwrap_cc_enableinterrupt(void)
{
	int ret = RET_ERROR;

	VBI_PRINT("VBI CC interrupt ON\n");

	ret = VBI_CC_InterruptControl(TRUE);

	gVBIInterruptControl = 1;

	return ret;
}

static int _vbi_kwrap_cc_startslicer(void)
{
	int ret = RET_OK;

	//do nothing in ioctl

	return ret;
}

static int _vbi_kwrap_cc_stopslicer(void)
{
	int ret = RET_OK;

	//do nothing in ioctl

	return ret;
}

static int _vbi_kwrap_cc_disableinterrupt(void)
{
	int ret = RET_ERROR;

	VBI_PRINT("VBI CC Interrupt OFF\n");

	ret = VBI_CC_InterruptControl(FALSE);

	gVBIInterruptControl = 0;

	return ret;
}


/* ���� �� workaround�� kernel driver code���� �������� */
static int _vbi_kwrap_cc_correct_parity(UINT8 *data)
{
    int ret = RET_ERROR;

    do{
		if(_vbi_kwrap_cc_checkparity(*data)>0){
		    // 20111202 : Modified to recover data when 2 LSB are "01"
			if((*data & 0x03) == 0x02) *data |= 0x01;
		}

        ret = RET_OK;
	} while(0);

    return ret;
}


/* Return  2 : Parity Error
 * Return  1 : Do not update proFilter(ex. incase of not counting 0x80)
 * Return  0 : Parity OK
 * Return -1 : Function error */
static int _vbi_kwrap_cc_checkparity(UINT8 data)
{
	 int ret = RET_ERROR;
	UINT8 Mask[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

	UINT32	i = 0;
	UINT8 Parity_check = 0;

    do{
		Parity_check = (data & Mask[i]);

		for(i=1; i<8 ;i++) {
    		Parity_check ^= (data & Mask[i]) >> i; }

		if(Parity_check == 0) {
			CC_DEBUG_PRINT("[VBI CC] CC parity error detected! Error data is [0x%x]\n", data);
			ret = 2;
		}
		else ret = 0;

		if((gVBIDebugModeStatus.dataProfile.cc_dont_count_80>0)&&(data == 0x80)) ret = 1;

	} while(0);

    return ret;
}

/*	Return	1:	Can't fix hamming error
 *	Return	0:	Success fixing hamming error
 *	Return RET_ERROR: function error
 */
static int _vbi_kwrap_ttx_correct_hamming_8_4(UINT8 *code)
{
	int ret = RET_ERROR;
	UINT8 org_data;

	org_data = gVBI_TTX_Decrypt_Hamming1_Correction_Tab[*code];

	if ( org_data < 0xff ) {
		*code = gVBI_TTX_Encrypt_Hamming_Tab[org_data & 0x0F];
		ret = 0;
	}
	else {
		/* Failed recovering Hamming error */
		ret = 1;
	}

	return ret;
}


/* Return  2 : Parity Error
 * Return  0 : Parity OK
 * Return -1 : Function error */
static int _vbi_kwrap_ttx_check8to4hamming(UINT8 data)
{
	int ret = RET_ERROR;

	switch(data)
	{
		case 0x02:
		case 0x15:
		case 0x2F:
		case 0x38:
		case 0x49:
		case 0x5E:
		case 0x64:
		case 0x73:
		case 0x8c:
		case 0x9B:
		case 0xA1:
		case 0xB6:
		case 0xC7:
		case 0xD0:
		case 0xEA:
		case 0xFD:
			ret = 0;	// No Hamming error
			break;
		default:
			ret = 2;	// Hamming error

			if(gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter] == 1)
				VBI_PRINT("[VBI TTX] Check Hamming Error on [0x%x] -> Error[%d]\n", data, ret);
			break;
	}

	TTX_DEBUG_PRINT("[VBI TTX] Check Hamming Error on [0x%x] -> Error[%d]\n", data, ret);

	return ret;
}

static int _vbi_kwrap_updatedataprofilter(int error)
{
	int ret = RET_ERROR;

	do{
		/* Step 0. Check overflow of full counter */
		if(gVBIDebugModeStatus.dataProfile.full_count >= gVBIDebugModeStatus.dataProfile.max_count_value)
		{
			VBI_PRINT("[%s:%d] Data proFilter counter overflow.\n", __F__, __L__);
			VBI_PRINT("Profile Result [ERROR]/[TOTAL] : [%u]/[%u]\n",	gVBIDebugModeStatus.dataProfile.error_count, gVBIDebugModeStatus.dataProfile.full_count);
			break;
		}

		/* Step 1. Incase of not operating proFilter on 0x80 data, return OK*/
		if(error == 1) {ret=RET_OK; break;}

		/* Step 2. Increase full count */
		gVBIDebugModeStatus.dataProfile.full_count++;

		/* Step 3. Increase error count if error has been detected */
		if(error > 1) gVBIDebugModeStatus.dataProfile.error_count++;

		ret = RET_OK;
	}while(0);

	return ret;
}

int vbi_kwrap_resetdataprofilter(void)
{
	int ret = RET_ERROR;

	do{
		/* Step 1. Reset counter */
		gVBIDebugModeStatus.dataProfile.full_count	=0;
		gVBIDebugModeStatus.dataProfile.error_count	=0;

		ret = RET_OK;
	}while(0);

	return ret;
}



int vbi_kwrap_ttx_setdebugmodekprint(int mode)
{
	int ret = RET_ERROR;

	if(mode>0)
		VBI_TTX_DebugPrintMode(1);
	else
		VBI_TTX_DebugPrintMode(0);

	return ret;
}

int vbi_kwrap_cc_setdebugmodekprint(int mode)
{
	int ret = RET_ERROR;

	if(mode==2) ret = VBI_CC_SetPrintResultOfLineDetect(1);
	else if(mode == 1) ret = VBI_CC_DebugPrintMode(1);
	else if(mode == 3) ret = VBI_CC_DebugPrintMode(3);
	else if(mode == 4) ret = VBI_CC_DebugPrintMode(4);
	else
	{
		ret = VBI_CC_SetPrintResultOfLineDetect(0);
		ret |= VBI_CC_DebugPrintMode(0);
	}

	return ret;
}

int vbi_kwrap_setlogmprintmask(int logLevel, BOOLEAN onOff)
{
#if 0
	int ret = RET_ERROR;
	LX_VBI_LOGM_SETTING_T stParams;
	
	VBI_CHECK_DEVICE();

	do{
		/* Step 1. Load param */
		stParams.logLevel = logLevel;
		stParams.onOff = onOff;

		ret = VBI_SetLogmPrint(&stParams);

		ret = RET_OK;
	}while(0);
		
	return ret;
#endif
	return 0;
}

static int _vbi_kwrap_get_cp_data(UINT8 **ppacket, int *is_analog_cp_protected,int *is_analog_cp_Stable)
{
	int ret, i;
	volatile UINT8 *packet;

	do{
	    if(VBI_get_buffer_ptr() == NULL) BREAK_WRONG(0);
		/* Step 02. Get CGMS packet from memory.*/
		*ppacket = (UINT8 *)((uintptr_t)VBI_get_buffer_ptr() + (uintptr_t)VBI_get_ttx_parameter_ptr()->CGMS_Offset);

		packet = *ppacket;

		CGMS_DEBUG_PRINT("[VBI CGMS] Sliced data : [%10ph]\n", packet);

		/* Get Analog CP Info from kernel */
		ret = VBI_CheckAnalogCP();
		CGMS_DEBUG_PRINT("[VBI CGMS] Got Analog CP info from kernel : ret [0x%08x]\n", ret);

		if(ret == LX_VBI_CP_TYPE_ANALOG_1) 
			*is_analog_cp_protected = 0x1;
		else 
			*is_analog_cp_protected = 0x0;

		for(i=0;i<gVBIAnalogCPCopyProtectionRAWFilterSize;i++){
			gVBIAnalogCPCopyProtectionRAWFilter[i] =  gVBIAnalogCPCopyProtectionRAWFilter[i+1];
		}

		/* New data in to buffer */
		gVBIAnalogCPCopyProtectionRAWFilter[gVBIAnalogCPCopyProtectionRAWFilterSize] = *is_analog_cp_protected;

		/* Check stablity */
		for(i=0;i<gVBIAnalogCPCopyProtectionRAWFilterSize;i++){
			if(gVBIAnalogCPCopyProtectionRAWFilter[i] != gVBIAnalogCPCopyProtectionRAWFilter[i+1]){
				*is_analog_cp_Stable = *is_analog_cp_Stable + 1;
			}
		}

		CGMS_DEBUG_PRINT("[VBI CGMS] Filter: AnalogCP [%8ph]\n", &gVBIAnalogCPCopyProtectionRAWFilter[0]);
	}while(0);

	return ret;
}

static int _vbi_kwrap_process_cp_data(UINT8 **ppacket)
{
	UINT8 cGmsBit;
	UINT8 stableCheck = 0x00;
	UINT8 modified_cgmsbit0;
	UINT8 modified_cgmsbit1;
	volatile UINT8 *packet;
	int i;
	int is_WSS_CP_Stable = 0;

	if(ppacket == NULL)
		return RET_ERROR;

	packet = *ppacket;

	/* Copy to buffer */
	packet[10] = packet[3];

	/* Increment VBI Sliced ID*/
	gVBICopyProtectionDataID++;

	if(packet[10] == 0x09){
		stableCheck = packet[7];
		cGmsBit = packet[8];

		stableCheck = stableCheck<<4; stableCheck = stableCheck & 0xF0;
		cGmsBit = cGmsBit>>4; cGmsBit = cGmsBit & 0x03;

		stableCheck = stableCheck | cGmsBit;

		/* Shift WSS CP Stable Filter */
		for(i=0;i<gVBIWSSCopyProtectionRAWFilterSize;i++){
			gVBIWSSCopyProtectionRAWFilter[i] =  gVBIWSSCopyProtectionRAWFilter[i+1];
		}

		/* New data in to buffer */
		gVBIWSSCopyProtectionRAWFilter[gVBIWSSCopyProtectionRAWFilterSize] = stableCheck;

		/* Check stablity */
		for(i=0;i<gVBIWSSCopyProtectionRAWFilterSize;i++){
			if(gVBIWSSCopyProtectionRAWFilter[i] != gVBIWSSCopyProtectionRAWFilter[i+1]){
				is_WSS_CP_Stable++;
			}
		}

		CGMS_DEBUG_PRINT("[VBI CGMS] RAW WSS ID [%d] \n", 	gVBICopyProtectionDataID);
		for(i=0;i<=gVBIWSSCopyProtectionRAWFilterSize;i++) {
			CGMS_DEBUG_PRINT("[VBI CGMS] RAW Filter[%d] <= wss [0x%x]\n", i, gVBIWSSCopyProtectionRAWFilter[i]);
		}
		CGMS_DEBUG_PRINT("[VBI CGMS] RAW WSS stable size is [%d] \n", is_WSS_CP_Stable);

		if(is_WSS_CP_Stable <= gVBIWSSCopyProtectionRAWFilterThreshold){

			/* 20130724 : Do not use memcpy. Kernel memory alignment message comes when memcpy is used */
			//memcpy((void *)(packet + 11), (void *)(packet + 7), 3);
			packet[11] = packet[7];
			packet[12] = packet[8];
			packet[13] = packet[9];
			//memset((void *)(packet + 14), 0, 1);
			packet[14] = 0;
		}
		else{
			//memcpy((void *)(packet + 11), (void *)(packet + 7), 1);
			packet[11] = packet[7];
			memset((void *)((uintptr_t)packet + (uintptr_t)12), 0, 3);
		}
	}
	else if((packet[10] == 0x0a)|| (packet[10] == 0x0b)){
		stableCheck = packet[8];
		cGmsBit = packet[7];

		stableCheck = stableCheck & 0x03;
		cGmsBit = cGmsBit>>4; cGmsBit = cGmsBit & 0x0C;

		stableCheck = stableCheck | cGmsBit;

		/* Shift CGMS Stable Filter */
		for(i=0;i<gVBICGMSCopyProtectionRAWFilterSize;i++){
			gVBICGMSCopyProtectionRAWFilter[i] =  gVBICGMSCopyProtectionRAWFilter[i+1];
		}

		/* New data in to buffer */
		gVBICGMSCopyProtectionRAWFilter[gVBICGMSCopyProtectionRAWFilterSize] = stableCheck;

		/* Check stablity */
		for(i=0;i<gVBICGMSCopyProtectionRAWFilterSize;i++){
			if(gVBICGMSCopyProtectionRAWFilter[i] != gVBICGMSCopyProtectionRAWFilter[i+1]){
				is_WSS_CP_Stable++;
			}
		}
		CGMS_DEBUG_PRINT("[VBI CGMS] RAW CGMS ID [%d] \n", 	gVBICopyProtectionDataID);
		for(i=0;i<=gVBICGMSCopyProtectionRAWFilterSize;i++) {
			CGMS_DEBUG_PRINT("[VBI CGMS] RAW Filter[%d] <= cmgs [0x%x]\n", i, gVBICGMSCopyProtectionRAWFilter[i]);
		}
		CGMS_DEBUG_PRINT("[VBI CGMS] RAW CGMS stable size is [%d] \n", is_WSS_CP_Stable);


		if(is_WSS_CP_Stable <= gVBICGMSCopyProtectionRAWFilterThreshold){
			/* 20130724 : Do not use memcpy. Kernel memory alignment message comes when memcpy is used */
			//memcpy((void *)(packet + 11), (void *)(packet + 7), 3);
			packet[11] = packet[7];
			packet[12] = packet[8];
			packet[13] = packet[9];
			//memset((void *)(packet + 14), 0, 1);
			packet[14] = 0;
		}
		else{
			modified_cgmsbit0 = packet[7] & 0x3F;
			modified_cgmsbit1 = packet[8] & 0xFC;

			/*
			memcpy((void *)(packet + 11), (void *)(&modified_cgmsbit0), 1);
			memcpy((void *)(packet + 12), (void *)(&modified_cgmsbit1), 1);
			memcpy((void *)(packet + 13), (void *)(packet + 9), 1);
			memset((void *)(packet + 14), 0, 1);
			*/
			packet[11] = modified_cgmsbit0;
			packet[12] = modified_cgmsbit1;
			packet[13] = packet[9];
			packet[14] = 0;
		}


	}
	else{
		/* Copy To buffer */
		/* 20130724 : Do not use memcpy. Kernel memory alignment message comes when memcpy is used */
		//memcpy((void *)(packet + 11), (void *)(packet + 7), 3);
		packet[11] = packet[7];
		packet[12] = packet[8];
		packet[13] = packet[9];
		//memset((void *)(packet + 14), 0, 1);
		packet[14] = 0;
	}

	/* Copy VBI Sliced data ID */
	//memcpy((void *)(packet + 14), (void *)(&gVBICopyProtectionDataID), 1);
	packet[14] = gVBICopyProtectionDataID;

	return RET_OK;
}

void vbi_kwrap_dbg_initialize(void)
{
#ifdef SEETV_BRINGUP
	g_vbi_logm_fd = KADP_LOGM_ObjRegister(KADP_VBI);
	if(g_vbi_logm_fd < 0)
	{
		printf("[%s:%u] fail register logm\n", __F__, __L__);
		return;
	}

	KADP_LOGM_BitMaskEnable(g_vbi_logm_fd, LX_LOGM_LEVEL_NOTI);
	KADP_LOGM_BitMaskEnable(g_vbi_logm_fd, LX_LOGM_LEVEL_INFO);
	KADP_LOGM_BitMaskEnable(g_vbi_logm_fd, LX_LOGM_LEVEL_ERROR);
	KADP_LOGM_BitMaskEnable(g_vbi_logm_fd, LX_LOGM_LEVEL_WARNING);
#endif
}

void vbi_kwrap_dbg_shutdown(void)
{
#ifdef SEETV_BRINGUP
	int ret;

	ret = KADP_LOGM_ObjDeregister(KADP_VBI);
	if(ret < 0)
	{
		printf("[%s:%u] fail deregister logm\n", __F__, __L__);
		return;
	}
	g_vbi_logm_fd = -1; 
#endif
}

static int _vbi_kwrap_ttx_unittest(LX_TTX_PACKET_TYPE_T **gptPB)
{
	UINT32 a, u32VBIDebugFirstData, u32VBIDebugSecondData;
	int i;

	/* This part is for debugging purpose. Complicated algorithm for MW UNIT test.
	 * This part may not be easy to observe the code
	 */
	TTX_DEBUG_PRINT("[VBI TTX] RUNNING ON TARA UNIT TEST MODE. THIS WILL SEND TEST PATTERN TO TARA MW\n");
	a = 0;

	if(gVBIDebugMWUnitTestPointer !=0)  gVBIDebugMWUnitTestSubPointer += 144;
	for(i = 0; i<144; i+=3){
		u32VBIDebugFirstData = gVBITeletextUnitTestSig[i + gVBIDebugMWUnitTestSubPointer] > '9' ? gVBITeletextUnitTestSig[i + gVBIDebugMWUnitTestSubPointer] -'A' +10  :  gVBITeletextUnitTestSig[i + gVBIDebugMWUnitTestSubPointer] - '0';
		u32VBIDebugSecondData = gVBITeletextUnitTestSig[i + 1 + gVBIDebugMWUnitTestSubPointer] > '9' ? gVBITeletextUnitTestSig[i + 1 + gVBIDebugMWUnitTestSubPointer] -'A' +10  :  gVBITeletextUnitTestSig[i + 1 + gVBIDebugMWUnitTestSubPointer] - '0';

		u32VBIDebugFirstData = u32VBIDebugFirstData & 0x0000000F;
		u32VBIDebugSecondData = u32VBIDebugSecondData & 0x0000000F;

		g8VBIDebugInputLine[a] = (u32VBIDebugFirstData << 4) | u32VBIDebugSecondData;
		a++;
	}

	gVBIDebugMWUnitTestPointer++;
	if(gVBIDebugMWUnitTestPointer > 10){
		gVBIDebugMWUnitTestPointer = 0;
		gVBIDebugMWUnitTestSubPointer = 0;
	}

	_g_TTX_packet_for_UnitTest.TTX_Packet_Unit = 1;
	_g_TTX_packet_for_UnitTest.pTTX_Packet_Buffer = (UINT8 *)&g8VBIDebugInputLine;

	*gptPB = &_g_TTX_packet_for_UnitTest;

	return RET_OK;
}

static int _vbi_kwrap_ttx_hammingcorrection(LX_TTX_PACKET_TYPE_T **gptPB)
{
	int i;
	int fixed_result;
	UINT8 firstData, secondData;
	LX_TTX_PACKET_TYPE_T *pTTX_Packet;

	if(gptPB == NULL)
		return RET_ERROR;

	pTTX_Packet = *gptPB;

	for(i=0; i<(int)pTTX_Packet->TTX_Packet_Unit;i++) {

		/* 0. Initiate result checker & Backup original data */
		fixed_result = 0;
		firstData	= pTTX_Packet->pTTX_Packet_Buffer[6+(LX_TTX_PACKET_UNIT*i)];
		secondData	= pTTX_Packet->pTTX_Packet_Buffer[7+(LX_TTX_PACKET_UNIT*i)];

		/* 1. Fix hamming error on 6th data */
		if(_vbi_kwrap_ttx_check8to4hamming(pTTX_Packet->pTTX_Packet_Buffer[6+(LX_TTX_PACKET_UNIT*i)]) > 0) {
			fixed_result = _vbi_kwrap_ttx_correct_hamming_8_4((UINT8 *)&pTTX_Packet->pTTX_Packet_Buffer[6+(LX_TTX_PACKET_UNIT*i)]);

			/* Leave a mark that the Data was modified compared to the origial Sliced data */
			pTTX_Packet->pTTX_Packet_Buffer[0+(LX_TTX_PACKET_UNIT*i)] = 0xde;
			pTTX_Packet->pTTX_Packet_Buffer[1+(LX_TTX_PACKET_UNIT*i)] = 0xad;
		}
		/* 2. Fix hamming error on 7th data */
		if(_vbi_kwrap_ttx_check8to4hamming(pTTX_Packet->pTTX_Packet_Buffer[7+(LX_TTX_PACKET_UNIT*i)]) > 0) {
			fixed_result += _vbi_kwrap_ttx_correct_hamming_8_4((UINT8 *)&pTTX_Packet->pTTX_Packet_Buffer[7+(LX_TTX_PACKET_UNIT*i)]);

			/* Leave a mark that the Data was modified compared to the origial Sliced data */
			pTTX_Packet->pTTX_Packet_Buffer[2+(LX_TTX_PACKET_UNIT*i)] = 0xbe;
			pTTX_Packet->pTTX_Packet_Buffer[3+(LX_TTX_PACKET_UNIT*i)] = 0xef;
		}

		/* 3. Write in 'DEAD'(both hamming error) on 6th&7th data only when one of the two byte has error */
		if(fixed_result >0 ){
			TTX_DEBUG_PRINT("Warning! Detected Failur on Hamming correction operation. Result was [%d]\n", fixed_result);
			pTTX_Packet->pTTX_Packet_Buffer[6+(LX_TTX_PACKET_UNIT*i)] = firstData;
			pTTX_Packet->pTTX_Packet_Buffer[7+(LX_TTX_PACKET_UNIT*i)] = secondData;
			pTTX_Packet->pTTX_Packet_Buffer[0+(LX_TTX_PACKET_UNIT*i)] = 0xbe;
			pTTX_Packet->pTTX_Packet_Buffer[1+(LX_TTX_PACKET_UNIT*i)] = 0xef;
			pTTX_Packet->pTTX_Packet_Buffer[2+(LX_TTX_PACKET_UNIT*i)] = 0xde;
			pTTX_Packet->pTTX_Packet_Buffer[3+(LX_TTX_PACKET_UNIT*i)] = 0xad;
		}

		/* etc. Debugger */
		TTX_DEBUG_PRINT("[VBI TTX] Hamming corrector [0x%x]/[0x%x] --> [0x%x]/[0x%x] , Give up[%d]\n", firstData, secondData,  pTTX_Packet->pTTX_Packet_Buffer[6+(LX_TTX_PACKET_UNIT*i)], pTTX_Packet->pTTX_Packet_Buffer[7+(LX_TTX_PACKET_UNIT*i)], fixed_result);

	}

	return RET_OK;
}

static int _vbi_kwrap_ttx_dataprofilter(LX_TTX_PACKET_TYPE_T **gptPB)
{
	int i, hamming_6, hamming_7;
	LX_TTX_PACKET_TYPE_T *pTTX_Packet;

	if(gptPB == NULL)
		return RET_ERROR;

	pTTX_Packet = *gptPB;

	for(i=0; i<(int)pTTX_Packet->TTX_Packet_Unit;i++) {
		hamming_6 = _vbi_kwrap_ttx_check8to4hamming(pTTX_Packet->pTTX_Packet_Buffer[6+(LX_TTX_PACKET_UNIT*i)]);
		hamming_7 = _vbi_kwrap_ttx_check8to4hamming(pTTX_Packet->pTTX_Packet_Buffer[7+(LX_TTX_PACKET_UNIT*i)]);
		if( (hamming_6 > 0 ) || (hamming_7 > 0 ) )
		{
			VBI_PRINT("ttx error : [%48ph]\n", (UINT8 *)&pTTX_Packet->pTTX_Packet_Buffer[(LX_TTX_PACKET_UNIT*i)]);
		}

		if((_vbi_kwrap_updatedataprofilter(hamming_6)<0)||\
				(_vbi_kwrap_updatedataprofilter(hamming_7)<0)){
			gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter] = 0;
			VBI_PRINT("VBI TTX data error rate proFilter has completed its job!\n");
		}
	}

	return RET_OK;
}

__attribute__((unused)) static int _vbi_kwrap_ttx_data_file_dump(LX_TTX_PACKET_TYPE_T **gptPB)
{
	int ret = RET_OK;

#ifdef SEETV_BRINGUP
	LX_TTX_PACKET_TYPE_T *pTTX_Packet;

	if(gptPB == NULL)
		return RET_ERROR;

	pTTX_Packet = *gptPB;

	z = 0;
	for(i=0; i<(int)pTTX_Packet->TTX_Packet_Unit;i++) {
		for(y=0; y< LX_TTX_PACKET_UNIT; y++) {
			fprintf(gVBIDebugModeStatus.outfile, "%2x ", pTTX_Packet->pTTX_Packet_Buffer[z]);
			z++;
		}
		fprintf(gVBIDebugModeStatus.outfile, "\n");
	}
#endif
	return ret;

}

static int _vbi_kwrap_cc_dataprofilter(LX_CC_DATA_T *packet)
{
	int parity_1, parity_2;

	parity_1 = _vbi_kwrap_cc_checkparity(packet->data1);
	parity_2 = _vbi_kwrap_cc_checkparity(packet->data2);

	if(parity_1 == 2)
		VBI_PRINT("CC parity error 1 [0x%x]\n", packet->data1);
	if(parity_2 == 2)
		VBI_PRINT("CC parity error 2 [0x%x]\n", packet->data2);

	if((_vbi_kwrap_updatedataprofilter(parity_1)<0)||\
			(_vbi_kwrap_updatedataprofilter(parity_2)<0)){
		gVBIDebugModeStatus.modeOnOff[VBI_DEBUG_MODE_DATA_PROFilter] = 0;
		VBI_PRINT("VBI CC data error rate proFilter has completed its job!\n");
	}

	return RET_OK;
}

static int _vbi_kwrap_calculate_cp_type(UINT8 **ppacket)
{
	int i;
	int is_WSS_CP_Stable = 0;
	LX_VBI_CP_TYPE_T ret = RET_ERROR;
	volatile UINT8 *packet;
	UINT8 cGmsBit = 0x00;
	UINT8 vbiSlicedID = 0;
	UINT8 analogCP = 0;

	if(ppacket == NULL)
		return LX_VBI_CP_TYPE_NONE;

	packet = *ppacket;

	vbiSlicedID = (UINT8)(*(packet + 14));
	analogCP	= (UINT8)(*(packet + 15));

	CGMS_DEBUG_PRINT("[VBI CGMS] VBI Sliced ID is [0x%x]. AnalogCP is[0x%x] \n", vbiSlicedID, analogCP);
	for(i=0; i<6; i++) {
		CGMS_DEBUG_PRINT("[VBI CGMS] From memory : #%2d data is : [0x%x]\n", i, *(packet+i+10));
	}

	/* Step 03. Check Analog CP */
	if(analogCP != 0x00) 
		ret = LX_VBI_CP_TYPE_ANALOG_1;
	else 
		ret = LX_VBI_CP_TYPE_NONE;

	if((packet[10] == 0x0a) || (packet[10] == 0x0b)){
		/* Proceed if header was a CGMS header */
		cGmsBit = packet[11]; CGMS_DEBUG_PRINT("[VBI CGMS] Recieved CGMS data of [0x%x]\n",cGmsBit);
		cGmsBit = cGmsBit>>6; cGmsBit = cGmsBit & 0x03;
		//cGmsBit = _gBitReverse[(int)cGmsBit];
		CGMS_DEBUG_PRINT("[VBI CGMS] Processed CGMS data bit is [0x%x]\n", cGmsBit);

		if(cGmsBit == 0x00)
			ret |= LX_VBI_CP_TYPE_CGMS_0; 
		else if(cGmsBit == 0x1)
			ret |= LX_VBI_CP_TYPE_CGMS_2;
		else if(cGmsBit == 0x2)
			ret |= LX_VBI_CP_TYPE_CGMS_1; 
		else /* if(cGmsBit == 0x3) */
			ret |= LX_VBI_CP_TYPE_CGMS_3; 
		/*
		else
			ret |= LX_VBI_CP_TYPE_NONE; 
			*/
	}
	else if(packet[10] == 0x09){
		cGmsBit = packet[12]; 
		CGMS_DEBUG_PRINT("[VBI CGMS Recieved WSS CP data of [0x%x]\n", cGmsBit);
		cGmsBit = cGmsBit>>4; 
		cGmsBit = cGmsBit & 0x03;
		//cGmsBit = _gBitReverse[(int)cGmsBit];

		/* Shift WSS CP Stable Filter */
		for(i=0;i<gVBIWSSCopyProtectionFilterSize;i++){
			gVBIWSSCopyProtectionFilter[i] =  gVBIWSSCopyProtectionFilter[i+1];
		}

		/* New data in to buffer */
		gVBIWSSCopyProtectionFilter[gVBIWSSCopyProtectionFilterSize] = cGmsBit;

		/* Check stablity */
		for(i=0;i<gVBIWSSCopyProtectionFilterSize;i++){
			if(gVBIWSSCopyProtectionFilter[i] != gVBIWSSCopyProtectionFilter[i+1]){
				is_WSS_CP_Stable++;
			}
		}

		CGMS_DEBUG_PRINT("[VBI CGMS] Processed WSS CP data bit is [0x%x]\n", cGmsBit);
		for(i=0;i<=gVBIWSSCopyProtectionFilterSize;i++) {
			CGMS_DEBUG_PRINT("[VBI CGMS] Filter[%d] <= WSSCgms [0x%x]\n", i, gVBIWSSCopyProtectionFilter[i]);
		}

		/* Send data if valid & stable */
		if((cGmsBit != 0x00)&&(is_WSS_CP_Stable <= gVBIWSSCopyProtectionFilterThreshold)) 
			ret |= LX_VBI_CP_TYPE_WSS_1;
		else 
			ret |= LX_VBI_CP_TYPE_WSS_0;
	}

	return ret;
}

static int vbi_kwrap_cp_dataflush_thread(void *data)
{
	int ret;
	VBI_PRINT("\n_______ CP Thread ______\n");

	/* Step 0. Stamp Thread Flag */
	gIsVBIThreadCPAlive = TRUE;
	
	while(1)
	{
		if(!gIsVBIThreadCPAlive) {
			VBI_PRINT("[%s:%d] Forced kill thread \n", __F__, __L__);	
			break;
		}

#ifndef VBI_LATCHUP_DEBUG
		/* Step 1. CP data flusher */
		ret = vbi_kwrap_copyprotection_dataflusher_task();
		if(ret < 0) {
			VBI_PRINT("[%s:%d] Exiting CP Thread due to abnormal status in KWRAP VBI module\n", __F__, __L__);	
			break;
		}
#endif
		
		/* Step 2. 625/525 selector */
		ret = vbi_kwrap_checkvline625();
		if(ret < 0) {
			VBI_PRINT("[%s:%d] Exiting CP Thread due to abnormal status in KWRAP VBI module\n", __F__, __L__);	
			break;
		}
		
		/* Step 3. Sleep */
		OS_MsecSleep(100);
	}
	
	gIsVBIThreadCPAlive = FALSE;
	
	return 0;
}
