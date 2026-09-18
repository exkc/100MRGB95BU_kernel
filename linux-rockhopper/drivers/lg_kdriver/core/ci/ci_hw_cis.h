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
 *  CI register details. ( used only within kdriver )
 *
 *  @author		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  @author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  @author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  @author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  @version	1.0
 *  @date		2015.1.1
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef __CI_HW_CIS_H__
#define __CI_HW_CIS_H__

#include <linux/types.h>
#include "base_types.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Max count for nonvalid tuples */
#define MAX_TUPLE_COUNT_ERR		300

/* tuple code */
#define CISTPL_VERS_1			0x15
#define CISTPL_CONFIG			0x1A
#define CISTPL_CFTABLE_ENTRY	0x1B
#define CISTPL_DEVICE_OC		0x1C
#define CISTPL_DEVICE_OA		0x1D
#define CISTPL_MANFID			0x20
#define CISTPL_DEVICE			0x01
#define CISTPL_DEVICE_A			0x17
#define CISTPL_DEVICE_TEMP		0x24

#define CISTPL_NO_LINK			0x14
#define CISTPL_END				0xFF
#define CISTPL_LINK_END			0xFF

/* sub-tuple code */
#define CFGST_CIF				0xC0
#define CCST_TERMINATE			0xFF
#define STCE_EV					0xC0
#define STCE_PD					0xC1

/* DVB-CI compliant information */

#define	TPLLV1_MAJOR			0x05	// in CISTPL_VERS_1
#define	TPLLV1_MINOR			0x00	// in CISTPL_VERS_1
#define	TPCC_RADR_MAX			0x0FFE	// in CISTPL_CONFIG
#define	DVB_CI_COMPLIANT_IFN	0x0241	// in CISTPL_CONFIG-CCST_CIF
#define TPCE_IF					0x04	// in CISTPL_CFTABLE_ENTRY
#define TPCE_IO					0x22	// in CISTPL_CFTABLE_ENTRY

/* return value */
#define	CIS_OK					0
#define	CIS_FAIL				(-1)
#define	CIS_PARSETIMEOUT		(-2)

/* CIS tuple data bit definition */
#define	EXT_BIT					0x80
/* CISTPL_CONFIG */
#define	TPCC_RASZ_MASK			0x03
#define	TPCC_RMSZ_MASK			0x3c
#define	TPCC_RFSZ_MASK			0xc0
#define CONFIG_OPTION_BIT		0x01
#define	CONFIG_STATUS_BIT		0x02
#define	PIN_REPLACE_BIT			0x04
#define SOCKET_COPY_BIT			0x08
#define	EXT_STATUS_BIT			0x10
#define	IO_BASE0_BIT			0x20
#define	IO_BASE1_BIT			0x40
#define	IO_BASE2_BIT			0x80
#define	IO_BASE3_BIT			0x01
#define	IO_LIMIT_BIT			0x02
#define PWR_MANSUP_BIT			0x04
#define	TPCE_FS_MISC_BIT		0x80
#define TPCE_FS_MEMSP_BIT		0x60
#define	TPCE_FS_IRQ_BIT			0x10
/* CISTPL_CFTABLE_ENTRY */
#define	TPCE_INDX_IF_BIT		0x80
#define	TPCE_INDX_DEF_BIT		0x40
#define	TPCE_FS_IOSP_BIT		0x08
#define TPCE_FS_TIME_BIT		0x04
#define	TPCE_FS_POWER_BIT		0x03
/* POWER description structure */
#define	PWR_PDWNI_BIT			0x40
#define	PWR_PEAKI_BIT			0x20
#define	PWR_AVRGI_BIT			0x10
#define	PWR_STATI_BIT			0x08
#define	PWR_MAXV_BIT			0x04
#define	PWR_MINV_BIT			0x02
#define PWR_NOMV_BIT			0x01
/* CISTPL_DEVICE_OA & OC */
#define	VCC_5V					0
#define	VCC_3V3					1
#define VCC_XVX					2  //VCC_xVx (x may be constant)
#define	VCC_CB					3
#define	DTYPE_NULL				0x0
#define	DTYPE_ROM				0x1
#define	DTYPE_OTPROM			0x2
#define	DTYPE_EPROM				0x3
#define	DTYPE_EEPROM			0x4
#define	DTYPE_FLASH				0x5
#define	DTYPE_SRAM				0x6
#define	DTYPE_DRAM				0x7
#define	DTYPE_FUNCSPEC			0xd
#define	DTYPE_EXTEND			0xe
#define	DSPEED_NULL				0x0
#define	DSPEED_250NS			0x1
#define DSPEED_200NS			0x2
#define	DSPEED_150NS			0x3
#define	DSPEED_100NS			0x4
#define	DSPEED_EXT				0x7
#define	SP_MAN1_0				0x1
#define	SP_MAN1_2				0x2
#define	SP_MAN1_3				0x3
#define	SP_MAN1_5				0x4
#define	SP_MAN2_0				0x5
#define	SP_MAN2_5				0x6
#define	SP_MAN3_0				0x7
#define	SP_MAN3_5				0x8
#define	SP_MAN4_0				0x9
#define	SP_MAN4_5				0xa
#define	SP_MAN5_0				0xb
#define	SP_MAN5_5				0xc
#define	SP_MAN6_0				0xd
#define	SP_MAN7_0				0xe
#define	SP_MAN8_0				0xf
#define	SP_1_NANO_SEC			0x0
#define	SP_10_NANO_SEC			0x1
#define	SP_100_NANO_SEC			0x2
#define	SP_1_MICRO_SEC			0x3
#define	SP_10_MICRO_SEC			0x4
#define	SP_100_MICRO_SEC		0x5
#define	SP_1_MILI_SEC			0x6
#define	SP_10_MILI_SEC			0x7
#define _512B					0x0
#define _2KB					0x1
#define _8KB					0x2
#define _32KB					0x3
#define _128KB					0x4
#define _512KB					0x5
#define _2MB					0x6
/* CISTPL_VERS_1 */
#define	PCSTAND_FEB95			0x0500
#define	PCMCIA2_X				0x0401
#define	PCMCIA1_0				0x0400
/* CISTPL_CFTABLE_ENTRY */
#define	MEMORY					0x0
#define	IO_MEMORY				0x1
#define	CUSTOM_IF0				0x4
#define	CUSTOM_IF1				0x5
#define	CUSTOM_IF2				0x6
#define	CUSTOM_IF3				0x7
#define	VCC_ONLY				0x01
#define	VCC_VPP					0x02
#define	VCC_VPP_12				0x03
#define	SGL2					0x01
#define	LNG2CADDR2				0x02
#define	MEMSP_DES				0x03
#define	PWR_MAN1_0				0x0
#define	PWR_MAN1_2				0x1
#define	PWR_MAN1_3				0x2
#define	PWR_MAN1_5				0x3
#define	PWR_MAN2_0				0x4
#define	PWR_MAN2_5				0x5
#define	PWR_MAN3_0				0x6
#define	PWR_MAN3_5				0x7
#define	PWR_MAN4_0				0x8
#define	PWR_MAN4_5				0x9
#define	PWR_MAN5_0				0xa
#define	PWR_MAN5_5				0xb
#define	PWR_MAN6_0				0xc
#define	PWR_MAN7_0				0xd
#define	PWR_MAN8_0				0xe
#define	PWR_MAN9_0				0xf
#define	PWR_100_NANO_A			0x0
#define	PWR_1_MICRO_A			0x1
#define	PWR_10_MICRO_A			0x2
#define	PWR_100_MICRO_A			0x3
#define	PWR_1_MILI_A			0x4
#define	PWR_10_MILI_A			0x5
#define	PWR_100_MILI_A			0x6
#define	PWR_1_A					0x7
#define	PWR_10_MICRO_V			0x0
#define	PWR_100_MICRO_V			0x1
#define	PWR_1_MILI_V			0x2
#define	PWR_10_MILI_V			0x3
#define	PWR_100_MILI_V			0x4
#define	PWR_1_V					0x5
#define	PWR_10_V				0x6
#define	PWR_100_V				0x7
#define	IO_8BIT					0x1
#define	IO_16BIT				0x2
#define	IO_BOTH					0x3
#define DEVICE_OAOC_STORAGE_MAX		1

/* tuple buffer size */
#define	CIS_TPL_BUF_SIZE		257 // maximum possible tuple length

#define	CIS_AM_STEP				0x00000004
#define	CIS_AM_STEP16			0x00000002			//for 16bit burst mode

/* CIS_ReadTuple function return value */
#define	TUPLE_NOT_END			0
#define	TUPLE_END				1
#define	TUPLE_LAST				2
#define	TUPLE_INT				3					// for ISR

/* Delay value */
#define SLEEP_VALUE_INIT		20
#define SLEEP_VALUE_INC			200	//160
#define MAX_DELAY_TRY			4

#define VERS_1_INFO_LEN			40
#define CCST_CIF_STRING_LENGTH	20

#define CIS_CFTABLE_ENTRY_NUM(_idx)		((_idx) & 0x3F)

#define feat_flag_power(_feat)		(((_feature_flag *)(&(_feat->b_flag)))->b_power)
#define feat_flag_time(_feat)		(((_feature_flag *)(&(_feat->b_flag)))->b_time)
#define feat_flag_io_space(_feat)	(((_feature_flag *)(&(_feat->b_flag)))->b_io_space)
#define feat_flag_irq(_feat)		(((_feature_flag *)(&(_feat->b_flag)))->b_irq)
#define feat_flag_mem_space(_feat)	(((_feature_flag *)(&(_feat->b_flag)))->b_mem_space)
#define feat_flag_misc(_feat)		(((_feature_flag *)(&(_feat->b_flag)))->b_misc)

enum {
	DVB_CI_COMPLIANT		= 0,
	DVB_CI_NOT_COMPLIANT	= 1,
	DATA_AVAILABLE			= 2,
	DATA_NOT_AVAILABLE		= 3,
};

enum {
	CIS_CHECK_STEP_NONE		= 0,
	CIS_CHECK_STEP_START,
	CIS_CHECK_STEP_1ST_DONE,
	CIS_CHECK_STEP_LAST_DONE,
	CIS_CHECK_STEP_MAX
};

enum {
	COR_WRITE_STEP_NONE		= 0,
	COR_WRITE_STEP_DONE,
	COR_WRITE_STEP_MAX
};

/**
 *	tuple(VERS_1) information structure
 */
struct cis_vers_1 {
	u8		major;
	u8		minor;
	u8		manufact[VERS_1_INFO_LEN];
	u8		product[VERS_1_INFO_LEN];
	u8		add1[VERS_1_INFO_LEN];
	u8		add2[VERS_1_INFO_LEN];
	u8		is_ci_plus;
	u8		is_checked;
	u8		raw[CIS_TPL_BUF_SIZE];
	u8		len;
	u32		version;
	u32		profile;
};
typedef struct cis_vers_1 cis_vers_1_t;

/**
 *	tuple(CCST_CIF) information structure
 */
struct cis_ccst_cif {
	u16		if_id_num;
	u16		if_id_num_base;
	u8		str[CCST_CIF_STRING_LENGTH]; // 20 bytes
//	u8		dummy[2];
};
typedef struct cis_ccst_cif cis_ccst_cif_t;

/**
 *	tuple(CONFIG) information structure
 */
struct cis_config {
	u8				size;
	u8				last_index;
	u16				mask;
	//
	u32				base_addr;
	//
	u8 				tpcc_rfsz;
	u8				tpcc_rmsz;
	u8				tpcc_rasz;
	u8				rsvd;
	//
	cis_ccst_cif_t	ccst_cif;
};
typedef struct cis_config cis_config_t;

/**
 *	tuple(PWR_DESCRIPT) information structure
 */
struct pwr_descript {
	u8		pwr_sel;
	u8		nom_v;
	u8		nom_v_x;
	u8		min_v;
	u8		min_v_x;
	u8		max_v;
	u8		max_v_x;
	u8		stat_i;
	u8		stat_i_x;
	u8		avrg_i;
	u8		avrg_i_x;
	u8		peak_i;
	u8		peak_i_x;
	u8		pdwn_i;
	u8		pdwn_i_x;
	u8		dummy;
};
typedef struct pwr_descript pwr_descript_t;

typedef struct __feature_flag {
	u32		b_power				:2,
			b_time				:1,
			b_io_space			:1,
			b_irq				:1,
			b_mem_space			:2,
			b_misc				:1,
			//
			rsvd08				:1,
			rsvd09				:1,
			rsvd0A				:1,
			rsvd0B				:1,
			rsvd0C				:1,
			rsvd0D				:1,
			rsvd0E				:1,
			rsvd0F				:1,
			//
			_rsvd				:(32-16);
} _feature_flag;

/**
 *	tuple(CFTABLE_ENTRY) information structure
 */
struct cis_cftable_feature {
	u8		time;
	u8		io_space;
	u8		irq;
	u8		mem_space;
	/* */
	u8		misc;
	u8		dummy[3];
	/* */
	u32		b_flag;
};
typedef struct cis_cftable_feature cis_cftable_feature_t;

/*
 * tuple(STCE_EVPD) information structure
 */
struct cis_stce_evpd {
	u8		environment[10];
	u8		physical_dev[20];
};
typedef struct cis_stce_evpd cis_stce_evpd_t;

struct cis_cftable_entry {
	u8		idx;
	u8		intf;
	u8		feature;
	u8		dummy;
	/* */
	cis_cftable_feature_t feat;
	/* */
	pwr_descript_t	pwr_info_field[3];
	/* */
	cis_stce_evpd_t	stce_evpd;
};
typedef struct cis_cftable_entry cis_cftable_entry_t;


/**
 *	tuple status structure
 */
struct cis_status {
	int		parse_count;
	int		status_vers_1;
	int		status_config;
	int		status_cftable;
};
typedef struct cis_status cis_status_t;

struct ci_dev_cis_info
{
	ktime_t					start_t;
	ktime_t					end_1st_t;
	ktime_t					end_last_t;
	int						rcnt_1st_det;
	int						rcnt_analysis;
	int						retry;
	int						cis_step;
	int						cor_step;
	/* */
	cis_vers_1_t			info_vers_1;
	cis_config_t			info_config;
	cis_cftable_entry_t		info_cftable;
	cis_status_t			info_status;
};
typedef struct ci_dev_cis_info ci_dev_cis_info_t;

static inline int ci_chk_compliance(cis_status_t *cis_status)
{
	if ((cis_status->status_vers_1 == DVB_CI_COMPLIANT) &&
		(cis_status->status_config == DVB_CI_COMPLIANT) &&
		(cis_status->status_cftable == DVB_CI_COMPLIANT))
	{
		return DVB_CI_COMPLIANT;
	}
	return -1;
}

static inline void ci_hw_reset_cis_info(CI_DEV_T *cidev)
{
	memset((void *)cidev->cis_info, 0x00, sizeof(ci_dev_cis_info_t));
}

static inline void ci_hw_cis_set_chk_state(CI_DEV_T *cidev, int state)
{
	ci_dev_cis_info_t *cis_info = cidev->cis_info;
	cis_vers_1_t *cis_vers_1 = &cis_info->info_vers_1;

	cis_vers_1->is_checked = state;
}

int CI_CIS_CheckCIS(CI_DEV_T *cidev);
int CI_CIS_WriteCOR(CI_DEV_T *cidev);

int CI_CIS_GetCISString(CI_DEV_T *cidev, UINT8 tuple, UINT8 *len, UINT8 *buf, UINT8 maxlen);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* __CI_HW_CIS_H__ */

