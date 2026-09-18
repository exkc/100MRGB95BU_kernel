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
 *  main configuration file for ci device
 *	ci device will teach you how to make device driver with new platform.
 *
 *  author 		Srinivasan Shanmugam (srinivasan.shanmugam@lge.com)
 *  author		Hwajeong Lee (hwajeong.lee@lge.com)
 *  author		Jinhwan Bae (jinhwan.bae@lge.com) - modifier
 *  author		Hyunho Kim (hyunho747.kim@lge.com) - modifier
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_ci
 *	@{
 */

#ifndef	_CI_CFG_H_
#define	_CI_CFG_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
//#define SUPPORT_CI_DEVICE_READ_WRITE_FOPS

//#define CI_ENABLE_ERR	/* it is recommended to enable this always */
//#define CI_ENABLE_INFO
//#define CI_ENABLE_DBG_INFO
//#define CIS_ENABLE_INFO
//#define CIS_ENABLE_TUPLE_DUMP
//#define CIS_ENABLE_PARSE_DUMP
//#define CI_IO_ENABLE_INFO
//#define CI_IO_DUMP
//#define CI_DEBUG_PRINT_ON
//#define CI_IO_DELAY_PRINT
//#define CI_IO_TIME_PRINT
//#define CI_BUILD_TIME_PRINT
//#define CI_MON_FR_RETRY
//#define CI_KERN_LOG
//#define CI_DATA_TEST_ON

#define CI_POL_CHECK_ON
#define CI_OPT_CHK_MODE

//#define CI_CIS_ADDR_LIMIT

#define CI_OS_PROC_BASE
#define CI_PROC_PCAP_ON


/* Delay definitions */
#define	DEFAULT_CI_DELAY_CIS_CONFIG_FIRST_TUPLE_OK 				5

/* 20131021 jinhwan.bae
    changed from 10 to 12. after changing delay function from msleep to usleep_range,
    IPP SMARDTV SmartCAM-3 CI+ Reference Module fail to Check CIS.
    After change this delay from 10 to 11, working well, but consider margin, set to 12*/
// #define	DEFAULT_CI_DELAY_CIS_CONFIG_FIRST_TUPLE_NG 				10
#define	DEFAULT_CI_DELAY_CIS_CONFIG_FIRST_TUPLE_NG 				12

#define	DEFAULT_CI_DELAY_CIS_END_WRITE_COR						100
#define	DEFAULT_CI_DELAY_CIS_DURING_READ_TUPLE					5
/* 20141007 hyunho747.kim
   changed from 20 to 160.
   Some CAMs require bigger delay between tuple blocks
   because they might transfer partialy wrong tuple data
   : CONAX CAM  (SN : 7060104300000025, Pairing ID : 005-8201-2102, Test 22 / SMiT)
   : STRONG CAM (SN : 7061120200001557, Pairing ID : 005-8217-5606, NO_07 / RisksTV)
*/
/* 20141013 hyunho747.kim
   changed from 160 to 200.
   Without log display, it required at least 200ms delay for this CAM
   : CONAX CAM  (SN : 7060104300000025, Pairing ID : 005-8201-2102, Test 22 / SMiT)
*/
/* 20141104 hyunho747.kim
   changed from 200 to 20 (back to the original value)
   Too long CIS time(http://hlm.lge.com/issue/browse/NEWCERT-491) issue
*/
#define	DEFAULT_CI_DELAY_CIS_END_READ_TUPLE_INITIAL				20
#define	DEFAULT_CI_DELAY_CIS_PARSE_NON_CI_TUPLE					3
#define	DEFAULT_CI_DELAY_INIT_POWER_CONTROL						5		// H13 Blocked in Routine, L9 5
#define	DEFAULT_CI_DELAY_INIT_AFTER_INTERRUPT_ENABLE			10
#define	DEFAULT_CI_DELAY_CAM_INIT_BTW_VCC_CARDRESET				300
#define	DEFAULT_CI_DELAY_CAM_INIT_BTW_CARDRESET_NOTRESET		20     // 5 -> 20 for gives more margine in reset toggle
#define	DEFAULT_CI_DELAY_CAM_INIT_BTW_CARDRESET_EN_PCCARD		80     // for CE(Card Enable, Enable PC Card)
#define	DEFAULT_CI_DELAY_IO_SOFT_RESET_CHECK_FR					10
#define	DEFAULT_CI_DELAY_IO_END_SOFT_RESET						0		// L9 Blocked, 0 Originally (10)
#define	DEFAULT_CI_DELAY_IO_NEGOBUF_BEFORE_SOFTRESET			0		// L9 Blocked, 0 Originally (100)
#define	DEFAULT_CI_DELAY_IO_NEGOBUF_CHECK_DA					10
#define	DEFAULT_CI_DELAY_IO_NEGOBUF_CHECK_FR					10
#define	DEFAULT_CI_DELAY_IO_NEGOBUF_AFTER_WRITE_DATA			5		// L9 Final 5, L9 Previously (10)
#define	DEFAULT_CI_DELAY_IO_READ_CHECK_DA						10
#define	DEFAULT_CI_DELAY_IO_WRITE_CHECK_DA						10
#define	DEFAULT_CI_DELAY_IO_WRITE_CHECK_FR						10
#define	DEFAULT_CI_DELAY_IO_WRITE_FIRST_BYTE_STAT_RD_FR_WE		10
#define	DEFAULT_CI_DELAY_IO_WRITE_MIDDLE_BYTE_CHECK_WE			10
#define	DEFAULT_CI_DELAY_IO_WRITE_LAST_BYTE_CHECK_WE			10

#define MAX_CHECK_COUNT		500
#define MAX_VALID_TUPLE_CNT_CHK	260
#define	MAXIM_RETRY_COUNT	600

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define	CI_MODULE			"ci"
//#define CI_MAX_DEVICE		1
enum _CI_IDX {
	CI_DEV_0 		= 0,
	CI_MAX_DEVICE,
};


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define OK			 0
#define NOT_OK		-1

#define COMMON_CS_BASE			(0xD0000000)
#define COMMON_CS2_BASE			(COMMON_CS_BASE+0x8000000)
#define COMMON_DVBCI_BASE		(COMMON_CS2_BASE+0x0)
#define COMMON_CI_REG_BASE		(COMMON_DVBCI_BASE + 0x10000)
#define COMMON_CI_CAM_BASE		(COMMON_DVBCI_BASE)

#define CI_SMC_BASE				0xFF400038
#define CI_SMC_SIZE				0x1C

#ifndef O18_IRQ_DVB_CI
#define O18_IRQ_DVB_CI			(32 + 25)
#endif

#ifndef M19_IRQ_DVB_CI
#define M19_IRQ_DVB_CI			(32 + 25)
#endif

#ifndef O20_IRQ_DVB_CI
#define O20_IRQ_DVB_CI			(32 + 25)
#endif

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
enum
{
	DELAY_CIS_CONFIG_FIRST_TUPLE_OK = 0,
	DELAY_CIS_CONFIG_FIRST_TUPLE_NG,
	DELAY_CIS_END_WRITE_COR,
	DELAY_CIS_DURING_READ_TUPLE,
	DELAY_CIS_END_READ_TUPLE_INITIAL,
	DELAY_CIS_PARSE_NON_CI_TUPLE,
	DELAY_INIT_POWER_CONTROL,
	DELAY_INIT_AFTER_INTERRUPT_ENABLE,
	DELAY_CAM_INIT_VCC_CARD_RESET,
	DELAY_CAM_INIT_CARD_RESET_NOT_RESET,
	DELAY_CAM_INIT_CARD_RESET_EN_PCCARD,
	DELAY_IO_SOFT_RESET_CHECK_FR,
	DELAY_IO_END_SOFT_RESET,
	DELAY_IO_NEGO_BUFF_BEFORE_SOFT_RESET,
	DELAY_IO_NEGO_BUFF_CHECK_DA,
	DELAY_IO_NEGO_BUFF_CHECK_FR,
	DELAY_IO_NEGO_BUFF_AFTER_WRITE_DATA,
	DELAY_IO_READ_CHECK_DA,
	DELAY_IO_WRITE_CHECK_DA,
	DELAY_IO_WRITE_CHECK_FR,
	DELAY_IO_WRITE_1ST_BYTE_STAT_RD_FR_WE,
	DELAY_IO_WRITE_MIDDLE_BYTE_CHECK_WE,
	DELAY_IO_WRITE_LAST_BYTE_CHECK_WE,
	/* */
	DELAY_MAX_COUNT_R_PRE,
	DELAY_MAX_COUNT_R,
	DELAY_MAX_COUNT_W_PRE,
	DELAY_MAX_COUNT_W,
	DELAY_MAX_COUNT_DIV,
	DELAY_MAXIM_RETRY_CNT,
	/* */
	DELAY_MAX_COUNT_CIS_CHK,
	DELAY_ENTRY_MAX,
};


typedef struct
{
	int		irq_num;
	UINT32	smc_phys_addr;
	UINT32	smc_phys_size;

	UINT32	reg_base;
	UINT32	reg_size;
	UINT32	mod_base;
	UINT32	mod_size;

	UINT32	cis_addr_limit;

	UINT32	delays[DELAY_ENTRY_MAX];

	UINT8	smc_need_vcc;
} CI_CFG_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void CI_CFG_PreInit(void);
CI_CFG_T* CI_GetConfig(void);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _CI_CFG_H_ */

/** @} */

