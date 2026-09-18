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

//#define DEMOD_ROM_TEST // Full or ROM
//#define FPGA_RDK_M17
//#define FPGA_RDK_M17_PRINT
//#define FW_AXI_EN
//#define JTAG_DEBUG
//#define ATSC3_ON
//#define __EVAL_GUI__
//#define FPGA_CPBOX
#define M16P		0x14
#define L18F		0x18
#define M16P3		0x19

#ifdef __KERNEL__
#include "demod_impl.h"
#else
#ifndef __EVAL_GUI__
#include "tu_common.h"
#else
#include <stdarg.h>
#include "../stdafx.h"
#include "../Log.h"
#endif
#endif


#ifdef __EVAL_GUI__
#define __F__	__FUNCTION__
#ifndef USER_RET_OK
#define USER_RET_OK				0
#endif

#ifndef USER_RET_FAIL
#define USER_RET_FAIL			1
#endif



#define I2C_OK			1
#define TYPE_SI2178B	0
#define TYPE_SI2158B	1
#define TYPE_RDA5815S	2

#define DEV_ID_FPGA		0x13//0x63 //0x13
#define DEV_ID_CHIP		0x1c

#define DEVID_RDA5815S	0x0c
#define DEVID_LNB		0x08

#define MOD_DVB_C		0x40
#define MOD_DVB_C2		0x41
#define MOD_DVB_T		0x00
#define MOD_DVB_T2		0x01
#define MOD_QAM		0x48
#define MOD_VSB			0x08
#define MOD_ISDB_T		0x10
#define MOD_DVB_S		0x60
#define MOD_DVB_S2		0x61
#define MOD_ISDB_C		0x50
#define MOD_DVB_S2X	0x62
#define MOD_DTMB		0x55

#define BW_8MHZ			8
#define BW_7MHZ			7
#define BW_6MHZ			6
#define BW_1P7MHZ		9
#define BW_6P1MHZ		10
#define BW_4MHZ			4
#define BW_40MHZ		40

#define CRTL_OWN_LSB		4
#define CRTL_OWN_MASK		0x01
#define RSP_LSB				2
#define RSP_MASK			0x01

#define INT_EN_LSB			3
#define INT_EN_MASK			0x01

#define FW_TYPE_AUTO		0
#define FW_TYPE_MANUAL		1

#define I2C_TYPE_MCU		1
#define I2C_TYPE_DIRECT		0

#define CODE_NAME_B17A0		0
#define CODE_NAME_M16P		1
#define CODE_NAME_UBB2		2

#define REG_00H	 0
#define REG_01H	 1
#define REG_14H	 2
#define REG_16H	 3
#define REG_20H	 4
#define REG_21H	 5
#define REG_26H	 6
#define REG_27H	 7
#define REG_28H	 8
#define REG_31H	 9
#define REG_32H	 10
#define REG_33H	 11
#define REG_40H	 12
#define REG_41H	 13
#define REG_48H	 14
#define REG_50H	 15
#define REG_60H	 16
#define REG_70H	 17
#define REG_1FH	 18
#define REG_71H	 19
#define REG_72H	 20
#endif

#define SRD_EN_C_ENABLE		0x01
#define SRD_EN_C_DISABLE	0x00

#ifndef UINT8
	typedef unsigned char UINT8;
#endif

#ifndef UINT16
	typedef unsigned short UINT16;
#endif

#ifndef UINT32
	typedef unsigned int UINT32;
#endif

#ifndef UINT64
	typedef unsigned long long	UINT64;
#endif

#ifndef SINT8
	typedef signed char SINT8;
#endif

#ifndef SINT16
	typedef signed short SINT16;
#endif

#ifndef SINT32
	typedef signed int SINT32;
#endif

#ifndef SINT64
	typedef signed long long SINT64;
#endif

/* Uncomment the following line to activate all traces in the code */
#define  DbbTRACES

#ifdef    DbbTRACES

#ifdef __KERNEL__
#define DBB_PRINT   printk
#define DBB_DUMP_PRINT   printk
#else
#ifndef __EVAL_GUI__
#define DBB_PRINT   dbgprint
//#define DBB_PRINT   printf
#define DBB_DUMP_PRINT   printf
#else
#define DBB_PRINT   printf
#define DBB_DUMP_PRINT   printf
#endif
#endif

#else
  #define DBB_PRINT(...)               /* empty */
#endif /* DbbTRACES */
#define NO_DEMOD_ERROR                    					0x00
#define ERROR_DEMOD_PARAMETER_OUT_OF_RANGE 	0x01
#define ERROR_DEMOD_ALLOCATING_CONTEXT     		0x02
#define ERROR_DEMOD_SENDING_COMMAND        		0x03
#define ERROR_DEMOD_CTS_TIMEOUT            			0x04
#define ERROR_DEMOD_ERROR                				0x05
#define ERROR_DEMOD_POLLING_CTS            			0x06
#define ERROR_DEMOD_POLLING_RESPONSE       			0x07
#define ERROR_DEMOD_LOADING_FIRMWARE       		0x08
#define ERROR_DEMOD_LOADING_BOOTBLOCK      		0x09
#define ERROR_DEMOD_STARTING_FIRMWARE      		0x0a
#define ERROR_DEMOD_SW_RESET               				0x0b
#define ERROR_DEMOD_INCOMPATIBLE_PART      		0x0c
#define ERROR_DEMOD_DISEQC_BUS_NOT_READY  		0x0d
#define ERROR_DEMOD_UNKNOWN_COMMAND        		0xf0
#define ERROR_DEMOD_UNKNOWN_PROPERTY       		0xf1
#define ERROR_DEMOD_READ     						0xf2
#define ERROR_DEMOD_WRITE							0xf3


#define DEMOD_DD_MAX_LENGTH				80

#define DEMOD_DD_DOWNLOAD_ON_CHANGE		1
#define DEMOD_DD_DOWNLOAD_ALWAYS			0

#define DEMOD_DD_TERRESTRIAL				1


#define DEMOD_DD_CLOCK_ALWAYS_OFF			0
#define DEMOD_DD_CLOCK_ALWAYS_ON			1
#define DEMOD_DD_CLOCK_MANAGED				2

#define DEMOD_DD_DVBT_MIN_LOCK_TIME		100
#define DEMOD_DD_DVBT_MAX_LOCK_TIME		2000
#define DEMOD_DD_DVBT_MAX_SEARCH_TIME		1000

#define DEMOD_DD_DVBT2_MIN_LOCK_TIME       100
#define DEMOD_DD_DVBT2_MAX_LOCK_TIME		2000
#define DEMOD_DD_DVBT2_MAX_SEARCH_TIME		1000

#define DEMOD_DD_VSB_MIN_LOCK_TIME       	100
#define DEMOD_DD_VSB_MAX_LOCK_TIME		  	2000
#define DEMOD_DD_VSB_MAX_SEARCH_TIME		500

#define DEMOD_DD_QAM_MIN_LOCK_TIME       	100
#define DEMOD_DD_QAM_MAX_LOCK_TIME			2000
#define DEMOD_DD_QAM_MAX_SEARCH_TIME		500

#define DEMOD_DD_ISDBT_MIN_LOCK_TIME       100
#define DEMOD_DD_ISDBT_MAX_LOCK_TIME		2000
#define DEMOD_DD_ISDBT_MAX_SEARCH_TIME		500

#define DEMOD_DD_ATSC3_MIN_LOCK_TIME       100
#define DEMOD_DD_ATSC3_MAX_LOCK_TIME		2000
#define DEMOD_DD_ATSC3_MAX_SEARCH_TIME		1000

#define DEMOD_DD_DVBC_MIN_LOCK_TIME		100
#define DEMOD_DD_DVBC_MAX_LOCK_TIME		2000
#define DEMOD_DD_DVBC_MAX_SEARCH_TIME		500


#define DEMOD_DD_DVBS_MIN_LOCK_TIME		50
#define DEMOD_DD_DVBS_MAX_LOCK_TIME		5000
#define DEMOD_DD_DVBS_MAX_SEARCH_TIME		5000

#define DEMOD_DD_DVBS2_MIN_LOCK_TIME		50
#define DEMOD_DD_DVBS2_MAX_LOCK_TIME		5000
#define DEMOD_DD_DVBS2_MAX_SEARCH_TIME		5000

#define DEMOD_DD_DTMB_MIN_LOCK_TIME       		100
#define DEMOD_DD_DTMB_MAX_LOCK_TIME		  	2000
#define DEMOD_DD_DTMB_MAX_SEARCH_TIME		500

#define DEMOD_DD_SAT_MAX_SEARCH_TIME		60000

#define DEMOD_DD_CABLE						2
#define DEMOD_DD_SATELLITE					3

#define DEMOD_DD_SAT_BLIND_LPF_DEFAULT 40000
#define DEMOD_DD_DVBS_JUMPING_SYMBOLRATE_THRESHOLD 5000 //KHz


#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifndef LX_DEMOD_FIRMWARE_STRUCT
typedef struct  _LX_DEMOD_FIRMWARE_STRUCT
{
	unsigned char firmware_addr;
	unsigned int firmware_size;
	unsigned char firmware_table[98304];

} LX_DEMOD_FIRMWARE_STRUCT;
#endif


#define FW_FOR_SINGLE_CHIP		0x0
#define FW_FOR_DUAL_CHIP		0x1
#define FW_FOR_SOC				0x2
#define FW_FOR_UNKNOWN		0xff


#ifdef FPGA_RDK_M17

#define CHIP_ID_F1	0x26
#define CHIP_ID_F2	0x24
#define CHIP_ID_F3	0x2c
#define CHIP_ID_F4	0x2e

typedef struct _LX_DEMOD_Si2158b_CONFIG {
	unsigned char	Tuner_specinv_sel;
	unsigned char	Tuner_BW_sel;
	unsigned int	Tuner_lif_freq;
	unsigned char	Tuner_lif_amp;
	unsigned char	Tuner_lif_offset;
	unsigned char	Tuner_AGC_source;
	unsigned char	Tuner_AGC_decim;
	unsigned char	Tuner_AGC_speed;
	unsigned char	Tuner_RF_top;
	unsigned char	Tuner_OUT_type;
	unsigned char	Tuner_EXT_AGC_p3db;
	unsigned char	Tuner_EXT_AGC_m3db;
	unsigned char	Tuner_IEN_chlien;
	unsigned char	Tuner_INT_sense_chlposen;
	unsigned char	Tuner_INT_sense_chlnegen;
	unsigned char	Tuner_MOD_modulation;
	unsigned char	Tuner_LNB_EN;
	signed char	Tuner_RSQ_RSSI_hi;
	signed char	Tuner_RSQ_RSSI_lo;

} LX_DEMOD_Si2158b_CONFIG;

typedef struct _LX_DEMOD_DVBC_STATUS {
	unsigned char	sync_lock;
	unsigned char	samlock_cqs;
	unsigned char	qamMode;
	unsigned char	pFEC_lock;
	unsigned char	pTR_lock;
	unsigned char	pCARR_lock;
	unsigned char	pSYNC_lock;
	unsigned char	pTPS_lock;
	unsigned char	pMODE_det;
	unsigned char	pAGC_lock;
	unsigned char	NEVER_lock;
	double	symbolRate;
} LX_DEMOD_DVBC_STATUS;

typedef struct _LX_DEMOD_QAM_STATUS {
	unsigned char	sys_lock;
	unsigned char	samlock_cqs;
	unsigned char	gs_done;
	unsigned char	qamMode;
	unsigned char	pFEC_lock;
	unsigned char	pTR_lock;
	unsigned char	pCARR_lock;
	unsigned char	pSYNC_lock;
	unsigned char	pTPS_lock;
	unsigned char	pMODE_det;
	unsigned char	pAGC_lock;
	unsigned char	NEVER_lock;
	double	symbolRate;
} LX_DEMOD_QAM_STATUS;


typedef struct _LX_DEMOD_ISDBT_STATUS {
	unsigned char	tmccf_lock;
	unsigned char	mode_lock;
	unsigned char	pFftMode;
	unsigned char	pGIMode;
	unsigned char	qamMode;
	unsigned char	pFEC_lock;
	unsigned char	pTR_lock;
	unsigned char	pCARR_lock;
	unsigned char	pSYNC_lock;
	unsigned char	pTPS_lock;
	unsigned char	pMODE_det;
	unsigned char	pAGC_lock;
	unsigned char	NEVER_lock;
} LX_DEMOD_ISDBT_STATUS;

typedef struct _LX_DEMOD_DVBT_STATUS {
	unsigned char	cirlock;
	unsigned char	tps_lock;
	unsigned char	txpsw_lock;
	unsigned char	mode_lock;
	unsigned char	pFftMode;
	unsigned char	pGIMode;
	unsigned char	pHierachMode;
	unsigned char	pLpCodeRate;
	unsigned char	pHpCodeRate;
	unsigned char	pCellIDLength;
	unsigned char	pTpsParams;
	unsigned char	qamMode;
	unsigned char	pBSetHp;
	unsigned char	tpcorrect;
	unsigned char	pFEC_lock;
	unsigned char	pTR_lock;
	unsigned char	pCARR_lock;
	unsigned char	pSYNC_lock;
	unsigned char	pTPS_lock;
	unsigned char	pMODE_det;
	unsigned char	pAGC_lock;
	unsigned char	NEVER_lock;
} LX_DEMOD_DVBT_STATUS;

typedef struct _LX_DEMOD_VSB_STATUS {
	unsigned char	cirlock;
	unsigned char	tps_lock;
	unsigned char	txpsw_lock;
	unsigned char	mode_lock;
	unsigned char	pFEC_lock;
	unsigned char	pTR_lock;
	unsigned char	pCARR_lock;
	unsigned char	pSYNC_lock;
	unsigned char	pTPS_lock;
	unsigned char	pMODE_det;
	unsigned char	pAGC_lock;
	unsigned char	NEVER_lock;
	unsigned short	pFeclocktime;
	unsigned short	pSyslocktime;
} LX_DEMOD_VSB_STATUS;


typedef struct _LX_DEMOD_STATUS {
	Si2158b_CONFIG	*Si2158b_status;
	DVBC_STATUS		*Cstatus;
	QAM_STATUS		*Qstatus;
	ISDBT_STATUS	*ITstatus;
	DVBT_STATUS		*Tstatus;
	VSB_STATUS		*Vstatus;
	//COMMON_STATUS	*COMMONstatus;

} LX_DEMOD_STATUS;

#define MOD_DVB_C		0x40
#define MOD_DVB_C2		0x41
#define MOD_DVB_T		0x00
#define MOD_DVB_T2		0x01
#define MOD_QAM		0x48
#define MOD_VSB			0x08
#define MOD_ISDB_T		0x10
#define MOD_DVB_S		0x60
#define MOD_DVB_S2		0x61
#define MOD_ISDB_C		0x50
#define MOD_DVB_S2X	0x62
#define MOD_DTMB		0x55

#define BW_8MHZ			0x08
#define BW_7MHZ			0x07
#define BW_6MHZ			0x06
#define BW_1P7MHZ		0x09
#define BW_6P1MHZ		0x10

#ifndef I2C_NOTOK
#define I2C_NOTOK		-1
#endif

#ifndef I2C_OK
#define I2C_OK			1
#endif

#define TYPE_SI2158B	0
#define TYPE_RDA5815S	1


#define IIC_100KHZ 	0
#define IIC_400KHZ 	1


#ifdef __EVAL_GUI__
#define LG_IIC_ReadType0LS( a, b, c )			    LG_IIC_ReadType0( a, b, c, IIC_100KHZ)
#define LG_IIC_ReadType1LS( a, b, c, d )		  LG_IIC_ReadType1( a, b, c, d, IIC_100KHZ)
#define LG_IIC_ReadType2LS( a, b, c, d, e )		LG_IIC_ReadType2( a, b, c, d, e, IIC_100KHZ)
#define LG_IIC_ReadTypeXLS( a, b, c, d, e )		LG_IIC_ReadTypeX( a, b, c, d, e, IIC_100KHZ)

#define LG_IIC_WriteType0LS( a, b, c )			  LG_IIC_WriteType0( a, b, c, IIC_100KHZ)
#define LG_IIC_WriteType1LS( a, b, c, d )		  LG_IIC_WriteType1( a, b, c, d, IIC_100KHZ)
#define LG_IIC_WriteType2LS( a, b, c, d, e )	LG_IIC_WriteType2( a, b, c, d, e, IIC_100KHZ)
#define LG_IIC_WriteTypeXLS( a, b, c, d, e )	LG_IIC_WriteTypeX( a, b, c, d, e, IIC_100KHZ)

#define LG_IIC_ReadType0HS( a, b, c )			    LG_IIC_ReadType0( a, b, c, IIC_400KHZ)
#define LG_IIC_ReadType1HS( a, b, c, d )		  LG_IIC_ReadType1( a, b, c, d, IIC_400KHZ)
#define LG_IIC_ReadType2HS( a, b, c, d, e )		LG_IIC_ReadType2( a, b, c, d, e, IIC_400KHZ)
#define LG_IIC_ReadTypeXHS( a, b, c, d, e )		LG_IIC_ReadTypeX( a, b, c, d, e, IIC_400KHZ)

#define LG_IIC_WriteType0HS( a, b, c )			  LG_IIC_WriteType0( a, b, c, IIC_400KHZ)
#define LG_IIC_WriteType1HS( a, b, c, d )		  LG_IIC_WriteType1( a, b, c, d, IIC_400KHZ)
#define LG_IIC_WriteType2HS( a, b, c, d, e )	LG_IIC_WriteType2( a, b, c, d, e, IIC_400KHZ)
#define LG_IIC_WriteTypeXHS( a, b, c, d, e )	LG_IIC_WriteTypeX( a, b, c, d, e, IIC_400KHZ)
#else
#define LG_IIC_ReadType0LS( a, b, c )
#define LG_IIC_ReadType1LS( a, b, c, d )
#define LG_IIC_ReadType2LS( a, b, c, d, e )
#define LG_IIC_ReadTypeXLS( a, b, c, d, e )

#define LG_IIC_WriteType0LS( a, b, c )
#define LG_IIC_WriteType1LS( a, b, c, d )
#define LG_IIC_WriteType2LS( a, b, c, d, e )
#define LG_IIC_WriteTypeXLS( a, b, c, d, e )

#define LG_IIC_ReadType0HS( a, b, c )
#define LG_IIC_ReadType1HS( a, b, c, d )
#define LG_IIC_ReadType2HS( a, b, c, d, e )
#define LG_IIC_ReadTypeXHS( a, b, c, d, e )

#define LG_IIC_WriteType0HS( a, b, c )
#define LG_IIC_WriteType1HS( a, b, c, d )
#define LG_IIC_WriteType2HS( a, b, c, d, e )
#define LG_IIC_WriteTypeXHS( a, b, c, d, e )
#endif
#endif


#endif /* _DBB_DEMOD_TYPEDEFS_H_ */
