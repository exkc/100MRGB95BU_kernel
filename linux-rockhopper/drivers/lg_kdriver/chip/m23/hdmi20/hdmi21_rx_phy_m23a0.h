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



/** @file
 *
 * Register access for hdmi20 phy 
 *
 * author     Won Hur (won.hur@lge.com)
 * version    1.0
 * date       2022.03.08
 * note       Additional information.
 *
 * @addtogroup lg11xxx_sys
 * @{
 */
#ifndef __HDMI20_RX_PHY_M23A0_H__
#define __HDMI20_RX_PHY_M23A0_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "hdmi21_rx_phy_b0_m23a0.h"
#include "hdmi21_rx_phy_b1_m23a0.h"
#include "hdmi21_rx_phy_b2_m23a0.h"

//#include "hdmi21_phy_reg_table.h"
#include "m23a0_table_header.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/**
 * Bit field mask
 * @param m	width
 * @param n shift
 */
#ifndef MSK
#define MSK(m, n)		(((1 << (m)) - 1) << (n))
#endif

/**
 * Bit mask
 * @param n shift
 */
#ifndef BIT
#define BIT(n)			MSK(1, (n))
#endif


/* M23:A0 */
#define PHY_REG_M23A0_SHDW(_port)		(phyReg_M23a0[_port].shdw.M23)
#define PHY_REG_B1_M23A0_SHDW(_port)	(phyReg_B1_M23a0[_port].shdw.M23)
#define PHY_REG_B2_M23A0_SHDW(_port)	(phyReg_B2_M23a0[_port].shdw.M23)

/* M23 COMMON */
#define _REG_PHY_APB_RdFL(_chip, _port, _reg, _data) \
	do{ __PHY_Reg_##_chip##_RdFL( _port, _reg, (UINT32*)(&(_data))); } while(0)

#define _REG_PHY_APB_WrFL(_chip, _port, _reg, _data) \
	do{ __PHY_Reg_##_chip##_WrFL(_port, _reg, *((UINT32*)(&(_data)))); } while(0)

#define _REG_PHY_B1_APB_RdFL(_chip, _port, _reg, _data) \
	do{ __PHY_Reg_B1_##_chip##_RdFL( _port, _reg, (UINT32*)(&(_data))); } while(0)

#define _REG_PHY_B1_APB_WrFL(_chip, _port, _reg, _data) \
	do{ __PHY_Reg_B1_##_chip##_WrFL(_port, _reg, *((UINT32*)(&(_data)))); } while(0)

#define _REG_PHY_B2_APB_RdFL(_chip, _port, _reg, _data) \
	do{ __PHY_Reg_B2_##_chip##_RdFL( _port, _reg, (UINT32*)(&(_data))); } while(0)

#define _REG_PHY_B2_APB_WrFL(_chip, _port, _reg, _data) \
	do{ __PHY_Reg_B2_##_chip##_WrFL(_port, _reg, *((UINT32*)(&(_data)))); } while(0)


#define PHY_M23_REG_RdFL(_chip, _port, _r)						\
	do{ 														\
		_REG_PHY_APB_RdFL(_chip, _port,							\
					  _r##_##_chip##_REG_ADDR, 					\
					  PHY_REG_##_chip##_SHDW(_port)->_r);		\
	} while(0)

#define PHY_M23_REG_B1_RdFL(_chip, _port, _r)					\
	do{ 														\
		_REG_PHY_B1_APB_RdFL(_chip,	_port,						\
					  _r##_B1_##_chip##_REG_ADDR, 				\
					  PHY_REG_B1_##_chip##_SHDW(_port)->_r);	\
	} while(0)

#define PHY_M23_REG_B2_RdFL(_chip, _port, _r)					\
	do{ 														\
		_REG_PHY_B2_APB_RdFL(_chip,	_port,						\
					  _r##_B2_##_chip##_REG_ADDR, 				\
					  PHY_REG_B2_##_chip##_SHDW(_port)->_r);	\
	} while(0)


#define PHY_M23_REG_WrFL(_chip,_port, _r)						\
	do{ 														\
		_REG_PHY_APB_WrFL(_chip, _port,							\
					  _r##_##_chip##_REG_ADDR,					\
					  PHY_REG_##_chip##_SHDW(_port)->_r);		\
	} while(0)

#define PHY_M23_REG_B1_WrFL(_chip,_port, _r)						\
	do{ 															\
		_REG_PHY_B1_APB_WrFL(_chip,_port,							\
					  _r##_B1_##_chip##_REG_ADDR,					\
					  PHY_REG_B1_##_chip##_SHDW(_port)->_r);		\
	} while(0)

#define PHY_M23_REG_B2_WrFL(_chip,_port, _r)						\
	do{ 															\
		_REG_PHY_B2_APB_WrFL(_chip,_port,							\
					  _r##_B2_##_chip##_REG_ADDR,					\
					  PHY_REG_B2_##_chip##_SHDW(_port)->_r);		\
	} while(0)




/* Below Macro's do not use I2C, it just access the shadow's */
#define PHY_M23_REG_Rd01(_chip,_port,_r,_f01,_v01) \
	_REG_Rd01(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_M23_REG_Rd02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_M23_REG_B1_Rd01(_chip,_port,_r,_f01,_v01) \
	_REG_Rd01(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_M23_REG_B1_Rd02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_M23_REG_B2_Rd01(_chip,_port,_r,_f01,_v01) \
	_REG_Rd01(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_M23_REG_B2_Rd02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)


#define PHY_M23_REG_Wr01(_chip,_port,_r,_f01,_v01) \
	_REG_Wr01(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_M23_REG_Wr02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_M23_REG_B1_Wr01(_chip,_port,_r,_f01,_v01) \
	_REG_Wr01(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_M23_REG_B1_Wr02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_M23_REG_B2_Wr01(_chip,_port,_r,_f01,_v01) \
	_REG_Wr01(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_M23_REG_B2_Wr02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)


/* M23:A0 */
#define PHY_REG_M23A0_RdFL(_port,_r)		{PHY_M23_REG_RdFL(M23A0,_port,_r);}
#define PHY_REG_M23A0_WrFL(_port,_r)		{PHY_M23_REG_WrFL(M23A0,_port,_r);}

#define PHY_REG_B1_M23A0_RdFL(_port,_r)		{PHY_M23_REG_B1_RdFL(M23A0,_port,_r);}
#define PHY_REG_B1_M23A0_WrFL(_port,_r)		{PHY_M23_REG_B1_WrFL(M23A0,_port,_r);}

#define PHY_REG_B2_M23A0_RdFL(_port,_r)		{PHY_M23_REG_B2_RdFL(M23A0,_port,_r);}
#define PHY_REG_B2_M23A0_WrFL(_port,_r)		{PHY_M23_REG_B2_WrFL(M23A0,_port,_r);}


#define PHY_REG_M23A0_Rd01(_port,_r,_f01,_v01)			{PHY_M23_REG_Rd01(M23A0,_port,_r,_f01,_v01);}
#define PHY_REG_M23A0_Rd02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_M23_REG_Rd02(M23A0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B1_M23A0_Rd01(_port,_r,_f01,_v01)			{PHY_M23_REG_B1_Rd01(M23A0,_port,_r,_f01,_v01);}
#define PHY_REG_B1_M23A0_Rd02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_M23_REG_B1_Rd02(M23A0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B2_M23A0_Rd01(_port,_r,_f01,_v01)			{PHY_M23_REG_B2_Rd01(M23A0,_port,_r,_f01,_v01);}
#define PHY_REG_B2_M23A0_Rd02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_M23_REG_B2_Rd02(M23A0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_M23A0_Wr01(_port,_r,_f01,_v01)			{PHY_M23_REG_Wr01(M23A0,_port,_r,_f01,_v01);}
#define PHY_REG_M23A0_Wr02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_M23_REG_Wr02(M23A0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B1_M23A0_Wr01(_port,_r,_f01,_v01)			{PHY_M23_REG_B1_Wr01(M23A0,_port,_r,_f01,_v01);}
#define PHY_REG_B1_M23A0_Wr02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_M23_REG_B1_Wr02(M23A0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B2_M23A0_Wr01(_port,_r,_f01,_v01)			{PHY_M23_REG_B2_Wr01(M23A0,_port,_r,_f01,_v01);}
#define PHY_REG_B2_M23A0_Wr02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_M23_REG_B2_Wr02(M23A0,_port,_r,_f01,_v01,_f02,_v02);}

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
/* M23:A0 */
typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_PHY_REG_M23A0_T	*M23;
	} shdw;
} HDMI21_PHY_REG_CTRL_M23A0_T;

typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_PHY_REG_B1_M23A0_T	*M23;
	} shdw;
} HDMI21_PHY_REG_CTRL_B1_M23A0_T;


typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_PHY_REG_B2_M23A0_T	*M23;
	} shdw;
} HDMI21_PHY_REG_CTRL_B2_M23A0_T;

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
/* IOCTL */
int HDMI21_PHY_M23A0_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);

int HDMI21_PHY_M23A0_InitiatePhySystemCtrl(UINT8 port);
void HDMI21_PHY_M23A0_UpdatePhyLockFlag(UINT8 port);
int HDMI21_PHY_M23A0_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);
int HDMI21_PHY_M23A0_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff);
int HDMI21_PHY_M23A0_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain);
int HDMI21_PHY_M23A0_Check_TCSDone(UINT8 port);
int HDMI21_PHY_M23A0_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId);

int HDMI21_PHY_M23A0_Rx_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode);
UINT8 HDMI21_PHY_M23A0_Get_TMDS_FREQ(UINT8 port, int isMSB);
void HDMI21_PHY_M23A0_UpdatePhyTMDSclock(UINT8 port);
int HDMI21_PHY_M23A0_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId);
int HDMI21_PHY_M23A0_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId);
int HDMI21_PHY_M23A0_IsPhyPdbPowerOn(UINT8 port);
int HDMI21_PHY_M23A0_Check_SyncRecovery(UINT8 port);
int HDMI21_PHY_M23A0_Check_TMDSError(UINT8 port);
int HDMI21_PHY_M23A0_Check_DeltaError(UINT8 port);
int HDMI21_PHY_M23A0_Check_DeltaEye(UINT8 port);
int HDMI21_PHY_M23A0_Check_CEDError(UINT8 port);
int HDMI21_PHY_M23A0_Check_DfeResult(UINT8 port);
int HDMI21_PHY_M23A0_ToggleTCSEn(int port, int isSet);
int HDMI21_PHY_M23A0_Update_TMDS_TCS_Value(UINT8 port, int isClear);
void HDMI21_PHY_M23A0_InitiateDfeCenter(UINT8 port);
int HDMI21_PHY_M23A0_CheckDfeDone(UINT8 port);

/* 2020/06/09 : M23A0 Chip Bug SWWA */
int  HDMI21_PHY_M23A0_CheckEqCalDone(int port);
void HDMI21_PHY_M23A0_SetSaffManualValue(int port);
void HDMI21_PHY_M23A0_GetSaffValue(int port);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#endif
