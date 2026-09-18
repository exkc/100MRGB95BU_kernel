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

#include <linux/kernel.h>	/**< printk() */
#include <linux/vmalloc.h>
#include <linux/file.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/errno.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,11,0)
#include <linux/kernel_read_file.h>
#endif


#include "sys_regs.h"
#include "hma_alloc.h"
#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"
#include "demod_util.h"

#include "demod_common_o24.h"
#include "demod_dvb_o24.h"

#include "demod_fw_o24.h"
#include "demod_util_o24.h"
#include "demod_api_o24.h"
#include "demod_ipc_o24.h"

#include <O24_DEMOD_ALL_FW.h>
#define DEMOD_DDR_FW 	O24_DEMOD_ALL_FW
#define DEMOD_FW_NAME 	"O24_DEMOD_ALL_FW"

/* macro definition */
#define DEMOD_CHIP_INFO	0x24a0

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

typedef enum _fw_maker_type {
	DEMOD_FW_INVALID = -1,
	DEMOD_FW_NEW = 0,
	DEMOD_FW_OLD,
} fw_maker_t;

typedef struct _fw_maker_header {
	unsigned char magic[8];		// "DEMOD FW"
	unsigned char fw_date[4];	// 20190722
	unsigned char fw_ver[4];	// 20A00011
	unsigned char fw_author[10];	// samin.ryu
	unsigned char fw_datetime[6];	//19 07 22 16 07 00
} fw_maker_h;

static unsigned char fw_start_lg_lx7_2[] = {0x06, 0x01, 0x00, 0x00, 0x34, 0x00, 0x00, 0x50,};
static unsigned char fw_start_lg_lx7[]   = {0x06, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0xe4, 0x13,};
static unsigned char fw_start_lg_108_x[] = {0x06, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,};
static unsigned char fw_start_lg_108_v[] = {0x00, 0xc5, 0x49, 0x10, 0xd5, 0x49, 0x20, 0xe5, 0x49,};

int DEMOD_O24_FW_Get_Info(const UINT8 * p_fw_bin, UINT32 * p_fw_date, UINT32 * p_fw_ver, char * p_fw_builder, UINT8 * p_fw_buildtime) {
	fw_maker_h * fwh;
	fw_maker_t fwt = DEMOD_FW_OLD;
	int ret = 0;

	if (NULL == p_fw_bin)
		p_fw_bin = DEMOD_DDR_FW->firmware_table;

	fwh = (fw_maker_h *)p_fw_bin;

	ret = memcmp(fwh->magic, FW_MAKER_MAGIC, 8);
	if (0 == ret) {
		fwt = DEMOD_FW_NEW;
		p_fw_bin += sizeof(fw_maker_h);

		DEMOD_NOTI("fw info date %02X%02X%02X%02X, ver %02X%02X%02X%02X, %02X/%02X/%02X %02X:%02X:%02X, %s\n",
					fwh->fw_date[0], fwh->fw_date[1], fwh->fw_date[2], fwh->fw_date[3],
					fwh->fw_ver[0], fwh->fw_ver[1], fwh->fw_ver[2], fwh->fw_ver[3],
					fwh->fw_datetime[0], fwh->fw_datetime[1], fwh->fw_datetime[2], fwh->fw_datetime[3], fwh->fw_datetime[4], fwh->fw_datetime[5],
					DEMOD_BYTE_TO_HEXSTR((char *)fwh->fw_author, 10));

		if (NULL != p_fw_date)
			*p_fw_date = ntohl(*(UINT32 *)fwh->fw_date);
		if (NULL != p_fw_ver)
			*p_fw_ver = ntohl(*(UINT32 *)fwh->fw_ver);
		if (NULL != p_fw_builder)
			memcpy(p_fw_builder, fwh->fw_author, 10);
		if (NULL != p_fw_buildtime)
			memcpy(p_fw_buildtime, fwh->fw_datetime, 6);
	} else {
		fwt = DEMOD_FW_OLD;
	}

	if (0 == memcmp(p_fw_bin, fw_start_lg_lx7_2, sizeof(fw_start_lg_lx7_2))) {
		DEMOD_INFO("fw built with lg_lx7_2\n");
	} else if (0 == memcmp(p_fw_bin, fw_start_lg_lx7, sizeof(fw_start_lg_lx7))) {
		DEMOD_INFO("fw built with lg_lx7\n");
	} else if (0 == memcmp(p_fw_bin, fw_start_lg_108_x, sizeof(fw_start_lg_108_x))) {
		DEMOD_INFO("fw built with lg_108_x\n");
	} else if (0 == memcmp(p_fw_bin, fw_start_lg_108_v, sizeof(fw_start_lg_108_v))) {
		DEMOD_INFO("fw built with lg_108_v\n");
	} else {
		DEMOD_ERROR("invalid fw type, dump %s ...\n", DEMOD_BYTE_TO_HEXSTR((char *)p_fw_bin, 8));
		fwt = DEMOD_FW_INVALID;
	}

	return fwt;
}

/*
 * ref from int te_read_file_from_path(const char *path, void **buf, size_t max_size) @core/te/te_util.c
 */
static int _DEMOD_O24_FW_Read_FilePath(const char *path, void *buf, size_t max_size)
{

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#if LINUX_VERSION_CODE < KERNEL_VERSION(6,11,0)
	loff_t size;
	int rc;

	rc = kernel_read_file_from_path(path, &buf, &size, max_size,
					READING_FIRMWARE_PREALLOC_BUFFER);
	if (rc < 0) {
		DEMOD_ERROR("read failed %s, %d", path, rc);
		return rc;
	}

#else
	ssize_t size;
	size = kernel_read_file_from_path(path, 0, &buf, max_size, NULL,
					READING_FIRMWARE);
	if (size < 0) {
		DEMOD_ERROR("read failed %s, %d", path, size);
		return size;
	}
#endif
	return size;
#else
	DEMOD_INFO("not support file read (need above kernel 5.4)\n");
#endif

	
}


static char * _demod_fw_path_list[] = {
	"/var/demod_fw.bin",
	"/usr/local/lib/firmware/demod_fw.bin",
	"/usr/lib/firmware/demod_fw.bin",
};

static int _DEMOD_O24_FW_Load(UINT8 * fw, int * fwlen) {
	size_t path_num = sizeof(_demod_fw_path_list) / sizeof(char *);
	int i;
	int size = 0;

	for (i = 0; i < path_num; i++) {
		if (_demod_fw_path_list[i]) {
			size = _DEMOD_O24_FW_Read_FilePath(_demod_fw_path_list[i], fw, LX_DEMOD_FW_MAXSIZE);
			if (size > 0) {
				break;
			}
		}
	}

	if (size <= 0) {
		DEMOD_INFO("can't find demod_fw.bin\n");
		return size;
	}

	DEMOD_NOTI("read %s (%d bytes)\n", _demod_fw_path_list[i], size);
	*fwlen = size;

	return NO_DEMOD_ERROR;
}

static void _DEMOD_O24_MCU_Reset (BOOL flag) {
#if 1
	if(flag) {
		CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_DBB, crg_dbb3);
		CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_DBB, crg_dbb3, reg_soft_rst_mcu_n, 1);
		CTOP_CTRL_O24Ax_WrFL(SCRG_CTRL_DBB, crg_dbb3);
		DEMOD_PRINT("set CTOP DBB MCU reset\n");
	} else {
		CTOP_CTRL_O24Ax_RdFL(SCRG_CTRL_DBB, crg_dbb3);
		CTOP_CTRL_O24Ax_Wr01(SCRG_CTRL_DBB, crg_dbb3, reg_soft_rst_mcu_n, 0);
		CTOP_CTRL_O24Ax_WrFL(SCRG_CTRL_DBB, crg_dbb3);
		DEMOD_PRINT("clr CTOP DBB MCU reset\n");
	}
#endif
}

static void _DEMOD_O24_REG_Init	(BOOL flag) {
#if 1
	if(flag) {
		CTOP_CTRL_O24Ax_RdFL(IP_CTRL_DBB, ipw_dbb_004);
		CTOP_CTRL_O24Ax_Wr01(IP_CTRL_DBB, ipw_dbb_004, reg_dbb_reg_init, 1);
		CTOP_CTRL_O24Ax_WrFL(IP_CTRL_DBB, ipw_dbb_004);
		DEMOD_PRINT("set CTOP DBB REG init\n");
	} else {
		CTOP_CTRL_O24Ax_RdFL(IP_CTRL_DBB, ipw_dbb_004);
		CTOP_CTRL_O24Ax_Wr01(IP_CTRL_DBB, ipw_dbb_004, reg_dbb_reg_init, 0);
		CTOP_CTRL_O24Ax_WrFL(IP_CTRL_DBB, ipw_dbb_004);
		DEMOD_PRINT("clr CTOP DBB REG init\n");
	}
#endif
}

//#define DEMOD_SPEND_TIME_CHECK
#if defined(DEMOD_SPEND_TIME_CHECK)
#define SPEND_TIME_DECLARE()	UINT64 start_clock;
#define SPEND_TIME_START()	start_clock = DEMOD_L0_SystemClock();
#define SPEND_TIME_CHECK(desc) { \
	UINT32 spend_us, spend_ms; \
	DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us); \
	DEMOD_INFO("TC: %s, spend %3u.%03ums\n", desc, spend_ms, spend_us); \
	start_clock = DEMOD_L0_SystemClock(); \
}
#define SPEND_TIME_CHECK_MSG(desc) { \
	UINT32 spend_us, spend_ms; \
	DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us); \
	DEMOD_NOTI("TC: %s, spend %3u.%03ums\n", desc, spend_ms, spend_us); \
	start_clock = DEMOD_L0_SystemClock(); \
}

#else
#define SPEND_TIME_DECLARE()		{}
#define SPEND_TIME_START()		{}
#define SPEND_TIME_CHECK(desc)		{}
#define SPEND_TIME_CHECK_MSG(desc)	{ DEMOD_NOTI("%s done\n", desc); }
#endif

static int _DEMOD_O24_ResetFirmware (LX_DEMOD_L2_Context * pFrontend) {
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

static int _DEMOD_O24_StopFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int ret = NO_DEMOD_ERROR;

	ret = DEMOD_L1_API_FinishFirmware(pFrontend->demod);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_API_FinishFirmware with ret %d\n", ret);
		return ret;
	}

	/* MCU stall */
	ret = DEMOD_L1_API_StopFirmware(pFrontend->demod);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_ERROR("DEMOD_L1_API_FinishFirmware with ret %d\n", ret);
		return ret;
	}

	DEMOD_L0_system_wait(1);

	return ret;
}

static int _DEMOD_O24_InitFirmware (LX_DEMOD_L2_Context * pFrontend, UINT32 fw_clk, UINT32 adc_clk) {
	int ret = NO_DEMOD_ERROR;

	SPEND_TIME_DECLARE();
	SPEND_TIME_START();

	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		_DEMOD_O24_MCU_Reset(MCU_RESET);		SPEND_TIME_CHECK("MCU_RESET");
		DEMOD_L0_system_wait(1);			SPEND_TIME_CHECK("wait(1)");

		/* MCU FW control register init */
		ret = DEMOD_L1_API_InitFirmware_DDR(pFrontend->demod, fw_clk, adc_clk);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("DEMOD_L1_API_InitFirmware_DDR with ret %d\n", ret);
			return ret;
		}
								SPEND_TIME_CHECK("InitFirmware_DDR");
		_DEMOD_O24_MCU_Reset(MCU_RELEASE);		SPEND_TIME_CHECK("MCU_RELEASE");
		DEMOD_L0_system_wait(1);			SPEND_TIME_CHECK("wait(1)");

		_DEMOD_O24_REG_Init(REG_SET);			SPEND_TIME_CHECK("REG_SET");
		DEMOD_L0_system_wait(1);			SPEND_TIME_CHECK("wait(1)");
		_DEMOD_O24_REG_Init(REG_CLEAR);			SPEND_TIME_CHECK("REG_CLEAR");
	} else {
		/* MCU FW control register init */
		ret = DEMOD_L1_API_InitFirmware(pFrontend->demod, fw_clk, adc_clk);
		if (ret != NO_DEMOD_ERROR) {
			DEMOD_ERROR("DEMOD_L1_API_InitFirmware with ret %d\n", ret);
			return ret;
		}						SPEND_TIME_CHECK("InitFirmware");
	}

	return NO_DEMOD_ERROR;
}

static LX_DEMOD_FW_STRUCT _firmware_file = {0, 0,};

static int _DEMOD_O24_CheckFirmware (LX_DEMOD_L2_Context * pFrontend, LX_DEMOD_FW_STRUCT * fw_table) {
	UINT32 * fw_addr = NULL;
	int ret = RET_OK;

	UINT8 * data;
	UINT32 size;

	UINT8 * ddr_data;

	if (0 != _firmware_file.firmware_size) {
		data = _firmware_file.firmware_table;;
		size = _firmware_file.firmware_size;

		DEMOD_NOTI("using firmware file, size %d\n", size);
	} else {
		data = fw_table->firmware_table;
		size = fw_table->firmware_size;

		DEMOD_NOTI("using firmware header, size %d\n", size);
	}

	ret = DEMOD_O24_FW_Get_Info(data, NULL, NULL, NULL, NULL);
	if (DEMOD_FW_INVALID == ret ) {
		DEMOD_INFO("FW_Check error %d\n", ret);
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	} else if (DEMOD_FW_OLD == ret) {
		/* nop */
	} else if (DEMOD_FW_NEW == ret) {
		data = data + sizeof(fw_maker_h);
	}

	DEMOD_DEBUG("fw copy from ddr\n");

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

	ret = memcmp(data, ddr_data, size);
	DEMOD_INFO("ddr fw check : %d (size %d)\n", ret, size);

	return ret;
}

#if (DEMOD_COMM == DEMOD_COMM_APB)
static int _DEMOD_O24_LoadFirmware_SOC (LX_DEMOD_L2_Context * pFrontend, UINT8 * data, UINT32 size) {
	UINT32 * fw_addr = NULL;

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
static int _DEMOD_O24_LoadFirmware_EXT (LX_DEMOD_L2_Context * pFrontend, UINT8 * data, UINT32 size) {
	int ret = RET_OK;
	int tryCount = 0;

	for(tryCount = 0; tryCount < 5; tryCount++)
	{
		UINT32 down_addr = 0;
		UINT32 base_addr = 0;
		int left_count = 0;
		int done_count = 0;

		DEMOD_INFO("fw download to DDR, try #%d\n", tryCount);

		DEMOD_L0_Lock_CommDevice(pFrontend->demod->chip);

		pFrontend->demod->chip->fw_done = 0;

		down_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock(pFrontend->demod->chip, REG_FW_DL_ADDR, 4, &down_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		down_addr = 0x50000000;
		if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock(pFrontend->demod->chip, REG_FW_DL_BASE, 4, &down_addr)) {
			ret = -ERROR_DEMOD_LOADING_FIRMWARE;
			continue;
		}

		down_addr = 0x50000000;
		left_count = size;

		while (left_count > 0) {
			if(left_count >= 0x80)
			{
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock(pFrontend->demod->chip, down_addr, 0x80, data + done_count)) {
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}

				done_count += 0x80;
				left_count -= 0x80;
			} else {
				if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock(pFrontend->demod->chip, down_addr, left_count, data + done_count)) {
					ret = -ERROR_DEMOD_LOADING_FIRMWARE;
					break;
				}

				done_count += left_count;
				left_count = 0;
			}

			down_addr += 0x80;
		}

		DEMOD_L0_Unlock_CommDevice(pFrontend->demod->chip);

		if (NO_DEMOD_ERROR != ret) {
			continue;
		}

		DEMOD_INFO("LGDBB Success!! => Count(%d)\n", tryCount);
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

static int _DEMOD_O24_LoadFirmware (LX_DEMOD_L2_Context * pFrontend, LX_DEMOD_FW_STRUCT * fw_table) {
	UINT32 mem_base_addr;
	int ret = RET_OK;

	UINT8 * data;
	UINT32 size;

	SPEND_TIME_DECLARE();
	SPEND_TIME_START();

	_firmware_file.firmware_size = 0;
	ret = _DEMOD_O24_FW_Load(&_firmware_file.firmware_table[0], &_firmware_file.firmware_size);

	if (0 != _firmware_file.firmware_size) {
		data = _firmware_file.firmware_table;;
		size = _firmware_file.firmware_size;

		DEMOD_NOTI("using firmware demod_fw.bin, size %d\n", size);
	} else {
		data = fw_table->firmware_table;
		size = fw_table->firmware_size;

		DEMOD_NOTI("using firmware header, size %d\n", size);
	}

	ret = DEMOD_O24_FW_Get_Info(data, NULL, NULL, NULL, NULL);
	if (DEMOD_FW_INVALID == ret ) {
		DEMOD_INFO("FW_Check error %d\n", ret);
		return -ERROR_DEMOD_LOADING_FIRMWARE;
	} else if (DEMOD_FW_OLD == ret) {
		DEMOD_INFO("old type fw\n");
	} else if (DEMOD_FW_NEW == ret) {
		DEMOD_INFO("new type fw\n");
		data = data + sizeof(fw_maker_h);
	}

	DEMOD_DEBUG("copy to ddr start with data %p, size %u\n", data, size);
	SPEND_TIME_CHECK("FW load to mem & Check");

#if (DEMOD_COMM == DEMOD_COMM_APB)
	ret = _DEMOD_O24_LoadFirmware_SOC(pFrontend, data, size);
	mem_base_addr = gMemCfgDEMOD_FW.memory_base;
#elif (DEMOD_COMM == DEMOD_COMM_I2C) || (DEMOD_COMM == DEMOD_COMM_FPGA)
	ret = _DEMOD_O24_LoadFirmware_EXT(pFrontend, data, size);
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

	return NO_DEMOD_ERROR;
}

static int _DEMOD_O24_StartFirmware (LX_DEMOD_L2_Context * pFrontend) {
	int tryCount = 0;
	int ret = 0;

	SPEND_TIME_DECLARE();
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
	}							SPEND_TIME_CHECK("StartFirmware");

	DEMOD_PRINT("FW %s, loading done\n", DEMOD_FW_NAME);


	DEMOD_L0_system_wait(10);				SPEND_TIME_CHECK("wait(10)");

	tryCount = 1000;
	while ((tryCount-- > 0) && ((ret = DEMOD_L1_API_IsReady(pFrontend->demod)) != NO_DEMOD_ERROR)) {
		DEMOD_L0_system_wait(1);
	}							SPEND_TIME_CHECK("IsReady");
	DEMOD_NOTI("FW ver 0x%08x, date 0x%08x\n", pFrontend->demod->fw_ver, pFrontend->demod->fw_date);

	if(ret != NO_DEMOD_ERROR) 	{
		DEMOD_ERROR("failed f/w start with ret %d, tryCount %d\n", ret, tryCount);
		return ret;
	}

	return NO_DEMOD_ERROR;
}

#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
static int _DEMOD_O24_FW_FPAG_Reset(void) {
	/* FPGA box reset routine */
	UINT8 rptSlvAddr = 0xE0 >> 1;
	UINT8 rdData=0, wrData=0;
	UINT32 temp;

	int err=0;

	DEMOD_I2C_Raw_Lock();

	DEMOD_I2C_Raw_Read(rptSlvAddr, 0x7000, 1, &rdData);
	DEMOD_NOTI("I2C_RPT_CTRL read 0x%02x, err %d\n", rdData, err);

	// HWRSTENB set 0 to enable SW reset for FPGA
	wrData = rdData & 0x7f;
	DEMOD_I2C_Raw_Write(rptSlvAddr, 0x7000, 1, &wrData);

	DEMOD_I2C_Raw_Read(rptSlvAddr, 0x7000, 1, &rdData);
	DEMOD_NOTI("I2C_RPT_CTRL HWRSTENB set 0, read 0x%02x, err %d\n", rdData, err);

	msleep(100);

	// HWRSTENB set 1 to disable SW reset for FPGA
	wrData = rdData | 0x80;
	DEMOD_I2C_Raw_Write(rptSlvAddr, 0x7000, 1, &wrData);
	msleep(100);

	DEMOD_I2C_Raw_Read(rptSlvAddr, 0x7000, 1, &rdData);
	DEMOD_NOTI("I2C_RPT_CTRL HWRSTENB set 1, read 0x%02x, err %d\n", rdData, err);

	msleep(500);

	DEMOD_I2C_Raw_Unlock();

	return NO_DEMOD_ERROR;
}
#endif	// DEMOD_CONFIG_CROSS_PLATFORM

static int _DEMOD_O24_FW_Initialize(demod_fw_type fw_type) {
	LX_DEMOD_L2_Context *	pFrontend = DEMOD_Get_LGDBB_Context();
	LX_DEMOD_FW_STRUCT * 	fw_table = NULL;

	UINT32			fw_clk = 0;
	UINT32			adc_clk = 0;
	int 			ret = NO_DEMOD_ERROR;

	UINT64 			begin_clock;
	UINT32			spend_us;
	UINT32			spend_ms;
	UINT64			spend_clock;

	SPEND_TIME_DECLARE();
	SPEND_TIME_START();

	begin_clock = DEMOD_L0_SystemClock();

#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
	_DEMOD_O24_FW_FPAG_Reset();
#endif

	SPEND_TIME_START();

	if ((pFrontend->demod->fw_state == DEMOD_FW_STATE_RESET) || (pFrontend->demod->fw_state == DEMOD_FW_STATE_INIT)) {
		DEMOD_NOTI("skip DEMOD_LockDevice(), already locked\n");
	} else {
		/* first firmware loading after boot */
		DEMOD_LockDevice();
	}							SPEND_TIME_CHECK("DEMOD_LockDevice");

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	fw_clk = pFrontend->sysclk;
	adc_clk = pFrontend->adcclk;
#endif

	if (fw_clk == 0 || adc_clk == 0) {
		if (fw_type == DEMOD_FW_TYPE_TER) {
			fw_clk = DEMOD_PROP_CLOCK_MODE_96MHZ;		// 1X 12MHZ, 8X 96MHZ
			adc_clk = DEMOD_PROP_ADC_ADCCLK_24MHZ;
		}
		else if (fw_type == DEMOD_FW_TYPE_SAT) {
#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
			fw_clk = DEMOD_PROP_CLOCK_MODE_80MHZ;		// 1X 15.5MHZ, 8X 124MHZ
			adc_clk = DEMOD_PROP_ADC_ADCCLK_80MHZ;
#else
			fw_clk = DEMOD_PROP_CLOCK_MODE_124MHZ;		// 1X 15.5MHZ, 8X 124MHZ
			adc_clk = DEMOD_PROP_ADC_ADCCLK_124MHZ;
#endif
		}
		else {
			DEMOD_ERROR("fw_type invalid %d\n", fw_type);
			return ERROR_DEMOD_FW_INIT;
		}
	}

#if defined(PLATFORM_FPGA)
	// o24_fpga, for fpga integrated test
	fw_clk = DEMOD_PROP_CLOCK_MODE_400MHZ;
	if (fw_type == DEMOD_FW_TYPE_TER) {
		adc_clk = DEMOD_PROP_ADC_ADCCLK_24MHZ;
	} else {
		adc_clk = DEMOD_PROP_ADC_ADCCLK_60P8MHZ;
	}
#endif

	fw_table = (LX_DEMOD_FW_STRUCT *)DEMOD_DDR_FW;

	DEMOD_INFO("try fw init with %u, %u, %u\n", pFrontend->demod->chip->fw_type, fw_type, fw_clk);

	/* When first init after boot, set chip information */
	if (pFrontend->demod->chip->fw_type == DEMOD_FW_TYPE_INV) {
		DEMOD_INFO("set chip info 0x%04X\n", DEMOD_CHIP_INFO);
		DEMOD_L2_Set_ChipInfo(pFrontend, DEMOD_CHIP_INFO, DEMOD_CHIP_IF);
	}							SPEND_TIME_CHECK("Set_ChipInfo");

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

		if (NO_DEMOD_ERROR != _DEMOD_O24_StopFirmware(pFrontend)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}						SPEND_TIME_CHECK("StopFirmare");

		DEMOD_O24_IPC_Enable(FALSE);			SPEND_TIME_CHECK("IPC Disable");

		DEMOD_O24_IPC_Reset();				SPEND_TIME_CHECK("IPC_Reset");

		if (NO_DEMOD_ERROR != _DEMOD_O24_InitFirmware(pFrontend, fw_clk, adc_clk)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}						SPEND_TIME_CHECK("InitFirmware");

		if (pFrontend->demod->chip->fw_skip == 0) {
			if (NO_DEMOD_ERROR != _DEMOD_O24_LoadFirmware(pFrontend, fw_table)) {
				ret = ERROR_DEMOD_LOADING_FIRMWARE;
				goto return_with_api_unlock;
			}
		}						SPEND_TIME_CHECK("LoadFirmware");

		pFrontend->demod->chip->fw_type = fw_type;

	} else {
		DEMOD_NOTI("fw re-init for type change, fw_state %d\n", pFrontend->demod->fw_state);

		if (NO_DEMOD_ERROR != DEMOD_L2_Set_SoftRst(pFrontend, 1, 0, 0, 0, 0, 0, 0)) {
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
			return _DEMOD_O24_FW_Initialize(fw_type);
			//goto return_with_api_unlock;
		}						SPEND_TIME_CHECK_MSG("SoftRst");

		if (NO_DEMOD_ERROR != DEMOD_L0_LockDevice(pFrontend->demod->chip))
			return ERROR_DEMOD_LOADING_FIRMWARE;
		DEMOD_NOTI("device locked\n");

		DEMOD_L0_system_wait(10);			SPEND_TIME_CHECK("wait(10)");

		if (NO_DEMOD_ERROR != _DEMOD_O24_ResetFirmware(pFrontend)) {
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
			return _DEMOD_O24_FW_Initialize(fw_type);
		}						SPEND_TIME_CHECK("ResetFirmware");

		if (NO_DEMOD_ERROR != _DEMOD_O24_StopFirmware(pFrontend)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}						SPEND_TIME_CHECK("StopFirmware");

		DEMOD_O24_IPC_Enable(FALSE);			SPEND_TIME_CHECK("IPC Disable");

		DEMOD_O24_IPC_Reset();				SPEND_TIME_CHECK("IPC_Reset");

		if (NO_DEMOD_ERROR != _DEMOD_O24_InitFirmware(pFrontend, fw_clk, adc_clk)) {
			ret = ERROR_DEMOD_LOADING_FIRMWARE;
			goto return_with_api_unlock;
		}						SPEND_TIME_CHECK("InitFirmware");

		pFrontend->demod->chip->fw_type = fw_type;
	}

	//DEMOD_O24_Set_UART(TRUE);

	if (NO_DEMOD_ERROR != _DEMOD_O24_StartFirmware(pFrontend)) {
		ret = ERROR_DEMOD_LOADING_FIRMWARE;
		goto return_with_api_unlock;
	}							SPEND_TIME_CHECK("StartFirmware");

	DEMOD_O24_IPC_Enable(TRUE);				SPEND_TIME_CHECK("IPC Enable");

	DEMOD_PRINT("try device unlock\n");
	DEMOD_L0_UnlockDevice(pFrontend->demod->chip);
	DEMOD_PRINT("device unlock\n");				SPEND_TIME_CHECK("UnlockDevice");

	if(DEMOD_L2_Init(pFrontend) != NO_DEMOD_ERROR)
	{
		DEMOD_ERROR("DEMOD_L2_Init Failed\n");
		ret = -ERROR_DEMOD_ERROR;
		goto return_with_device_unlock;
	}							SPEND_TIME_CHECK("L2_Init");

	spend_clock = DEMOD_L0_CalcSpendClock(begin_clock, &spend_ms, &spend_us);
	DEMOD_INFO("TC: FW_Initialize, total spend %3u.%03ums\n",spend_ms, spend_us);
	DEMOD_NOTI("fw init done\n");

	DEMOD_UnlockDevice();

#if defined(DEMOD_FW_INIT_BOOST)
	_DEMOD_O24_FW_Init_Boost(0);
#endif

	DEMOD_CHIP_PROC_Init();

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

int DEMOD_O24_FW_Initialize (void)
{
	DEMOD_NOTI("FW_TYPE_TER\n");
	return _DEMOD_O24_FW_Initialize(DEMOD_FW_TYPE_TER);
}

int DEMOD_O24_SAT_FW_Initialize (void)
{
	DEMOD_NOTI("FW_TYPE_SAT\n");
	return _DEMOD_O24_FW_Initialize(DEMOD_FW_TYPE_SAT);
}

