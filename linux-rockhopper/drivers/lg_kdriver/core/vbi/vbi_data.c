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
#include <linux/fcntl.h>	/**< O_ATTXMODE */
//#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <linux/vmalloc.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */
#include <base_types.h>
#include <linux/mm.h>		/** pgprot_noncached */

#include "vbi_module.h"
#include "vbi_hw.h"
#include "vbi_drv.h"
#include "vbi_data.h"
#include "vbi_cfg.h"
#include "vbi_kapi.h"

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

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
//int g_enable_vps_slicer = 0;	// no use
extern LX_VBI_INIT_MODE_T gVBIInitiateMode;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
volatile void *gVBI_data_mem_addr;
volatile void *gVBI_CC_CGMS_data_mem_addr;


unsigned int gVBIDataMemoryStart;
unsigned int gVBIDataMemorySize	;

unsigned int gVBIVpsMemoryStart;
unsigned int gVBIVpsMemorySize	;

unsigned int gVBIWssMemoryStart;
unsigned int gVBIWssMemorySize;

unsigned int gVBICgmsMemoryStart;
unsigned int gVBICgmsMemorySize;

unsigned int gVBIHeaderMemoryStart;

sBufInform *savedBufHeader = NULL;

sBufInform cc_buf;
/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static sBufInform *buf;

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 *
 * TTX_irq_handler irq handler
 *
 * @param	irq , device id , regs
 * @return	0 : OK , -1 : NOK
 *
*/


int VBI_TTX_InitDataMemory(void)
{
	int ret = RET_OK;

	gVBIDataMemoryStart	= 0;
	gVBIDataMemorySize	= (gstMemCfgVBI->buf_memory_size - 0x70);

	gVBICgmsMemoryStart = gVBIDataMemoryStart + gVBIDataMemorySize;
	gVBICgmsMemorySize	= 16;

	gVBIVpsMemoryStart	= gVBICgmsMemoryStart + gVBICgmsMemorySize;
	gVBIVpsMemorySize	= 16;

	gVBIWssMemoryStart	= gVBIVpsMemoryStart + gVBIVpsMemorySize;
	gVBIWssMemorySize	= 16;

	gVBIHeaderMemoryStart	= gVBIWssMemoryStart + gVBIWssMemorySize;

	VBI_PRINT("[VBI TTX]Attempting to get data address of [0x%08x] size [0x%08x] ...\n", gstMemCfgVBI->buf_memory_base , gstMemCfgVBI->buf_memory_size);

#if USE_VBI_DEVICE_DRIVER_MEMORY
	if(gstMemCfgVBI->buf_memory_size > 0)
		gVBI_data_mem_addr = (volatile unsigned long)vmap_phys(gstMemCfgVBI->buf_memory_base , gstMemCfgVBI->buf_memory_size);
#else
#ifdef USE_V4L2_VBI
	gVBI_data_mem_addr = (volatile unsigned long *)vmalloc(gstMemCfgVBI->buf_memory_size);
#else
	gVBI_data_mem_addr = (volatile unsigned long *)__vmalloc(gstMemCfgVBI->buf_memory_size, GFP_KERNEL | __GFP_HIGHMEM, pgprot_noncached(PAGE_KERNEL) );
#endif
#endif

	VBI_PRINT("[VBI TTX]vmap address of [0x%8p] ...\n", gVBI_data_mem_addr);

	// buffer header initialize
	buf = (sBufInform *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBIHeaderMemoryStart);
	buf->header = 0;
	buf->tailer = 0;
	buf->count = 0;
	buf->CGMS_offset = gVBICgmsMemoryStart;
	buf->VPS_offset = gVBIVpsMemoryStart;
	buf->WSS_offset = gVBIWssMemoryStart;
	buf->ttx_data_count = 0;

	gVBI_CC_CGMS_data_mem_addr = (void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBICgmsMemoryStart);

	VBI_PRINT("%s done CGMS offset [%x] VPS offset [%x] WSS offset [%x] \n", __func__ , buf->CGMS_offset, buf->VPS_offset , buf->WSS_offset);
	return ret;
}

int VBI_TTX_UninitDataMemory(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	// buffer header initialize
	buf->header = 0;
	buf->tailer = 0;
	buf->count = 0;
	buf->CGMS_offset =0;
	buf->VPS_offset = 0;
	buf->WSS_offset = 0;
	buf->status = 0;
	buf->ttx_data_count = 0;

#if USE_VBI_DEVICE_DRIVER_MEMORY
	vunmap_phys((void *)gVBI_data_mem_addr);
#else
	vfree((void *)gVBI_data_mem_addr);
#endif

	return ret;
}


int VBI_TTX_GetMemorySize(void)
{
	return gstMemCfgVBI->buf_memory_size;
}

int VBI_TTX_GetDataAddr(sHeaderData *data)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	switch(data->type)
	{
		// by wonsik.do TTX data is contained both in odd and even fileds.
		case 0x6:	// teletext
		case 0x7:	// teletext

			if((buf->tailer + TTX_DATA_SIZE) >= (gVBIDataMemorySize	- TTX_DATA_SIZE))
			{
				buf->tailer = 0;
			}
			else
			{
				buf->tailer += TTX_DATA_SIZE;
			}

			data->addr = (void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)buf->tailer);

			if(buf->tailer == buf->header) buf->status |= LX_TTX_TYPE_TTX; //(1<<0);

			buf->count++;

			/* 2014-05-09 : Won Hur
			 * Added TTX data counter for debug reference
			 * This would be initiated by the user */
			buf->ttx_data_count++;
		break;
		case 0x0a:
		case 0x0b:
			data->addr = 0;	//Do not proceed writing CGMS again... for memory protection
			break;

		// by wonsik.do WSS and VPS are contained only in odd filed.
		//case 0xc:	// VPS
		case 0xd:	// VPS
			data->addr = (void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBIVpsMemoryStart);
			buf->count++;
			buf->status |= LX_TTX_TYPE_VPS; //(1<<0);
		break;

		// by wonsik.do WSS and VPS are contained only in odd filed.
		//case 0x8:	// WSS
		case 0x9:	// WSS
			data->addr = (void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBIWssMemoryStart);
			buf->count++;
			buf->status |= LX_TTX_TYPE_WSS; //(1<<0);
		break;

		default:
			data->addr = 0;
			ret = RET_ERROR;
		break;

	}

	return ret;
}

int VBI_TTX_ClearTTXMemory(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	buf->header = 0;
	buf->tailer = 0;
	buf->count = 0;

	return ret;
}

int VBI_TTX_ClearVPSMemory(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

//	if(g_enable_vps_slicer == 1) return ret;	// no use

	memset((void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)buf->VPS_offset), 0 , gVBIVpsMemorySize);

	return ret;
}


int VBI_TTX_ClearWSSMemory(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	memset((void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)buf->WSS_offset), 0 , gVBIWssMemorySize);

	return ret;
}

int VBI_TTX_ClearAllMemory(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	VBI_TTX_ClearTTXMemory();
	VBI_TTX_ClearVPSMemory();
	VBI_TTX_ClearWSSMemory();

	return ret;
}



/* won.hur : Code for CC is as below : */
/* 이 함수에 대해서는 항상 size를 1로 사용할것.
 * 보다싶이 overflow에 대한 감지 기능이 없이 바로 쓰고 있음.
 * segmentation fault 발생 혹은 시스템 정지를 부를수 있음 */
int VBI_CC_PutVBIData(unsigned int *data , unsigned int size)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	/* 방어 코드 삽입 */
	if(size >= 2) VBI_WARN("VBI CC : Warning! VBI_CC_PutVBIData function cannot operate on mutliple data size over 1.\n");

	memcpy((void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)cc_buf.tailer) , (void *)data , size*4 );

	cc_buf.tailer += size*4;

	if(cc_buf.tailer >= gstMemCfgVBI->buf_memory_size - 0x100)
	{
		cc_buf.tailer = 0;
	}

	cc_buf.count++;

    return ret;
}

int VBI_PutCGMSData(sCGMS *data)
{
	int ret = RET_OK;

	if(gVBI_CC_CGMS_data_mem_addr == 0)
	{
		VBI_ERROR("Error! Memory for CGMS data is not allocated!\n");
#ifdef INCLUDE_KDRV_BE
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_VBI, VBI_SKEEPER_VBI_DATA_ERROR_STATUS, __L__);
#endif
		return RET_ERROR;
	}
	else
	{
		memcpy((void *)(gVBI_CC_CGMS_data_mem_addr), (void *)data, 10);
	//	VBI_PRINT("[VBI CGMS] put data : [0:0x%x][1:0x%x][2:0x%x][3:0x%x][4:0x%x][5:0x%02x][6:0x%x] \n", data->Preamble, data->Status, data->DataCount, data->LineCount, data->data0, data->data1, data->data2 );
	}
	return ret;
}

int VBI_CC_GetVBIData(LX_CC_DATA_T *cc_data , unsigned int size)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == 0) {
#ifdef INCLUDE_KDRV_BE
		(void)VIDEO_SKeeperUpdateIndex(LX_VP_ST_KEEPER_MODULE_VBI, VBI_SKEEPER_VBI_DATA_ERROR_STATUS, __L__);
#endif
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	if(cc_buf.header != cc_buf.tailer)
	{
		cc_data->data1 = *(unsigned int*)(gVBI_data_mem_addr + cc_buf.header) & 0xFF;
		cc_data->data2 = (*(unsigned int*)(gVBI_data_mem_addr + cc_buf.header) & 0xFF00) >> 8;
		cc_data->field = (*(unsigned int*)(gVBI_data_mem_addr + cc_buf.header) & 0x10000)>>16;
		cc_data->status = (*(unsigned int*)(gVBI_data_mem_addr + cc_buf.header) & 0xE0000)>>17;
		cc_data->line_number = (*(unsigned int*)(gVBI_data_mem_addr + cc_buf.header) & 0xFFC00000)>>22;
		//CC_PRINT("line number : [%d] , data : [0x%x]\n", cc_data->line_number, *(unsigned int*)(gVBI_data_mem_addr + cc_buf.header) );
		cc_buf.header += 4;
		if(cc_buf.header >= gstMemCfgVBI->buf_memory_size - 0x100)
		{
			cc_buf.header = 0;
		}

		if(cc_buf.count != 0)
			cc_buf.count--;
	}
	else
	{
		cc_data->data1 = 0;
		cc_data->data2 = 0;
		cc_data->field = 0;
		cc_data->status = 0;
		cc_data->line_number = 0;
	}

	return ret;
}

int VBI_CC_InitDataMemory(void)
{
	int ret = 0;
	// buffer header initialize
	cc_buf.header = 0;
	cc_buf.tailer = 0;
	cc_buf.count = 0;

	CC_PRINT("[VBI CC]Attempting to get data address of [0x%08x] size [0x%08x] ...\n", gstMemCfgVBI->buf_memory_base , gstMemCfgVBI->buf_memory_size);

//	gVBI_data_mem_addr = (volatile void *)vmap_phys(gstMemCfgVBI->buf_memory_base , gstMemCfgVBI->buf_memory_size);
#if USE_VBI_DEVICE_DRIVER_MEMORY
	if(gstMemCfgVBI->buf_memory_size > 0)
		gVBI_data_mem_addr = (volatile unsigned long)vmap_phys(gstMemCfgVBI->buf_memory_base , gstMemCfgVBI->buf_memory_size);

#else
#ifdef USE_V4L2_VBI
	gVBI_data_mem_addr = (volatile unsigned long *)vmalloc(gstMemCfgVBI->buf_memory_size);
#else
	gVBI_data_mem_addr = (volatile unsigned long *)__vmalloc(gstMemCfgVBI->buf_memory_size, GFP_KERNEL | __GFP_HIGHMEM, pgprot_noncached(PAGE_KERNEL) );
#endif
#endif

	/* TTX 드라이버와 DDR 메모리 구조 동일하게 가져오기 위한 코드 */
	gVBIDataMemoryStart	= 0;
	gVBIDataMemorySize	= (gstMemCfgVBI->buf_memory_size - 0x70);

	gVBICgmsMemoryStart = gVBIDataMemoryStart + gVBIDataMemorySize;
	gVBICgmsMemorySize	= 16;

	gVBIVpsMemoryStart	= gVBICgmsMemoryStart + gVBICgmsMemorySize;
	gVBIVpsMemorySize	= 16;

	gVBIWssMemoryStart	= gVBIVpsMemoryStart + gVBIVpsMemorySize;
	gVBIWssMemorySize	= 16;

	gVBIHeaderMemoryStart	= gVBIWssMemoryStart + gVBIWssMemorySize;

	// buffer header initialize
	buf = (sBufInform *)(gVBI_data_mem_addr + gVBIHeaderMemoryStart);
	buf->header = 0;
	buf->tailer = 0;
	buf->count = 0;
	buf->CGMS_offset = gVBICgmsMemoryStart;
	buf->VPS_offset = gVBIVpsMemoryStart;
	buf->WSS_offset = gVBIWssMemoryStart;
	/* 끝 */

	gVBI_CC_CGMS_data_mem_addr = (void *)((uintptr_t)gVBI_data_mem_addr + (uintptr_t)gVBICgmsMemoryStart);

	CC_PRINT("[%s:%d] done base addr [0x%x] size [0x%x] to [0x%p] \n", __F__ , __L__, gstMemCfgVBI->buf_memory_base , gstMemCfgVBI->buf_memory_size, gVBI_data_mem_addr);

	return ret;
}

int VBI_CC_UninitDataMemory(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	// buffer header initialize
	cc_buf.header = 0;
	cc_buf.tailer = 0;
	cc_buf.count = 0;

	buf->header = 0;
	buf->tailer = 0;
	buf->count = 0;
	buf->CGMS_offset =0;
	buf->VPS_offset = 0;
	buf->WSS_offset = 0;
	buf->status = 0;

	vunmap_phys((void *)gVBI_data_mem_addr);

	CC_PRINT("%s done\n", __func__);

	gVBI_data_mem_addr = 0;

	return ret;
}


int VBI_CC_GetVBIBufferInform(void)
{
	return ((int)cc_buf.count);
}

int VBI_CC_SetVBIBufferClear(void)
{
	int ret = RET_OK;

	if(gVBI_data_mem_addr == NULL) {
		VBI_ERROR("Error! Data memory was not initiated.\n");
		return RET_ERROR;
	}

	cc_buf.header = 0;
	cc_buf.tailer = 0;
	cc_buf.count = 0;

	return ret;
}

unsigned int VBI_CC_CheckDataParity(unsigned int data)
{
	int ret = RET_OK;
	unsigned char data0, data1;

	int i = 0;
	UINT8 parity_check0 = 0;
	UINT8 parity_check1 = 0;
	UINT8 Mask[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

	data0 = (unsigned char)((data & 0x0000FF00)>>8);
	data1 = (unsigned char)((data & 0x000000FF));

	parity_check0 = (data0 & Mask[i]);
	parity_check1 = (data1 & Mask[i]);

	for(i=1; i<8; i++)
	{
		parity_check0 ^= (data0 & Mask[i]) >> i;
		parity_check1 ^= (data1 & Mask[i]) >> i;
	}

	if((parity_check0 == 1)&&(parity_check1 == 1)) ret = 1;
	else ret = 0;

	return ret;
}

unsigned int VBI_TTX_GetVBIDataLineCount(unsigned int *data)
{
	unsigned int ret = RET_OK;
	unsigned int data_line_count_lsb = *(data);

	ret = (data_line_count_lsb&0x000003FF);

	return ret;
}

int VBI_Data_Suspend(void)
{
	int ret = RET_OK;

	VBI_INFO("[%s:%d] Checking initiated history : [%d]\n", __F__, __L__, gVBIInitiateMode);

	if((gVBIInitiateMode > LX_VBI_INIT_NONE) && (gVBIInitiateMode < LX_VBI_INIT_MAXNUM)){
		if(savedBufHeader == NULL){
			savedBufHeader = (sBufInform *)kmalloc(sizeof(sBufInform), GFP_KERNEL);
		}

		memcpy((void *)savedBufHeader, (void *)buf, sizeof(sBufInform));

		VBI_INFO("[%s:%d] Done copying buffer header information to heap memory. \n",__F__, __L__ );
	}
	else{
		VBI_INFO("[%s:%d] Skipping VBI DATA suspend operation due to unknown initiate history\n",__F__, __L__ );
	}

	return ret;
}

int VBI_Data_Resume(void)
{
	int ret = RET_OK;

	VBI_INFO("[%s:%d] Checking initiated history : [%d]\n", __F__, __L__, gVBIInitiateMode);

	if((gVBIInitiateMode > LX_VBI_INIT_NONE) && (gVBIInitiateMode < LX_VBI_INIT_MAXNUM)){
		if(savedBufHeader != NULL){
			memcpy((void *)buf, (void *)savedBufHeader, sizeof(sBufInform));
			kfree(savedBufHeader);
			savedBufHeader = NULL;

			VBI_INFO("[%s:%d] Done restoring buffer header information to DDR memory. \n",__F__, __L__ );
		}
		else{
			VBI_ERROR("[%s:%d] Cannot find saved-buffer-header data! VBI will not work properly. Addr[0x%8p]\n",__F__, __L__, savedBufHeader);
			ret = RET_ERROR;
		}
	}
	else{
		VBI_INFO("[%s:%d] Skipping VBI Data resume operation due to unknown initiate history\n",__F__, __L__ );
	}

	return ret;
}

void *VBI_get_buffer_ptr(void)
{
	return (void *)gVBI_data_mem_addr;
}

unsigned int VBI_get_buffer_size(void)
{
	return gstMemCfgVBI->buf_memory_size;
}
LX_TTX_PARAMETER_T *VBI_get_ttx_parameter_ptr(void)
{
	return (LX_TTX_PARAMETER_T *)buf;
}
/** @} */
