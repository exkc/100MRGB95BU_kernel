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
 * author     taejun.lee 
 * version    1.0
 * date       2019.05.13
 * note       Additional information.
 *
 * @addtogroup lg11xxx_sys
 * @{
 */
#ifndef __HDMI20_EARC_PHY_O20_H__
#define __HDMI20_EARC_PHY_O20_H__


/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "hdmi20_kapi.h"
#include "hdmi_kapi.h"
#include "hdmi21_earc_phy_o20a0.h"

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/
/* O20 COMMON */
#define PHY_EARC_REG_O20A0_SHDW	(phyEARC_REG_o20a0.shdw.O20)

#define _EARC_REG_PHY_APB_RdFL(_chip, _EARC_REG, _data) \
	do{ __PHY_EARC_Reg_##_chip##_RdFL(_EARC_REG, (UINT32*)(&(_data))); } while(0)

#define _EARC_REG_PHY_APB_WrFL(_chip, _EARC_REG, _data) \
	do{ __PHY_EARC_Reg_##_chip##_WrFL(_EARC_REG, *((UINT32*)(&(_data)))); } while(0)

#define PHY_O20_EARC_REG_RdFL(_chip, _r)						\
	do{ 														\
		_EARC_REG_PHY_APB_RdFL(_chip,							\
					  _r##_##_chip##_EARC_REG_ADDR, 					\
					  PHY_EARC_REG_##_chip##_SHDW->_r);		\
	} while(0)

#define PHY_O20_EARC_REG_WrFL(_chip, _r)						\
	do{ 														\
		_EARC_REG_PHY_APB_WrFL(_chip,							\
					  _r##_##_chip##_EARC_REG_ADDR,					\
					  PHY_EARC_REG_##_chip##_SHDW->_r);		\
	} while(0)

/* Below Macro's do not use I2C, it just access the shadow's */
#define PHY_O20_EARC_REG_Rd01(_chip,_r,_f01,_v01) \
	_REG_Rd01(PHY_EARC_REG_##_chip##_SHDW,_r,_f01,_v01)

#define PHY_O20_EARC_REG_Rd02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(PHY_EARC_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)

#define PHY_O20_EARC_REG_Wr01(_chip,_r,_f01,_v01) \
	_REG_Wr01(PHY_EARC_REG_##_chip##_SHDW,_r,_f01,_v01)

#define PHY_O20_EARC_REG_Wr02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(PHY_EARC_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)


/* O20:A0 */
#define PHY_EARC_REG_O20A0_RdFL(_r)		{PHY_O20_EARC_REG_RdFL(O20A0,_r);}
#define PHY_EARC_REG_O20A0_WrFL(_r)		{PHY_O20_EARC_REG_WrFL(O20A0,_r);}

#define PHY_EARC_REG_O20A0_Rd01(_r,_f01,_v01)				{PHY_O20_EARC_REG_Rd01(O20A0,_r,_f01,_v01);}
#define PHY_EARC_REG_O20A0_Rd02(_r,_f01,_v01,_f02,_v02)		{PHY_O20_EARC_REG_Rd02(O20A0,_r,_f01,_v01,_f02,_v02);}

#define PHY_EARC_REG_O20A0_Wr01(_r,_f01,_v01)				{PHY_O20_EARC_REG_Wr01(O20A0,_r,_f01,_v01);}
#define PHY_EARC_REG_O20A0_Wr02(_r,_f01,_v01,_f02,_v02)		{PHY_O20_EARC_REG_Wr02(O20A0,_r,_f01,_v01,_f02,_v02);}
/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_EARC_PHY_REG_O20A0_T	*O20;
	} shdw;
} HDMI21_EARC_PHY_REG_CTRL_O20A0_T;


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
/* IOCTL */

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
int HDMI21_PHY_EARC_O20A0_InitiatePhySystemCtrl(void);
int HDMI21_PHY_EARC_O20A0_Rx_AccessPhy(LX_HDMI20_PHY_ACCESS_T *pPhyCtrl, int size);


#endif
