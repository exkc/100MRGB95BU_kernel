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


#ifndef DEMOD_MODULE_H
#define DEMOD_MODULE_H


#include "demod_kapi.h"
#include "i2c_core.h"

 /*
 	define
 */
#if defined(DEMOD_CHIP_NAME_o22)
#define	DEMOD_IP_BASE_ADDR			(O22_DBB_IP_TOP_BASE + 0x5300)
#define DEMOD_IP_SYSTEM_REG_SIZE	(0x300)
#elif defined(DEMOD_CHIP_NAME_m23)
#define	DEMOD_IP_BASE_ADDR			(M23_DBB_IP_TOP_BASE + 0x5300)
#define DEMOD_IP_SYSTEM_REG_SIZE	(0x300)
#elif defined(DEMOD_CHIP_NAME_o24) //!//
#ifndef O24_DBB_IP_BASE
#define O24_DBB_IP_BASE                              0xC6870000   // 64KB
#endif
#define	DEMOD_IP_BASE_ADDR			(O24_DBB_IP_BASE + 0x5300)
#define DEMOD_IP_SYSTEM_REG_SIZE	(0x300)
#elif defined(DEMOD_CHIP_NAME_o26) //chungiii
#ifndef O26_DBB_IP_BASE
#define O26_DBB_IP_BASE                              0xC8A00000   // 64KB  //chungiii
#endif
#define	DEMOD_IP_BASE_ADDR			(O26_DBB_IP_BASE + 0x5300)
#define DEMOD_IP_SYSTEM_REG_SIZE	(0x300)
#else
#define	DEMOD_IP_BASE_ADDR			0
#define DEMOD_IP_SYSTEM_REG_SIZE	0
#endif

#define	DEMOD_O18_BASE_ADDR			0xc600f000
#define DEMOD_O18_SYSTEM_REG_SIZE	0x100

#define	DEMOD_M19_BASE_ADDR			0xC910A400
#define DEMOD_M19_SYSTEM_REG_SIZE	0x100

#define	DEMOD_O20_BASE_ADDR			0xC9225300
#define DEMOD_O20_SYSTEM_REG_SIZE	0x200

#define	DEMOD_E60_BASE_ADDR			0xC30B5300
#define DEMOD_E60_SYSTEM_REG_SIZE	0x200


/*
	Device inform
*/

/**
 * I2C .
 */


typedef struct
{
	LX_I2C_DEV_HANDLE		handle;
	UINT32				slvAddr;
	UINT8				portI2C;
} LX_DEMOD_I2C_DESCRIPT_T;

typedef enum
{
	DEMOD_SW_TYPE_NONE		= 0x0,
	DEMOD_SW_TYPE_DVB		= 0x1,
	DEMOD_SW_TYPE_ATSC		= 0x2,
	DEMOD_SW_TYPE_DTMB		= 0x4,
} LX_DEMOD_SW_TYPE_T;

typedef struct
{
	LX_DEMOD_SW_TYPE_T		sw_type;
	BOOLEAN				mem_alloc;
	BOOLEAN				power_save;
	BOOLEAN				apb_access;
} DEMOD_DEV_T;
DEMOD_DEV_T * DEMOD_Get_Device_Data(void);

typedef struct
{
	UINT8  				id; //device minor number
	LX_DEMOD_I2C_DESCRIPT_T		handleDTV;
//	LX_DEMOD_I2C_DESCRIPT_T		handleATV;
//	BOOLEAN				bInit;
	UINT32				IFFrq;

	LX_DEMOD_OPER_MODE_T 		operMode;
	LX_DEMOD_OPER_MODE_T 		tranMode;
	LX_DEMOD_RF_MODE_T		systemMode;
	LX_DEMOD_SYMRDET_MODE_T 	symbr;
//	BOOLEAN 			bIsSerial;
	BOOLEAN				bIsTPoutEn;

	LX_DEMOD_CONTROL_STATE_T	controlState;
	LX_DEMOD_ACQUIRE_PROCESS_T	acqState;
	LX_DEMOD_FLAG_T			scanJobFlag;

	BOOLEAN 			bSetParams;
	LX_DEMOD_CONFIG_T		setCfgParam;
	LX_DEMOD_CONFIG_T		getCfgParam;
	LX_DEMOD_LOCK_STATE_T		lockStatus;

	LX_DEMOD_SIGNAL_CTX_T		signalStatus;
	SINT32 				freqOffset;

	BOOLEAN				bMonitorEnable;
	BOOLEAN 			bNotifiedLock;
	BOOLEAN 			bNotifiedUnlock;

	UINT8 				unLockLongCount;
	UINT8 				unLockCount;
	UINT8				lockCount;
	BOOLEAN				instantBoot;
	BOOLEAN				bSignalStatusValid;
	BOOLEAN				bCountryGrpEU;
} DEMOD_CTX_T;

void DEMOD_CLR_CTX (void);
DEMOD_CTX_T * DEMOD_Get_CTX (int devno);

#ifndef LX_ADEMOD_Result
typedef UINT32          		LX_ADEMOD_Result;      /*  return codes                    */
#endif

#ifndef BOOL
typedef int				BOOL;
#endif


/*
	Enum define
*/


/*
	global variable
*/


/*
	function prototype
*/

int DEMOD_I2C_open (UINT8 portI2C, UINT16 deviceID);
int DEMOD_I2C_Close (void);
int DEMOD_I2C_Read (UINT16 address, UINT16 nBytes, UINT8 *pData);
int DEMOD_I2C_Write (UINT16 address, UINT16 nBytes, UINT8 *pData);

void DEMOD_I2C_Raw_Lock(void);
void DEMOD_I2C_Raw_Unlock(void);
int DEMOD_I2C_Raw_Read(UINT8 slvaddr, UINT16 address, UINT16 nBytes, UINT8 *pData);
int DEMOD_I2C_Raw_Write(UINT8 slvaddr, UINT16 address, UINT16 nBytes, UINT8 *pData);

int ADC_Test_I2C_Read (UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData);
int ADC_Test_I2C_Write (UINT8 slvAddr, UINT8 address, UINT16 nBytes, UINT8 *pData);
int DEMOD_ADC_Control (LX_DEMOD_ADC_VOLTAGE_SEL_T votageSel);

/* HW function */
int DEMOD_ResetHW (void);
int DEMOD_OperModeReset (LX_DEMOD_OPER_MODE_T operMode);
int DEMOD_SetInclk (LX_DEMOD_INCLK_SEL_T *inclk);
int DEMOD_InitHW (void);
int DEMOD_AdcInit (void);
int DEMOD_SetI2C (void);
BOOLEAN KHAL_DEMOD_FWdn (void);
BOOLEAN KHAL_DEMOD_Ioremap (void);
void KHAL_DEMOD_Init_gIsFWDn (BOOLEAN done);
void KHAL_DEMOD_Init_gIs_ioremap (BOOLEAN done);

int DEMOD_Get_I2C_Handle (UINT8 portI2C, UINT16 deviceID);
int DEMOD_FW_Initialize (void);
int DEMOD_SAT_FW_Initialize (void);
int DEMOD_ALL_FW_Initialize (void);
int DEMOD_FW_Configuration_Initialize (LX_DEMOD_OPER_MODE_T operMode);
int DEMOD_API_Suspend (void);
int DEMOD_DVB_C_reset (void);

int DEMOD_DVB_SW_Init (void);
int DEMOD_DTMB_SW_Init (void);
int DEMOD_ATSC_SW_Init (void);
int DEMOD_VSB_SetDemod_Simple (void);

int DEMOD_SAT_DiSeqContol (BOOLEAN OnOff);
int DEMOD_SetPll (LX_DEMOD_OPER_MODE_T operMode);
int DEMOD_SetADC (LX_DEMOD_OPER_MODE_T operMode);

int DEMOD_DBB_I2C_Read (UINT16 address, UINT16 nBytes, UINT8 *pData);
int DEMOD_DBB_I2C_Write (UINT16 address, UINT16 nBytes, UINT8 *pData);

int DEMOD_DBB_APB_DEBUG_Read (UINT16 address, UINT32 *pData);
int DEMOD_DBB_APB_Read (UINT16 address, UINT32 *pData);
int DEMOD_DBB_APB_Write (UINT16 address, UINT32 *pData);
int DEMOD_DBB_PDB_Write (UINT32 value);

int DEMOD_APB_Read (UINT32 addr, UINT32 *pval);
int DEMOD_APB_Write (UINT32 addr, UINT32 *val);

int DEMOD_Reg_Close (void);
void KHAL_DEMOD_PanamaOn (BOOLEAN On);

const char * DEMOD_Get_OPER_MODE_Name (LX_DEMOD_OPER_MODE_T oper_mode);
#endif
