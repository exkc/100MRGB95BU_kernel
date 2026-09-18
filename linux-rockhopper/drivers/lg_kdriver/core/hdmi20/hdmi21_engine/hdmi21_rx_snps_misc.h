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
 *  @date       2019-04-01
 *  @note       Additional information.
 */

#ifndef	_HDMI21_RX_SNPS_MISC_H_
#define	_HDMI21_RX_SNPS_MISC_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/


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

#define HDMI21_SNPS_REG_CORE_ID							(0x0)
#define HDMI21_SNPS_REG_VER_NUMBER						(0x4)
#define HDMI21_SNPS_REG_VER_TYPE						(0x8)
#define HDMI21_SNPS_REG_CONFIG_REG						(0xC)
#define HDMI21_SNPS_REG_CORE_TIMESTAMP_HHMM				(0x14)
#define HDMI21_SNPS_REG_CORE_TIMESTAMP_MMDD				(0x18)
#define HDMI21_SNPS_REG_CORE_TIMESTAMP_YYYY 			(0x1C)


#define HDMI21_SNPS_REG_GLOBAL_SWRESET_REQUEST			(0x20)
#define HDMI21_SNPS_FIELD_EARCTX_SWRESETREQ				BIT(22)
#define HDMI21_SNPS_FIELD_PHYCTRL_SWRESETREQ			BIT(21)
#define HDMI21_SNPS_FIELD_APB_SWRESETREQ				BIT(17)
#define HDMI21_SNPS_FIELD_CEC_SWRESETREQ				BIT(16)
#define HDMI21_SNPS_FIELD_DATAPATH_SWRESETREQ			BIT(12)
#define HDMI21_SNPS_FIELD_PKTFIFO_SWRESETREQ			BIT(11)
#define HDMI21_SNPS_FIELD_HDCP_SWRESETREQ				BIT(10)
#define HDMI21_SNPS_FIELD_AUDIO_SWRESETREQ				BIT(9)
#define HDMI21_SNPS_FIELD_AVPUNIT_SWRESETREQ			BIT(8)
#define HDMI21_SNPS_FIELD_HDCPQP_SWRESETREQ				BIT(5)
#define HDMI21_SNPS_FIELD_DATAPATHONLY_SWRESETREQ		BIT(4)
#define HDMI21_SNPS_FIELD_MAIN_SWRESETREQ				BIT(0)

#define HDMI21_SNPS_REG_GLOBAL_SWENABLE					(0x24)
#define HDMI21_SNPS_FIELD_EARCTX_CMDC_ENABLE			BIT(24)
#define HDMI21_SNPS_FIELD_EARCTX_DMAC_ENABLE			BIT(23)
#define HDMI21_SNPS_FIELD_EARCTX_ENABLE					BIT(22)
#define HDMI21_SNPS_FIELD_PHYCTRL_ENABLE				BIT(21)
#define HDMI21_SNPS_FIELD_CEC_ENABLE					BIT(16)
#define HDMI21_SNPS_FIELD_FRL_ENABLE					BIT(14)
#define HDMI21_SNPS_FIELD_TMDS_ENABLE					BIT(13)
#define HDMI21_SNPS_FIELD_DATAPATH_ENABLE				BIT(12)
#define HDMI21_SNPS_FIELD_PKTFIFO_ENABLE				BIT(11)
#define HDMI21_SNPS_FIELD_HDCP_ENABLE					BIT(10)
#define HDMI21_SNPS_FIELD_AUDIO_ENABLE					BIT(9)
#define HDMI21_SNPS_FIELD_AVPUNIT_ENABLE				BIT(8)
#define HDMI21_SNPS_FIELD_MAIN_ENABLE					BIT(0)

#define HDMI21_SNPS_REG_GLOBAL_TIMER_REF_BASE			(0x28)
#define HDMI21_SNPS_FIELD_TIMER_REFERENCE_BASE			MSK(29, 0)


#define HDMI21_SNPS_REG_CORE_CONFIG						(0x50)
#define HDMI21_SNPS_FIELD_HPD_D							BIT(3)
#define HDMI21_SNPS_FIELD_HPD_C							BIT(2)
#define HDMI21_SNPS_FIELD_HPD_B							BIT(1)
#define HDMI21_SNPS_FIELD_HPD_A							BIT(0)


#define HDMI21_SNPS_REG_CMU_CONFIG0						(0x60)
#define HDMI21_SNPS_FIELD_TMDSQPCLK_STABLE_FREQ_MARGIN	MSK(15, 16)
#define HDMI21_SNPS_FIELD_AUDCLK_STABLE_FREQ_MARGIN		MSK(15, 0)	

#define HDMI21_SNPS_REG_CMU_CONFIG3						(0x6C)
#define HDMI21_SNPS_FIELD_FRLCLK_STABLE_FREQ_MARGIN		MSK(15, 0)

#define HDMI21_SNPS_REG_CMU_CONFIG4						(0x70)
#define HDMI21_SNPS_FIELD_EARC_BPCLK_STABLE_FREQ_MARGIN	MSK(15, 16)
#define HDMI21_SNPS_FIELD_EARC_AUDCLK_STABLE_FREQ_MARGIN	MSK(15, 0)

#define HDMI21_SNPS_REG_CMU_STATUS						(0x7C)
#define HDMI21_SNPS_FIELD_TIMER_BASE_LOCKED_ST			BIT(28)
#define HDMI21_SNPS_FIELD_EARC_BPCLK_OFF_ST				BIT(27)
#define HDMI21_SNPS_FIELD_EARC_BPCLK_LOCKED_ST			BIT(26)
#define HDMI21_SNPS_FIELD_EARC_AUDCLK_OFF_ST			BIT(25)
#define HDMI21_SNPS_FIELD_EARC_AUDCLK_LOCKED_ST			BIT(24)
#define HDMI21_SNPS_FIELD_FRLCLK_OFF_ST					BIT(23)
#define HDMI21_SNPS_FIELD_FRLCLK_LOCKED_ST				BIT(22)
#define HDMI21_SNPS_FIELD_TMDSQPCLK_OFF_ST				BIT(5)
#define HDMI21_SNPS_FIELD_TMDSQPCLK_LOCKED_ST			BIT(4)
#define HDMI21_SNPS_FIELD_AUDCLK_OFF_ST					BIT(1)
#define HDMI21_SNPS_FIELD_AUDCLK_LOCKED_ST				BIT(0)

#define HDMI21_SNPS_REG_CMU_AUDCLK_FREQ					(0x80)
#define HDMI21_SNPS_FIELD_AUDCLK_FREQ					MSK(20, 0)

#define HDMI21_SNPS_REG_CMU_TMDSQPCLK_FREQ				(0x84)
#define HDMI21_SNPS_FIELD_TMDSQPCLK_FREQ				MSK(20, 0)

#define HDMI21_SNPS_REG_CMU_MAIN_CONFIG					(0xBC)
#define HDMI21_SNPS_FIELD_CMU_EN						BIT(0)

#define HDMI21_SNPS_REG_MAINUNIT_STATUS					(0x150)
#define HDMI21_SNPS_FIELD_EARC_BPCLK_VALID_STABLE_ST	BIT(3)
#define HDMI21_SNPS_FIELD_TMDSVALID_STABLE_ST			BIT(1)
#define HDMI21_SNPS_FIELD_AUDPLL_LOCK_STABLE_ST			BIT(0)

#define HDMI21_SNPS_REG_I2C_SLAVE_CONFIG0				(0x160)
#define HDMI21_SNPS_FIELD_I2C_REPLY_NACK				BIT(20)	
#define HDMI21_SNPS_FIELD_I2C_H2_SEL_ADDR_QST			MSK(8, 12)
#define HDMI21_SNPS_FIELD_I2C_SPIKE_SUPPR_QST			MSK(2, 8)
#define HDMI21_SNPS_FIELD_I2C_TIMEOUT_EN_QST			BIT(4)
#define HDMI21_SNPS_FIELD_I2C_TIMEOUT_CNT_QST			MSK(3, 0)

#define HDMI21_SNPS_REG_I2C_SLAVE_CONFIG1				(0x164)
#define HDMI21_SNPS_FIELD_I2C_SDA_OUT_HOLD_VALUE_QST	MSK(8, 8)
#define HDMI21_SNPS_FIELD_I2C_SDA_IN_HOLD_VALUE_QST		MSK(8, 0)
	
	
	
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	HDMI21_SNPS_RST_MAIN 		= 0x00000001,
	HDMI21_SNPS_RST_AVPUNIT		= 0x00000002,
	HDMI21_SNPS_RST_AUDIO		= 0x00000004,
	HDMI21_SNPS_RST_HDCP		= 0x00000008,
	HDMI21_SNPS_RST_PKTFIFO		= 0x00000010,
	HDMI21_SNPS_RST_DATAPATH	= 0x00000020,
	HDMI21_SNPS_RST_CEC			= 0x00000040,
	HDMI21_SNPS_RST_APB			= 0x00000080,
	HDMI21_SNPS_RST_PHYCTRL		= 0x00000100,
	HDMI21_SNPS_RST_EARCTX		= 0x00000200,
	HDMI21_SNPS_RST_DATAPATHONLY= 0x00000400,
	HDMI21_SNPS_RST_HDCPQP		= 0x00000800,
	HDMI21_SNPS_RST_MAXNUM		= 0xFFFFFFFF, 
} HDMI21_SNPS_RST_TYPE_T;

typedef enum
{
	HDMI21_SNPS_CMU_AUDCLK_LOCKED		= HDMI21_SNPS_FIELD_AUDCLK_LOCKED_ST,
	HDMI21_SNPS_CMU_AUDCLK_OFF			= HDMI21_SNPS_FIELD_AUDCLK_OFF_ST,		
	HDMI21_SNPS_CMU_TMDSQPCLK_LOCKED	= HDMI21_SNPS_FIELD_TMDSQPCLK_LOCKED_ST,
	HDMI21_SNPS_CMU_TMDSQPCLK_OFF		= HDMI21_SNPS_FIELD_TMDSQPCLK_OFF_ST,
	HDMI21_SNPS_CMU_FRLCLK_LOCKED		= HDMI21_SNPS_FIELD_FRLCLK_LOCKED_ST,
	HDMI21_SNPS_CMU_FRLCLK_OFF			= HDMI21_SNPS_FIELD_FRLCLK_OFF_ST,
	HDMI21_SNPS_CMU_EARC_AUDCLK_LOCKED	= HDMI21_SNPS_FIELD_EARC_AUDCLK_LOCKED_ST,
	HDMI21_SNPS_CMU_EARC_AUDCLK_OFF		= HDMI21_SNPS_FIELD_EARC_AUDCLK_OFF_ST,
	HDMI21_SNPS_CMU_EARC_BPCLK_LOCKED	= HDMI21_SNPS_FIELD_EARC_BPCLK_LOCKED_ST,
	HDMI21_SNPS_CMU_EARC_BPCLK_OFF		= HDMI21_SNPS_FIELD_EARC_BPCLK_OFF_ST,
	HDMI21_SNPS_CMU_TIMER_BASE_LOCKED	= HDMI21_SNPS_FIELD_TIMER_BASE_LOCKED_ST
} HDMI21_SNPS_CMU_STATUS_T;

	
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
UINT32 HDMI21_MISC_Rx_Get_CoreID(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_MISC_Rx_Get_CoreVerNum(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_MISC_Rx_Get_CoreVerType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_MISC_Rx_Get_CoreTStampHHMM(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_MISC_Rx_Get_CoreTStampMMDD(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32 HDMI21_MISC_Rx_Get_CoreTStampYYYY(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

void	HDMI21_MISC_Rx_Set_ResetCore(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, HDMI21_SNPS_RST_TYPE_T type);
void	HDMI21_MISC_Rx_Set_RefClkValue(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value);
UINT32 	HDMI21_MISC_Rx_Get_RefClkValue(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

void 	HDMI21_MISC_Rx_Set_CoreHpdConfig(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value);
void 	HDMI21_MISC_Rx_Set_CoreCmuTmdsQpClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value);
void 	HDMI21_MISC_Rx_Set_CoreCmuAudioClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value);
void 	HDMI21_MISC_Rx_Set_CoreCmuFlrClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value);
void 	HDMI21_MISC_Rx_Set_CoreCmuEarcBpClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value);
void 	HDMI21_MISC_Rx_Set_CoreCmuEarcAudClkMargin(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT16 value);

HDMI21_SNPS_CMU_STATUS_T HDMI21_MISC_Rx_Get_CoreCmuStatus(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

UINT32	HDMI21_MISC_Rx_Get_CoreCmuAudClkFreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
UINT32	HDMI21_MISC_Rx_Get_CoreCmuTmdsQpClkFreq(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);

void	HDMI21_MISC_Rx_Set_CoreCmuEnable(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool enable);

void 	HDMI21_MISC_Rx_Set_I2cSlaveSpikeSuppr(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value);
void 	HDMI21_MISC_Rx_Set_I2cSlaveTimeOutEn(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, bool enable);
void 	HDMI21_MISC_Rx_Set_I2cSlaveTimeOutCnt(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 value);
void	HDMI21_MISC_Rx_Set_I2cSlaveSdaHoldTime(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 holdOut, UINT32 holdIn);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

