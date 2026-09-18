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

#ifndef	_HDMI21_RX_SNPS_PEXTRACT_H_
#define	_HDMI21_RX_SNPS_PEXTRACT_H_

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



#define HDMI21_SNPS_REG_PKTEX_BCH_ERRCORR_CONFIG		(0x7C0)
#define HDMI21_SNPS_FIELD_BCH_AUD_ERRCORR_EN_QST		BIT(1)
#define HDMI21_SNPS_FIELD_BCH_ERRCORR_EN_QST			BIT(0)


#define HDMI21_SNPS_REG_PKTEX_BCH_ERRFILT_CONFIG		(0x7C4)
#define HDMI21_SNPS_FIELD_BCHSP_GENPKT1_ERRFILT_QST		BIT(29)
#define HDMI21_SNPS_FIELD_BCHSP_GENPKT0_ERRFILT_QST		BIT(28)
#define HDMI21_SNPS_FIELD_BCHSP_EMD_ERRFILT_QST			BIT(14)
#define HDMI21_SNPS_FIELD_BCHSP_DRMIF_ERRFILT_QST		BIT(13)
#define HDMI21_SNPS_FIELD_BCHSP_NTSCVBIIF_ERRFILT_QST	BIT(12)
#define HDMI21_SNPS_FIELD_BCHSP_AUDIF_ERRFILT_QST		BIT(10)
#define HDMI21_SNPS_FIELD_BCHSP_SRCPDIF_ERRFILT_QST		BIT(9)
#define HDMI21_SNPS_FIELD_BCHSP_AVIIF_ERRFILT_QST		BIT(8)
#define HDMI21_SNPS_FIELD_BCHSP_VSIF_ERRFILT_QST		BIT(7)
#define HDMI21_SNPS_FIELD_BCHSP_AMD_ERRFILT_QST			BIT(6)
#define HDMI21_SNPS_FIELD_BCHSP_GMD_ERRFILT_QST			BIT(5)
#define HDMI21_SNPS_FIELD_BCHSP_ISRC_ERRFILT_QST		BIT(4)
#define HDMI21_SNPS_FIELD_BCHSP_ACP_ERRFILT_QST			BIT(3)
#define HDMI21_SNPS_FIELD_BCHSP_GCP_ERRFILT_QST			BIT(2)
#define HDMI21_SNPS_FIELD_BCHSP_ACR_ERRFILT_QST			BIT(1)
#define HDMI21_SNPS_FIELD_BCHPH_ERRFILT_QST				BIT(0)

#define HDMI21_SNPS_REG_PKTEX_CHKSUM_ERRFILT_CONFIG		(0x7C8)
#define HDMI21_SNPS_FIELD_CHKSUM_GENPKT1_ERRFILT_QST	BIT(29)
#define HDMI21_SNPS_FIELD_CHKSUM_GENPKT0_ERRFILT_QST	BIT(28)
#define HDMI21_SNPS_FIELD_CHKSUM_DRMIF_ERRFILT_QST		BIT(6)
#define HDMI21_SNPS_FIELD_CHKSUM_NTSCVBIIF_ERRFILT_QST	BIT(5)
#define HDMI21_SNPS_FIELD_CHKSUM_AUDIF_ERRFILT_QST		BIT(3) 
#define HDMI21_SNPS_FIELD_CHKSUM_SRCPDIF_ERRFILT_QST	BIT(2)
#define HDMI21_SNPS_FIELD_CHKSUM_AVIIF_ERRFILT_QST		BIT(1)
#define HDMI21_SNPS_FIELD_CHKSUM_VSIF_ERRFILT_QST		BIT(0)

#define HDMI21_SNPS_REG_PKTEX_BCHERR_ACC_STATUS			(0x7CC)
#define HDMI21_SNPS_FIELD_BCHAUDERR_ACC_STS				MSK(16, 16)
#define HDMI21_SNPS_FIELD_BCHERR_ACC_STS				MSK(16, 0)


#define HDMI21_SNPS_REG_PKTEX_FIELDS_BCHERR_STATUS		(0x7D0)
#define HDMI21_SNPS_FIELD_FIELDS_SINCE_BCHAUDERR_STS	MSK(16, 16)
#define HDMI21_SNPS_FIELD_FIELDS_SINCE_BCHERR_STS		MSK(16, 0)

#define HDMI21_SNPS_REG_GENPKT_TYPE_CONFIG				(0x7D4)
#define HDMI21_SNPS_FIELD_GENPKT1_TYPE					MSK(8, 16)
#define HDMI21_SNPS_FIELD_GENPKT0_TYPE					MSK(7, 0)

#define HDMI21_SNPS_REG_PKTEX_UPI_CONFIG				(0x800)
#define HDMI21_SNPS_FIELD_UPI_GENPKT1_TYPE_EN_OUTPUT	BIT(29)
#define HDMI21_SNPS_FIELD_UPI_GENPKT0_TYPE_EN_OUTPUT	BIT(28)
#define HDMI21_SNPS_FIELD_UPI_EMD_EN_OUTPUT				BIT(21)
#define HDMI21_SNPS_FIELD_UPI_DRMIF_EN_OUTPUT			BIT(20)
#define HDMI21_SNPS_FIELD_UPI_NTSCVBIIF_EN_OUTPUT		BIT(19)
#define HDMI21_SNPS_FIELD_UPI_AUDIF_EN_OUTPUT			BIT(17)
#define HDMI21_SNPS_FIELD_UPI_SRCPDIF_EN_OUTPUT			BIT(16)
#define HDMI21_SNPS_FIELD_UPI_AVIIF_EN_OUTPUT			BIT(15)
#define HDMI21_SNPS_FIELD_UPI_VSIF_EN_OUTPUT			BIT(14)
#define HDMI21_SNPS_FIELD_UPI_MSOBA_EN_OUTPUT			BIT(13)
#define HDMI21_SNPS_FIELD_UPI_MSA_EN_OUTPUT				BIT(12)
#define HDMI21_SNPS_FIELD_UPI_AMD_EN_OUTPUT				BIT(11)
#define HDMI21_SNPS_FIELD_UPI_3DOBA_EN_OUTPUT			BIT(10)
#define HDMI21_SNPS_FIELD_UPI_3DA_EN_OUTPUT				BIT(9)
#define HDMI21_SNPS_FIELD_UPI_GMD_EN_OUTPUT				BIT(8)
#define HDMI21_SNPS_FIELD_UPI_HBR_EN_OUTPUT				BIT(7)
#define HDMI21_SNPS_FIELD_UPI_DST_EN_OUTPUT				BIT(6)
#define HDMI21_SNPS_FIELD_UPI_OBA_EN_OUTPUT				BIT(5)
#define HDMI21_SNPS_FIELD_UPI_ISRC_EN_OUTPUT			BIT(4) 
#define HDMI21_SNPS_FIELD_UPI_ACP_EN_OUTPUT				BIT(3)
#define HDMI21_SNPS_FIELD_UPI_GCP_EN_OUTPUT				BIT(2)
#define HDMI21_SNPS_FIELD_UPI_AS_EN_OUTPUT				BIT(1)
#define HDMI21_SNPS_FIELD_UPI_ACR_EN_OUTPUT				BIT(0)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/


	
/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
void HDMI21_PEXTRACT_Rx_Set_Initiate(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler);
void HDMI21_PEXTRACT_Rx_Set_GenPKTType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int type, UINT8 header);
void HDMI21_PEXTRACT_Rx_Set_UpiOutType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, UINT32 type);

int	HDMI21_PEXTRACT_Rx_Get_AccumBCHErrCnt(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isAudio);
int	HDMI21_PEXTRACT_Rx_Get_FieldCntError(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int isAudio);

UINT8 HDMI21_PEXTRACT_Rx_Get_GenPKTType(HDMI21_HAL_RX_DEVICE_DATA *pDevHandler, int type);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

