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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     won.hur
 *  @version    1.0
 *  @date       2019-06-27
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_DSC_H_
#define	_HDMI21_RX_DSC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "base_types.h"
#include "reg_ctrl.h"
#include "sys_reg_base.h"

#include "hdmi21_hal_driver.h"		/* Device Handler */
#include "hdmi21_rx_dsc_core_o20a0.h"
#include "hdmi21_rx_dsc_top_o20a0.h"
#include "hdmi21_rx_fec_o20a0.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
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

#define HDMI21_DSC_F20IPC_VERSION			(0x00010002) /* version 1.2 */
#define HDMI21_DSC_F20IPC_MAGIC_START 		(0xBE0A0ACE)
#define HDMI21_DSC_F20IPC_MAGIC_END			(0xACE0DEAD)
#define HDMI21_DSC_PPS_DATA_SIZE			(sizeof(HDMI21_HAL_DSC_PPS_O20A0_T) / 4)

#define HDMI21_DSC_O20_F20_PPS_ADDR			(0xF023F830)	
#define HDMI21_DSC_O22_F22_PPS_ADDR			(0xF403F830)	// IIF -> DSC
#define HDMI21_DSC_O24_F24_PPS_ADDR			(0xF403F830)	// IIF -> DSC
#define HDMI21_DSC_O26_F24_PPS_ADDR			(0x0)	// FEC is no longer used from O26 



#define HDMI21_DSC_SUPPORT_VIC_CNT			(68)
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
/* DSC Top */
#define DSC_TOP_REG_O20A0_SHDW		(dscTopReg_o20a0.shdw.O20)

#define _REG_DSC_TOP_APB_RdFL(_chip, _reg, _data) \
	do{ __DSC_TOP_Reg_##_chip##_RdFL(_reg, (UINT32*)(&(_data))); } while(0)

#define _REG_DSC_TOP_APB_WrFL(_chip, _reg, _data) \
	do{ __DSC_TOP_Reg_##_chip##_WrFL(_reg, *((UINT32*)(&(_data)))); } while(0)

#define DSC_TOP_O20_REG_RdFL(_chip, _r)						\
	do{ 														\
		_REG_DSC_TOP_APB_RdFL(_chip,						\
					  _r##_##_chip##_REG_ADDR, 					\
					  DSC_TOP_REG_##_chip##_SHDW->_r);		\
	} while(0)

#define DSC_TOP_O20_REG_WrFL(_chip, _r)						\
	do{ 														\
		_REG_DSC_TOP_APB_WrFL(_chip,							\
					  _r##_##_chip##_REG_ADDR,					\
					  DSC_TOP_REG_##_chip##_SHDW->_r);		\
	} while(0)

/* Below Macro's do not use I2C, it just access the shadow's */
#define DSC_TOP_O20_REG_Rd01(_chip, _r,_f01,_v01) \
	_REG_Rd01(DSC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01)

#define DSC_TOP_O20_REG_Rd02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(DSC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)

#define DSC_TOP_O20_REG_Wr01(_chip,_r,_f01,_v01) \
	_REG_Wr01(DSC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01)

#define DSC_TOP_O20_REG_Wr02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(DSC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)


/* O20:A0 */
#define DSC_TOP_REG_O20A0_RdFL(_r)		{DSC_TOP_O20_REG_RdFL(O20A0,_r);}
#define DSC_TOP_REG_O20A0_WrFL(_r)		{DSC_TOP_O20_REG_WrFL(O20A0,_r);}

#define DSC_TOP_REG_O20A0_Rd01(_r,_f01,_v01)			{DSC_TOP_O20_REG_Rd01(O20A0,_r,_f01,_v01);}
#define DSC_TOP_REG_O20A0_Rd02(_r,_f01,_v01,_f02,_v02)	{DSC_TOP_O20_REG_Rd02(O20A0,_r,_f01,_v01,_f02,_v02);}

#define DSC_TOP_REG_O20A0_Wr01(_r,_f01,_v01)			{DSC_TOP_O20_REG_Wr01(O20A0,_r,_f01,_v01);}
#define DSC_TOP_REG_O20A0_Wr02(_r,_f01,_v01,_f02,_v02)	{DSC_TOP_O20_REG_Wr02(O20A0,_r,_f01,_v01,_f02,_v02);}


/* DSC Core */
#define DSC_CORE_REG_O20A0_SHDW		(dscCoreReg_o20a0.shdw.O20)

#define _REG_DSC_CORE_APB_RdFL(_chip, _reg, _data) \
	do{ __DSC_CORE_Reg_##_chip##_RdFL(_reg, (UINT32*)(&(_data))); } while(0)

#define _REG_DSC_CORE_APB_WrFL(_chip, _reg, _data) \
	do{ __DSC_CORE_Reg_##_chip##_WrFL(_reg, *((UINT32*)(&(_data)))); } while(0)

#define DSC_CORE_O20_REG_RdFL(_chip, _r)						\
	do{ 														\
		_REG_DSC_CORE_APB_RdFL(_chip,						\
					  _r##_##_chip##_REG_ADDR, 					\
					  DSC_CORE_REG_##_chip##_SHDW->_r);		\
	} while(0)

#define DSC_CORE_O20_REG_WrFL(_chip, _r)						\
	do{ 														\
		_REG_DSC_CORE_APB_WrFL(_chip,							\
					  _r##_##_chip##_REG_ADDR,					\
					  DSC_CORE_REG_##_chip##_SHDW->_r);		\
	} while(0)



/* Below Macro's do not use I2C, it just access the shadow's */
#define DSC_CORE_O20_REG_Rd01(_chip, _r,_f01,_v01) \
	_REG_Rd01(DSC_CORE_REG_##_chip##_SHDW,_r,_f01,_v01)

#define DSC_CORE_O20_REG_Rd02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(DSC_CORE_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)

#define DSC_CORE_O20_REG_Wr01(_chip,_r,_f01,_v01) \
	_REG_Wr01(DSC_CORE_REG_##_chip##_SHDW,_r,_f01,_v01)

#define DSC_CORE_O20_REG_Wr02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(DSC_CORE_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)


/* O20:A0 */
#define DSC_CORE_REG_O20A0_RdFL(_r)		{DSC_CORE_O20_REG_RdFL(O20A0,_r);}
#define DSC_CORE_REG_O20A0_WrFL(_r)		{DSC_CORE_O20_REG_WrFL(O20A0,_r);}

#define DSC_CORE_REG_O20A0_Rd01(_r,_f01,_v01)			{DSC_CORE_O20_REG_Rd01(O20A0,_r,_f01,_v01);}
#define DSC_CORE_REG_O20A0_Rd02(_r,_f01,_v01,_f02,_v02)	{DSC_CORE_O20_REG_Rd02(O20A0,_r,_f01,_v01,_f02,_v02);}

#define DSC_CORE_REG_O20A0_Wr01(_r,_f01,_v01)			{DSC_CORE_O20_REG_Wr01(O20A0,_r,_f01,_v01);}
#define DSC_CORE_REG_O20A0_Wr02(_r,_f01,_v01,_f02,_v02)	{DSC_CORE_O20_REG_Wr02(O20A0,_r,_f01,_v01,_f02,_v02);}


/* FEC Top */
#define FEC_TOP_REG_O20A0_SHDW		(fecTopReg_o20a0.shdw.O20)

#define _REG_FEC_TOP_APB_RdFL(_chip, _reg, _data) \
	do{ __FEC_TOP_Reg_##_chip##_RdFL(_reg, (UINT32*)(&(_data))); } while(0)

#define _REG_FEC_TOP_APB_WrFL(_chip, _reg, _data) \
	do{ __FEC_TOP_Reg_##_chip##_WrFL(_reg, *((UINT32*)(&(_data)))); } while(0)

#define FEC_TOP_O20_REG_RdFL(_chip, _r)						\
	do{ 														\
		_REG_FEC_TOP_APB_RdFL(_chip,						\
					  _r##_##_chip##_REG_ADDR, 					\
					  FEC_TOP_REG_##_chip##_SHDW->_r);		\
	} while(0)

#define FEC_TOP_O20_REG_WrFL(_chip, _r)						\
	do{ 														\
		_REG_FEC_TOP_APB_WrFL(_chip,							\
					  _r##_##_chip##_REG_ADDR,					\
					  FEC_TOP_REG_##_chip##_SHDW->_r);		\
	} while(0)

/* Below Macro's do not use I2C, it just access the shadow's */
#define FEC_TOP_O20_REG_Rd01(_chip, _r,_f01,_v01) \
	_REG_Rd01(FEC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01)

#define FEC_TOP_O20_REG_Rd02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Rd02(FEC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)

#define FEC_TOP_O20_REG_Wr01(_chip,_r,_f01,_v01) \
	_REG_Wr01(FEC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01)

#define FEC_TOP_O20_REG_Wr02(_chip,_r,_f01,_v01,_f02,_v02) \
	_REG_Wr02(FEC_TOP_REG_##_chip##_SHDW,_r,_f01,_v01,_f02,_v02)


/* O20:A0 */
#define FEC_TOP_REG_O20A0_RdFL(_r)		{FEC_TOP_O20_REG_RdFL(O20A0,_r);}
#define FEC_TOP_REG_O20A0_WrFL(_r)		{FEC_TOP_O20_REG_WrFL(O20A0,_r);}

#define FEC_TOP_REG_O20A0_Rd01(_r,_f01,_v01)			{FEC_TOP_O20_REG_Rd01(O20A0,_r,_f01,_v01);}
#define FEC_TOP_REG_O20A0_Rd02(_r,_f01,_v01,_f02,_v02)	{FEC_TOP_O20_REG_Rd02(O20A0,_r,_f01,_v01,_f02,_v02);}

#define FEC_TOP_REG_O20A0_Wr01(_r,_f01,_v01)			{FEC_TOP_O20_REG_Wr01(O20A0,_r,_f01,_v01);}
#define FEC_TOP_REG_O20A0_Wr02(_r,_f01,_v01,_f02,_v02)	{FEC_TOP_O20_REG_Wr02(O20A0,_r,_f01,_v01,_f02,_v02);}

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_DSC_TOP_REG_O20A0_T	*O20;
	} shdw;
} HDMI21_DSC_TOP_REG_CTRL_O20A0_T;

typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_DSC_CORE_REG_O20A0_T	*O20;
	} shdw;
} HDMI21_DSC_CORE_REG_CTRL_O20A0_T;

typedef struct
{
	union {
		UINT32          *addr;
		HDMI21_FEC_TOP_REG_O20A0_T	*O20;
	} shdw;
} HDMI21_FEC_TOP_REG_CTRL_O20A0_T;


typedef struct
{
	UINT32 addr;
	UINT32 value;
} HDMI21_CHIPINFO_DATA_T;

typedef enum 
{
	HDMI21_DSC_F20_VID_DELAY_CONFIG0 = 0,
	HDMI21_DSC_F20_VID_DELAY_CONFIG1,
	HDMI21_DSC_F20_VID_WRITE_CONFIG0,
	HDMI21_DSC_F20_VID_READ_CONFIG_0,
	HDMI21_DSC_F20_VID_READ_CONFIG_1,
	HDMI21_DSC_F20_VID2FEC_CH,
	HDMI21_DSC_F20_VID2FEC_ENABLE,
	HDMI21_DSC_F20_DSC2CVI_EN,
	HDMI21_DSC_F20_DSC2CVI_VSYNC,
	HDMI21_DSC_F20_DSC2CVI_VIDEO_FORMAT,
	HDMI21_DSC_F20_DSC2CVI_HSYNC,
	HDMI21_DSC_F20_DSC2CVI_START_FIFO,
	HDMI21_DSC_F20_D2C_SIG_ENABLE,
	HDMI21_DSC_F20_D2C_SYNC_DELAY,
	HDMI21_DSC_F20_FDEC_DSC_R01,
	HDMI21_DSC_F20_FDEC_DSC_R02,
	HDMI21_DSC_F20_FDEC_CONFIG_CTRL,
	HDMI21_DSC_F20_DEC_MAIN_CONF,
	HDMI21_DSC_F20_DEC0_DF_CTRL,
	HDMI21_DSC_F20_DEC1_DF_CTRL,
	HDMI21_DSC_F20_CRG_CVI02,
	HDMI21_DSC_F20_CRG_IIF13,
	HDMI21_DSC_F20_MAXNUM
} HDMI21_DSC_F20_SETDATA_T;


typedef struct
{
	UINT32 magicStart;	/* Always have to be "be a ace" -> 0xBE0A0ACE
						   This would be defined as "HDMI21_DSC_F20IPC_MAGIC_START" */
	UINT32 ipcVersion;	/* Indication of IPC data structure version 
						   This would be defined as "HDMI21_DSC_F20IPC_VERSION" */
	UINT32 msgId;		/* Will increament once data is refreshed. First data should be 1, not 0 */
	UINT32 cnt;		/* Count of Addr/Data array */
	HDMI21_CHIPINFO_DATA_T pps[HDMI21_DSC_PPS_DATA_SIZE];
	HDMI21_CHIPINFO_DATA_T f20Data[HDMI21_DSC_F20_MAXNUM];	/* Data requirment from jinhyuck92.kim. Check AVTASK-440 */
	UINT32 magicEnd;	/* Always have to be "ace dead" -> 0xACE0DEAD 
						   This would be defined as "HDMI21_DSC_F20IPC_MAGIC_END" */
} HDMI21_FEC_IPC_DATA_T;


typedef struct
{
	UINT32 vic;
	UINT32 hactive;
	UINT32 vactive;
	UINT32 vtotal;
	UINT32 vfreq;
	UINT32 hcActive_444;
	UINT32 hcBlank_444;
	UINT32 hcActive_422;
	UINT32 hcBlank_422;
	UINT32 hcActive_420;
	UINT32 hcBlank_420;
	UINT32 vfront;
	UINT32 vsync;
	UINT32 vback;
} HDMI21_DSC_VIC_LIST_T;

typedef struct
{
	UINT32 hsync_444;
	UINT32 hsync_422;
	UINT32 hsync_420;
	UINT32 hback_444;
	UINT32 hback_422;
	UINT32 hback_420;
	UINT32 hfront_444;
	UINT32 hfront_422;
	UINT32 hfront_420;
} HDMI21_DSC_VIC_H_PARAM_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void	HDMI21_DSC_Rx_Set_Initialize(void);
int 	HDMI21_DSC_Rx_Set_ExecuteDscModule(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
int		HDMI21_DSC_Rx_Set_InputPort(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32	HDMI21_DSC_Rx_TOP_Read(UINT32 addr);
void	HDMI21_DSC_Rx_TOP_Write(UINT32 addr, UINT32 data);
UINT32	HDMI21_DSC_Rx_CORE_Read(UINT32 addr);
void	HDMI21_DSC_Rx_CORE_Write(UINT32 addr, UINT32 data);
UINT32	HDMI21_FEC_Rx_TOP_Read(UINT32 addr);
void	HDMI21_FEC_Rx_TOP_Write(UINT32 addr, UINT32 data);

int HDMI21_DSC_Rx_Set_F20IpcData(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_FEC_IPC_DATA_T *pIpc);
int HDMI21_FEC_Rx_PQE_Write(HDMI21_FEC_IPC_DATA_T *pIpc);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

