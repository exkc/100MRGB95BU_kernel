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
 * date       2019.12.17
 * note       Additional information.
 *
 * @addtogroup lg11xxx_sys
 * @{
 */
#ifndef __HDMI20_RX_PHY_E60B0_H__
#define __HDMI20_RX_PHY_E60B0_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"

#include "hdmi21_rx_phy_b0_e60b0.h"
#include "hdmi21_rx_phy_b1_e60b0.h"
#include "hdmi21_rx_phy_b2_e60b0.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* E60:B0 */
#define PHY_REG_E60B0_SHDW(_port)		(phyReg_e60b0[_port].shdw.E60)
#define PHY_REG_B1_E60B0_SHDW(_port)	(phyReg_B1_e60b0[_port].shdw.E60)
#define PHY_REG_B2_E60B0_SHDW(_port)	(phyReg_B2_e60b0[_port].shdw.E60)

/* E60 COMMON */
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


#define PHY_E60_REG_RdFL(_chip, _port, _r)						\
	do{ 														\
		_REG_PHY_APB_RdFL(_chip, _port,							\
					  _r##_##_chip##_REG_ADDR, 					\
					  PHY_REG_##_chip##_SHDW(_port)->_r);		\
	} while(0)

#define PHY_E60_REG_B1_RdFL(_chip, _port, _r)					\
	do{ 														\
		_REG_PHY_B1_APB_RdFL(_chip,	_port,						\
					  _r##_B1_##_chip##_REG_ADDR, 				\
					  PHY_REG_B1_##_chip##_SHDW(_port)->_r);	\
	} while(0)

#define PHY_E60_REG_B2_RdFL(_chip, _port, _r)					\
	do{ 														\
		_REG_PHY_B2_APB_RdFL(_chip,	_port,						\
					  _r##_B2_##_chip##_REG_ADDR, 				\
					  PHY_REG_B2_##_chip##_SHDW(_port)->_r);	\
	} while(0)


#define PHY_E60_REG_WrFL(_chip,_port, _r)						\
	do{ 														\
		_REG_PHY_APB_WrFL(_chip, _port,							\
					  _r##_##_chip##_REG_ADDR,					\
					  PHY_REG_##_chip##_SHDW(_port)->_r);		\
	} while(0)

#define PHY_E60_REG_B1_WrFL(_chip,_port, _r)						\
	do{ 															\
		_REG_PHY_B1_APB_WrFL(_chip,_port,							\
					  _r##_B1_##_chip##_REG_ADDR,					\
					  PHY_REG_B1_##_chip##_SHDW(_port)->_r);		\
	} while(0)

#define PHY_E60_REG_B2_WrFL(_chip,_port, _r)						\
	do{ 															\
		_REG_PHY_B2_APB_WrFL(_chip,_port,							\
					  _r##_B2_##_chip##_REG_ADDR,					\
					  PHY_REG_B2_##_chip##_SHDW(_port)->_r);		\
	} while(0)




/* Below Macro's do not use I2C, it just access the shadow's */
#define PHY_E60_REG_Rd01(_chip,_port,_r,_f01,_v01) \
	_REG_Rd01(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_E60_REG_Rd02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_E60_REG_B1_Rd01(_chip,_port,_r,_f01,_v01) \
	_REG_Rd01(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_E60_REG_B1_Rd02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_E60_REG_B2_Rd01(_chip,_port,_r,_f01,_v01) \
	_REG_Rd01(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_E60_REG_B2_Rd02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)


#define PHY_E60_REG_Wr01(_chip,_port,_r,_f01,_v01) \
	_REG_Wr01(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_E60_REG_Wr02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_REG_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_E60_REG_B1_Wr01(_chip,_port,_r,_f01,_v01) \
	_REG_Wr01(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_E60_REG_B1_Wr02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_REG_B1_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)

#define PHY_E60_REG_B2_Wr01(_chip,_port,_r,_f01,_v01) \
	_REG_Wr01(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01)

#define PHY_E60_REG_B2_Wr02(_chip,_port,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_REG_B2_##_chip##_SHDW(_port),_r,_f01,_v01,_f02,_v02)


/* E60:B0 */
#define PHY_REG_E60B0_RdFL(_port,_r)		{PHY_E60_REG_RdFL(E60B0,_port,_r);}
#define PHY_REG_E60B0_WrFL(_port,_r)		{PHY_E60_REG_WrFL(E60B0,_port,_r);}

#define PHY_REG_B1_E60B0_RdFL(_port,_r)		{PHY_E60_REG_B1_RdFL(E60B0,_port,_r);}
#define PHY_REG_B1_E60B0_WrFL(_port,_r)		{PHY_E60_REG_B1_WrFL(E60B0,_port,_r);}

#define PHY_REG_B2_E60B0_RdFL(_port,_r)		{PHY_E60_REG_B2_RdFL(E60B0,_port,_r);}
#define PHY_REG_B2_E60B0_WrFL(_port,_r)		{PHY_E60_REG_B2_WrFL(E60B0,_port,_r);}


#define PHY_REG_E60B0_Rd01(_port,_r,_f01,_v01)			{PHY_E60_REG_Rd01(E60B0,_port,_r,_f01,_v01);}
#define PHY_REG_E60B0_Rd02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_E60_REG_Rd02(E60B0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B1_E60B0_Rd01(_port,_r,_f01,_v01)			{PHY_E60_REG_B1_Rd01(E60B0,_port,_r,_f01,_v01);}
#define PHY_REG_B1_E60B0_Rd02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_E60_REG_B1_Rd02(E60B0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B2_E60B0_Rd01(_port,_r,_f01,_v01)			{PHY_E60_REG_B2_Rd01(E60B0,_port,_r,_f01,_v01);}
#define PHY_REG_B2_E60B0_Rd02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_E60_REG_B2_Rd02(E60B0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_E60B0_Wr01(_port,_r,_f01,_v01)			{PHY_E60_REG_Wr01(E60B0,_port,_r,_f01,_v01);}
#define PHY_REG_E60B0_Wr02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_E60_REG_Wr02(E60B0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B1_E60B0_Wr01(_port,_r,_f01,_v01)			{PHY_E60_REG_B1_Wr01(E60B0,_port,_r,_f01,_v01);}
#define PHY_REG_B1_E60B0_Wr02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_E60_REG_B1_Wr02(E60B0,_port,_r,_f01,_v01,_f02,_v02);}

#define PHY_REG_B2_E60B0_Wr01(_port,_r,_f01,_v01)			{PHY_E60_REG_B2_Wr01(E60B0,_port,_r,_f01,_v01);}
#define PHY_REG_B2_E60B0_Wr02(_port,_r,_f01,_v01,_f02,_v02)	{PHY_E60_REG_B2_Wr02(E60B0,_port,_r,_f01,_v01,_f02,_v02);}


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
/* E60:B0 */
typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_PHY_REG_E60B0_T	*E60;
	} shdw;
} HDMI21_PHY_REG_CTRL_E60B0_T;

typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_PHY_REG_B1_E60B0_T	*E60;
	} shdw;
} HDMI21_PHY_REG_CTRL_B1_E60B0_T;


typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_PHY_REG_B2_E60B0_T	*E60;
	} shdw;
} HDMI21_PHY_REG_CTRL_B2_E60B0_T;
/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
/* IOCTL */
int HDMI21_PHY_E60B0_Rx_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);

int HDMI21_PHY_E60B0_InitiatePhySystemCtrl(UINT8 port);
void HDMI21_PHY_E60B0_UpdatePhyLockFlag(UINT8 port);
int HDMI21_PHY_E60B0_Rx_AccessPhy(UINT8 port, LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);
int HDMI21_PHY_E60B0_ControlPhyPDB(UINT8 port, BOOLEAN bOnOff);
int HDMI21_PHY_E60B0_Set_3G6G_Mode(UINT8 port, UINT8 isAuto, HDMI21_HAL_PHY_INITIATED_MODE_T mode, UINT8 isScrambling, UINT8 lowfreqGain);
int HDMI21_PHY_E60B0_Check_TCSDone(UINT8 port);
int HDMI21_PHY_E60B0_Reset_EqOffsetCalibration(UINT8 port, UINT8 isReset, UINT32 callerId);

int HDMI21_PHY_E60B0_Rx_Initiate_Phy(int port, HDMI21_HAL_PHY_INITIATED_MODE_T mode);
UINT8 HDMI21_PHY_E60B0_Get_TMDS_FREQ(UINT8 port, int isMSB);
void HDMI21_PHY_E60B0_UpdatePhyTMDSclock(UINT8 port);
int HDMI21_PHY_E60B0_Reset_PLLPDB(UINT8 port, UINT8 isReset, UINT32 callerId);
int HDMI21_PHY_E60B0_PowerControl_PLLPDB(UINT8 port, UINT8 isDown, UINT32 callerId);
int HDMI21_PHY_E60B0_IsPhyPdbPowerOn(UINT8 port);
int HDMI21_PHY_E60B0_Check_SyncRecovery(UINT8 port);
int HDMI21_PHY_E60B0_Check_TMDSError(UINT8 port);
int HDMI21_PHY_E60B0_Check_DeltaError(UINT8 port);
int HDMI21_PHY_E60B0_Check_DeltaEye(UINT8 port);
int HDMI21_PHY_E60B0_Check_CEDError(UINT8 port);
int HDMI21_PHY_E60B0_Check_DfeResult(UINT8 port);
int HDMI21_PHY_E60B0_ToggleTCSEn(int port, int isSet);
int HDMI21_PHY_E60B0_Update_TMDS_TCS_Value(UINT8 port, int isClear);
void HDMI21_PHY_E60B0_InitiateDfeCenter(UINT8 port);
int HDMI21_PHY_E60B0_CheckDfeDone(UINT8 port);

/* 2020/06/09 : E60B0 Chip Bug SWWA */
int  HDMI21_PHY_E60B0_CheckEqCalDone(int port);
void HDMI21_PHY_E60B0_SetSaffManualValue(int port);
void HDMI21_PHY_E60B0_GetSaffValue(int port);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#endif
