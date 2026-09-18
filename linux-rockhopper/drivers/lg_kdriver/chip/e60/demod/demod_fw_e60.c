/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013-2019 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/*  @file
 *
 *	demod api warpper
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-06-13
 *	@note
 */

#define DEMOD_TAG "[CHIP.FW] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include <DBB_DEMOD_L2_Common_API.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/kernel.h>	/**< printk() */
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/errno.h>

#include "sys_regs.h"
#include "hma_alloc.h"
#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"
#include "demod_util.h"

#include "demod_common_e60.h"
#include "demod_dvb_e60.h"

#include "demod_fw_e60.h"
#include "demod_util_e60.h"
#include "demod_api_e60.h"
#include "demod_ipc_e60.h"

#include <E60_DEMOD_ALL_FW_A_1_1_DDR.h>
#define DEMOD_DDR_FW 	E60_DEMOD_ALL_FW_A_1_1
#define DEMOD_FW_NAME 	"E60_DEMOD_FW_A_1_1"

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern LX_DEMOD_L2_Context * DEMOD_GetContext (void);
#define DEMOD_E60_GetContext DEMOD_GetContext


#else
#error not support platform
#endif

/* macro definition */
#define DEMOD_CHIP_INFO	0x60a0

#if defined(DEMOD_CONFIG_EXT)
#define DEMOD_CHIP_IF	LX_DEMOD_L0_IF_EXT
#else
#define DEMOD_CHIP_IF	LX_DEMOD_L0_IF_SOC
#endif

#define FW_MAKER_MAGIC	"DEMOD_FW"

#define STR_VALUE(s)    #s
#define STR_VALUE_OF(s) STR_VALUE(s)

#define MCU_RESET		1
#define MCU_RELEASE		0
#define REG_SET			1
#define REG_CLEAR		0

#define DEMOD_DDR_FW E60_DEMOD_ALL_FW_A_1_1
#define DEMOD_FW_NAME "E60_DEMOD_FW_A_1_1"

typedef enum _fw_maker_type {
	DEMOD_FW_INVALID = -1,
	DEMOD_FW_NEW = 0,
	DEMOD_FW_LG_108_X = 1,
	DEMOD_FW_LG_108_V = 2,
} fw_maker_t;

typedef struct _fw_maker_header {
	unsigned char magic[8];		// "DEMOD FW"
	unsigned char fw_date[4];	// 20190722
	unsigned char fw_ver[4];	// 20A00011
	unsigned char fw_author[10];	// samin.ryu
	unsigned char fw_datetime[6];	//19 07 22 16 07 00
} fw_maker_h;

static unsigned char fw_start_lg_108_x[] = {0x06, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,};
static unsigned char fw_start_lg_108_v[] = {0x00, 0xc5, 0x49, 0x10, 0xd5, 0x49, 0x20, 0xe5, 0x49,};

static int _DEMOD_E60_FW_Check(UINT8 * fwd) {
	fw_maker_h * fwh = (fw_maker_h *)fwd;
	int ret;

	ret = memcmp(fwd, FW_MAKER_MAGIC, 8);
	if (0 == ret) {
		fwd += sizeof(fw_maker_h);

		DEMOD_NOTI("fw info date %02X%02X%02X%02X, ver %02X%02X%02X%02X, %02X/%02X/%02X %02X:%02X:%02X, %s\n",
					fwh->fw_date[0], fwh->fw_date[1], fwh->fw_date[2], fwh->fw_date[3],
					fwh->fw_ver[0], fwh->fw_ver[1], fwh->fw_ver[2], fwh->fw_ver[3],
					fwh->fw_datetime[0], fwh->fw_datetime[1], fwh->fw_datetime[2], fwh->fw_datetime[3], fwh->fw_datetime[4], fwh->fw_datetime[5],
					DEMOD_BYTE_TO_HEXSTR((char *)fwh->fw_author, 10));

		if (0 == memcmp(fwd, fw_start_lg_108_x, sizeof(fw_start_lg_108_x))) {
			ret = DEMOD_FW_LG_108_X;
			DEMOD_INFO("fw built with lg_108_x\n");
		}

		if (0 == memcmp(fwd, fw_start_lg_108_v, sizeof(fw_start_lg_108_v))) {
			DEMOD_INFO("fw built with lg_108_v\n");
			ret = DEMOD_FW_LG_108_V;
		}

		if (ret == 0)
			return DEMOD_FW_INVALID;

		return DEMOD_FW_NEW;
	}

	ret = memcmp(fwd, fw_start_lg_108_x, sizeof(fw_start_lg_108_x));
	if (0 == ret) {
		DEMOD_INFO("old fw built with lg_108_x\n");
		return DEMOD_FW_LG_108_X;
	}

	ret = memcmp(fwd, fw_start_lg_108_v, sizeof(fw_start_lg_108_v));
	if (0 == ret) {
		DEMOD_INFO("old fw built with lg_108_v\n");
		return DEMOD_FW_LG_108_V;
	}

	DEMOD_ERROR("ret %d, invalid fw %s\n", ret, DEMOD_BYTE_TO_HEXSTR((char *)fwd, 8));
	return DEMOD_FW_INVALID;
}

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
/*
 * ref from int te_read_file_from_path(const char *path, void **buf, size_t max_size) @core/te/te_util.c
 */
static int _DEMOD_E60_FW_Read_FilePath(const char *path, void *buf, size_t max_size)
{
	int ret;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	loff_t size;
	ret = kernel_read_file_from_path(path, &buf, &size, max_size, READING_FIRMWARE_PREALLOC_BUFFER);
	if (ret >= 0)
		return size;
	else
		return ret;
#else
	struct file *f;
	loff_t i_size, pos;
	char *data = (char *)buf;
	/*
	 * Refer to fw_get_filesystem_firmware in drivers/base/firmware_class.c
	 * and use kernel_read_file_from_path from kernel 4.6
	 */
	f = filp_open(path, O_RDONLY, 0);
	if (IS_ERR(f)) {
		return PTR_ERR(f);
	}

	i_size = i_size_read(file_inode(f));
	if (i_size <= 0) {
		DEMOD_ERROR("Can't get file size(%lld)\n", i_size);
		ret = -EINVAL;
		goto err_size;
	}

	if (max_size > 0 && i_size > max_size) {
		DEMOD_ERROR("Filesize(%lld) over max_size(%zu)\n",
				i_size, max_size);
		ret = -EFBIG;
		goto err_size;
	}

	pos = 0;
	while (pos < i_size) {
		ret = kernel_read(f, pos, data + pos, i_size - pos);
		DEMOD_NOTI("pos %lld, i_size %lld, ret %d\n", pos, i_size, ret);
		if (ret < 0)
			goto err_read;

		if (ret == 0)
			break;

		pos += ret;
	}

	if (pos != i_size) {
		DEMOD_ERROR("pos %lld != i_size %lld\n", pos, i_size);
		ret = -EIO;
		goto err_read;
	}
	data[i_size] = 0;   /* add NULL ternmination for string parsing */

	fput(f);

	return pos;

err_read:
err_size:
	fput(f);

	return ret;
#endif
}

static int _DEMOD_E60_FW_Load(UINT8 * fw, int * fwlen) {
	const char * name = "/var/demod_fw.bin";
	int size;

	size = _DEMOD_E60_FW_Read_FilePath(name, fw, *fwlen);

	if (size <= 0) {
		DEMOD_PRINT("%s is not exist, %d\n", name, size);
		return size;
	}

	DEMOD_NOTI("read %s (%d bytes)\n", name, size);

	*fwlen = size;

	return NO_DEMOD_ERROR;
}

static void _DEMOD_E60_MCU_Reset (BOOL flag) {

	DEMOD_PRINT("%s", __FUNCTION__);

	if(flag) { // MCU reset
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, emmcsyn_03);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_03, reg_dbb__mcu_reset, 0);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, emmcsyn_03);
		DEMOD_PRINT("MCU reset\n");
	} else { // MCU reset release
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, emmcsyn_03);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_03, reg_dbb__mcu_reset, 1);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, emmcsyn_03);
		DEMOD_PRINT("MCU release\n");
	}
}

static void _DEMOD_E60_REG_Init (BOOL flag) {

	DEMOD_PRINT("%s", __FUNCTION__);

	if(flag) { // REG Init
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, emmcsyn_03);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_03, reg_dbb__dbbreg_init, 1);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, emmcsyn_03);
		DEMOD_PRINT("REG Init\n");
	} else	{ // REG Init	release
		CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, emmcsyn_03);
		CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, emmcsyn_03, reg_dbb__dbbreg_init, 0);
		CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, emmcsyn_03);
		DEMOD_PRINT("REG release\n");
	}
}
#else
LX_DEMOD_FIRMWARE_STRUCT E60_DEMOD_FW_USER = {0, 0, {0,}};

static int _DEMOD_E60_FW_Load(UINT8 * fw, unsigned int * fwlen) {
	*fwlen = E60_DEMOD_FW_USER.firmware_size;
	memcpy(fw, E60_DEMOD_FW_USER.firmware_table, E60_DEMOD_FW_USER.firmware_size);
	return 0;
}

static void _DEMOD_E60_MCU_Reset (BOOL flag) {
}

static void _DEMOD_E60_REG_Init (BOOL flag) {
}

#endif

//#define DEMOD_SPEND_TIME_CHECK
#if defined(DEMOD_SPEND_TIME_CHECK)
#define SPEND_TIME_START() \
	start_clock = DEMOD_L0_SystemClock();

#define SPEND_TIME_CHECK(desc) { \
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us); \
	DEMOD_INFO("TC: %s, spend %3u.%03ums\n", desc, spend_ms, spend_us); \
	start_clock = DEMOD_L0_SystemClock(); \
}
#define SPEND_TIME_CHECK_MSG(desc) { \
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us); \
	DEMOD_NOTI("TC: %s, spend %3u.%03ums\n", desc, spend_ms, spend_us); \
	start_clock = DEMOD_L0_SystemClock(); \
}

#else
#define SPEND_TIME_START()
#define SPEND_TIME_CHECK(desc)
#define SPEND_TIME_CHECK_MSG(desc) { \
	DEMOD_NOTI("%s done\n", desc); \
}

#endif

static int _DEMOD_E60_ResetFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int ret = NO_DEMOD_ERROR;

	// have to clear fw type, fw ver before send SYSTEM_INIT to mcu
	DEMOD_L1_API_FinishFirmware(pFrontend->demod);

	ret = DEMOD_L1_IPC_Send_Sync(pFrontend->demod, CMD_TYPE_SYSTEM_INIT, 0, NULL, 0);

	if (ret != NO_DEMOD_ERROR) {
		DEMOD_NOTI("send SYSTEM_INIT fail, ret %d\n", ret);
		pFrontend->demod->fw_state = DEMOD_FW_STATE_FAULT;
		return ret;
	}

	DEMOD_L0_system_wait(10);

	return NO_DEMOD_ERROR;
}

static int _DEMOD_E60_StopFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int ret = NO_DEMOD_ERROR;

	ret = DEMOD_L1_API_FinishFirmware(pFrontend->demod);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_API_FinishFirmware with ret %d\n", ret);
		return ret;
	}

	//if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV)
	{
		/* MCU stall */
		ret = DEMOD_L1_API_StopFirmware(pFrontend->demod);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("DEMOD_L1_API_FinishFirmware with ret %d\n", ret);
			return ret;
		}

		DEMOD_L0_system_wait(1);
	//} else {
	//	DEMOD_NOTI("skip DEMOD_L1_API_StopFirmware\n");
	}

	return ret;
}

static int _DEMOD_E60_InitFirmware (LX_DEMOD_L2_Context * pFrontend, UINT32 fw_clk, UINT32 adc_clk) {
	int ret = NO_DEMOD_ERROR;
#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64	start_clock;
	UINT64	spend_clock;
	UINT32	spend_us;
	UINT32	spend_ms;
#endif
	SPEND_TIME_START();

	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		_DEMOD_E60_MCU_Reset(MCU_RESET);
		SPEND_TIME_CHECK("MCU_RESET");

		DEMOD_L0_system_wait(1);
		SPEND_TIME_CHECK("wait(1)");

		/* MCU FW control register init */
		ret = DEMOD_L1_API_InitFirmware_DDR(pFrontend->demod, fw_clk, adc_clk);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("DEMOD_L1_API_InitFirmware_DDR with ret %d\n", ret);
			return ret;
		}
		SPEND_TIME_CHECK("InitFirmware_DDR");

		_DEMOD_E60_MCU_Reset(MCU_RELEASE);
		SPEND_TIME_CHECK("MCU_RELEASE");

		DEMOD_L0_system_wait(1);
		SPEND_TIME_CHECK("wait(1)");

		_DEMOD_E60_REG_Init(REG_SET);
		SPEND_TIME_CHECK("REG_SET");

		DEMOD_L0_system_wait(1);
		SPEND_TIME_CHECK("wait(1)");

		_DEMOD_E60_REG_Init(REG_CLEAR);
		SPEND_TIME_CHECK("REG_CLEAR");
	} else {
		/* MCU FW control register init */
		ret = DEMOD_L1_API_InitFirmware(pFrontend->demod, fw_clk, adc_clk);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("DEMOD_L1_API_InitFirmware with ret %d\n", ret);
			return ret;
		}
		SPEND_TIME_CHECK("InitFirmware");
	}

	return NO_DEMOD_ERROR;
}

static LX_DEMOD_FW_STRUCT _firmware_file = {0, 0,};

static int _DEMOD_E60_CheckFirmware (LX_DEMOD_L2_Context * pFrontend, LX_DEMOD_FW_STRUCT * fw_table) {
	UINT32 *		fw_addr = NULL;
	int				ret = RET_OK;

	UINT8 *	 		data;
	UINT32			size;

	UINT8 *			ddr_data;

	if (0 != _firmware_file.firmware_size) {
		data = _firmware_file.firmware_table;;
		size = _firmware_file.firmware_size;

		DEMOD_NOTI("using firmware file, size %d\n", size);
	} else {
		data = fw_table->firmware_table;
		size = fw_table->firmware_size;

		DEMOD_NOTI("using firmware header, size %d\n", size);
	}

	ret = _DEMOD_E60_FW_Check(data);
	if (DEMOD_FW_INVALID == ret ) {
		DEMOD_INFO("FW_Check error %d\n", ret);
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	} else if (DEMOD_FW_LG_108_X == ret || DEMOD_FW_LG_108_V == ret) {
		/* nop */
	} else if (DEMOD_FW_NEW == ret) {
		data = data + sizeof(fw_maker_h);
	}

	DEMOD_DEBUG("fw copy from ddr\n");

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	if(NULL != data) {
		ddr_data = vmalloc((size + 3) & ~0x3);
		if (!ddr_data) {
			ret = -ERROR_DEMOD_PTRNULL;
			DEMOD_ERROR("vmalloc failed size %d (%d)\n", size, (size + 3) & ~0x3);
			return ret;
		}

		if(size > gMemCfgDEMOD_FW.memory_size) {
			DEMOD_ERROR("f/w size(%d) over mem size(%d)\n", size, gMemCfgDEMOD_FW.memory_size);
			return RET_ERROR;
		}

		fw_addr = (UINT32 *)vmap_phys(gMemCfgDEMOD_FW.memory_base, size);
		if(!fw_addr) {
			DEMOD_ERROR("vmap_phys fail!!!\n");
			return RET_ERROR;
		}

		memcpy(ddr_data, fw_addr, size);
		rmb(); // use wmb before mcu is awoken

		vunmap_phys(fw_addr);
	} else {
		DEMOD_ERROR("f/w table is null\n");
		return RET_ERROR;
	}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	int	tryCount = 0;
	ddr_data = (UINT8 *)malloc((size + 3) & ~0x3);

	if (!ddr_data) {
		ret = -ERROR_DEMOD_PTRNULL;
		DEMOD_ERROR("malloc failed size %d (%d)\n", size, (size + 3) & ~0x3);
		return ret;
	}

	for(tryCount = 0; tryCount < 5; tryCount++)
	{
		UINT32 down_addr = 0;
		UINT32 base_addr = 0;
		int left_count = size;
		int done_count = 0;

		DEMOD_INFO("fw copy from DDR, try #%d\n", tryCount);

		pFrontend->demod->chip->fw_done = 0;
		pFrontend->demod->chip->i2c_indirect = 0;

		down_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_FW_DL_ADDR, 4, &down_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		down_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_FW_DL_BASE, 4, &down_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		/* set I2C base addr for ddr access */
		base_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_I2C_HBASE, 4, &base_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		down_addr = (UINT16)down_addr;
		while (left_count > 0) {
			pFrontend->demod->chip->i2c_indirect = 3;

			if(left_count >= 0x80)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(pFrontend->demod->chip, (UINT16)down_addr, 0x80, ddr_data + done_count)) {
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}

				done_count += 0x80;
				left_count -= 0x80;
			} else {
				if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes(pFrontend->demod->chip, (UINT16)down_addr, left_count, ddr_data + done_count)) {
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}

				done_count += left_count;
				left_count = 0;
			}

			down_addr += 0x80;

			if(down_addr >= 0x10000)
			{
				down_addr -= 0x10000;
				base_addr += 0x10000;
				pFrontend->demod->chip->i2c_indirect = 0;

				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_I2C_HBASE, 4, &base_addr)){
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}
			}
		}
		if (NO_DEMOD_ERROR != ret) {
			continue;
		}

		pFrontend->demod->chip->i2c_indirect = 0;
		base_addr = 0xF0040000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_I2C_HBASE, 4, &base_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		DEMOD_INFO("LGDBB Success!! => Count(%d)\n", tryCount);
		//pFrontend->demod->chip->fw_done = 1;
		break;
	}

	if(ret != NO_DEMOD_ERROR && tryCount == 5)
	{
		DEMOD_ERROR("LGDBB Fail!! => Count(%d)\n", tryCount);
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	}
#endif

	ret = memcmp(data, ddr_data, size);
	DEMOD_INFO("ddr fw check : %d (size %d)\n", ret, size);

	return ret;
}

#if (DEMOD_COMM == DEMOD_COMM_APB)
static int _DEMOD_E60_LoadFirmware_SOC (LX_DEMOD_L2_Context * pFrontend, UINT8 * data, UINT32 size) {
	UINT32 *		fw_addr = NULL;

	DEMOD_INFO("ddr phy base 0x%08x, size %8x, %u\n", gMemCfgDEMOD_FW.memory_base, gMemCfgDEMOD_FW.memory_size, gMemCfgDEMOD_FW.memory_size);

	if(NULL != data) {
		DEMOD_DEBUG("copy to ddr phase #1\n");
		if(size > gMemCfgDEMOD_FW.memory_size) {
			DEMOD_ERROR("f/w size(%d) over mem size(%d)\n", size, gMemCfgDEMOD_FW.memory_size);
			return RET_ERROR;
		}

		fw_addr = (UINT32 *)vmap_phys(gMemCfgDEMOD_FW.memory_base, size);
		DEMOD_DEBUG("copy to ddr phase #2, fw_addr %p\n", fw_addr);
		if(!fw_addr) {
			DEMOD_ERROR("vmap_phys fail!!!\n");
			return RET_ERROR;
		}

		DEMOD_DEBUG("copy to ddr phase #3\n");
		memcpy(fw_addr, data, size);
		wmb(); // use wmb before mcu is awoken
		DEMOD_DEBUG("copy to ddr phase #4\n");

		//mem_base_addr = gMemCfgDEMOD_FW.memory_base;
		vunmap_phys(fw_addr);
	} else {
		DEMOD_ERROR("f/w table is null\n");
		return RET_ERROR;
	}

	return RET_OK;
}
#endif

#if (DEMOD_COMM == DEMOD_COMM_I2C) || (DEMOD_COMM == DEMOD_COMM_FPGA)
static int _DEMOD_E60_LoadFirmware_EXT (LX_DEMOD_L2_Context * pFrontend, UINT8 * data, UINT32 size) {
	int	ret = RET_OK;
	int	tryCount = 0;
	
	for(tryCount = 0; tryCount < 5; tryCount++)
	{
		UINT32 down_addr = 0;
		UINT32 base_addr = 0;
		int left_count = size;
		int done_count = 0;

		DEMOD_INFO("fw download to DDR, try #%d\n", tryCount);

		pFrontend->demod->chip->fw_done = 0;
		pFrontend->demod->chip->i2c_indirect = 0;

		down_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_FW_DL_ADDR, 4, &down_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		down_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_FW_DL_BASE, 4, &down_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		/* set I2C base addr for ddr access */
		base_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_I2C_HBASE, 4, &base_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		down_addr = (UINT16)down_addr;
		while (left_count > 0) {
			pFrontend->demod->chip->i2c_indirect = 3;

			if(left_count >= 0x80)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, (UINT16)down_addr, 0x80, data + done_count)) {
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}

				done_count += 0x80;
				left_count -= 0x80;
			} else {
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, (UINT16)down_addr, left_count, data + done_count)) {
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}

				done_count += left_count;
				left_count = 0;
			}

			down_addr += 0x80;

			if(down_addr >= 0x10000)
			{
				down_addr -= 0x10000;
				base_addr += 0x10000;
				pFrontend->demod->chip->i2c_indirect = 0;

				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_I2C_HBASE, 4, &base_addr)){
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}
			}
		}
		if (NO_DEMOD_ERROR != ret) {
			continue;
		}

		pFrontend->demod->chip->i2c_indirect = 0;
		base_addr = 0xF0040000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_I2C_HBASE, 4, &base_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		DEMOD_INFO("LGDBB Success!! => Count(%d)\n", tryCount);
		//pFrontend->demod->chip->fw_done = 1;
		break;
	}

	if(ret != NO_DEMOD_ERROR && tryCount == 5)
	{
		DEMOD_ERROR("LGDBB Fail!! => Count(%d)\n", tryCount);
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	}

	return NO_DEMOD_ERROR;
}
#endif

static int _DEMOD_E60_LoadFirmware (LX_DEMOD_L2_Context * pFrontend, LX_DEMOD_FW_STRUCT * fw_table) {
	UINT32			mem_base_addr;
	int				ret = RET_OK;

	UINT8 *	 		data;
	UINT32			size;

#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64			start_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
	UINT64			spend_clock;
#endif
	SPEND_TIME_START();

	_DEMOD_E60_FW_Load(&_firmware_file.firmware_table[0], &_firmware_file.firmware_size);

	if (0 != _firmware_file.firmware_size) {
		data = _firmware_file.firmware_table;;
		size = _firmware_file.firmware_size;

		DEMOD_NOTI("using firmware file, size %d\n", size);
	} else {
		data = fw_table->firmware_table;
		size = fw_table->firmware_size;

		DEMOD_NOTI("using firmware header, size %d\n", size);
	}

	ret = _DEMOD_E60_FW_Check(data);
	if (DEMOD_FW_INVALID == ret) {
		DEMOD_INFO("FW_Check error %d\n", ret);
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	} else if (DEMOD_FW_LG_108_X == ret || DEMOD_FW_LG_108_V == ret) {
		/* nop */
	} else if (DEMOD_FW_NEW == ret) {
		data = data + sizeof(fw_maker_h);
	}

	DEMOD_DEBUG("copy to ddr start with data %p, size %u\n", data, size);
	SPEND_TIME_CHECK("FW load to mem & Check");

#if (DEMOD_COMM == DEMOD_COMM_APB)
	ret = _DEMOD_E60_LoadFirmware_SOC(pFrontend, data, size);
	mem_base_addr = gMemCfgDEMOD_FW.memory_base;
#elif (DEMOD_COMM == DEMOD_COMM_I2C) || (DEMOD_COMM == DEMOD_COMM_FPGA)
	ret = _DEMOD_E60_LoadFirmware_EXT(pFrontend, data, size);
	mem_base_addr = 0x50000000;
#else
	ret = RET_ERROR;
	mem_base_addr = 0x0;
#endif
	if (RET_ERROR == ret) {
		DEMOD_ERROR("LoadFirmware failed\n");
		return ret;
	}
	DEMOD_INFO("copy to ddr finish with mem_base_addr 0x%08x\n", mem_base_addr);
	SPEND_TIME_CHECK("FW load to DDR from mem");
		
	ret = DEMOD_L2_Set_MemAddr(pFrontend, mem_base_addr);
	if(NO_DEMOD_ERROR != ret) {
		DEMOD_ERROR("DEMOD_L2_Set_MemAddr failed\n");
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	}

	return NO_DEMOD_ERROR;
}

static int _DEMOD_E60_StartFirmware (LX_DEMOD_L2_Context * pFrontend)
{
	int  			tryCount = 0;
	int  			ret = 0;

#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64			start_clock;
	UINT64			spend_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
#endif
	SPEND_TIME_START();

	tryCount = 10;
	do {
		ret = DEMOD_L1_API_StartFirmware(pFrontend->demod);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("[DEMOD_API] FAIL, DEMOD_L1_API_StartFirmware() 0x%02x: %s\n",
				ret, DEMOD_L1_API_Error_Text(ret));
			DEMOD_L0_system_wait(3);
			continue;
		}
	} while ((tryCount-- > 0) && (ret != NO_DEMOD_ERROR));

	if(ret != NO_DEMOD_ERROR) 	{
		DEMOD_ERROR("failed f/w downloading with ret %d, tryCount %d\n", ret, tryCount);
		return ret;
	}

	DEMOD_NOTI("FW %s, loading done\n", DEMOD_FW_NAME);
	SPEND_TIME_CHECK("StartFirmware");

	wmb();rmb();
	SPEND_TIME_CHECK("wmb/rmb");

	DEMOD_L0_system_wait(10);
	SPEND_TIME_CHECK("wait(10)");

	tryCount = 1000;
	while ((tryCount-- > 0) && ((ret = DEMOD_L1_API_IsReady(pFrontend->demod)) != NO_DEMOD_ERROR)) {
		DEMOD_L0_system_wait(1);
	}
	SPEND_TIME_CHECK("IsReady");

	DEMOD_L1_IPC_Reset(pFrontend->demod);
	SPEND_TIME_CHECK("IPC_Reset");
	
	DEMOD_NOTI("FW ver 0x%08x, date 0x%08x\n", pFrontend->demod->fw_ver, pFrontend->demod->fw_date);
	if(ret != NO_DEMOD_ERROR) 	{
		DEMOD_ERROR("failed f/w start with ret %d, tryCount %d\n", ret, tryCount);
		return ret;
	}

	return NO_DEMOD_ERROR;
}

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/kthread.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

static struct task_struct * _fw_reset_thread = NULL;
wait_queue_head_t			_fw_reset_wait;

static int _DEMOD_E60_FW_Reset_Task(void * data);
#endif

static int _DEMOD_E60_FW_Initialize(demod_fw_type fw_type) {
	LX_DEMOD_L2_Context *	pFrontend = DEMOD_E60_GetContext();
	LX_DEMOD_FW_STRUCT * 	fw_table = NULL;

	UINT32			fw_clk;
	UINT32			adc_clk;
//	UINT32			error_flag = 0;

	int 			ret = NO_DEMOD_ERROR;

	UINT64 			begin_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
	UINT64			spend_clock;
#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64 			start_clock;
#endif
	begin_clock = DEMOD_L0_SystemClock();

	SPEND_TIME_START();

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	init_waitqueue_head(&_fw_reset_wait);

	if (NULL == _fw_reset_thread) {
		_fw_reset_thread = kthread_run(_DEMOD_E60_FW_Reset_Task, (void *)pFrontend, "demod_fw_reset_handler");
	}
#endif


	if ((pFrontend->demod->fw_state == DEMOD_FW_STATE_RESET) || (pFrontend->demod->fw_state == DEMOD_FW_STATE_INIT)) {
		DEMOD_NOTI("skip DEMOD_LockDevice(), already locked\n");
	} else {
		/* first firmware loading after boot */
		DEMOD_LockDevice();
	}
	SPEND_TIME_CHECK("DEMOD_LockDevice");

	if (fw_type == DEMOD_FW_TYPE_TER) {
		fw_clk = DEMOD_CLOCK_96MHZ;		// 1X 12MHZ, 8X 96MHZ
		adc_clk = DEMOD_CLOCK_24MHZ;
	}
	else if (fw_type == DEMOD_FW_TYPE_SAT) {
		fw_clk = DEMOD_CLOCK_124MHZ;		// 1X 15.5MHZ, 8X 124MHZ
		adc_clk = DEMOD_CLOCK_124MHZ;
	}
	else {
		DEMOD_ERROR("fw_type invalid %d\n", fw_type);
		return ERROR_DEMOD_FW_INIT;
	}

	fw_table = (LX_DEMOD_FW_STRUCT *)DEMOD_DDR_FW;

	DEMOD_INFO("try fw init with %u, %u, %u\n", pFrontend->demod->chip->fw_type, fw_type, fw_clk);

	/* When first init after boot, set chip information */
	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		DEMOD_INFO("set chip info 0x%04X\n", DEMOD_CHIP_INFO);
		DEMOD_L2_Set_ChipInfo(pFrontend, DEMOD_CHIP_INFO, DEMOD_CHIP_IF);
	}
	SPEND_TIME_CHECK("Set_ChipInfo");

	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		if ((pFrontend->demod->fw_state == DEMOD_FW_STATE_RESET)) {
			DEMOD_NOTI("skip device lock, already locked\n");
		} else {
			if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip)) {
				ret = ERROR_DEMOD_LOADING_FIRMWARE;
				goto return_with_device_unlock;
			}
			DEMOD_NOTI("fw init - device locked\n");
		}

//		ResetFirmware not need at 1st firmware loading.
//		if (NO_DEMOD_ERROR != _DEMOD_E60_ResetFirmware(pFrontend))
//			return ERROR_DEMOD_LOADING_FIRMWARE;
//		SPEND_TIME_CHECK("ResetFirmware");

		if (NO_DEMOD_ERROR != _DEMOD_E60_StopFirmware(pFrontend)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("StopFirmare");

		DEMOD_L1_IPC_Enable(pFrontend->demod, FALSE);
		SPEND_TIME_CHECK("IPC Disable");

		if (NO_DEMOD_ERROR != _DEMOD_E60_InitFirmware(pFrontend, fw_clk, adc_clk)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}

		SPEND_TIME_CHECK("InitFirmware");

		if (pFrontend->demod->chip->fw_skip == 0) {
			if (NO_DEMOD_ERROR != _DEMOD_E60_LoadFirmware(pFrontend, fw_table)) {
				ret = ERROR_DEMOD_LOADING_FIRMWARE;
				goto return_with_api_unlock;
			}
		}
		SPEND_TIME_CHECK("LoadFirmware");

/*
		//ret = _DEMOD_E60_CheckFirmware(pFrontend, (LX_DEMOD_FW_STRUCT *)E60_DEMOD_ALL_FW_A_1_1);
		ret = _DEMOD_E60_CheckFirmware(pFrontend, fw_table);
		if (ret == NO_DEMOD_ERROR) {
			DEMOD_ERROR("fw check ok\n");
		} else {
			DEMOD_ERROR("fw check error with %d\n", ret);
		}
		SPEND_TIME_CHECK("CheckFirmware");
*/

		pFrontend->demod->chip->fw_type = fw_type;

	} else {
		DEMOD_NOTI("fw re-init for type change, fw_state %d\n", pFrontend->demod->fw_state);

		if (NO_DEMOD_ERROR != DEMOD_L1_SET_DD_SoftRst(pFrontend->demod, 1, 0, 0, 0, 0, 0, 0)) {
			rmb();
			DEMOD_NOTI("faild SoftRst, fw_state %d\n", pFrontend->demod->fw_state);
			if (pFrontend->demod->fw_state > DEMOD_FW_STATE_RUN) {
				DEMOD_NOTI("faild SoftRst, fw re-init skip cause by fw_state %d\n", pFrontend->demod->fw_state);
				DEMOD_UnlockDevice();

				spend_clock = DEMOD_L0_SystemClock();
				while (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN) {
					DEMOD_L0_CalcSpendClock(spend_clock, &spend_ms, &spend_us);
					if (spend_ms > 10000) {
						break;
					}
					DEMOD_L0_system_wait(1);
				}
				DEMOD_NOTI("wait for reset process done, took %u.%03u, state %d\n", spend_ms, spend_us, pFrontend->demod->fw_state);

				if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN)
					ret = ERROR_DEMOD_FW_NOT_READY;
				else
					ret = NO_DEMOD_ERROR;
				return ret;
			}
			DEMOD_NOTI("faild SoftRst, retry forced fw init, fw_state %d\n", pFrontend->demod->fw_state);
			pFrontend->demod->chip->fw_type = DEMOD_FW_TYPE_INV;
			pFrontend->demod->fw_state = DEMOD_FW_STATE_INIT;
			wmb();
			return _DEMOD_E60_FW_Initialize(fw_type);
			//goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK_MSG("SoftRst");

		if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip))
			return ERROR_DEMOD_LOADING_FIRMWARE;
		SPEND_TIME_CHECK("LockDevice");

		DEMOD_L0_system_wait(10);
		SPEND_TIME_CHECK("wait(10)");

		if (NO_DEMOD_ERROR != _DEMOD_E60_ResetFirmware(pFrontend)) {
			rmb();
			DEMOD_NOTI("faild ResetFirmware, retry forced fw init\n");
			if (pFrontend->demod->fw_state > DEMOD_FW_STATE_RUN) {
				DEMOD_NOTI("faild ResetFirmware, fw re-init skip cause by fw_state %d\n", pFrontend->demod->fw_state);
				DEMOD_UnlockDevice();

				spend_clock = DEMOD_L0_SystemClock();
				while (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN) {
					DEMOD_L0_CalcSpendClock(spend_clock, &spend_ms, &spend_us);
					if (spend_ms > 10000) {
						break;
					}
					DEMOD_L0_system_wait(1);
				}
				DEMOD_NOTI("wait for reset process done, took %u.%03u, state %d\n", spend_ms, spend_us, pFrontend->demod->fw_state);

				if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN)
					ret = ERROR_DEMOD_FW_NOT_READY;
				else
					ret = NO_DEMOD_ERROR;
				return ret;
			}
			pFrontend->demod->chip->fw_type = DEMOD_FW_TYPE_INV;
			pFrontend->demod->fw_state = DEMOD_FW_STATE_INIT;
			return _DEMOD_E60_FW_Initialize(fw_type);
			//ret = ERROR_DEMOD_LOADING_FIRMWARE;
			//goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("ResetFirmware");

		if (NO_DEMOD_ERROR != _DEMOD_E60_StopFirmware(pFrontend)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("StopFirmware");

		DEMOD_L1_IPC_Enable(pFrontend->demod, FALSE);
		SPEND_TIME_CHECK("IPC Disable");

		if (NO_DEMOD_ERROR != _DEMOD_E60_InitFirmware(pFrontend, fw_clk, adc_clk)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}
		SPEND_TIME_CHECK("InitFirmware");

//		after 1st firmware loading, no more need LoadFirmware. It will be used at DC on/off.
//		if (NO_DEMOD_ERROR != _DEMOD_E60_LoadFirmware(pFrontend, fw_table))
//			return ERROR_DEMOD_LOADING_FIRMWARE;
		pFrontend->demod->chip->fw_type = fw_type;
	}

	//DEMOD_E60_Set_UART(TRUE);

	if (NO_DEMOD_ERROR != _DEMOD_E60_StartFirmware(pFrontend)) {
		ret = ERROR_DEMOD_LOADING_FIRMWARE;
		goto return_with_api_unlock;
	}
	SPEND_TIME_CHECK_MSG("StartFirmware");

	DEMOD_L1_IPC_Enable(pFrontend->demod, TRUE);
	SPEND_TIME_CHECK("IPC Enable");

	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
	SPEND_TIME_CHECK("UnlockDevice");

	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("DEMOD_L2_Init Failed\n");
		ret = -ERROR_DEMOD_ERROR;
		goto return_with_device_unlock;
	}
	SPEND_TIME_CHECK("L2_Init");

	spend_clock = DEMOD_L0_CalcSpendClock(begin_clock, &spend_ms, &spend_us);
	DEMOD_INFO("TC: FW_Initialize, spend %3u.%03ums\n",spend_ms, spend_us);
	DEMOD_NOTI("fw init done\n");

	DEMOD_UnlockDevice();
	return NO_DEMOD_ERROR;

return_with_api_unlock:
	DEMOD_NOTI("try DEMOD_L0_UnlockDevice with ret %d\n", ret);
	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
	DEMOD_NOTI("done DEMOD_L0_UnlockDevice\n");
return_with_device_unlock:
	DEMOD_UnlockDevice();
	DEMOD_NOTI("fw init failed with ret %d\n", ret);
	return ret;
}

int DEMOD_E60_FW_Initialize (void)
{
	return _DEMOD_E60_FW_Initialize(DEMOD_FW_TYPE_TER);
}

int DEMOD_E60_SAT_FW_Initialize (void)
{
	return _DEMOD_E60_FW_Initialize(DEMOD_FW_TYPE_SAT);
}

int DEMOD_E60_ALL_FW_Initialize (void)
{
	return _DEMOD_E60_FW_Initialize(DEMOD_FW_TYPE_TER);
}

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
static UINT8 _DEMOD_E60_Get_Valid_OperMode(LX_DEMOD_L2_Context *	pFrontend) {
	UINT8 reply_operMode = pFrontend->demod->rsp->dd_status.reply_operMod;
	UINT8 trans_operMode = g_demod_ctx_info[0].tranMode;
	UINT8 operMode = LX_DEMOD_UNKOWN_OPMODE;

	UINT8 fw_type = pFrontend->demod->chip->fw_type;

	switch(g_demod_ctx_info[0].tranMode)
	{
		case LX_DEMOD_ATSC:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_VSB;
			break;
		case LX_DEMOD_QAM:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_QAM;
			break;
		case LX_DEMOD_ISDBT:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_ISDBT;
			break;
		case LX_DEMOD_DVBT:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBT;
			break;
		case LX_DEMOD_DVBT2:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBT2;
			break;
		case LX_DEMOD_DVBC:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBC;
			break;
		case LX_DEMOD_DVBC2:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBC2;
			break;
		case LX_DEMOD_DTMB:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DTMB;
			break;
		case LX_DEMOD_DVBS:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBS;
			break;
		case LX_DEMOD_DVBS2:
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBS2;
			break;
		default :
			DEMOD_PRINT_ALWAYS("[DEMOD_CHIP] Invaild Opermode parameter %d\n", trans_operMode);
			trans_operMode = DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN;
			break;
	}

	DEMOD_INFO("[DEMOD_FW] reply 0x%02x, trans 0x%02x, fwtype %d\n", reply_operMode, trans_operMode, fw_type);

	switch (pFrontend->demod->rsp->dd_status.reply_operMod) {
	case DEMOD_DD_MODE_PROP_MODULATION_VSB:
	case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:
	case DEMOD_DD_MODE_PROP_MODULATION_QAM:
	case DEMOD_DD_MODE_PROP_MODULATION_ISDBT:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBC2:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS:
	case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:
	case DEMOD_DD_MODE_PROP_MODULATION_DTMB:
		reply_operMode = pFrontend->demod->rsp->dd_status.reply_operMod;
		break;
	default:
		reply_operMode = DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN;
	}

	if (DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN == trans_operMode) {
		if (DEMOD_DD_MODE_PROP_MODULATION_UNKNOWN == reply_operMode) {
			if (fw_type == DEMOD_FW_TYPE_TER)
				operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBT;
			else if (fw_type == DEMOD_FW_TYPE_SAT)
				operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBS;
			else
				operMode = DEMOD_DD_MODE_PROP_MODULATION_DVBT;
		} else {
			operMode = reply_operMode;
		}
		DEMOD_ERROR("[DEMOD_FW] trans_operMode LX_DEMOD_UNKNOWN_OPMODE, use reply_operMode: %02x, fwtype %d => operMode %02x\n", reply_operMode, fw_type, operMode);
	} else {
		operMode = trans_operMode;
	}

	DEMOD_INFO("[DEMOD_FW] reply 0x%02x, trans 0x%02x, operMod 0x%02x, fwtype %d\n", reply_operMode, trans_operMode, operMode, fw_type);

	return operMode;
}

static int _DEMOD_E60_FW_Reset_Task(void * data) {
	int	ret = NO_DEMOD_ERROR;

	LX_DEMOD_L2_Context *	pFrontend = (LX_DEMOD_L2_Context *)data;
	LX_DEMOD_OPER_MODE_T	lx_operMode;

	UINT8 operMode = _DEMOD_E60_Get_Valid_OperMode(pFrontend);
	UINT8 fw_type = pFrontend->demod->chip->fw_type;
	UINT32 error_flag = 0;

	DEMOD_NOTI("start\n");

	while (!kthread_should_stop()) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		ret = wait_event_interruptible_timeout(_fw_reset_wait, (pFrontend->demod->fw_error > 0),  msecs_to_jiffies(10000));
		//ret = wait_event_interruptible(_fw_reset_wait, (pFrontend->demod->fw_error > 0));
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		//Sleep(100);
		if (pEvent != NULL) {
			WaitForSingleObject(pEvent->m_hObject, 500);
		} else {
			fprintf(stderr, "CEvent is null\n");
		}
#else
		ret = 0;
#endif

		if (ret < 0) {
			DEMOD_DEBUG("wait_event stopped with %d, fw_state %d, fw_error %d\n", ret, pFrontend->demod->fw_state, pFrontend->demod->fw_error);
			continue;
		} else if (ret == 0) {
			DEMOD_DEBUG("wait_event timeout, fw_state %d, fw_error %d\n", pFrontend->demod->fw_state, pFrontend->demod->fw_error);
			continue;
		} else {
			DEMOD_INFO("wait_event success with %d, fw_state %d, fw_error %d\n", ret, pFrontend->demod->fw_state, pFrontend->demod->fw_error);
		}

		switch(pFrontend->demod->fw_error) {
			case DEMOD_FW_STATE_TIMEOUT:
				DEMOD_LockDevice();

				DEMOD_L1_IPC_Wait_Cancel(pFrontend->demod);
				if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip)) {
					DEMOD_ERROR("failed L0_LockDevice, fw timeout reset cancelled\n");
					continue;
				}

				/* ADC disable */
				CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, admd_mip7);
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, admd_mip7, reg_dbb__admd_bias_pdb, 0);
				CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, admd_mip7);
				//DEMOD_NOTI("#1 adc disabled\n");

				pFrontend->demod->fw_error = 0;
				wmb();

				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_ERROR_FLAG, 4, &error_flag)) {
					DEMOD_ERROR("failed write REG_ERROR_FLAG 0x%08x\n", error_flag);
				}
				DEMOD_INFO("#1 adc off, cleare error flag done\n");
				break;

			case DEMOD_FW_STATE_RESET:
				operMode = _DEMOD_E60_Get_Valid_OperMode(pFrontend);

				switch (operMode) {
				case DEMOD_DD_MODE_PROP_MODULATION_VSB:			lx_operMode = LX_DEMOD_ATSC;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_ATSC3:		lx_operMode = LX_DEMOD_ATSC3;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_QAM: 		lx_operMode = LX_DEMOD_QAM;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_ISDBT: 		lx_operMode = LX_DEMOD_ISDBT;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBT:		lx_operMode = LX_DEMOD_DVBT;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBT2:		lx_operMode = LX_DEMOD_DVBT2;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBC:		lx_operMode = LX_DEMOD_DVBC;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBC2:		lx_operMode = LX_DEMOD_DVBC2;	fw_type = DEMOD_FW_TYPE_TER;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBS:		lx_operMode = LX_DEMOD_DVBS;	fw_type = DEMOD_FW_TYPE_SAT;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DVBS2:		lx_operMode = LX_DEMOD_DVBS2;	fw_type = DEMOD_FW_TYPE_SAT;	break;
				case DEMOD_DD_MODE_PROP_MODULATION_DTMB:		lx_operMode = LX_DEMOD_DTMB;	fw_type = DEMOD_FW_TYPE_TER;	break;
				default:
					DEMOD_ERROR("[DEMOD_API] LX_DEMOD_UNKNOWN_OPMODE with value : %02x, forced set LX_DEMOD_DVBT\n", operMode);
					lx_operMode = LX_DEMOD_DVBT;
					fw_type = DEMOD_FW_TYPE_TER;
					break;
				}

				DEMOD_NOTI("#2 fw reset with oper 0x%x, lx %u, fw_type %d\n", operMode, lx_operMode, fw_type);

				DEMOD_E60_API_Suspend();
				DEMOD_E60_OperModeReset(lx_operMode);

				pFrontend->demod->fw_error = 0;
				wmb();

				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(pFrontend->demod->chip, REG_ERROR_FLAG, 4, &error_flag)) {
					DEMOD_ERROR("failed write REG_ERROR_FLAG 0x%08x\n", error_flag);
				}
				DEMOD_INFO("#2 cleared error flag\n");

				ret = _DEMOD_E60_FW_Initialize(fw_type);
				DEMOD_E60_StdOperModeContrl(lx_operMode, 0, 0);

				CTOP_CTRL_E60Ax_RdFL(CTOP_SYN_DBB, admd_mip7);
				CTOP_CTRL_E60Ax_Wr01(CTOP_SYN_DBB, admd_mip7, reg_dbb__admd_bias_pdb, 1);
				CTOP_CTRL_E60Ax_WrFL(CTOP_SYN_DBB, admd_mip7);
				DEMOD_INFO("#2 adc enabled\n");

				if (ret == NO_DEMOD_ERROR) {
					DEMOD_INFO("#2 try newtune\n");
					DEMOD_Retune(lx_operMode);
				}
				break;

			default:
				DEMOD_NOTI("unexpected fw_state : %d\n", pFrontend->demod->fw_state);
				continue;
			break;
		}
	}

	_fw_reset_thread = NULL;
	return NO_DEMOD_ERROR;
}
#endif

int DEMOD_E60_FW_Error_Handler (int errcode) {
	int	ret = NO_DEMOD_ERROR;
	LX_DEMOD_L2_Context * pFrontend = DEMOD_E60_GetContext();

	if (pFrontend->demod->fw_error > 0) {
		DEMOD_NOTI("already in reset process, errcode 0x%04x, fw_state %d, fw_error %d\n", errcode, pFrontend->demod->fw_state, pFrontend->demod->fw_error);
		return ret;
	}
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	switch (errcode) {
	case CMD_TYPE_ERROR_TIMEOUT:
		DEMOD_INFO("wakeup fw_reset_task for adc off\n");
		pFrontend->demod->fw_state = DEMOD_FW_STATE_TIMEOUT;
		pFrontend->demod->fw_error = DEMOD_FW_STATE_TIMEOUT;
		wmb();

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		wake_up_interruptible(&_fw_reset_wait);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		pEvent->PulseEvent();
#endif
		break;

	case CMD_TYPE_ERROR_FWRESET:
		if (pFrontend->demod->fw_state < DEMOD_FW_STATE_RUN) {
			DEMOD_NOTI("fw is not running, discard reset request, errcode 0x%04x, fw_state %d, fw_error %d\n", errcode, pFrontend->demod->fw_state, pFrontend->demod->fw_error);
			return ret;
		}
		DEMOD_INFO("wakeup fw_reset_task\n");
		pFrontend->demod->fw_state = DEMOD_FW_STATE_RESET;
		pFrontend->demod->fw_error = DEMOD_FW_STATE_RESET;
		wmb();
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		wake_up_interruptible(&_fw_reset_wait);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		pEvent->PulseEvent();
#endif
		break;
	default:
		break;
	}
#endif

	return ret;
}

int DEMOD_E60_FW_ReInitalize (int mode) {
	LX_DEMOD_L2_Context *	pFrontend = DEMOD_E60_GetContext();
	int						ret = NO_DEMOD_ERROR;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	LX_DEMOD_OPER_MODE_T 	opmode;
	UINT8					fw_type;

	if (mode < 0) {
		if (pFrontend->demod->fw_state != DEMOD_FW_STATE_RUN) {
			DEMOD_WARN("fw is not ready\n");
			return -ERROR_DEMOD_FW_NOT_READY;
		}

		if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip))
			return -ERROR_DEMOD_OS_LOCK;

		ret = DEMOD_L1_IPC_Send (pFrontend->demod, CMD_TYPE_TEST_FTIMEOUT, 0, NULL, 0);

		DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
		return ret;
	}

	if (mode == 3) {
		/* fw check */
		_DEMOD_E60_CheckFirmware(pFrontend, (LX_DEMOD_FW_STRUCT *)DEMOD_DDR_FW);
		return NO_DEMOD_ERROR;
	}

	switch (mode) {
	case 0:
		/* forced init dvd & fw load */
		fw_type = DEMOD_FW_TYPE_TER;

		DEMOD_E60_DVB_SW_Init();
		break;

	case 1:
		/* fw swreset & fw load */
		fw_type			= pFrontend->demod->chip->fw_type;

		DEMOD_E60_API_Suspend();

		DEMOD_NOTI("FW Re-Init with type %d\n", fw_type);

		if (RET_OK !=  DEMOD_E60_Get_OperMode (&opmode)) {
			DEMOD_WARN("Get OperMode error, forced set opmode to DVBT\n");
			opmode = LX_DEMOD_DVBT;
		}
		DEMOD_E60_OperModeReset(opmode);
		DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0);
		usleep_range(10000,11000);	/* 10ms ~ 11ms */
		break;

	case 2:
		/* fw swreset & fw restart (like ter<->sat change) */
		fw_type			= pFrontend->demod->chip->fw_type;
		DEMOD_NOTI("FW Re Start with type %d\n", fw_type);

		if (RET_OK !=  DEMOD_E60_Get_OperMode (&opmode)) {
			DEMOD_WARN("Get OperMode error, forced set opmode to DVBT\n");
			opmode = LX_DEMOD_DVBT;
		}
		DEMOD_E60_OperModeReset(opmode);
		DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0);
		usleep_range(10000,11000);	/* 10ms ~ 11ms */
		break;

	default:
		DEMOD_ERROR("invliad mode %d\n", mode);
		return ERROR_DEMOD_FW;
		break;
	}

	ret = _DEMOD_E60_FW_Initialize(fw_type);
	DEMOD_E60_StdOperModeContrl(opmode, 0, 0);

	if (NO_DEMOD_ERROR == ret) {
		DEMOD_INFO("try newtune\n");
		DEMOD_Retune(opmode);
	}
#endif

	return ret;
}

