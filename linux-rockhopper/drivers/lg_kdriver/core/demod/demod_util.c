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
 *	demod utils
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-05-30
 *	@note
 */

#define DEMOD_TAG "[UTIL] "

#if defined(__XTENSA__)
#include <dsa_fw.h>
#include <demod_main.h>

#elif defined(__KERNEL__)
#include <linux/kernel.h>	/**< printk() */
#include <linux/vmalloc.h>
//#include <linux/file.h>
//#include <linux/time.h>
#include <linux/types.h> 	/**< size_t */
#include <linux/errno.h>

#include "os_util.h"
#include "debug_util.h"
//#include "sys_regs.h"  //chungiii fpga
#include "hma_alloc.h"	// vmap_phys

#include "demod_impl.h"
#include "demod_module.h"

#include "demod_hw.h"
#include "demod_util.h"

#elif defined(_WIN32)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

void DEMOD_Test_DDR_MEM(void);



char sdbglog[DEMOD_DBG_LOG_MAX];

static char hex_to_char_table[] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

char * DEMOD_BYTE_TO_HEXSTR_r(char * out, int outlen, char * src, int srclen) {
	int i;

	memset(out, 0, outlen);

	if (src == NULL || srclen == 0)
		return out;

	if (srclen >= outlen)
		srclen = outlen - 1;

	for (i = 0; i < srclen; i++) {
		//SPRINTF(&out[i * 2], "%02X", arr[i]);
		out[i * 2 + 0] = hex_to_char_table[(src[i] >> 4 & 0xF)];
		out[i * 2 + 1] = hex_to_char_table[(src[i] >> 0 & 0xF)];
	}

	return out;
}

char * DEMOD_BYTE_TO_HEXSTR(char * arr, int len) {
	int i;
	static char out[192 + 1] = {0,};
	int len_max = (sizeof(out) - 1) / 3;

	memset(out, 0, sizeof(out));

	if (arr == NULL || len == 0)
		return out;

	if (len > len_max)
		len = len_max;

	for (i = 0; i < len; i++) {
		//SPRINTF(&out[i * 2], "%02X", arr[i]);
		out[i * 3 + 0] = hex_to_char_table[(arr[i] >> 4 & 0xF)];
		out[i * 3 + 1] = hex_to_char_table[(arr[i] >> 0 & 0xF)];
		out[i * 3 + 1] = ' ';
	}

	return out;
}


char * DEMOD_BYTE_TO_CHARSTR_r(char * out, int outlen, char * src, int srclen) {
	int i;

	memset(out, 0, outlen);

	if (src == NULL || srclen == 0)
		return out;

	if (srclen >= outlen)
		srclen = outlen - 1;


	for (i = 0; i < srclen; i++) {
		out[i] = src[i];
	}

	return out;
}

char * DEMOD_BYTE_TO_CHARSTR(char * arr, int len) {
	int i;
	static char out[192] = {0,};

	memset(out, 0, sizeof(out));

	if (arr == NULL || len == 0)
		return out;

	if (len >= sizeof(out))
		len = sizeof(out) - 1;

	for (i = 0; i < len; i++) {
		//SPRINTF(&out[i], "%c", arr[i]);
		out[i] = arr[i];
	}

	return out;
}

int DEMOD_DUMP_BYTE(char * dst, unsigned char * src, int size) {
	int i;
	int idx = 0;
	int wsiz = LEN_TO_WORD(size);

	for (i = 0; i < wsiz; i++) {
		if ((i & 0x3) == 0x0) {
			idx += SPRINTF(dst + idx, "x%02x ", IDX_TO_ADDR(i));
		}
		//idx += SPRINTF(dst + idx, "%s ", DEMOD_Array_to_HexString((char *)&src[i * 4], 4));
		idx += SPRINTF(dst + idx, "%02x %02x %02x %02x  ", src[IDX_TO_ADDR(i)], src [IDX_TO_ADDR(i) + 1], src[IDX_TO_ADDR(i) + 2], src[IDX_TO_ADDR(i) + 3]);

		if ((i & 0x3) == 0x3)
			idx += SPRINTF(dst + idx, "\n");
	}

	idx += SPRINTF(dst + idx, "\n");
	return idx;
}

int DEMOD_DUMP_WORD(char * dst, unsigned int * wsrc, int size) {
	int i;
	int idx = 0;
	int wsiz = LEN_TO_WORD(size);

	for (i = 0; i < wsiz; i++) {
		if ((i & 0x3) == 0x0) {
			idx += SPRINTF(dst + idx, "x%03x ", IDX_TO_ADDR(i));
		}
		//idx += SPRINTF(dst + idx, "%s ", DEMOD_Array_to_HexString((char *)&wsrc[i], 4));
		idx += SPRINTF(dst + idx, "%08x ", wsrc[i]);

		if ((i & 0x7) == 0x7)
			idx += SPRINTF(dst + idx, "\n");
		else if ((i & 0x3) == 0x3)
			idx += SPRINTF(dst + idx, " ");
	}

	idx += SPRINTF(dst + idx, "\n");
	return idx;
}

#if defined(__KERNEL__)
int DEMOD_Get_Debug_Level(char * dbgbuf){
	UINT32 mask;
	int pos = 0;

	LOGM_ObjMaskGet(g_demod_debug_fd, &mask);
	pos += SPRINTF(dbgbuf + pos,	"print enabled   : 0x%08X\n", mask);
	LOGM_ObjHiddenMaskGet(g_demod_debug_fd, &mask);
	pos += SPRINTF(dbgbuf + pos,	"hidden (logm)   : 0x%08X\n", mask);
	LOGM_ObjUserMaskGet(g_demod_debug_fd, &mask);
	pos += SPRINTF(dbgbuf + pos,	"forced disabled : 0x%08X\n", mask);

	pos += SPRINTF(dbgbuf + pos,	"\ncommand list"
					"0: default\n"
					"\tserial+logm : DEMOD_ERROR,DEMOD_WARN,DEMOD_NOTI, DEMOD_MCU_ERROR\n"
					"\tlogm        : DEMOD_INFO, DEMOD_MCU_PRINT\n"
					"\tdisable     : DEMOD_PRINT, DEMOD_MCU_DEBUG\n"
					"\tblock       : DEMOD_DEBUG, DEMOD_TRACE\n");
	pos += SPRINTF(dbgbuf + pos,	"  1: enable all w/o MCU (PRINT, DEBUG, TRACE set enable)\n");
	pos += SPRINTF(dbgbuf + pos,	"  2: clear hidden mask w/o MCU (INFO, DEBUG, TRACE will show on kernel log and logm)\n");
	pos += SPRINTF(dbgbuf + pos,	"  3: clear  block mask w/o MCU (DEBUG, TRACE no more block)\n");
	pos += SPRINTF(dbgbuf + pos,	"  4: enable MCU log (MCU_ERROR, MCU_PRINT, MCU_DEBUG)\n");
	pos += SPRINTF(dbgbuf + pos,	"  5: disable MCU log w/o MCU_ERROR\n");
	pos += SPRINTF(dbgbuf + pos,	"255: all of log levels show on kernel log\n");
	return pos;
}

int DEMOD_Set_Debug_Level(int enable){
	if(g_demod_debug_fd < 0)
	{
		DEMOD_ERROR("g_demod_debug_fd not opend\n");
		return RET_ERROR;
	}

	switch (enable) {
	case 0:
	default:
		DEMOD_NOTI("logm set default\n");

		/* default on/off */
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_NOTI);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_INFO);
		LOGM_ObjBitMaskDisable		(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG);
		LOGM_ObjBitMaskDisable		(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE);

		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_ALWAYS);
		LOGM_ObjBitMaskDisable		(g_demod_debug_fd, LX_LOGM_LEVEL_PRINT);

		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_ERROR);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT);
		LOGM_ObjBitMaskDisable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);

		/* set hidden maks : logm only */
		LOGM_ObjBitHiddenMaskEnable	(g_demod_debug_fd, LX_LOGM_LEVEL_INFO);
		LOGM_ObjBitHiddenMaskEnable	(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG);
		LOGM_ObjBitHiddenMaskEnable	(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE);

		LOGM_ObjBitHiddenMaskEnable 	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT);
		LOGM_ObjBitHiddenMaskEnable 	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);

		/* set forced disabled */
		LOGM_ObjBitUserMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG);
		LOGM_ObjBitUserMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE);
		LOGM_ObjBitUserMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);
		break;


	case 1:
		DEMOD_NOTI("all enable w/o MCU\n");

		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_ERROR);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_WARNING);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_NOTI);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_INFO);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE);

		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_ALWAYS);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_PRINT);
		break;

	case 2:
		/* clear hidden mask */
		DEMOD_NOTI("clear hidden mask w/o MCU (logm only -> serial + logm)\n");

		LOGM_ObjBitHiddenMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_INFO);
		LOGM_ObjBitHiddenMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG);
		LOGM_ObjBitHiddenMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE);
		break;

	case 3:
		/* clear blocked bit & all enable */
		DEMOD_NOTI("clear forced mask w/o MCU (blocked -> not blocked)\n");

		LOGM_ObjBitUserMaskEnable	(g_demod_debug_fd, LX_LOGM_LEVEL_DEBUG);
		LOGM_ObjBitUserMaskEnable	(g_demod_debug_fd, LX_LOGM_LEVEL_TRACE);
		break;

	case 4:
		DEMOD_NOTI("enable MCU log\n");
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_ERROR);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT);
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);

		LOGM_ObjBitHiddenMaskDisable 	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT);
		LOGM_ObjBitHiddenMaskDisable 	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);

		LOGM_ObjBitUserMaskEnable	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);
		break;

	case 5:
		DEMOD_NOTI("disable MCU log (exclude MCU_ERROR)\n");
		LOGM_ObjBitMaskEnable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_ERROR);
		LOGM_ObjBitMaskDisable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT);
		LOGM_ObjBitMaskDisable		(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);

		LOGM_ObjBitHiddenMaskEnable 	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_PRINT);
		LOGM_ObjBitHiddenMaskEnable 	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);

		LOGM_ObjBitUserMaskDisable	(g_demod_debug_fd, LX_LOGM_LEVEL_MCU_DEBUG);
		break;

	case 255:
		DEMOD_NOTI("enable all log\n");
		DEMOD_Set_Debug_Level(3);
		DEMOD_Set_Debug_Level(2);
		DEMOD_Set_Debug_Level(1);
		// enable mcu
		DEMOD_Set_Debug_Level(4);
		break;
	}

	return RET_OK;
}

#define DDR_MEM_OFFSET	0x3C000
#define DDR_MEM_SIZE	0x4000
#define DDR_MEM_WSIZE	(DDR_MEM_SIZE >> 2)

unsigned int ddr_mem_dump[DDR_MEM_WSIZE];

void DEMOD_Test_DDR_MEM(void) {
	UINT32 * ddr_addr = NULL;
	UINT32 offset = DDR_MEM_OFFSET;
	UINT32 size = DDR_MEM_SIZE;

	UINT32 i;
	static UINT32 v = 0;

	static char logbuf[512];
	int logpos = 0;

	ddr_addr = (UINT32 *)vmap_phys(gMemCfgDEMOD_FW.memory_base + offset, size);
	DEMOD_INFO("[DEMOD_UTIL] test ddr base 0x%08X, offset 0x%08X, target 0x%08X, size %d(0x%08X), vaddr %p\n",
		gMemCfgDEMOD_FW.memory_base, offset, gMemCfgDEMOD_FW.memory_base + offset, size, size,
		ddr_addr);

	if(!ddr_addr) {
		DEMOD_ERROR("[DEMOD_UTIL] test vmap_phys fail!!!\n");
		return;
	}

	for (i = 0; i < (size >> 2); i++) {
		ddr_addr[i] = v;
	}
	wmb();

	for (i = 0; i < (size >> 2); i++) {
		ddr_mem_dump[i] = ddr_addr[i];
	}
	rmb();

	for (i = 0; i < (size >> 2); i++) {
		if (ddr_mem_dump[i] == v) {
			logpos += SPRINTF(logbuf + logpos, ".");
		} else {
			logpos += SPRINTF(logbuf + logpos, "%08X", ddr_mem_dump[i]);
		}
		if ((i & 0x3F) == 0x3F) {
			DEMOD_INFO("[DEMOD_UTIL] %s\n", logbuf);
			logpos = 0;
		}
	}

	if (logpos > 0) {
		DEMOD_INFO("[DEMOD_UTIL] %s\n", logbuf);
		logpos = 0;
	}

	vunmap_phys(ddr_addr);
	v++;
}

int DEMOD_Get_Test(char * dbgbuf){
	int pos = 0;

	pos += SPRINTF(dbgbuf + pos, "1: ddr mem test\n");
	pos += SPRINTF(dbgbuf + pos, "2: fw timeout test\n");
	return pos;
}

int DEMOD_Set_Test(int enable){
	switch (enable) {
	case 1:
		DEMOD_NOTI("DDR Test\n");
		DEMOD_Test_DDR_MEM();
		break;
	case 2:
		DEMOD_NOTI("fw timeout test\n");
		DEMOD_FW_ReInit(-1);
		break;
	default:
		DEMOD_NOTI("N/I for %d\n", enable);
		break;
	}
	return RET_OK;
}
#endif

