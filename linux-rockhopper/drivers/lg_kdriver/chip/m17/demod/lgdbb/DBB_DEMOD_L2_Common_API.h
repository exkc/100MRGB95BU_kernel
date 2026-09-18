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
**  Name:DBB_DEMOD_L2_Common_API.c
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

#ifndef   _DBB_DEMOD_L2_Common_API_H_
#define   _DBB_DEMOD_L2_Common_API_H_

  #define   DEMOD_TERRESTRIAL_FRONT_END
  #define  DEMOD_SATELLITE_FRONT_END

#include "DBB_DEMOD_L1_API.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"


typedef struct _LX_DEMOD_L2_Context {
	LX_DEMOD_L1_Context *demod;
	LX_DEMOD_L1_Context  demodObj;
	UINT8      	demod_init_done; //x
	UINT8		standard;  //x
	UINT32          detected_rf; //o
	UINT32          centerFrq; //x

	UINT8 		num_PLP_total;
	UINT8 		set_PLP_ID;

#ifndef LG3307_API

	UINT8     		auto_detect_DVBT_T2;  ///DVBT / DVBT2
	UINT8     		cable_blind_scan;	//DVBC
	UINT32		baseAddr;
	UINT8		eAlarm;	//ISDB_T

#ifdef DEMOD_SATELLITE_FRONT_END
	UINT8 satellite_init_done;
	UINT8 auto_detect_SAT;
	UINT8 satellite_blind_search;
	UINT8 satellite_spectrum_inversion;
#ifndef __KERNEL__
	UINT8 find_chnum;
	UINT32 find_freq[200];
	UINT32 find_symrate[200];
#endif
#endif /*DEMOD_SATELLITE_FRONT_END */

#endif /* DEMOD_SATELLITE_FRONT_END */


} LX_DEMOD_L2_Context;

typedef struct _LX_DEMOD_L2_SIG_STATUS
{
	SINT32 snr;
	SINT32 offsetFrq_Hz;
	SINT32 sam_offsetFrq_Hz;
	SINT16 if_agc;
	UINT32 mse_info;
	UINT32 constPwr;
	UINT32 constPwr_eq;
	UINT32 ber;
	UINT32 packetError;
	UINT32 sym_rate;
	UINT8 signalQuality;
	UINT8 operatingMode;
	UINT8 constellation;
	UINT8 spInv;
	UINT8 bandwidth;
	UINT8 demodLock;
	UINT8 lock_l1b;
	UINT8 lock_l1d;

	SINT32 snr_demod;
	SINT32 snr_eq;
	UINT32 mse_info_demod;
	UINT32 mse_info_eq;

	UINT8 guardInterval; /// ATSC3/DVBT/DVBT2/ISDBT
	UINT8 codeRate; /// ATSC3/DVBT/DVBT2/ISDBT
	UINT8 fftMode; /// ATSC3/DVBT/DVBT2/ISDBT

#ifndef LG3307_API

	UINT16 cell_id; /// DVBT
	UINT8 hierarchy; /// DVBT
	UINT8 hierarchy_sel; /// DVBT	
	UINT8 il_mode;///DTMB
	UINT8 pn_const;///DTMB
	UINT8 pn_mode;///DTMB
	UINT8 carr_mode;///DTMB
	
#endif

	UINT8 num_PLP; ///ATSC3 / DVBT2
	UINT8 current_plp_id;
	UINT8 bw_Ext;
	UINT8 pp;

} LX_DEMOD_L2_SIG_STATUS;

 typedef struct _LX_DEMOD_L2_PART_INFO
{

	  UINT8   fw_major;
	  UINT8   fw_minor;
  	  UINT8   fw_year;
	  UINT8   fw_month;
      UINT8   fw_day;
	  UINT8   chip_type;
	  UINT8   chip_rev;

}   LX_DEMOD_L2_PART_INFO;

typedef struct
{
	UINT8			constel;			///< QAM mode
	UINT8			code_rate;			///< code rate
	UINT32			sn_ref;				///< Nordig C/N reference spec.
}LX_DEMOD_SQI_CN_ATSC3P1_T;


SINT64  _DEMOD_do_div64_32(SINT64 dividend, SINT32 divisor);
SINT64  _DEMOD_do_div64_64(SINT64 dividend, SINT64 divisor);
extern UINT8 DEMOD_L2_Configure           (LX_DEMOD_L2_Context *frontend);
#ifndef __EVAL_GUI__
extern UINT8 DEMOD_L2_Opermode_Configure           (LX_DEMOD_L2_Context *frontend , LX_DEMOD_OPER_MODE_T operMode);
#endif
extern UINT8 DEMOD_L2_Standby                   (LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_WakeUp                    (LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_PowerUpWithPatch          (LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_LoadFirmware_IRAM		(LX_DEMOD_L2_Context *frontend, LX_DEMOD_FIRMWARE_STRUCT fw_table[], UINT8 nbLines);
extern UINT8 DEMOD_L2_LoadFirmware_DRAM		(LX_DEMOD_L2_Context *frontend, LX_DEMOD_FIRMWARE_STRUCT fw_table[], UINT8 nbLines);

extern UINT8 DEMOD_L2_Init                      (LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_Media                     (LX_DEMOD_L2_Context *frontend, UINT8 modulation);
extern UINT8 DEMOD_L2_StartFirmware		(LX_DEMOD_L2_Context *frontend);

/*****************************************************************************************/
extern UINT8 DEMOD_L2_Switch_to_standard (LX_DEMOD_L2_Context *front_end, UINT8 new_standard);
extern UINT8 DEMOD_L2_Check_NeverLock_state   (LX_DEMOD_L2_Context *front_end);
extern UINT8 DEMOD_L2_Check_NeverLock_loop   (LX_DEMOD_L2_Context *front_end, UINT8 standard);
extern UINT8 DEMOD_L2_Check_lock_loop   (LX_DEMOD_L2_Context *front_end, UINT8 standard);
extern UINT8 DEMOD_L2_Check_BlindLock_state   (LX_DEMOD_L2_Context *front_end);
extern UINT8 DEMOD_L2_Check_BlindLock_loop   (LX_DEMOD_L2_Context *front_end, UINT8 standard);


extern UINT8 DEMOD_L2_Set_Invert_Spectrum (LX_DEMOD_L2_Context *front_end);

extern UINT8 DEMOD_L2_Get_LockStatus(LX_DEMOD_L2_Context *frontend, UINT8 *pOperMode,  UINT8 *pFecLock);
#ifndef __EVAL_GUI__
extern UINT8 DEMOD_L2_Get_OperMode(LX_DEMOD_L2_Context *frontend, LX_DEMOD_OPER_MODE_T *reply_opmode);
#endif
extern UINT8 DEMOD_L2_SignalStatus     (LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_SIG_STATUS *pSignalStatus);
extern UINT8 DEMOD_L2_SendCommand(LX_DEMOD_L2_Context *frontend, UINT32 cmd_code);
extern UINT8 DEMOD_L2_Set_Property(LX_DEMOD_L2_Context *frontend, UINT32 prop_code);

extern UINT8 DEMOD_L2_GET_REG(LX_DEMOD_L2_Context *front_end, UINT16  addr, UINT8 length, UINT8   *readData);
extern UINT8 DEMOD_L2_GET_REG_MAP(LX_DEMOD_L2_Context *front_end, UINT16  addr, UINT8 length, UINT8 *readData);
extern UINT8 DEMOD_L2_SET_REG(LX_DEMOD_L2_Context *front_end,  UINT16  addr, UINT8 length, UINT32   wrData);

extern UINT8 DEMOD_L2_Tuner_I2C_Enable (LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_Tuner_I2C_Disable(LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_Get_PartInfo(LX_DEMOD_L2_Context *frontend, LX_DEMOD_L2_PART_INFO *fwInfo);
extern UINT8 DEMOD_L2_GetDump(LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_Get_Property(LX_DEMOD_L2_Context *frontend, UINT32 prop_code);
extern UINT8 DEMOD_L2_Set_ChipInfo(LX_DEMOD_L2_Context *frontend, UINT16 chipVer);
extern UINT8 DEMOD_L2_Set_SoftRst(LX_DEMOD_L2_Context *frontend, UINT8 softrstb, UINT8 softrstsyncb, UINT8 softrsteq1b, UINT8 softrsteq2b, UINT8 softrstdiseqcb, UINT8 softrstfecb, UINT8 softrsttpifb);

#ifndef LG3307_API

extern UINT8 DEMOD_L2_InitMem (LX_DEMOD_L2_Context *frontend);
extern UINT8 DEMOD_L2_Set_MemAddr (LX_DEMOD_L2_Context *frontend, UINT32 baseAddr);
extern UINT8 DEMOD_L2_PowerUpWithMem (LX_DEMOD_L2_Context *frontend);
#endif /* LG3307_API */

#endif /* _DBB_DEMOD_L2_Common_API_H_ */

