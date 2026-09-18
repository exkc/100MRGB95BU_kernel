/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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


/** @file
 *
 *  CIS extraction layer
 *
 *  author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version	0.6
 *  date		2010.02.22
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */


/*=============================================================================+
| Include                                                                      |
+=============================================================================*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#include <asm/irq.h>
#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/memory.h>

#include "ci_util.h"
#include "ci_dev.h"
#include "ci_proc.h"
#include "ci_hw_cis.h"
#include "ci_hw_ops.h"

static inline int _ci_hw_addr_is_overflow(CI_DEV_T *cidev, int offset)
{
	u32	cis_addr_limit = cidev->cfg->cis_addr_limit;

	if(cis_addr_limit && (offset >= cis_addr_limit))
	{
		LOG_CIS_ERR("	* offset(0x%X) overflow >= 0x%X\n", offset, cis_addr_limit);

		return 1;
	}
	return 0;
}


static int ci_hw_read_tuple(CI_DEV_T *cidev, char *buf, u32 *offset, int sleep_time)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
//	cis_config_t *cis_config = &cis_info->info_config;
//	cis_status_t *cis_status = &cis_info->info_status;
	char *pdata = NULL;
	char *pdata_r;
	u32 addr_offset = (*offset);
	u32 cnt = 0;
	u8 tuple_value = 0;
	u8 tuple_length = 0;
	u8 tuple_body = 0;
	int delay;

	pdata = buf;

	/* read tuple code */
	tuple_value = CICAM_READ8(cidev, addr_offset);
	cis_info->rcnt_analysis++;
	LOG_CIS_TUPLE2("> tuple_value = 0x%02X(0x%08X)\n", tuple_value, addr_offset);
//	LOG_CIS_TUPLE2("> tuple_value = 0x%02X\n", tuple_value);
	ci_pcap_mon_cis_data(cidev, &tuple_value, 1);
	if( tuple_value == CISTPL_END ) {
		return TUPLE_END;
	}

	*pdata++ = tuple_value;
	addr_offset += CIS_AM_STEP;

	if(_ci_hw_addr_is_overflow(cidev, addr_offset))
		return TUPLE_LAST;

	/* read tuple length */
	tuple_value = CICAM_READ8(cidev, addr_offset);
	cis_info->rcnt_analysis++;
	LOG_CIS_TUPLE2("> tuple_value = 0x%02X(0x%08X)\n", tuple_value, addr_offset);
//	LOG_CIS_TUPLE2("> tuple_value = 0x%02X\n", tuple_value);
	ci_pcap_mon_cis_data(cidev, &tuple_value, 1);
	if( tuple_value == CISTPL_LINK_END ) {
		return TUPLE_LAST;
	}

	*pdata++ = tuple_value;
	addr_offset += CIS_AM_STEP;

	if(_ci_hw_addr_is_overflow(cidev, addr_offset))
		return TUPLE_LAST;

	pdata_r = pdata;
	cnt = 0;

	delay = ci_get_delay_param(cidev, DELAY_CIS_DURING_READ_TUPLE);
	/* read tuple body */
	tuple_length = tuple_value;
	cis_info->rcnt_analysis += tuple_length;
	while (tuple_length--) {
		if (!ci_is_card_detected(cidev)) {	// for ISR
			return TUPLE_INT;
		}

		tuple_body = CICAM_READ8(cidev, addr_offset);
		LOG_CIS_TUPLE2("> tuple_body  = 0x%02X(0x%08X)\n", tuple_body, addr_offset);
//		LOG_CIS_TUPLE2("> tuple_body  = 0x%02X\n", tuple_body);
		*pdata++ = tuple_body;
		addr_offset += CIS_AM_STEP;

		if(_ci_hw_addr_is_overflow(cidev, addr_offset))
			return TUPLE_LAST;

		cnt++;

		ci_sleep(delay);
	}

	ci_pcap_mon_cis_data(cidev, pdata_r, cnt);

	/* update offset value */
	*offset = addr_offset;

	ci_sleep(sleep_time);

	return TUPLE_NOT_END;
}

#define STR_LEN_MAX  	25

#define STR_COMPAT_LEN 	11 /* "compatible[" */

#define STR_CIPLUS_LEN	7	/* "ciplus=" */
#define STR_CIPROF_LEN	7 	/* "ciprof=" */
#define MAX_CIPVER_NUM	32	/* 32bit error cover */

static UINT32 _ci_hw_check_ci_plus_version(char *compare_string, UINT32 version)
{
	char *str = compare_string;
	int i, num;
	char mode = 0;

	LOG_CIS_CIPLUS("* found ci-plus version\n");
	LOG_CIS_CIPLUS("*  string : %s\n", compare_string);

	if( (str[0] == '+') ||
		(str[0] == '-') ||
		(str[0] == '*') )
	{
		mode = str[0];
		str = str + 1;
	}

	num = simple_strtoul(str, NULL, 10);
	if(num > MAX_CIPVER_NUM)
	{
		LOG_WARNING("ver[%d] exceeds max num, set as max[%d]", num, MAX_CIPVER_NUM);
		num = MAX_CIPVER_NUM;
	}

	/* is it correct? Check it if problem happened */
	if (num > 0) {
		/* it's CI plus CAM */
		if(mode == 0 || mode == '+')
		{
			version = (0x1 << (num - 1));
		}
		else if(mode == '*')
		{
			for(i=0; i<num; i++)
			{
				version |= (0x1 << i);
			}
		}
		else // mode == '-'
		{
			version &= ~(0x1 << (num-1));
		}
	}
	else // Error case
	{
		LOG_ERROR("CI+ version[%d] parse error", num);
		version = 0;
	}

	LOG_CIS_CIPLUS("*  version    : 0x%08x\n", version);

	return version;
}

static int _ci_hw_check_ci_plus_profile(char *compare_string)
{
	char *str = compare_string;
	int num;

	LOG_CIS_CIPLUS("* found ci-plus profile\n");
	LOG_CIS_CIPLUS("*  string : %s\n", compare_string);

	num = simple_strtoul(str, NULL, 0);

	LOG_CIS_CIPLUS("*  profile    : 0x%08x\n", num);
	return num;
}

static void ci_hw_check_ci_plus_analysis(cis_vers_1_t *cis_vers_1,
										char *compare_string)
{
	UINT32 version = cis_vers_1->version;

	if (!strncasecmp(compare_string, "ciplus=", STR_CIPLUS_LEN)) {
		cis_vers_1->version = _ci_hw_check_ci_plus_version(compare_string + STR_CIPLUS_LEN, version);
		cis_vers_1->is_ci_plus = (cis_vers_1->version) ? 0x1 : 0x0;
	} else if (!strncasecmp(compare_string, "ciprof=", STR_CIPROF_LEN)) {
		cis_vers_1->profile = _ci_hw_check_ci_plus_profile(compare_string + STR_CIPROF_LEN);
	}
}

static void ci_hw_check_ci_plus(CI_DEV_T *cidev, char *buf, int rest_length)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_vers_1_t *cis_vers_1 = &cis_info->info_vers_1;
	char *pbuf, *compare_string, *temp_buf;
	//char testbuf[100] = "$compatible[ciplus=*3 ciprof=0x135 ciplus=-2]$"; //test string
	//buf = testbuf;
	//rest_length = 60;

	CHECK_ERROR(buf == NULL, return, "buf is NULL");
	CHECK_ERROR(rest_length <= 0, return, "invalid length[%d]", rest_length);

	temp_buf = (char*) kmalloc(rest_length + 1, GFP_KERNEL);
	CHECK_ERROR(temp_buf == NULL, goto exit, "fail to alloc");
	memcpy(temp_buf, buf, rest_length);
	temp_buf[rest_length] = '\0'; //For null termination

	pbuf = strnchr(temp_buf, rest_length, '$');
	if (pbuf == NULL) {
		goto exit;
	}
	pbuf++;

	if (strncasecmp(pbuf, "compatible[", STR_COMPAT_LEN) != 0) {
		goto exit;
	}

	pbuf += STR_COMPAT_LEN;

	pbuf = strsep(&pbuf, "]");
	LOG_CIS_CIPLUS("* comp_str : %s\n", pbuf);

	while (1) {
		if(pbuf == NULL) break;

		compare_string = strsep(&pbuf, " ");
		if(compare_string == NULL) break;

		ci_hw_check_ci_plus_analysis(cis_vers_1, compare_string);
	}

exit:
	if(temp_buf) kfree(temp_buf);
}

static int ci_hw_parse_vers1(CI_DEV_T *cidev, char *buf)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_vers_1_t *cis_vers_1 = &cis_info->info_vers_1;
//	cis_config_t *cis_config = &cis_info->info_config;
//	cis_status_t *cis_status = &cis_info->info_status;
	u8 *pstring[4];
	u8 *pdata;
	u8 string_idx;
	u8 tuple_body;
	UINT8 tuple_length;
	UINT8 rest_length;
	int tmp;
	int ret;

	pdata = ++buf;
	tuple_length = *pdata++;

	memset((void *)cis_vers_1, 0, sizeof(cis_vers_1_t));

	/* M14_TBD, tupleLen is not over than 255, set the value from UINT8* value,
	   Check and Delete It 2013. 07. 03, jinhwan.bae */
#if 0
	if (tuple_length > CIS_TPL_BUF_SIZE - 2) {
		LOG_CIS_PARSE("CIS - Actual Tuple Len - %d, Source buf(Tuple) size - %d\n",
						tuple_length, CIS_TPL_BUF_SIZE);

		return DATA_NOT_AVAILABLE;
	}
#endif

	cis_vers_1->len = tuple_length;
	memcpy(cis_vers_1->raw, pdata, tuple_length);

	cis_vers_1->major = *pdata++;
	cis_vers_1->minor = *pdata++;

	ret = ((cis_vers_1->major == TPLLV1_MAJOR) &&
			(cis_vers_1->minor == TPLLV1_MINOR)) ?	\
			DVB_CI_COMPLIANT : DVB_CI_NOT_COMPLIANT;

	/* parse version info string fields */
	pstring[0] = cis_vers_1->manufact;
	pstring[1] = cis_vers_1->product;
	pstring[2] = cis_vers_1->add1;
	pstring[3] = cis_vers_1->add2;
	rest_length = tuple_length - 2;
	string_idx = 0;

	tmp = 0;
	while ((rest_length--) && (string_idx < 4))
	{

		tuple_body = *pdata++;
	//	cim_dbg_2("0x%02x\n", tuple_body);

		if (tuple_body == 0xFF) {
			break;
		}

		if (tuple_body) {
			if (tmp < (VERS_1_INFO_LEN - 3)) {
				*(pstring[string_idx])++ = tuple_body;
				tmp++;
			}
		} else {
			*(pstring[string_idx])++ = tuple_body;
			*(pstring[string_idx]) = '\0';
			string_idx++;
			tmp = 0;

			if ((string_idx == 2) || (string_idx == 3)) {
				if (!cis_vers_1->is_ci_plus) {
					ci_hw_check_ci_plus(cidev, pdata, rest_length);
				}
			}
		}
	}

	ci_hw_cis_set_chk_state(cidev, 1);

	LOG_CIS_PARSE("  Major Version : 0x%02X\n", cis_vers_1->major);
	LOG_CIS_PARSE("  Minor Version : 0x%02X\n", cis_vers_1->minor);
	LOG_CIS_PARSE("  Manufact Str  : %s\n", cis_vers_1->manufact );
	LOG_CIS_PARSE("  Product Str   : %s\n", cis_vers_1->product );
	LOG_CIS_PARSE("  Add1 Str      : %s\n", cis_vers_1->add1 );
	LOG_CIS_PARSE("  Add2 Str      : %s\n", cis_vers_1->add2 );
	LOG_CIS_PARSE("  Is it CI+ CAM : 0x%08x[%s]\n",cis_vers_1->version,
					(cis_vers_1->is_ci_plus)? "yes" : "no");

	return ret;
}

static int _ci_hw_parse_config_chk_tpcc(cis_config_t *cis_config,
										int tuple_length, u8 tuple_body)
{
	u8 tpcc_rfsz, tpcc_rmsz, tpcc_rasz;

	/* size of configuration register base address */
	tpcc_rasz = (tuple_body & TPCC_RASZ_MASK) + 1;
	/* size of presence mask */
	tpcc_rmsz = ((tuple_body & TPCC_RMSZ_MASK) >> 2) + 1;
	/* byte size of RFU = it must be zero */
	tpcc_rfsz = (tuple_body & TPCC_RFSZ_MASK) >> 6;

	cis_config->tpcc_rasz = tpcc_rasz;
	cis_config->tpcc_rmsz = tpcc_rmsz;
	cis_config->tpcc_rfsz = tpcc_rfsz;
	LOG_CIS_PARSE("  TPCC_RASZ : %02d bytes\n", tpcc_rasz);
	LOG_CIS_PARSE("  TPCC_RMSZ : %02d bytes\n", tpcc_rmsz);
	LOG_CIS_PARSE("  TPCC_RFSZ : %02d bytes\n", tpcc_rfsz);

	if(tuple_length < (tpcc_rasz+tpcc_rmsz+tpcc_rfsz+2)) {
	//	LOG_CIS_ERR("CIS_ParseConfig: size error\n");
		LOG_CIS_ERR("  * Not DVB-CI compliant - tuple_length(%d) < %d\n",
					tuple_length, (tpcc_rasz+tpcc_rmsz+tpcc_rfsz+2));
		return -EFAULT;
	}

	return 0;
}

static void *_ci_hw_parse_config_chk_addr(cis_config_t *cis_config,
										u8 *pdata)
{
	u8 tpcc_rfsz, tpcc_rmsz, tpcc_rasz;
	u8 shift_byte;

	tpcc_rasz = cis_config->tpcc_rasz;
	tpcc_rmsz = cis_config->tpcc_rmsz;
	tpcc_rfsz = cis_config->tpcc_rfsz;

	/* Base Addr */
	cis_config->base_addr = 0;
	shift_byte = 0;
	while (tpcc_rasz--) {
		cis_config->base_addr |= ((u32)(*(++pdata))&0x000000FF) << (8*shift_byte++);
	}
	LOG_CIS_PARSE("  COR Base Addr    : 0x%04X\n", cis_config->base_addr);
	if (cis_config->base_addr > TPCC_RADR_MAX) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - base addr > 0x%04X\n", TPCC_RADR_MAX);
		return NULL;
	}

	cis_config->mask = *(++pdata);
	if (tpcc_rmsz > 1) {
		pdata += (tpcc_rmsz - 1);	// skip
	}

	return pdata;
}

static void *_ci_hw_parse_config_chk_sub_tuple(cis_ccst_cif_t *ccst_cif,
											u8 *pdata)
{
	u8 *str;
	u8 sub_tuple_code, sub_tuple_len;
	u8 exit_flag;
	u8 tuple_body;
	u16 if_num;

	sub_tuple_code = *(++pdata);
	if (sub_tuple_code != CFGST_CIF) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - sub_tuple_code, 0x%02X\n", sub_tuple_code);
		return NULL;
	}

	/* parse sub-tuple */
	sub_tuple_len = *(++pdata);
	tuple_body = *(++pdata);
	if (!(tuple_body & 0x40)) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - sub_tuple_code, 0x%02X\n", tuple_body);
		return NULL;
	}

	ccst_cif->if_id_num_base = tuple_body;
	if_num = tuple_body & 0xFF;
	tuple_body = *(++pdata);
	if_num |= ((u16)tuple_body<<8);
//	ccst_cif->if_id_num = tuple_body;
	ccst_cif->if_id_num = if_num;
	LOG_CIS_PARSE("  Interface ID Num : 0x%04X\n", if_num);
	if (if_num != DVB_CI_COMPLIANT_IFN) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - ID Num != 0x%04X\n", DVB_CI_COMPLIANT_IFN);
		return NULL;
	}

	sub_tuple_len -= 2;
	if (sub_tuple_len > CCST_CIF_STRING_LENGTH) {
		sub_tuple_len = CCST_CIF_STRING_LENGTH;
	}

	exit_flag = 0;
   	str = ccst_cif->str;
	while ((sub_tuple_len--) &&
			((tuple_body = *(++pdata))!=0xFF) &&
			(!exit_flag))
	{
		*str++ = tuple_body;
		if (tuple_body == 0x00)
			exit_flag = 1;
	}
	LOG_CIS_PARSE("  Interface Desc   : %s\n", ccst_cif->str);

	return pdata;
}

static int ci_hw_parse_config(CI_DEV_T *cidev, char *buf)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_config_t *cis_config = &cis_info->info_config;
	cis_ccst_cif_t *ccst_cif = &cis_config->ccst_cif;
//	cis_status_t *cis_status = &cis_info->info_status;
	u8 *pdata;
	u8 tuple_body;
	int tuple_length;
	int ret;

	pdata = ++buf;
	tuple_length = *pdata++;

	memset((void *)cis_config, 0, sizeof(cis_config_t));

	/* TPCC */
	tuple_body = *pdata++;
	ret = _ci_hw_parse_config_chk_tpcc(cis_config, tuple_length, tuple_body);
	if (ret != 0) {
		return DVB_CI_NOT_COMPLIANT;
	}

	/* Index */
	cis_config->size = tuple_body;
	cis_config->last_index = *pdata;
	LOG_CIS_PARSE("  Last Index Entry : 0x%02X\n", cis_config->last_index);

	pdata = _ci_hw_parse_config_chk_addr(cis_config, pdata);
	if (pdata == NULL) {
		return DVB_CI_NOT_COMPLIANT;
	}

	pdata = _ci_hw_parse_config_chk_sub_tuple(ccst_cif, pdata);
	if (pdata == NULL) {
		return DVB_CI_NOT_COMPLIANT;
	}

	return DVB_CI_COMPLIANT;
}

#define TPCE_INDX_CHK_BIT	(TPCE_INDX_DEF_BIT|TPCE_INDX_IF_BIT)

static void *_ci_hw_parse_cft_pre(CI_DEV_T *cidev, u8 *pdata)
{
	cis_cftable_entry_t *cis_cftable = &cidev->cis_info->info_cftable;
	u8 idx = 0, intf = 0, feature = 0;

	idx = (*pdata);
	LOG_CIS_INFO("  CFTABLE - Index       : 0x%02X\n", idx);
	LOG_CIS_INFO("              x... .... : Interface        - 0x%02X\n", (idx>>7)&0x01);
	LOG_CIS_INFO("              .x.. .... : Default          - 0x%02X\n", (idx>>6)&0x01);
	LOG_CIS_INFO("              ..xx xxxx : Config Entry Num - 0x%02X\n", idx & 0x3F);
	if ((idx & TPCE_INDX_CHK_BIT) != TPCE_INDX_CHK_BIT) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - Index[0x%02X]\n", idx);
   		return NULL;
	}
	cis_cftable->idx = idx;

	intf = *(++pdata);	//related to TPCE_INDX_IF_BIT
	LOG_CIS_INFO("  CFTABLE - I/F Type    : 0x%02X\n", intf);
	if (intf != TPCE_IF) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - I/F Type[0x%02X]\n", intf);
		return NULL;
	}
	cis_cftable->intf = intf;

	/* parsing features */
	feature = *(++pdata);
	LOG_CIS_INFO("  CFTABLE - Feature Sel : 0x%02X\n", feature);
	LOG_CIS_INFO("              x... .... : Misc             - 0x%02X\n", (feature&TPCE_FS_MISC_BIT)>>7);
	LOG_CIS_INFO("              .xx. .... : Mem space        - 0x%02X\n", (feature&TPCE_FS_MEMSP_BIT)>>5);
	LOG_CIS_INFO("              ...x .... : IRQ              - 0x%02X\n", (feature&TPCE_FS_IRQ_BIT)>>4);
	LOG_CIS_INFO("              .... x... : IO Space         - 0x%02X\n", (feature&TPCE_FS_IOSP_BIT)>>3);
	LOG_CIS_INFO("              .... .x.. : Time             - 0x%02X\n", (feature&TPCE_FS_TIME_BIT)>>2);
	LOG_CIS_INFO("              .... ..xx : Power            - 0x%02X\n", (feature&TPCE_FS_POWER_BIT)>>0);
	if (!(feature & TPCE_FS_IOSP_BIT) || !(feature & TPCE_FS_POWER_BIT)) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - Feature[0x%02X]\n", feature);
		return NULL;
	}
	cis_cftable->feature = feature;

	return pdata;
}

#define CI_PWR_INFO_FIELD_NEW

#if defined(CI_PWR_INFO_FIELD_NEW)
static int __ci_hw_parse_cft_pwr_info(CI_DEV_T *cidev,
									u8 *buf,
									pwr_descript_t *pwr_info,
									u8 index)
{
	u8 *pdata, *pval;
	u8 tuple_body = 0;
	int cnt = 0;

	pdata = buf;

	pval = &pwr_info->nom_v;
	pval += (index<<1);

	tuple_body = *(++pdata);
	cnt++;
	(*pval++) = tuple_body;
	if (tuple_body & EXT_BIT) {
		tuple_body = *(++pdata);
		(*pval) = tuple_body;
		cnt++;
	}

	/* skip */
	while (tuple_body & EXT_BIT) {
		tuple_body = *(++pdata);
	//	tuple_body = *(pdata++);
		cnt++;
	}

	return cnt;
}
#else
static void *__ci_hw_parse_cft_pwr_para_sel(u8 *buf, u8 *val, u8 *tuple, int *_cnt)
{
	u8 tuple_body;
	int cnt = 0;

	tuple_body = *(++buf);
	cnt++;
	(*val++) = tuple_body;
	if (tuple_body & EXT_BIT) {
		tuple_body = *(++buf);
		(*val) = tuple_body;
		cnt++;
	}

	(*tuple) = tuple_body;
	(*_cnt) = cnt;

	return buf;
}

static int __ci_hw_parse_cft_pwr_info_field(CI_DEV_T *cidev,
											u8 *buf,
											pwr_descript_t *pwr_info,
											u8 pwr_para_sel_bit)
{
	u8 *pdata, *pval;
	u8 tuple_body = 0;
	int i;
	int cnt = 0;

	pdata = buf;
#if 1
	pval = &pwr_info->nom_v;
	for (i = 0 ; i < 7 ; i++) {
		if (pwr_para_sel_bit & (1<<i)) {
			pdata = __ci_hw_parse_cft_pwr_para_sel(buf, pval, &tuple_body, &cnt);
			break;
		}
		pval += 2;
	}
#else
	if (pwr_para_sel_bit & PWR_NOMV_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->nom_v, &tuple_body, &cnt);
	} else if (pwr_para_sel_bit & PWR_MINV_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->min_v, &tuple_body, &cnt);
	} else if (pwr_para_sel_bit & PWR_MAXV_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->max_v, &tuple_body, &cnt);
	} else if (pwr_para_sel_bit & PWR_STATI_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->stat_i, &tuple_body, &cnt);
	} else if (pwr_para_sel_bit & PWR_AVRGI_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->avrg_i, &tuple_body, &cnt);
	} else if (pwr_para_sel_bit & PWR_PEAKI_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->peak_i, &tuple_body, &cnt);
	} else if (pwr_para_sel_bit & PWR_PDWNI_BIT) {
		pdata = __ci_hw_parse_cft_pwr_para_sel(buf, &pwr_info->pdwn_i, &tuple_body, &cnt);
	}
#endif

	/* skip */
	while (tuple_body & EXT_BIT) {
		tuple_body = *(++pdata);
	//	tuple_body = *(pdata++);
		cnt++;
	}

	return cnt;
}
#endif

static void *_ci_hw_parse_cft_power(CI_DEV_T *cidev, u8 *pdata, u8 feature)
{
	cis_cftable_entry_t *cis_cftable = &cidev->cis_info->info_cftable;
	cis_cftable_feature_t *feat = &cis_cftable->feat;
	pwr_descript_t *pwr_info;
	u8 pwr_val, pwr_para_sel;
	u8 info_len;
	int i, cnt;

	pwr_val = feature & TPCE_FS_POWER_BIT;
	feat_flag_power(feat) = pwr_val;
	pwr_info = cis_cftable->pwr_info_field;
	cnt = pwr_val;
	while (cnt--) {
		pwr_para_sel = *(++pdata);
		/* parse each power field */
		for (i = 0; i < 7; i++) {
		#if defined(CI_PWR_INFO_FIELD_NEW)
			if (!(pwr_para_sel & (1<<i))) {
				continue;
			}
			info_len = __ci_hw_parse_cft_pwr_info(cidev, pdata, pwr_info, i);
		#else
			info_len = __ci_hw_parse_cft_pwr_info_field(cidev, pdata, pwr_info,
													(pwr_para_sel & (0x01<<i)));
		#endif
			pdata += info_len;
		}
		pwr_info++;
	}

	pwr_info = cis_cftable->pwr_info_field;
	for (i = 0 ; i < pwr_val ; i++) {
		LOG_CIS_INFO("  CFTABLE - Feature : pwr info [%d]\n", i);
		LOG_CIS_INFO("                      pwr_sel  - 0x%02X\n", pwr_info->pwr_sel);
		LOG_CIS_INFO("                      nom_v    - 0x%02X\n", pwr_info->nom_v);
		LOG_CIS_INFO("                      nom_v_x  - 0x%02X\n", pwr_info->nom_v_x);
		LOG_CIS_INFO("                      min_v    - 0x%02X\n", pwr_info->min_v);
		LOG_CIS_INFO("                      min_v_x  - 0x%02X\n", pwr_info->min_v_x);
		LOG_CIS_INFO("                      max_v    - 0x%02X\n", pwr_info->max_v);
		LOG_CIS_INFO("                      max_v_x  - 0x%02X\n", pwr_info->max_v_x);
		LOG_CIS_INFO("                      stat_i   - 0x%02X\n", pwr_info->stat_i);
		LOG_CIS_INFO("                      stat_i_x - 0x%02X\n", pwr_info->stat_i_x);
		LOG_CIS_INFO("                      avrg_i   - 0x%02X\n", pwr_info->avrg_i);
		LOG_CIS_INFO("                      avrg_i_x - 0x%02X\n", pwr_info->avrg_i_x);
		LOG_CIS_INFO("                      peak_i   - 0x%02X\n", pwr_info->peak_i);
		LOG_CIS_INFO("                      peak_i_x - 0x%02X\n", pwr_info->peak_i_x);
		LOG_CIS_INFO("                      pdwn_i   - 0x%02X\n", pwr_info->pdwn_i);
		LOG_CIS_INFO("                      pdwn_i_x - 0x%02X\n", pwr_info->pdwn_i_x);

		pwr_info++;
	}

	return pdata;
}

static void *_ci_hw_parse_cft_time(CI_DEV_T *cidev, u8 *pdata, u8 feature)
{
	cis_cftable_feature_t *feat = &cidev->cis_info->info_cftable.feat;
	u8 tuple_body;

	/* skip tme information */
	if (feature & TPCE_FS_TIME_BIT) {
		tuple_body = *(++pdata);
		feat->time = tuple_body;
		feat_flag_time(feat) = 1;
	}
	return pdata;
}

static void *_ci_hw_parse_cft_io_space(CI_DEV_T *cidev, u8 *pdata, u8 feature)
{
	cis_cftable_feature_t *feat = &cidev->cis_info->info_cftable.feat;
	u8 tuple_body;

	if (feature & TPCE_FS_IOSP_BIT) {
		tuple_body = *(++pdata);
		feat->io_space = tuple_body;
		feat_flag_io_space(feat) = 1;
		LOG_CIS_INFO("  CFTABLE - Featrue : io space [0x%02X]\n", tuple_body);
		if (tuple_body != TPCE_IO) {
			LOG_CIS_ERR("  * Not DVB-CI compliant - IO Type, 0x%02X\n", tuple_body);
			return NULL;
		}
	}

	return pdata;
}

static void *_ci_hw_parse_cft_irq(CI_DEV_T *cidev, u8 *pdata, u8 feature)
{
	cis_cftable_feature_t *feat = &cidev->cis_info->info_cftable.feat;
	u8 tuple_body;

	if (feature & TPCE_FS_IRQ_BIT) {
		tuple_body = *(++pdata);
		feat->irq = tuple_body;
		feat_flag_irq(feat) = 1;
		LOG_CIS_INFO("  CFTABLE - Feature : irq [0x%02X]\n", tuple_body);
		if (tuple_body & 0x10) {
			pdata += 2;
		}
	}
	return pdata;
}

static void *_ci_hw_parse_cft_mem_space(CI_DEV_T *cidev, u8 *pdata, u8 feature)
{
	cis_cftable_feature_t *feat = &cidev->cis_info->info_cftable.feat;
	u8 tuple_body;

	if (feature & TPCE_FS_MEMSP_BIT) {
		int sel = (feature & TPCE_FS_MEMSP_BIT)>>5;

		feat_flag_mem_space(feat) = sel;

		switch (sel) {
			case 1 :
			case 2 :
			{
				pdata += (1<<sel);
			}
			break;
			case 3 :
			{
				u8 num_of_win, size_of_win;

				tuple_body = *(++pdata);
				feat->mem_space = tuple_body;
				LOG_CIS_INFO("  CFTABLE - Feature : Mem space [0x%02X]\n", tuple_body);
				num_of_win = tuple_body & 0x07;
				size_of_win = ((tuple_body & 0x18)>>3) + ((tuple_body & 0x60)>>5);
				if (tuple_body & 0x80) {
					size_of_win += (tuple_body & 0x60)>>5;
				}
				pdata += num_of_win * size_of_win;
			}
			break;

			default: break;
		}
	}
	return pdata;
}

static void *_ci_hw_parse_cft_misc(CI_DEV_T *cidev, u8 *pdata, u8 feature)
{
	cis_cftable_feature_t *feat = &cidev->cis_info->info_cftable.feat;
	u8 tuple_body;

	if (feature & TPCE_FS_MISC_BIT) {
		tuple_body = *(++pdata);
		feat->misc = tuple_body;
		feat_flag_misc(feat) = 1;
		LOG_CIS_INFO("  CFTABLE - Feature : Misc [0x%02X]\n", tuple_body);
		while (tuple_body & EXT_BIT) {
			tuple_body = *(++pdata);
		}
	}
	return pdata;
}

static void *_ci_hw_parse_cft_stce_evpd(CI_DEV_T *cidev, u8 *pdata, u8 *str)
{
//	ci_dev_cis_info_t *cis_info = cidev->cis_info;
//	cis_stce_evpd_t *cis_stce_evpd = &cis_info->info_stce_evpd;
	u8 *next;
	u8 tuple_body;
	u8 sub_tuple_len;

	sub_tuple_len = *(++pdata);
	tuple_body = *(++pdata);

	LOG_CIS_INFO("  CFTABLE - Sub-Tuple[0x%02X], Len[0x%02X]\n",
				tuple_body, sub_tuple_len);

	next = pdata + sub_tuple_len;
	while ((sub_tuple_len--) && (tuple_body != 0xFF)) {
		*str++ = tuple_body;
		if (tuple_body == 0x00) {
			break;
		}
		tuple_body = *(++pdata);
	}

	return next;
}

static int ci_hw_parse_cftable(CI_DEV_T *cidev, char *buf)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_cftable_entry_t *cis_cftable = &cis_info->info_cftable;
	cis_stce_evpd_t *stce_evpd = &cis_cftable->stce_evpd;
	u8 *pdata;
//	u8 *str;
	u8 tuple_body;
	u8 feature;
//	u8 sub_tuple_len;
	int tuple_length;
//	int ret;

	pdata = ++buf;
	tuple_length = *pdata++;

	memset((void *)cis_cftable, 0, sizeof(cis_cftable_entry_t));

	pdata = _ci_hw_parse_cft_pre(cidev, pdata);
	if (pdata == NULL) {
		return DVB_CI_NOT_COMPLIANT;
	}
	feature = cis_cftable->feature;

	/* parse power information */
	pdata = _ci_hw_parse_cft_power(cidev, pdata, feature);

	/* parse time information */
	pdata = _ci_hw_parse_cft_time(cidev, pdata, feature);

	/* parse I/O space information */
	pdata = _ci_hw_parse_cft_io_space(cidev, pdata, feature);
	if (pdata == NULL) {
		return DVB_CI_NOT_COMPLIANT;
	}

	/* parse IRQ information */
	pdata = _ci_hw_parse_cft_irq(cidev, pdata, feature);

	/* parse memory space information */
	pdata = _ci_hw_parse_cft_mem_space(cidev, pdata, feature);

	/* parse miscellaneous informations */
	pdata = _ci_hw_parse_cft_misc(cidev, pdata, feature);

	tuple_body = *(++pdata);
	if (tuple_body == 0xFF) {
		LOG_CIS_ERR("  * Not DVB-CI compliant - 0xFF\n");
		return DVB_CI_NOT_COMPLIANT;
	}

	/* parse environment sub-tuple */
	if (tuple_body == STCE_EV) {
		pdata = _ci_hw_parse_cft_stce_evpd(cidev, pdata, stce_evpd->environment);
		LOG_CIS_INFO("  Environment String    : %s\n", stce_evpd->environment);
	}

	/* parse physical device sub-tuple */
	tuple_body = *pdata;
	if (tuple_body == STCE_PD) {
		pdata = _ci_hw_parse_cft_stce_evpd(cidev, pdata, stce_evpd->physical_dev);
		LOG_CIS_INFO("  Physical Device Str   : %s\n", stce_evpd->physical_dev);
	}

	return DVB_CI_COMPLIANT;
}

static int ci_hw_parse_tuple_main(CI_DEV_T *cidev, char *buf)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_status_t *cis_status = &cis_info->info_status;
	u8 tuple_code;
	int ret = -EINVAL;

	tuple_code = *buf;

	switch (tuple_code) {
	case CISTPL_VERS_1 :
		LOG_CIS_INFO("[CISTPL_VERS_1] =================================================\n");

		if(cis_status->status_vers_1 != DVB_CI_COMPLIANT)
			cis_status->status_vers_1 = ci_hw_parse_vers1(cidev, buf);
		else
			LOG_CIS_INFO(" * Already checked - CISTPL_VERS_1\n");

		ret = 0;
		break;

	case CISTPL_CONFIG :
		LOG_CIS_INFO("[CISTPL_CONFIG] =================================================\n");

		if(cis_status->status_config != DVB_CI_COMPLIANT)
			cis_status->status_config = ci_hw_parse_config(cidev, buf);
		else
			LOG_CIS_INFO(" * Already checked - CISTPL_CONFIG\n");

		ret = 0;
		break;

	case CISTPL_CFTABLE_ENTRY :
		LOG_CIS_INFO("[CISTPL_CFTABLE_ENTRY] ==========================================\n");

		/* parse only if DVB_CI compliant tuple is not found */
		if(cis_status->status_cftable != DVB_CI_COMPLIANT)
			cis_status->status_cftable = ci_hw_parse_cftable(cidev, buf);
		else
			LOG_CIS_INFO(" * Already checked - CISTPL_CFTABLE_ENTRY\n");

		ret = 0;
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int ci_hw_parse_tuple_skip(CI_DEV_T *cidev, char *buf)
{
	u8 tuple_code;
	int ret = -EINVAL;

	tuple_code = *buf;

	switch (tuple_code) {
	case CISTPL_NO_LINK :
	case CISTPL_DEVICE :
	case CISTPL_DEVICE_A :
	case CISTPL_DEVICE_OC :
	case CISTPL_DEVICE_OA:
	case CISTPL_MANFID :
		LOG_CIS_INFO("[Tuple-0x%02X] Skipped ============================================\n",
					tuple_code);
		ret = 0;
		break;

	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

#define CI_TUPLE_VALID_CHECK_RANGE	0x800

static int ci_hw_parse_tuple(CI_DEV_T *cidev, char *buf, u32 offset)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
//	cis_config_t *cis_config = &cis_info->info_config;
	cis_status_t *cis_status = &cis_info->info_status;
	u8 tuple_code;
	int ret;

	ret = ci_hw_parse_tuple_main(cidev, buf);
	if(offset >= CI_TUPLE_VALID_CHECK_RANGE) {
		if(ci_chk_compliance(cis_status) == DVB_CI_COMPLIANT) {
			ret = TUPLE_END;
			goto out;
		}
	}

	if(ret == 0)
		goto out;

	ret = ci_hw_parse_tuple_skip(cidev, buf);
	if (ret == 0) {
		goto out;
	}

	tuple_code = *buf;

	cis_status->parse_count++;
	LOG_CIS_INFO("%d-CIS_ParseTuple: Not CI compliant tuple (TupleCode=0x%02X)\n",
				cis_status->parse_count, tuple_code);

	/* M14_TBD, CIS_ParseTuple_count is not over than 300, check it and remove it or change the threshold */
	if (cis_status->parse_count >= MAX_TUPLE_COUNT_ERR) {
	     LOG_CIS_ERR("  * Error in parsing tuple\n");
	     return CIS_PARSETIMEOUT;
	}

	ci_sleep(ci_get_delay_param(cidev, DELAY_CIS_PARSE_NON_CI_TUPLE));

out:
	LOG_CIS_PARSE("=================================================================\n");
	return (ret == TUPLE_END) ? ret : 0;
}

static int ci_hw_check_1st_tuple(CI_DEV_T *cidev, int chk_cnt,
								u32 delay_ok, u32 delay_ng)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	int count = chk_cnt + 20;
	UINT32 try = 0;
	UINT8 ci_value = 0;

	while(count--)
	{
		CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "card is not detected");
		CHECK_ERROR(ci_is_power_restart(cidev), return -EFAULT, "power_restart detected");

		if (ci_hw_verify_card_detection(cidev, 0, __func__))
		{
			LOG_ERROR("  * CI Removed (1)\n");
			return -ENODEV;
		}

		ci_value = CICAM_READ8(cidev, 0);
		cis_info->rcnt_1st_det++;
		LOG_CIS_TUPLE2("> ci_value = 0x%02X\n", ci_value);
		if (ci_value == CISTPL_DEVICE_OA)
		{
			if(try == 0) //Found at first try (init code indicates always false)
			{
				ci_sleep(delay_ok);
			}
			break;
		}
		ci_sleep(delay_ng);

		try++;
	}
	if(count <= 0)
	{
		LOG_ERROR("  * the first tuple not found try:%d last[0x%02X]\n", try, ci_value);
		return -ENODEV;
	}

	return 0;
}

static int _ci_hw_analysis_read_tuple(CI_DEV_T *cidev,
									char *cis_buf,
									u32 *offset,
									u32 sleep_time)
{
	int t_ret = 0;

	t_ret = ci_hw_read_tuple(cidev, cis_buf, offset, sleep_time);
	if (t_ret != TUPLE_INT) {
		if (ci_hw_verify_card_detection(cidev, 0, __func__) == 1) {
			LOG_CIS_ERR("  * CI Removed (2)\n");
			t_ret = TUPLE_INT;
		}
	}
	if (t_ret == TUPLE_INT) {
		LOG_CIS_ERR("  * TUPLE_INT detected\n");
		return -EFAULT;
	}
	if ((t_ret == TUPLE_END) || (t_ret == TUPLE_LAST)) {
		return t_ret;
	}

	LOG_CIS_TUPLE("Tuple Code=0x%02X, Tuple Length=%3d -------------------------------\n",
					cis_buf[0], cis_buf[1]+2);
	LOG_CIS_TUPLE("-----------------------------------------------------------------\n");

	return 0;
}

static int _ci_hw_analysis_parse_tuple(CI_DEV_T *cidev,
									char *cis_buf, u32 offset)
{
	int t_ret = 0;

	t_ret = ci_hw_parse_tuple(cidev, cis_buf, offset);
	if (t_ret == CIS_PARSETIMEOUT) {
		LOG_CIS_ERR("  * CIS configuration FAILED #1\n");
		t_ret = TUPLE_LAST;
	}
	if ((t_ret == TUPLE_END) || (t_ret == TUPLE_LAST)) {
		return t_ret;
	}

	if (ci_is_power_restart(cidev)) {	// for power restart
		LOG_CIS_ERR("  * power_restart detected\n");
		return -EFAULT;
	}

	memset((void *)cis_buf, 0x00, CIS_TPL_BUF_SIZE);

	return 0;
}

static int ci_hw_analysis_tuple(CI_DEV_T *cidev,
								int chk_cnt,
								u32 initial_sleep_time)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
//	cis_config_t *cis_config = &cis_info->info_config;
	cis_status_t *cis_status = &cis_info->info_status;
	char *cis_buf = NULL;
	u32 offset = 0;
	int count = 0;
	int retry_cnt = 0;
	int sleep_time = initial_sleep_time;
	int ret = 0;
	int t_ret = 0;
//	u32	cis_addr_limit = cidev->config->cis_addr_limit;

	cis_buf = (u8 *)ci_malloc(CIS_TPL_BUF_SIZE);
	if (cis_buf == NULL) {
		LOG_ERROR("unable to allocate cis_buf\n");
		return -ENOMEM;
	}

	while (1) {
		offset = 0;
		cis_status->parse_count = 0;
		count = chk_cnt;

		cis_status->status_vers_1 = DATA_NOT_AVAILABLE;
		cis_status->status_config = DATA_NOT_AVAILABLE;
		cis_status->status_cftable  = DATA_NOT_AVAILABLE;

		while (count--) {
			t_ret = _ci_hw_analysis_read_tuple(cidev, cis_buf, &offset, sleep_time);
			if ((t_ret == TUPLE_END) || (t_ret == TUPLE_LAST)) {
				break;
			}
			else if (t_ret != 0) {
				LOG_ERROR("Error in read_tuple");
				ret = t_ret;
				goto out;
			}

			t_ret = _ci_hw_analysis_parse_tuple(cidev, cis_buf, offset);
			if ((t_ret == TUPLE_END) || (t_ret == TUPLE_LAST)) {
				break;
			}
			else if (t_ret != 0) {
				LOG_ERROR("Error in parse_tuple");
				ret = t_ret;
				goto out;
			}
		}

		if (ci_chk_compliance(cis_status) == DVB_CI_COMPLIANT) {
			LOG_CIS_INFO("CIS configuration SUCCESS\n" );
			ret = 0;
			goto out;
		}

		// if the abnormal case, the try again (max 3, delay time is changed)
		if (++retry_cnt >= MAX_DELAY_TRY) {
			LOG_ERROR("CIS configuration FAILED #2\n" );
			ret = -EFAULT;
			goto out;
		}

		LOG_ERROR("  * Again get CIS configuration (%d try)\n", retry_cnt);
		sleep_time = SLEEP_VALUE_INC * retry_cnt;
	//	sleep_time += 100;

	//	ci_pcap_mon_cis_hdr(cidev, 1);	//cancel
		ci_pcap_mon_cis_pkt(cidev);		//save
		ci_pcap_mon_cis_hdr(cidev, 0);	//re-start

	//	cis_info->rcnt_analysis = 0;
	}

out:
	cis_info->retry = retry_cnt;
	ci_free(cis_buf);
	return ret;
}

static void _ci_hw_check_cis_pre(CI_DEV_T *cidev)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;

	ci_hw_reset_cis_info(cidev);

	cis_info->cis_step = CIS_CHECK_STEP_START;
	cis_info->start_t = ktime_get();
	cis_info->end_1st_t = ktime_add(cis_info->end_1st_t, cis_info->start_t);
	cis_info->end_last_t = ktime_add(cis_info->end_last_t, cis_info->start_t);

	ci_pcap_mon_cis_hdr(cidev, 0);

	LOG_CIS_INFO("Configuring CIS of %s\n", ci_dev_name(cidev));
	LOG_CIS_INFO("baseAddr: 0x%p \n", cidev->mod_addr);
}

/**
 * @brief
 *   core bridge function : Check CIS
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *  cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CIS_CheckCIS(CI_DEV_T *cidev)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	int chk_cnt;
	int delay_ok, delay_ng, delay_initial;
	int ret = 0;

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* detect & init */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");

	CI_OPS_SetHWMode(cidev, CHIP_MODE_ATTR, POD_MODE );

	if (ci_is_power_restart(cidev)) { // for power restart
		LOG_ERROR("power_restart detected\n");
		LOG_ERROR("Check CIS <<F>>");
		return -EFAULT;
	}

	mutex_lock(&cidev->access_mutex);
	if(!cidev->power_on)
	{
		mutex_unlock(&cidev->access_mutex);

		LOG_ERROR("VCC Power Off");
		LOG_ERROR("Check CIS <<F>>");
		return -EFAULT;
	}

	_ci_hw_check_cis_pre(cidev);

	chk_cnt = ci_get_delay_param(cidev, DELAY_MAX_COUNT_CIS_CHK);
	delay_ok = ci_get_delay_param(cidev, DELAY_CIS_CONFIG_FIRST_TUPLE_OK);
	delay_ng = ci_get_delay_param(cidev, DELAY_CIS_CONFIG_FIRST_TUPLE_NG);
	delay_initial = ci_get_delay_param(cidev, DELAY_CIS_END_READ_TUPLE_INITIAL);

	/* STEP 1 : check whether the first tuple is valid -----------------------*/
	/* the basic purpose of this checking is to check whether the module is
	   really ready.
	   note that some module is not ready even after asserting RDY signal. */
	ret = ci_hw_check_1st_tuple(cidev, chk_cnt, delay_ok, delay_ng);
	if (ret != 0) {
		goto out;
	}

	cis_info->cis_step = CIS_CHECK_STEP_1ST_DONE;
	cis_info->end_1st_t = ktime_get();

	/* STEP 2 : read & analyze CIS tuples ------------------------------------*/
	ret = ci_hw_analysis_tuple(cidev, chk_cnt, delay_initial);
	if (ret != 0) {
		ret = -EFAULT;
		goto out_2nd;
	}

	cis_info->cis_step = CIS_CHECK_STEP_LAST_DONE;
	cis_info->end_last_t = ktime_get();

	ci_pcap_mon_cis_pkt(cidev);

	ci_is_cam_cis_done(cidev) = 1;

	mutex_unlock(&cidev->access_mutex);

	LOG_INFO("Check CIS <<S>>");
	return 0;

out_2nd:
	cis_info->end_last_t = ktime_get();

out:
	ci_pcap_mon_cis_hdr(cidev, 1);

	mutex_unlock(&cidev->access_mutex);
	LOG_ERROR("Check CIS <<F>>");
	return ret;
}


int CI_CIS_GetCISString(CI_DEV_T *cidev, UINT8 tuple, UINT8 *len, UINT8 *buf, UINT8 maxlen)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_status_t *cis_status = &cis_info->info_status;
	cis_vers_1_t *vers_1 = &cis_info->info_vers_1;

	/* detect & init & CIS */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");
	CHECK_ERROR(!ci_is_cam_cis_done(cidev), return -EFAULT, "[ CAM CIS-Check not completed <<F>> ]");

	/* tuple check */
	CHECK_ERROR(tuple != CISTPL_VERS_1, return -EFAULT, "tuple:0x%02x is not supported", tuple);
	CHECK_ERROR(cis_status->status_vers_1 != DVB_CI_COMPLIANT, return -EFAULT, "CISTPL not parsed");

	if(maxlen >= vers_1->len)
	{
		memcpy(buf, vers_1->raw, vers_1->len);
		*len = vers_1->len;
	}
	else
	{
		LOG_WARNING("maxlen[%d] < actual len[%d], partially copied", maxlen, vers_1->len);
		memcpy(buf, vers_1->raw, maxlen);
		*len = maxlen;
	}

	return 0;
}

/**
 * @brief
 *  core bridge function : COR Write
 * @remarks
 *  DETAIL INFORMATION
 * @par requirements:
 *
 * @param
 *   cidev :pointer of ci device structure
 * @return
 *  int
 */
int CI_CIS_WriteCOR(CI_DEV_T *cidev)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_config_t *cis_config = &cis_info->info_config;
	cis_cftable_entry_t *cis_cftable = &cis_info->info_cftable;
#ifdef POD_ON_INIT
	UINT8 read_data;
#else
	u16 read_data;
#endif

	CHECK_ERROR(!cidev, return -EFAULT, "cidev is NULL");

	/* detect & init & CIS */
	CHECK_ERROR(!ci_is_card_detected(cidev), return -ENODEV, "[ CAM not inserted <<F>> ]");
	CHECK_ERROR(!ci_is_cam_init_done(cidev), return -EFAULT, "[ CAM Init not completed <<F>> ]");
	CHECK_ERROR(!ci_is_cam_cis_done(cidev), return -EFAULT, "[ CAM CIS-Check not completed <<F>> ]");

#ifdef POD_ON_INIT
	CI_OPS_SetHWMode(cidev, CHIP_MODE_ATTR, POD_MODE);
#else
	CI_OPS_SetHWMode(cidev, CHIP_MODE_ATTR, INIT_VAL);
#endif

	mutex_lock(&cidev->access_mutex);
	if(!cidev->power_on)
	{
		mutex_unlock(&cidev->access_mutex);

		LOG_ERROR("VCC Power Off");
		LOG_ERROR("Write COR <<F>>");

		return -EFAULT;
	}

#ifdef POD_ON_INIT
	CICAM_WRITE8(cidev, CIS_CFTABLE_ENTRY_NUM(cis_cftable->idx), (cis_config->base_addr << 1));
	read_data = CICAM_READ8(cidev, (cis_config->base_addr << 1));
#else
	CICAM_WRITE16(cidev, CIS_CFTABLE_ENTRY_NUM(cis_cftable->idx), cis_config->base_addr);
	read_data = CICAM_READ16(cidev, cis_config->base_addr);
#endif
	LOG_CIS_INFO("cor : cftable->idx[0x%04X], config->base_addr[0x%04X]",
			cis_cftable->idx, cis_config->base_addr);

	ci_pcap_mon_cor_pkt(cidev, cis_config->base_addr, read_data);

	ci_sleep(ci_get_delay_param(cidev, DELAY_CIS_END_WRITE_COR));

	cis_info->cor_step = COR_WRITE_STEP_DONE;

	ci_is_cam_cor_done(cidev) = 1;

	mutex_unlock(&cidev->access_mutex);

	LOG_INFO("Write COR <<S>>\n");
	return 0;
}

