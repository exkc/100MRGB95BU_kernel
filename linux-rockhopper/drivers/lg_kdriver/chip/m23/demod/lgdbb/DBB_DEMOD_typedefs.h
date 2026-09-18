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

/*****************************************************************************
**
**  Name:DBB_DEMOD_typedefs.h
**
**  Description:    .
**
**  Functions
**  Implemented:
**
**  References:
**
**  Exports:
**
**  Dependencies:
**
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   20-01-2016  Jeongpil Yun    Initial draft.
**
*****************************************************************************/
#ifndef   _DBB_DEMOD_TYPEDEFS_H_
#define   _DBB_DEMOD_TYPEDEFS_H_

#define DEMOD_CHIP_ID			0xB2

#define DEMOD_CHIP_O18 LX_CHIP_O18
#define DEMOD_CHIP_M19 LX_CHIP_M19
#define DEMOD_CHIP_O20 LX_CHIP_O20
#define DEMOD_CHIP_E60 LX_CHIP_E60
#define DEMOD_CHIP_O22 LX_CHIP_O22
#define DEMOD_CHIP_M23 LX_CHIP_M23

/* time spend check */
//#define DEMOD_SPEND_TIME_CHECK
/* demod priority increse to reduce fw init time */
//#define DEMOD_FW_INIT_BOOST

#define DEMOD_PLATFORM_UNKNOWN	0
#define DEMOD_PLATFORM_XTENSA	1
#define DEMOD_PLATFORM_KDRV	2
#define DEMOD_PLATFORM_GUI	3
#define DEMOD_PLATFORM_EXT	4

#define DEMOD_COMM_UNKNOWN	0
#define DEMOD_COMM_APB		1
#define DEMOD_COMM_I2C		2
#define DEMOD_COMM_FPGA		3

#if !defined(DEMOD_PLATFORM)
#if defined(__XTENSA__)
#define DEMOD_PLATFORM	DEMOD_PLATFORM_XTENSA
#define DEMOD_COMM		DEMOD_COMM_APB
#elif defined(__linux__)
#if defined(__KERNEL__)
#define DEMOD_PLATFORM	DEMOD_PLATFORM_KDRV
#if defined(DEMOD_CONFIG_CROSS_PLATFORM)
#define DEMOD_COMM		DEMOD_COMM_I2C
#else
#define DEMOD_COMM		DEMOD_COMM_APB
#endif
#else
#define DEMOD_PLATFORM	DEMOD_PLATFORM_EXT
#define DEMOD_COMM		DEMOD_COMM_I2C
#endif
#elif defined(_WIN32)
#if defined(EVAL_FPGA)
#define DEMOD_PLATFORM	DEMOD_PLATFORM_GUI
#define DEMOD_COMM		DEMOD_COMM_FPGA
#elif defined(EVAL_GUI)
#define DEMOD_PLATFORM	DEMOD_PLATFORM_GUI
#define DEMOD_COMM		DEMOD_COMM_I2C
#else
#define DEMOD_PLATFORM	DEMOD_PLATFORM_EXT
#define DEMOD_COMM		DEMOD_COMM_I2C
#endif
#endif
#endif

#if !defined(DEMOD_CHIP)
#if defined(DEMOD_CHIP_NAME_m23)
#define DEMOD_CHIP	DEMOD_CHIP_M23
#elif defined(DEMOD_CHIP_NAME_o22)
#define DEMOD_CHIP	DEMOD_CHIP_O22
#elif defined(DEMOD_CHIP_NAME_e60)
#define DEMOD_CHIP	DEMOD_CHIP_E60
#elif defined(DEMOD_CHIP_NAME_o20)
#define DEMOD_CHIP	DEMOD_CHIP_O20
#elif defined(DEMOD_CHIP_NAME_m19)
#define DEMOD_CHIP	DEMOD_CHIP_M19
#elif defined(DEMOD_CHIP_NAME_o18)
#define DEMOD_CHIP	DEMOD_CHIP_O18
#else
#if (DEMOD_PLATFORM != DEMOD_PLATFORM_XTENSA)
#error "DEMOD_CHIP not defined"
#endif
#endif
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include "demod_impl.h"
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
//#include <sdkddkver.h>
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#ifndef SINT8
typedef char 									SINT8;
#endif
#ifndef UINT8
typedef unsigned char 							UINT8;
#endif
#ifndef SINT16
typedef short 									SINT16;
#endif
#ifndef UINT16
typedef unsigned short 							UINT16;
#endif
#ifndef SINT32
typedef int 									SINT32;
#endif
#ifndef UINT32
//typedef unsigned int 							UINT32;
#endif
#ifndef SINT64
typedef long long 								SINT64;
#endif
#ifndef UINT64
typedef unsigned long long 						UINT64;
#endif
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
typedef char 									SINT8;
typedef unsigned char 							UINT8;
typedef short 									SINT16;
typedef unsigned short 							UINT16;
typedef int 									SINT32;
typedef unsigned int 							UINT32;
typedef long long 								SINT64;
typedef unsigned long long 						UINT64;
#endif

#ifndef TRUE
#define TRUE									( 1)
#endif
#ifndef FALSE
#define	FALSE									( 0)
#endif
#ifndef RET_OK
#define RET_OK									( 0)
#endif
#ifndef RET_ERROR
#define RET_ERROR								(-1)
#endif
#ifndef IDX_TO_ADDR
#define IDX_TO_ADDR(idx)						((idx) << 2)
#endif
#ifndef ADDR_TO_IDX
#define	ADDR_TO_IDX(addr)						((addr) >> 2)
#endif
#ifndef LEN_TO_WORD
#define LEN_TO_WORD(blen)						((blen + 3) >> 2)
#endif
#ifndef WORD_TO_LEN
#define WORD_TO_LEN(wlen)						((wlen) << 2)
#endif

//#define JTAG_DEBUG
//#define ATSC3_ON
#define DEMOD_MAGIC_CODE						0x44454F44

/* demod error code */
#define NO_DEMOD_ERROR                    		0x00

#define ERROR_DEMOD_ALLOCATING_CONTEXT     		0x02
#define ERROR_DEMOD_SENDING_COMMAND        		0x03
#define ERROR_DEMOD_CTS_TIMEOUT            		0x04
#define ERROR_DEMOD_ERROR                		0x05
#define ERROR_DEMOD_POLLING_CTS            		0x06
#define ERROR_DEMOD_POLLING_RESPONSE       		0x07
#define ERROR_DEMOD_LOADING_FIRMWARE       		0x08
#define ERROR_DEMOD_LOADING_BOOTBLOCK      		0x09
#define ERROR_DEMOD_STARTING_FIRMWARE      		0x0a
#define ERROR_DEMOD_SW_RESET               		0x0b
#define ERROR_DEMOD_INCOMPATIBLE_PART      		0x0c
#define ERROR_DEMOD_DISEQC_BUS_NOT_READY  		0x0d
#define ERROR_DEMOD_OS_LOCK						0x0e
#define ERROR_DEMOD_NOT_SUPPORT					0x0f

#define ERROR_DEMOD_PARAMETER	 				0x10
#define ERROR_DEMOD_PARAMETER_OUT_OF_RANGE	 	0x11

#define ERROR_DEMOD_RESULT						0x20
#define ERROR_DEMOD_RESULT_NOT_READY	 		0x21
#define ERROR_DEMOD_RESULT_UNKNOWN				0x22

#define ERROR_DEMOD_IPC							0xA0
#define ERROR_DEMOD_IPC_BUSY					0xA1
#define ERROR_DEMOD_IPC_EMPTY					0xA2
#define ERROR_DEMOD_IPC_TIMEOUT					0xA3
#define ERROR_DEMOD_IPC_INVALID					0xA4

#define ERROR_DEMOD_IPC_NOT_SUPPORT				0xAE
#define ERROR_DEMOD_IPC_FALUT					0xAF

#define ERROR_DEMOD_CBUF						0xC0
#define ERROR_DEMOD_CBUF_INV					0xC1
#define ERROR_DEMOD_CBUF_NULL					0xC2
#define ERROR_DEMOD_CBUF_FAULT					0xC3
#define ERROR_DEMOD_CBUF_EMPTY					0xC4
#define ERROR_DEMOD_CBUF_FULL					0xC5

#define ERROR_DEMOD_FW							0xFE
#define ERROR_DEMOD_FW_INIT						0xF0
#define ERROR_DEMOD_FW_NOT_READY				0xF1
#define ERROR_DEMOD_FW_TIMEOUT					0xF2
#define ERROR_DEMOD_FW_FAULT					0xFF

#define ERROR_DEMOD_INVALID						0xE0
#define ERROR_DEMOD_UNKNOWN_COMMAND        		0xE1
#define ERROR_DEMOD_UNKNOWN_PROPERTY       		0xE2
#define ERROR_DEMOD_READ     					0xE3
#define ERROR_DEMOD_WRITE						0xE4
#define ERROR_DEMOD_PTRNULL						0xE5
#define ERROR_DEMOD_FAULT						0xEF


/* demod time limit */
#define DEMOD_DD_MAX_LENGTH						80

#define DEMOD_DD_DOWNLOAD_ON_CHANGE				1
#define DEMOD_DD_DOWNLOAD_ALWAYS				0

#define DEMOD_DD_TERRESTRIAL					1

#define DEMOD_DD_CLOCK_ALWAYS_OFF				0
#define DEMOD_DD_CLOCK_ALWAYS_ON				1
#define DEMOD_DD_CLOCK_MANAGED					2

#define DEMOD_DD_DVBT_MIN_LOCK_TIME				100
#define DEMOD_DD_DVBT_MAX_LOCK_TIME				2000
#define DEMOD_DD_DVBT_MAX_SEARCH_TIME			1000

#define DEMOD_DD_DVBT2_MIN_LOCK_TIME   		  	100
#define DEMOD_DD_DVBT2_MAX_LOCK_TIME			2000
#define DEMOD_DD_DVBT2_MAX_SEARCH_TIME			1000

#define DEMOD_DD_VSB_MIN_LOCK_TIME       		100
#define DEMOD_DD_VSB_MAX_LOCK_TIME			  	2000
#define DEMOD_DD_VSB_MAX_SEARCH_TIME			500

#define DEMOD_DD_QAM_MIN_LOCK_TIME      	 	100
#define DEMOD_DD_QAM_MAX_LOCK_TIME				2000
#define DEMOD_DD_QAM_MAX_SEARCH_TIME			500

#define DEMOD_DD_ISDBT_MIN_LOCK_TIME   	    	100
#define DEMOD_DD_ISDBT_MAX_LOCK_TIME			2000
#define DEMOD_DD_ISDBT_MAX_SEARCH_TIME			500

#define DEMOD_DD_ATSC3_MIN_LOCK_TIME  	    	100
#define DEMOD_DD_ATSC3_MAX_LOCK_TIME			2000
#define DEMOD_DD_ATSC3_MAX_SEARCH_TIME			1000
#define DEMOD_DD_ATSC3_MAX_FEC_LOCK_TIME		1000

#define DEMOD_DD_DVBC_MIN_LOCK_TIME				100
#define DEMOD_DD_DVBC_MAX_LOCK_TIME				2000
#define DEMOD_DD_DVBC_MAX_SEARCH_TIME			500


#define DEMOD_DD_DVBS_MIN_LOCK_TIME				50
#define DEMOD_DD_DVBS_MAX_LOCK_TIME				5000
#define DEMOD_DD_DVBS_MAX_SEARCH_TIME			5000

#define DEMOD_DD_DVBS2_MIN_LOCK_TIME			50
#define DEMOD_DD_DVBS2_MAX_LOCK_TIME			5000
#define DEMOD_DD_DVBS2_MAX_SEARCH_TIME			5000

#define DEMOD_DD_DTMB_MIN_LOCK_TIME     	  	100
#define DEMOD_DD_DTMB_MAX_LOCK_TIME			  	2000
#define DEMOD_DD_DTMB_MAX_SEARCH_TIME			500

#define DEMOD_DD_SAT_MAX_SEARCH_TIME			60000

#define DEMOD_DD_CABLE							2
#define DEMOD_DD_SATELLITE						3

#define DEMOD_DD_SAT_BLIND_LPF_DEFAULT 			40000
#define DEMOD_DD_DVBS_JUMPING_SYMBOLRATE_THRESHOLD	5000 //KHz


#ifndef LX_DEMOD_FIRMWARE_STRUCT
typedef struct _LX_DEMOD_FIRMWARE_STRUCT
{
	unsigned char 		firmware_addr;
	unsigned int 		firmware_size;
	unsigned char 		firmware_table[0x20000];
} LX_DEMOD_FIRMWARE_STRUCT;
typedef struct _LX_DEMOD_FIRMWARE_STRUCT LX_DEMOD_FW_STRUCT;
#endif

typedef struct {
	unsigned char modulation;
	unsigned char lock_fec;
	unsigned char neverLock;
	unsigned char pe;

	unsigned short reset_flag;
	struct {
		unsigned char MAIN;
		unsigned char SYNC;
		unsigned char SYNC3A;
		unsigned char SYNC3B;
		unsigned char SYNC3C;
		unsigned char SAT_EQ;
		unsigned char SAT_SIGSRCH;
		unsigned char T2_PLPSEL;
		unsigned char TPRST;
	} reset_cnt;

	unsigned char selfrst_arg;
	unsigned char selfrst1_count;
	unsigned char selfrst2_count;
	unsigned char selfrst3_count;
	unsigned char selfrst4_count;
	unsigned char selfrst4_lock_pre;
	unsigned char selfrst5_lock_pre;
	unsigned char selfrst6_lock_pre;
	unsigned char selfrst7_lock_pre;
	unsigned char selfrst8_count;
	unsigned char selfrst8_precond_count;

	struct {
		unsigned char selfrst1;
		unsigned char selfrst2;
		unsigned char selfrst3;
		unsigned char selfrst4;
		unsigned char selfrst5;
		unsigned char selfrst6;
		unsigned char selfrst7;
		unsigned char selfrst8;
	} selfrst_cnt;

	unsigned char power_save;
	unsigned char last_cmd;
	unsigned char last_cmd_seq;
	unsigned char last_cmd_state;
} demod_fw_status_t;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
typedef enum
{
        /* TERRESTRIAL */
        LX_DEMOD_DVBT = 0,                      ///< Oper mode -> DVBT
        LX_DEMOD_DVBT2,                         ///< Oper mode -> DVBT2
        LX_DEMOD_ATSC,                          ///< Oper mode -> ATSC
        LX_DEMOD_ISDBT,                         ///< Oper mode -> ISDBT
        LX_DEMOD_DTMB,                          ///< Oper mode -> DTMB

        /* CABLE */
        LX_DEMOD_DVBC,                          ///< Oper mode -> DVBC
        LX_DEMOD_DVBC2,                         ///< Oper mode -> DVBC2
        LX_DEMOD_QAM,                           ///< Oper mode -> QAM
        LX_DEMOD_ISDBC,                         ///< Oper mode -> ISDBC

        /* SATELLITE */
        LX_DEMOD_DVBS,                          ///< Oper mode -> DVBS
        LX_DEMOD_DVBS2,                         ///< Oper mode -> DVBS2
        LX_DEMOD_BS,                            ///< Oper mode -> BS
        LX_DEMOD_CS,                            ///< Oper mode -> CS

        LX_DEMOD_ANALOG,                        ///< Oper mode -> ANALOG

        LX_DEMOD_OPER_END,                      ///< Oper mode -> END

        LX_DEMOD_ANALOG_Sleep,                  ///< Oper mode -> ANALOG Sleep
        LX_DEMOD_DIGITAL_Sleep,                 ///< Oper mode -> DIGTITAL Sleep
        LX_DEMOD_ALWAYSREADY,					///< for support low power mode
		
		LX_DEMOD_ATSC3,                         ///< Oper mode -> ATSC3

        LX_DEMOD_UNKOWN_OPMODE          		///< Oper mode ->  UNKNOWN
} LX_DEMOD_OPER_MODE_T;

#endif
#endif /* _DBB_DEMOD_TYPEDEFS_H_ */
