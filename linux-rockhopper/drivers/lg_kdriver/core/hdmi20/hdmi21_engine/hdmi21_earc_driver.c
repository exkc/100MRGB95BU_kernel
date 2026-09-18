/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

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
 *  @author		Taejun Lee (taejun.lee@lge.com)
 *  @version	1.0
 *  @date		2019-04-05
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/spinlock.h>
#include <linux/spinlock_types.h>
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/semaphore.h>
#include <linux/platform_device.h>
#include <asm/io.h>

#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/div64.h>
#include <linux/kthread.h>
#include <linux/seq_file.h>

#include <linux/gpio/machine.h>
#include <linux/gpio/consumer.h>

#include "hdmi21_earc_driver.h"

#include "hdmi21_rx_audio.h"
#include "hdmi21_rx_snps_vproc.h"
#include "hdmi21_rx_snps_misc.h"

#include "hdmi21_hal_driver.h"
#include "hdmi21_rx_disland.h" /* Data island control */
#include "../hdmi20_drv.h"

#include "hdmi_kapi.h"

#include "os_util.h"


/*----------------------------------------------------------------------------------------
  Constant Definitions
  ----------------------------------------------------------------------------------------*/
#define HDMI21_EARC_KERNEL_DRIVER_DATE 20190528
#define HDMI21_EARC_KERNEL_DRIVER_VER 0x01

#ifndef ON
#define ON	1
#endif

#ifndef OFF
#define OFF 0
#endif

/*----------------------------------------------------------------------------------------
  Macro Definitions
  ----------------------------------------------------------------------------------------*/
#define TBL_NUM(X)						(sizeof(X) /sizeof((X)[0]))
#define ENUM_TO_STR(x) #x

#define u32CHK_RANGE(X,Y,offset)		((((int)X - (int)Y) <= (int)offset) && (((int)X - (int)Y) >= -(int)offset))

#define E_TO_S(x) #x	

#define HDMI21_EARC_REG_WR(address,data)   \
	__sMapped_address_earc=(UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(__sMapped_address_earc == NULL) break;\
	*__sMapped_address_earc = data;\
	iounmap((void *)__sMapped_address_earc);\
}while(0);\

#define HDMI21_EARC_REG_RD(address,data)   \
	__sMapped_address_earc = (UINT32 *)ioremap(address, sizeof(UINT32));\
do{\
	if(__sMapped_address_earc == NULL) {data = 0; break;}\
	data = (unsigned int)*__sMapped_address_earc;\
	iounmap((void *)__sMapped_address_earc);\
}while(0);\

/*----------------------------------------------------------------------------------------
  Type Definitions
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
  ----------------------------------------------------------------------------------------*/
extern HDMI21_HAL_RX_DEVICE_DATA 		gHDMI21RxHandler[HDMI21_NUM_OF_MAX_PORTS];
extern HDMI20_DEV_CONTROL_T 			gHDMI21RxDevVideoControler[HDMI21__DEV_VIDEO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T			gHDMI21RxDevAudioControler[HDMI21__DEV_AUDIO_CONTROL_LIST_MAXNUM];
extern HDMI20_DEV_CONTROL_T			gHDMI21RxDevLinkControler[HDMI21__DEV_LINK_CONTROL_LIST_MAXNUM];

/* Number of Max operable ports */
extern int		g_hdmi20_number_of_ports;
/*----------------------------------------------------------------------------------------
  global Variables
  ----------------------------------------------------------------------------------------*/
/* I2C APB bridge memory */
HDMI21_HAL_MEMORY_MAPPING_T earcO20mem;
HDMI21_EARC_THREAD_CONTROLLER_T gHDMI21EARCThread = {NULL, 0, 0, HDMI21_EARC_INITIAL_THREAD_SLEEP_MS};

/* Device Data */
HDMI21_EARC_DEVICE_DATA gHDMI21EARCData;

/* Device controler : This contols the behavior of the Driver */
HDMI20_DEV_CONTROL_T	gHDMI21DevEARCControler[HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM]=
{
	{E_TO_S(HDMI21_EARC__VERSION)						, 0x0	, "[Ver] 20250613"},
	{E_TO_S(HDMI21_EARC__DEBUG)							, 0x0	, "===[EARC DEBUG MENU====="},
	{E_TO_S(HDMI21_EARC__LINE_DBG)						, 0x0	, "[DBG]Line Debug"},

	{E_TO_S(HDMI21_EARC__INFO)							, 0x0	, "=========[INFO]========="},
	{E_TO_S(HDMI21_EARC__INFO__FUNCTION_CALL)			, 0x0	, "[INFO]Funtion Call"},
	{E_TO_S(HDMI21_EARC__INFO__STATUS)					, 0x0	, "[INFO]Status"},
	{E_TO_S(HDMI21_EARC__INFO__REG)						, 0x0	, "[INFO]Reg"},
	{E_TO_S(HDMI21_EARC__INFO__CAP)						, 0x0	, "[INFO]Capability data structure"},
	{E_TO_S(HDMI21_EARC__INFO__MODE)					, 0x0	, "[INFO]eARC Mode(0:ARC, 1:eARC)"},
	{E_TO_S(HDMI21_EARC__INFO__CONNECTION)					, 0x0	, "[INFO]Connection Status"},
	{E_TO_S(HDMI21_EARC__INFO__GLOBAL)					, 0x0	, "[INFO]Global Value Status"},
	{E_TO_S(HDMI21_EARC__INFO__DEBUGGING_DATA)			, 0x0	, "[INFO]PHY 0x24 debugging data"},
	
	{E_TO_S(HDMI21_EARC__CNT)							, 0x0	, "=========[CNT]========="},
	{E_TO_S(HDMI21_EARC__CNT__RESTART)					, 0x0	, "[CNT]Restart"},
	{E_TO_S(HDMI21_EARC__CNT__HPD_STABLE)				, 0x5	, "[CNT]HPD Stable"},
	{E_TO_S(HDMI21_EARC__CNT__FORCE_READ)				, 0x0	, "[CNT]Force Read(1:Latency,2:Cap)"},
	{E_TO_S(HDMI21_EARC__CNT__HPD_BIT_WAIT_ON)			, 0x5	, "[CNT]HPD Bit On Wait"},
	{E_TO_S(HDMI21_EARC__CNT__HPD_BIT_WAIT_OFF)			, 0xA	, "[CNT]HPD Bit Off Wait"},
	
	{E_TO_S(HDMI21_EARC__SET)							, 0x0	, "=========[SET]========="},
	{E_TO_S(HDMI21_EARC__SET__I2C)						, 0x0	, "[SET]I2C"},
	{E_TO_S(HDMI21_EARC__SET__PHY)						, 0x0	, "[SET]PHY"},
	{E_TO_S(HDMI21_EARC__SET__LINK)						, 0x0	, "[SET]LINK"},
	{E_TO_S(HDMI21_EARC__SET__EARC_MODE)				, 0x0	, "[SET]eARC Mode(0:Off,1:ARC,2:eARC)"},
	{E_TO_S(HDMI21_EARC__SET__ECC_EN)					, 0x0	, "[SET]ECC Enable(1:On, 2:Off,)"},
	{E_TO_S(HDMI21_EARC__SET__ENDMARKER_EN)				, 0x0	, "[SET]EndMarker Enable(0:Off,1:enable)"},
	{E_TO_S(HDMI21_EARC__SET__HPDBIT_RESET_EN)			, 0x0	, "[SET]HPD Bit Reset Enable"},
	{E_TO_S(HDMI21_EARC__SET__ARC)						, 0x0	, "[SET]ARC"},
	{E_TO_S(HDMI21_EARC__SET__FORCE_READ_EN)			, 0x0	, "[SET]Force Rx info read Enable(0:off)"},
	{E_TO_S(HDMI21_EARC__SET__PHY_EXTR_RCTRL)			, 0xFF	, "[SET]PHY EXTR_RCTRL(0:off)"},
	{E_TO_S(HDMI21_EARC__SET__PHY_IREF_RBIAS)			, 0xFF	, "[SET]PHY IREF_RBIAS(0:off)"},
	{E_TO_S(HDMI21_EARC__SET__PHY_VREG_VREF)			, 0xFF	, "[SET]PHY VREG_VREF(0:off)"},


	{E_TO_S(HDMI21_EARC__CALL)							, 0x0	, "=========[CALL]========="},
	{E_TO_S(HDMI21_EARC__CALL__TEST)					, 0x0	, "[CALL]TEST"},
	{E_TO_S(HDMI21_EARC__CALL__TEST__IDLE1_REG_RESET)	, 0x0	, "[CALL]IDLE1 Force Reg reset TEST"},
	{E_TO_S(HDMI21_EARC__CALL__TEST__NONE_REG_RESET)	, 0x1	, "[CALL]None Force Reg reset TEST"},
	{E_TO_S(HDMI21_EARC_DBG)							, 0x0	, "=========[DBG]========="},
};

/* eARC Status */
static unsigned int *__sMapped_address_earc;

static HDMI21_EARC_XACT_STATUS_T 	_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__READY;
static HDMI21_EARC_XACT_RESULT_T 	_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__INIT;
static HDMI21_EARC_CONNECTION_INFO_T _gHdmi21EARCConnectionInfo; // NEED initialize
static BOOLEAN _gHdmi21EARCIsInit = FALSE;
static BOOLEAN _gHdmi21EARCIsDetectEn = FALSE;
static BOOLEAN _gHdmi21EARCIsDetect = FALSE;
static BOOLEAN _gHdmi21EARCIsOutEn = FALSE;
static BOOLEAN _gHdmi21EARCIsOut = FALSE;
static BOOLEAN _gHdmi21EARCIsStatChng = FALSE;
static BOOLEAN _gHdmi21EARCIsCapChng = FALSE;
static BOOLEAN _gHdmi21EARCStatChngFlag = FALSE;
static BOOLEAN _gHdmi21EARCCapChngFlag = FALSE;
static UINT32 _gHdmi21EARCRestartCnt = 0;
static UINT32 _gHdmi21EARCHPDStableCnt = 0;
static UINT32 _gHdmi21EARCForceReadCnt = 0;
static UINT32 _gHdmi21EARCReadCnt = 0;
static UINT32 _gHdmi21EARCReadCap = 0;
static UINT32 _gHdmi21EARCReadLatency = 0;
// HPD Bit Control
static BOOLEAN _gHdmi21EARCHpdBitResetEn = FALSE;
static BOOLEAN _gHdmi21EARCIsHpdBitReset = FALSE;
static UINT32 _gHdmi21EARCHpdBitWaitOnCnt = 0;
static UINT32 _gHdmi21EARCHpdBitWaitOffCnt = 0;

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
  ----------------------------------------------------------------------------------------*/
//static void __HDMI21_EARC_Init_Dev_Handler(UINT8 isResume);
static void __HDMI21_EARC_Get_Status(void);
static void __HDMI21_EARC_UpdateInfo(void);
static void __HDMI21_Tx_eARC_SetHpdBit(void);
static void __HDMI21_EARC_Get_Xact_Control(void);
static void __HDMI21_EARC_Get_Xact_Read(void);
static void __HDMI21_EARC_Get_Xact_Status(void);
static void __HDMI21_EARC_Get_Xact_Result(void);
static void __HDMI21_EARC_Debug(void);

/*----------------------------------------------------------------------------------------
  Static Variables
  ----------------------------------------------------------------------------------------*/

/*========================================================================================
  Implementation Group
  ========================================================================================*/

/*========================================================================================
  Implementation Group
  ========================================================================================*/

/* -------------------------------------------------------------------------------
 * Static Function below this line
 * ------------------------------------------------------------------------------- */
void HDMI21_Tx_EARC_InitializeMemAccess(void)
{	
	do{
		/* [Init]eARC Phy Register IOremap */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) ){
			earcO20mem.hwAddr = HDMI21_TX_EARC_O26_PHY_REG_ADDRESS;
			earcO20mem.size = HDMI21_TX_EARC_PHY_REG_SIZE;
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) ){
			earcO20mem.hwAddr = HDMI21_TX_EARC_O24_PHY_REG_ADDRESS;
			earcO20mem.size = HDMI21_TX_EARC_PHY_REG_SIZE;
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			earcO20mem.hwAddr = HDMI21_TX_EARC_M23_PHY_REG_ADDRESS;
			earcO20mem.size = HDMI21_TX_EARC_PHY_REG_SIZE;
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			earcO20mem.hwAddr = HDMI21_TX_EARC_O22_PHY_REG_ADDRESS;
			earcO20mem.size = HDMI21_TX_EARC_PHY_REG_SIZE;
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			earcO20mem.hwAddr = HDMI21_TX_EARC_PHY_REG_ADDRESS;
			earcO20mem.size = HDMI21_TX_EARC_PHY_REG_SIZE;
		}
		
		if(earcO20mem.hwAddr == 0) {
			HDMI20_INFO("HDMI eARC Error! Link HW memory value NULL. Abort memory allocation\n");
			break;
		}

		if(earcO20mem.pSwAddr == NULL) {
			earcO20mem.pSwAddr = (volatile UINT32 *)ioremap(earcO20mem.hwAddr, earcO20mem.size);
		}
		else{
			iounmap((void *)earcO20mem.pSwAddr);
			earcO20mem.pSwAddr = (volatile UINT32 *)ioremap(earcO20mem.hwAddr, earcO20mem.size);
		}
	}while(0);

}

int HDMI21_Tx_eARC_Open(void){
	int ret = RET_ERROR;
	UINT32 data;
	HDMI21_EARC_DEVICE_DATA *_e;
	
	do{
		/* [Init]eARC thread */
		if(gHDMI21EARCThread.isAlive <= 0){
#if 1		
			/* [Set]Phy Register */
			if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
#if 0			
				HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_M23_RESET, data)
				if((data & HDMI21_TX_EARC__I2C_M23_RESET_DISABLE) != HDMI21_TX_EARC__I2C_M23_RESET_DISABLE){
					//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
					HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_M23_RESET, HDMI21_TX_EARC__I2C_M23_RESET_DISABLE);
					_gHdmi21EARCIsInit = TRUE;
				}
#endif				
				_gHdmi21EARCIsInit = TRUE;
			}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
				HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_O22_RESET, data)
				if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
					//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
					HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
					_gHdmi21EARCIsInit = TRUE;
				}
			}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
				HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_B0_RESET, data)
				if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
					//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_B0_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
					HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_B0_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
					_gHdmi21EARCIsInit = TRUE;
				}
			}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
				HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_RESET, data)
				if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
					//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
					HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
					_gHdmi21EARCIsInit = TRUE;
				}
			}
#endif
			gHDMI21EARCThread.isAlive = 1;
			gHDMI21EARCThread.pThread= kthread_create( (void *)HDMI21_Tx_EARC_MainThread, 0, "hdmi21_earc_engine");
			if(gHDMI21EARCThread.pThread){
				HDMI20_INFO("HDMI eARC Initialing thread\n");
				wake_up_process(gHDMI21EARCThread.pThread);
			}else HDMI20_ERROR("Cannot initiate eARC thread\n");
			
			/* [Init]Count */
			_gHdmi21EARCRestartCnt = 0;

			/* [Init] eARC/ACR Enable */
			memset((void *)&gHDMI21EARCData, 0, sizeof(HDMI21_EARC_DEVICE_DATA));
			_e = &gHDMI21EARCData;

			_e->isArcOut = false;
			_e->isArcOutEn = false;
			_e->isEarcDetectEn = false;
		}else{
			HDMI20_INFO("HDMI eARC Warning! : Will not create HDMI eARC due to it is already ALIVE!\n");
		}

		HDMI20_INFO("HDMI eARC : Open!!!( OUT:%d, OUTeN:%d, eARC:%d, eARCeN:%d )\n", _gHdmi21EARCIsOut, _gHdmi21EARCIsOutEn, _gHdmi21EARCIsDetect, _gHdmi21EARCIsDetectEn);

		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_Tx_eARC_Init(UINT8 port){
	int ret = RET_ERROR;
	UINT32 cmdc_config = 0;
	UINT32 cmdc_control = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}
		
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			if(port != HDMI21_EARC_M23_OUTPUT_PORT){
				HDMI21_LINE_DBG(331, "Error! Port is not eARC port(%d / %d)\n", port, HDMI21_EARC_M23_OUTPUT_PORT);
				ret = RET_OK;
				break;
			}
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if(port != HDMI21_EARC_OUTPUT_PORT){
			HDMI21_LINE_DBG(331, "Error! Port is not eARC port(%d / %d)\n", port, HDMI21_EARC_OUTPUT_PORT);
				ret = RET_OK;
				break;
			}
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Init]Variable */
		_gHdmi21EARCIsOut = FALSE;
		_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__READY;
		_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__INIT;
		
		if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_gHdmi21EARCConnectionInfo.portNum = HDMI21_EARC_OUTPUT_PORT;
		}else{
			_gHdmi21EARCConnectionInfo.portNum = HDMI21_EARC_M23_OUTPUT_PORT;
		}
		_gHdmi21EARCConnectionInfo.earcStatus  = HDMI21_EARC_STATUS__OFF;
		_gHdmi21EARCConnectionInfo.latency_req = 0;
		_gHdmi21EARCConnectionInfo.latency = 0;
		memset((void *)&_gHdmi21EARCConnectionInfo.capability, 0, HDMI21_EARC_SIZE_OF_CAPS);
		_gHdmi21EARCHPDStableCnt = 0;	
		if(gHDMI21DevEARCControler[HDMI21_EARC__SET__FORCE_READ_EN].value){
			_gHdmi21EARCIsStatChng  = FALSE;
			_gHdmi21EARCIsCapChng = FALSE;
		}else{
			_gHdmi21EARCIsStatChng  = TRUE;
			_gHdmi21EARCIsCapChng = TRUE;
		}
		_gHdmi21EARCStatChngFlag = FALSE;
		_gHdmi21EARCCapChngFlag = FALSE;
		_gHdmi21EARCReadCnt = 0;
		_gHdmi21EARCReadCap = 0;
		_gHdmi21EARCReadLatency = 0;
		_gHdmi21EARCForceReadCnt = 0;

		/* [Set]Register */
		cmdc_control = HDMI21_TX_EARC_CMDC_CONTROL__RESET;
		_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
		//HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF);		// USER_CMDC_BP_MODE USER_CMDC_OUT_SEL
		
		if((_gHdmi21EARCIsDetectEn == TRUE) || (_gHdmi21EARCIsOutEn == TRUE)){
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_SEL);	// USER_APHY_CMDC_DRV_ICON USER_APHY_CMDC_TR_CTL
			if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_SEL);
			}else{
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_SEL);
			}
			_gHdmi21EARCIsOut = TRUE;
		}else{
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_ARC);	// USER_APHY_CMDC_DRV_ICON USER_APHY_CMDC_TR_CTL
			if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_OFF);
			}else{
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF);
			}
			_gHdmi21EARCIsOut = FALSE;
		}

		
		if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
		}else{
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
		}
		
		if(_gHdmi21EARCIsDetectEn == TRUE){
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC);	//USER_EARC_eARC_SEL
			_gHdmi21EARCIsDetect = TRUE;
		}else{
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC);		//USER_EARC_ARC_SEL
		}

		if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_EXTR_RCTRL].value != 0xFF){
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_EXTR_RCTRL, gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_EXTR_RCTRL].value);	
		}
		if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_IREF_RBIAS].value != 0xFF){
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_IREF_RBIAS, gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_IREF_RBIAS].value);	
		}
		if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_VREG_VREF].value != 0xFF){
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_VREG_VREF, gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_VREG_VREF].value);	
		}

		//eARC HPD on
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
		}else{
			cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
		}
		if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 1){
			cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE);
		}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 2){
			cmdc_config &= (0xFFFFFFFFB);
		}
		_p->link_write(HDMI21_TX_EARC_CMDC_CONFIG, cmdc_config);
		if(_gHdmi21EARCIsHpdBitReset){
			cmdc_control |=  (HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);
		}else{
			cmdc_control |=  (HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
		}
		_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);

		HDMI20_INFO("HDMI eARC : Init!!!(d20250613)( OUT:%d, OUTeN:%d, eARC:%d, eARCeN:%d )\n", _gHdmi21EARCIsOut, _gHdmi21EARCIsOutEn, _gHdmi21EARCIsDetect, _gHdmi21EARCIsDetectEn);

		ret = RET_OK;
	}while(0);
	return ret;
}

int HDMI21_Tx_eARC_Disconnect(UINT8 port){
	int ret = RET_ERROR;
	UINT32 cmdc_control = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */
		if(port >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", port);
			break;
		}

		if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
			if(port != HDMI21_EARC_M23_OUTPUT_PORT){
				HDMI21_LINE_DBG(331, "Error! Port is not eARC port(%d / %d)\n", port, HDMI21_EARC_M23_OUTPUT_PORT);
				ret = RET_OK;
				break;
			}
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			if(port != HDMI21_EARC_OUTPUT_PORT){
			HDMI21_LINE_DBG(331, "Error! Port is not eARC port(%d / %d)\n", port, HDMI21_EARC_OUTPUT_PORT);
				ret = RET_OK;
				break;
			}
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Set]eARC HPD Off */
		cmdc_control = _p->link_read(HDMI21_TX_EARC_CMDC_CONTROL) & HDMI21_TX_EARC_CMDC_CONTROL__HPD_OFF;
		_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);

		/* [Set]SW Reset*/
		//HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_AUDIO);
		if(lx_chip_rev( ) < LX_CHIP_REV( O22, A0)){
			HDMI21_MISC_Rx_Set_ResetCore(_p, HDMI21_SNPS_RST_EARCTX);
		}

		HDMI20_INFO("HDMI eARC : Disconnect!!!( OUT:%d, OUTeN:%d, eARC:%d, eARCeN:%d )\n", _gHdmi21EARCIsOut, _gHdmi21EARCIsOutEn, _gHdmi21EARCIsDetect, _gHdmi21EARCIsDetectEn);
		ret = RET_OK;
	}while(0);
	return ret;
}

int HDMI21_Tx_eARC_Suspend(void){
	int ret = RET_ERROR;
	int cnt = HDMI21_EARC_SUSPEND_TRY_COUNT;
	HDMI21_EARC_DEVICE_DATA *_e;

	/* [Close]eARC Thread */
	gHDMI21EARCThread.isAlive = 0;
	while(1)
	{
		if(gHDMI21EARCThread.stamp == 0){
			HDMI20_INFO("HDMI eARC Success closing Main thread\n");
			ret = RET_OK;
			break;
		}

		if(cnt <= 0){
			HDMI20_INFO("HDMI eARC Failed to exit Main thread\n");
			break;
		}
		cnt--;

		_e = (HDMI21_EARC_DEVICE_DATA *)&gHDMI21EARCData;

		_e->isArcOutEn = _gHdmi21EARCIsOutEn;
		_e->isEarcDetectEn = _gHdmi21EARCIsDetectEn;

		HDMI20_INFO("HDMI eARC : Suspend!!!(arcOutEn:%d, arcOut:%d, eARCDetectEn:%d)\n", _e->isArcOutEn, _e->isArcOut, _e->isEarcDetectEn);
		msleep(gHDMI21EARCThread.mSleep);
	}

	return ret;
}

int HDMI21_Tx_eARC_Resume(void){
	HDMI21_EARC_DEVICE_DATA *_e;
	UINT32 data;
	
	/* [Open]eARC Thread */
	if(gHDMI21EARCThread.isAlive <= 0){
		/* [Set]Phy Register */
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
#if 0		
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_M23_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_M23_RESET_DISABLE) != HDMI21_TX_EARC__I2C_M23_RESET_DISABLE){
				//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_M23_RESET, HDMI21_TX_EARC__I2C_M23_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
#endif			
			_gHdmi21EARCIsInit = TRUE;
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_O22_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
				//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_B0_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
				//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_B0_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_B0_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
				//HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
		}
		
		gHDMI21EARCThread.isAlive = 1;
		gHDMI21EARCThread.pThread= kthread_create( (void *)HDMI21_Tx_EARC_MainThread, 0, "hdmi21_earc_engine");
		if(gHDMI21EARCThread.pThread){
			HDMI20_INFO("HDMI eARC Initialing thread\n");
			wake_up_process(gHDMI21EARCThread.pThread);
		}else HDMI20_ERROR("Cannot initiate eARC thread\n");

		_e = (HDMI21_EARC_DEVICE_DATA *)&gHDMI21EARCData;

		_gHdmi21EARCIsOutEn = _e->isArcOutEn;
		_gHdmi21EARCIsDetectEn = _e->isEarcDetectEn;	
	}else{
		HDMI20_INFO("HDMI eARC Warning! : Will not create HDMI eARC due to it is already ALIVE!\n");
	}

	HDMI20_INFO("HDMI eARC : Resume!!!(arcOutEn:%d, isArcOut:%d, eARCDetectEn:%d)\n", _e->isArcOutEn, _e->isArcOut, _e->isEarcDetectEn);

	return RET_OK;
}

void HDMI21_Tx_EARC_MainThread(void)
{
	int ret = RET_ERROR;
	UINT32 cmdc_config = 0;
	UINT32 cmdc_control = 0;
	UINT32 cmdc_status = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_DEVICE_DATA *_p_out;

	HDMI20_INFO("HDMI eARC Main Thread Start \n");
	gHDMI21EARCThread.stamp = 0;

	while(1)
	{
		/* [Check]Thread */
		if(gHDMI21EARCThread.isAlive <= 0){ HDMI20_INFO("HDMII eARC Kill Thread\n"); break; }

		/* [Check]Baisc */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Debug] */
		__HDMI21_EARC_Debug();
		if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__DEBUGGING_DATA].value != 0){
			HDMI20_INFO("DEBUGGING_DATA[0x%08x] : [0x%08x] \n", HDMI21_TX_EARC_PHY_CMDC_DEBUGGING_DATA, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_CMDC_DEBUGGING_DATA));
		}
		
		if(_p_out->is5Vconnected && _p_out->isHPD){
			/* [Get]Status */
			__HDMI21_EARC_Get_Status();

			/* [Check/Set]OutPut Disable */
			if(((_gHdmi21EARCIsDetectEn == TRUE) && (_gHdmi21EARCIsOut  == TRUE) && (_gHdmi21EARCIsOutEn == FALSE)\
				&& ((_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__IDLE2) || (_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__ARC)))\
				|| ((_gHdmi21EARCIsDetectEn == FALSE) && (_gHdmi21EARCIsOut  == TRUE) && (_gHdmi21EARCIsOutEn == FALSE))){
				if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_OFF);
				}else{
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF);
				}
				_gHdmi21EARCIsOut = FALSE;
				__HDMI21_EARC_Get_Status();
				HDMI20_INFO("HDMI eARC : Set OUT OFF!!!???( Status:%d, OUT:%d, OUTeN:%d, eARC:%d, eARCeN:%d )\n", _gHdmi21EARCConnectionInfo.earcStatus, _gHdmi21EARCIsOut, _gHdmi21EARCIsOutEn, _gHdmi21EARCIsDetect, _gHdmi21EARCIsDetectEn);
			}

#if 0
			/* [Check/Set]eARC Mode */
			if(((_gHdmi21EARCIsDetectEn == TRUE) && (_gHdmi21EARCIsDetect == FALSE)) \
				&& ((_gHdmi21EARCConnectionInfo.earcStatus > HDMI21_EARC_STATUS__IDLE2) && (_gHdmi21EARCConnectionInfo.earcStatus < HDMI21_EARC_STATUS__ARC))){
				gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value = 1;
				if(_gHdmi21EARCConnectionInfo.earcStatus != HDMI21_EARC_STATUS__EARC){
					if(_gHdmi21EARCIsOut == FALSE){
						HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_SEL);	
						HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_SEL);
						_gHdmi21EARCIsOut = TRUE;
						_gHdmi21EARCIsOutEn = FALSE;
					}
					
					cmdc_control = HDMI21_TX_EARC_CMDC_CONTROL__RESET;
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC);

				}
				_gHdmi21EARCIsDetect = TRUE;
				HDMI20_INFO("HDMI2.1 eARC : Set eARC Mode -> 1(0:ARC, 1:eARC)!!!???\n");
				if(_gHdmi21EARCIsHpdBitReset){
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);
				}else{
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
				}

				__HDMI21_EARC_Get_Status();
			}
#endif

			/* [Check/Set]ARC Mode */
			if((_gHdmi21EARCIsDetectEn == TRUE) \
				&& (_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__IDLE2)){
				//HDMI21_Tx_eARC_SetEARCMode(FALSE);	
				gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value = 0;
				if(_gHdmi21EARCConnectionInfo.earcStatus != HDMI21_EARC_STATUS__ARC){
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_ARC);	

					cmdc_control = HDMI21_TX_EARC_CMDC_CONTROL__RESET;
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
					if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
						HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_NON_ODT_MODE);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
					}else{
						HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__NON_ODT_MODE);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
					}
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC);
					
					// HeartBeat setting
					if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
						cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
					}else{
						cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
					}
					if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 1){
						cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE);
					}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 2){
						cmdc_config &= (0xFFFFFFFFB);
					}
					_p->link_write(HDMI21_TX_EARC_CMDC_CONFIG, cmdc_config);

					// ARC setting
					cmdc_control |=  (HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON|HDMI21_TX_EARC_CMDC_CONTROL__H14BARC_ACTIVE);			
					_gHdmi21EARCIsDetect = FALSE;
					HDMI20_INFO("HDMI eARC : Set eARC Mode -> 0(0:ARC, 1:eARC)!!!???( Status:%d, OUT:%d, OUTeN:%d, eARC:%d, eARCeN:%d )\n", _gHdmi21EARCConnectionInfo.earcStatus, _gHdmi21EARCIsOut, _gHdmi21EARCIsOutEn, _gHdmi21EARCIsDetect, _gHdmi21EARCIsDetectEn);
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
				}

				__HDMI21_EARC_Get_Status();
			}

			if(gHDMI21DevEARCControler[HDMI21_EARC__CALL__TEST__IDLE1_REG_RESET].value != 0){
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					if((_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__IDLE1)\
						&& (HDMI21_EARC_I2cApbRead((UINT32)HDMI21_TX_EARC_PHY_CMDC_ARC_SEL) == HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC)){
						if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
							HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
						}else{
							HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
						}
						HDMI21_EARC_I2cApbWrite((UINT32)HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, (UINT32)HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC);	//USER_EARC_eARC_SEL
						_gHdmi21EARCIsDetect = TRUE;
						HDMI20_INFO("HDMI eARC : Force Set HDMI21_TX_EARC_PHY_CMDC_ARC_SEL ARC->eARC \n");
					}
				}
			}

			if(_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__EARC){
				/* [Sequnce]Info Read/Write */
				//Step1 : Update change flag 
				cmdc_status = _p->link_read(HDMI21_TX_EARC_CMDC_STATUS);
				if((cmdc_status & HDMI21_TX_EARC_CMDC_STATUS__STAT_STAT_CHNG) && (_gHdmi21EARCIsStatChng == FALSE)){
					_gHdmi21EARCIsStatChng = TRUE;
					HDMI20_INFO("HDMI eARC : Rx Latency Change 0 -> 1!!\n ");
				}

				if((cmdc_status & HDMI21_TX_EARC_CMDC_STATUS__STAT_CAP_CHNG)&& (_gHdmi21EARCIsCapChng == FALSE)){
					_gHdmi21EARCIsCapChng = TRUE;
					HDMI20_INFO("HDMI eARC : Rx Cap Change 0 -> 1!!\n ");
				}

				if((!(cmdc_status & HDMI21_TX_EARC_CMDC_STATUS__STAT_STAT_CHNG))\
					&& ((_gHdmi21EARCIsStatChng == TRUE) || (gHDMI21DevEARCControler[HDMI21_EARC__CNT__FORCE_READ].value == 1))){
					_gHdmi21EARCIsStatChng = FALSE;
					_gHdmi21EARCStatChngFlag = TRUE;
					gHDMI21DevEARCControler[HDMI21_EARC__CNT__FORCE_READ].value = 0;
					HDMI20_INFO("HDMI eARC : Rx Latency Change!! 1 -> 0\n ");	
				}

				if((!(cmdc_status & HDMI21_TX_EARC_CMDC_STATUS__STAT_CAP_CHNG))\
					&& ((_gHdmi21EARCIsCapChng == TRUE) || (gHDMI21DevEARCControler[HDMI21_EARC__CNT__FORCE_READ].value == 2))){
					_gHdmi21EARCIsCapChng = FALSE;
					_gHdmi21EARCCapChngFlag = TRUE;
					_gHdmi21EARCForceReadCnt = 0;
					gHDMI21DevEARCControler[HDMI21_EARC__CNT__FORCE_READ].value = 0;
					HDMI20_INFO("HDMI eARC : Rx Cap Change!! 1 -> 0!!\n ");
				}

				if((_gHdmi21EARCStatChngFlag || _gHdmi21EARCCapChngFlag) && (_gHdmi21EARCXactStatus == HDMI21_EARC_XACT_STATUS__READY)){
					_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__CHANGE;
				}
			
				// Step2 : Set xact control
				if(_gHdmi21EARCXactStatus == HDMI21_EARC_XACT_STATUS__CHANGE){
					__HDMI21_EARC_Get_Xact_Control();
				}

				// Step3 : Wait xact loading
				if(_gHdmi21EARCXactStatus == HDMI21_EARC_XACT_STATUS__LOADING){
					__HDMI21_EARC_Get_Xact_Status();
				}

				// Step4 : Read
				if(_gHdmi21EARCXactStatus == HDMI21_EARC_XACT_STATUS__FINISH){
					__HDMI21_EARC_Get_Xact_Read();
				}
				
				__HDMI21_Tx_eARC_SetHpdBit();
			}
			

			/* [Defense]eARC Restart */
			if((_gHdmi21EARCRestartCnt < gHDMI21DevEARCControler[HDMI21_EARC__CNT__RESTART].value) \
				&& (_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__IDLE2)){
				if(_gHdmi21EARCHPDStableCnt == gHDMI21DevEARCControler[HDMI21_EARC__CNT__HPD_STABLE].value){
					if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
						ret = HDMI21_HAL_Rx_Set_RestartHPD(HDMI21_EARC_OUTPUT_PORT);
					}else{
						ret = HDMI21_HAL_Rx_Set_RestartHPD(HDMI21_EARC_M23_OUTPUT_PORT);
					}
					_gHdmi21EARCRestartCnt++;
					_gHdmi21EARCHPDStableCnt = 0;

					cmdc_config = 0;
					if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
						cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
					}else{
						cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
					}
					if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 1){
						cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE);
					}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 2){
						cmdc_config &= (0xFFFFFFFFB);
					}
					_p->link_write(HDMI21_TX_EARC_CMDC_CONFIG, cmdc_config);

					cmdc_control = _p->link_read(HDMI21_TX_EARC_CMDC_CONTROL);
					if(_gHdmi21EARCIsHpdBitReset){
						_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);
					}else{
						_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
					}
					//_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
					gHDMI21DevEARCControler[HDMI21_EARC__LINE_DBG].value = 0;
					HDMI20_INFO("HDMI eARC Reset!!\n");
				}
				_gHdmi21EARCHPDStableCnt++;
			}

#if 0
			/* [Count]Force Read */
			if(_gHdmi21EARCForceReadCnt <= gHDMI21DevEARCControler[HDMI21_EARC__CNT__FORCE_READ].value\
				&& _gHdmi21EARCXactStatus == HDMI21_EARC_XACT_STATUS__READY){
				_gHdmi21EARCForceReadCnt++;
				//HDMI20_AUDIO("Force Read Cnt : %d", _gHdmi21EARCForceReadCnt);
			}
#endif			
		} // End of if(tx5Vconnected)
		else{
			/* 5V is not connected */
			if(gHDMI21DevEARCControler[HDMI21_EARC__CALL__TEST__NONE_REG_RESET].value != 0){
				if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
					if((_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__OFF)\
						&& (HDMI21_EARC_I2cApbRead((UINT32)HDMI21_TX_EARC_PHY_CMDC_ARC_SEL) == HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC)){
						if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
							HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
						}else{
							HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
						}
						HDMI21_EARC_I2cApbWrite((UINT32)HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, (UINT32)HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC);	//USER_EARC_eARC_SEL
						_gHdmi21EARCIsDetect = TRUE;
						HDMI20_INFO("HDMI eARC : Force Set HDMI21_TX_EARC_PHY_CMDC_ARC_SEL ARC->eARC \n");
					}
				}
			}
		}

		gHDMI21EARCThread.stamp = 1;
		msleep(gHDMI21EARCThread.mSleep);
	} // End of While(1)

	gHDMI21EARCThread.stamp = 0;
	gHDMI21EARCThread.isAlive = 0;
}

int HDMI21_Tx_eARC_SetEARCMode(BOOLEAN earcEnable){
	int ret = RET_ERROR;
	UINT32 cmdc_config = 0;
	UINT32 cmdc_control = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_DEVICE_DATA *_p_out;

	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! eARC Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}
		if(HDMI21_EARC_OUTPUT_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! eARC output Port exceeded max port size(%d)\n", HDMI21_EARC_OUTPUT_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Set]eARC Mode */
		cmdc_control = _p->link_read(HDMI21_TX_EARC_CMDC_CONTROL);
		if(earcEnable){
			_gHdmi21EARCIsDetectEn = TRUE;
			gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value = 1;
			if(_gHdmi21EARCConnectionInfo.earcStatus != HDMI21_EARC_STATUS__EARC){
				if(_gHdmi21EARCIsOut == FALSE){
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_SEL);	
					if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
						HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_SEL);
					}else{
						HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_SEL);
					}
					_gHdmi21EARCIsOut = TRUE;
					_gHdmi21EARCIsOutEn = FALSE;
				}

				cmdc_control = HDMI21_TX_EARC_CMDC_CONTROL__RESET;
				_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
				if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
				}else{
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
				}
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC);
				if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_EXTR_RCTRL].value != 0xFF){
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_EXTR_RCTRL, gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_EXTR_RCTRL].value);	
				}
				if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_IREF_RBIAS].value != 0xFF){
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_IREF_RBIAS, gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_IREF_RBIAS].value);	
				}
				if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_VREG_VREF].value != 0xFF){
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_VREG_VREF, gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY_VREG_VREF].value);	
				}

				// HeartBeat setting
				if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
					cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
				}else{
					cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
				}
				if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 1){
					cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE);
				}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 2){
					cmdc_config &= (0xFFFFFFFFB);
				}
				_p->link_write(HDMI21_TX_EARC_CMDC_CONFIG, cmdc_config);

				// HPD on
				if(_gHdmi21EARCIsHpdBitReset){
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);
				}else{
					_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
				}


				// Restart HPD
				if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
					ret = HDMI21_HAL_Rx_Set_RestartHPD(HDMI21_EARC_OUTPUT_PORT);
				}else{
					ret = HDMI21_HAL_Rx_Set_RestartHPD(HDMI21_EARC_M23_OUTPUT_PORT);
				}

				_gHdmi21EARCIsDetect = TRUE;
			}
		}else{
			_gHdmi21EARCIsDetectEn = FALSE;
			gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value = 0;
			if(_gHdmi21EARCConnectionInfo.earcStatus != HDMI21_EARC_STATUS__ARC){
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_ARC);	

				cmdc_control = HDMI21_TX_EARC_CMDC_CONTROL__RESET;
				_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
				if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_NON_ODT_MODE);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
				}else{
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__NON_ODT_MODE);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
				}
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC);

				// HeartBeat setting
				if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
					cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
				}else{
					cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
				}
				if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 1){
					cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE);
				}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 2){
					cmdc_config &= (0xFFFFFFFFB);
				}
				_p->link_write(HDMI21_TX_EARC_CMDC_CONFIG, cmdc_config);

				// ARC setting
				cmdc_control |=  (HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON|HDMI21_TX_EARC_CMDC_CONTROL__H14BARC_ACTIVE);
				_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
				_gHdmi21EARCIsDetect = FALSE;
			}
		}

		HDMI20_INFO("HDMI eARC : Set eARC Mode -> %d(0:ARC, 1:eARC)!!!\n", earcEnable);

		ret = RET_OK;
		}while(0);
	return ret;
}
int HDMI21_Tx_eARC_SetHpdBitOn(void){
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		_gHdmi21EARCHpdBitResetEn = TRUE;
		_gHdmi21EARCIsHpdBitReset = FALSE;
		_gHdmi21EARCHpdBitWaitOnCnt = 0;
		_gHdmi21EARCHpdBitWaitOffCnt = 0;
		//_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);	
		HDMI20_INFO("HDMI eARC : Set HPD Bit Reset En\n");
		
		ret = RET_OK;
	}while(0);

	return ret;
}

int HDMI21_Tx_eARC_SetVideoLatency(UINT8 latency){
	int ret = RET_ERROR;
	UINT32 xact_ctrl = 0;
	UINT32 wr0 = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Set]Latency */
		wr0 = ((UINT32)latency) << 8;
		HDMI20_INFO("HDMI eARC : Set Latency -> 0x%x(%d)\n", wr0, latency);
		_p->link_write(HDMI21_TX_EARC_CMDC_XACT_WR0, wr0);
		
		xact_ctrl =  (HDMI21_TX_EARC_CMDC_XACT_CTRL__TYPE__WRITE \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__DEVICEID__LATENCY \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__TX_LATENCY \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__SIZE__LATENCY);
		_p->link_write(HDMI21_TX_EARC_CMDC_XACT_CTRL, xact_ctrl);
		HDMI20_INFO("HDMI eARC : Set Latency xact -> 0x%x\n", xact_ctrl);

		_gHdmi21EARCConnectionInfo.latency_req = latency;
		
		ret = RET_OK;
	}while(0);

	return ret;
}

UINT32 HDMI21_EARC_I2cApbRead(UINT32 addr)
{
	UINT32 ret;
	UINT32 i2c_reset;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		//HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_M23_RESET, i2c_reset)
	}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_O22_RESET, i2c_reset)
	}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_B0_RESET, i2c_reset)
	}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_RESET, i2c_reset)
	}
		

	if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		ret = (UINT32)(*((UINT32 *)((uintptr_t)earcO20mem.pSwAddr + (uintptr_t)addr)));
	}else{
		if((earcO20mem.pSwAddr != NULL) && ((i2c_reset & HDMI21_TX_EARC__I2C_RESET_DISABLE) == HDMI21_TX_EARC__I2C_RESET_DISABLE)){
			ret = (UINT32)(*((UINT32 *)((uintptr_t)earcO20mem.pSwAddr + (uintptr_t)addr)));
		}
		else{
			HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.(i2c reset : 0x%x)\n", __F__, __L__, i2c_reset);
			ret = 0;
		}
	}
	

	return ret;
}

void   HDMI21_EARC_I2cApbWrite(UINT32 addr, UINT32 data)
{
	volatile UINT32* dest;
	UINT32 i2c_reset;

	if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		//HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_M23_RESET, i2c_reset)
	}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
		HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_O22_RESET, i2c_reset)
	}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_B0_RESET, i2c_reset)
	}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_RESET, i2c_reset)
	}

	if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
		dest = 	((UINT32 *)((uintptr_t)earcO20mem.pSwAddr + (uintptr_t)addr));
		*dest = data;	
	}else{
		if((earcO20mem.pSwAddr != NULL) && ((i2c_reset & HDMI21_TX_EARC__I2C_RESET_DISABLE) == HDMI21_TX_EARC__I2C_RESET_DISABLE)){
			dest = 	((UINT32 *)((uintptr_t)earcO20mem.pSwAddr + (uintptr_t)addr));
			*dest = data;	
		}
		else{
			HDMI20_ERROR("[%s:%d] Error! Device Driver access without initialization.(i2c reset : 0x%x)\n", __F__, __L__, i2c_reset);
		}
	}
}
int HDMI21_Tx_eARC_GetInfo(LX_HDMI_EARC_CONNECTION_INFO_T *pEARCConnectionInfo, int size, int isInternalCall){
   int ret = RET_ERROR;
   LX_HDMI_EARC_CONNECTION_INFO_T  data;

   do{
		/* [Check]Basic */
		if(pEARCConnectionInfo == NULL){
	       HDMI20_ERROR("Error! Null pointer recieved from USER!\n");
	       break;
		}
		if(size != sizeof(LX_HDMI_EARC_CONNECTION_INFO_T)){
	       HDMI20_ERROR("Error! Abnormal data size!([%zu] != [%d]) \n", sizeof(LX_HDMI_EARC_CONNECTION_INFO_T), size);
	       break;
		}

		/* [Init]Info */
		memset((void *)&data, 0, sizeof(LX_HDMI_EARC_CONNECTION_INFO_T));

		/* [Get] Update Info */
		__HDMI21_EARC_UpdateInfo();

		data.portNum = (LX_HDMI_EARC_OUTPUT_PORT_T)_gHdmi21EARCConnectionInfo.portNum;
		switch( _gHdmi21EARCConnectionInfo.earcStatus){
			case HDMI21_EARC_STATUS__OFF:
			case HDMI21_EARC_STATUS__IDLE1:
				data.earcStatus = LX_HDMI_EARC_STATUS__IDLE1;
				break;
			case HDMI21_EARC_STATUS__ARC:
			case HDMI21_EARC_STATUS__IDLE2:
				data.earcStatus = LX_HDMI_EARC_STATUS__IDLE2;
				break;
			case HDMI21_EARC_STATUS__DISC1:
				data.earcStatus = LX_HDMI_EARC_STATUS__DISC1;
				break;
			case HDMI21_EARC_STATUS__DISC2:
				data.earcStatus = LX_HDMI_EARC_STATUS__DISC2;
				break;
			case HDMI21_EARC_STATUS__EARC:
				data.earcStatus = LX_HDMI_EARC_STATUS__EARC;
				break;
			default:
				data.earcStatus = LX_HDMI_EARC_STATUS__IDLE1;
				break;
		}
		memcpy((UINT8 *)&data.capability, (UINT8 *)(&_gHdmi21EARCConnectionInfo.capability)+1, HDMI21_EARC_SIZE_OF_CAPS-1);
		data.latency_req = _gHdmi21EARCConnectionInfo.latency_req;
		data.latency = _gHdmi21EARCConnectionInfo.latency;

		/* [Set]Copy Info */
		if(gHDMI21DevEARCControler[HDMI21_EARC__CALL__TEST].value == 0){
			memcpy((LX_HDMI_EARC_CONNECTION_INFO_T *)pEARCConnectionInfo, &data, size);
		}else{
		   ret = copy_to_user((LX_HDMI_EARC_CONNECTION_INFO_T *)pEARCConnectionInfo, &data, sizeof(LX_HDMI_EARC_CONNECTION_INFO_T));
		}
		
		ret = RET_OK;

   }while(0);

   return ret;

}

void __HDMI21_EARC_UpdateInfo(void){
	do{
		/* [Get]Info */
		__HDMI21_EARC_Get_Status();
		if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__CONNECTION].value > 0){
			HDMI20_INFO("HDMI eARC : Get Connection Status -> %x(0:OFF, 1:IDLE1, 2:IDLE2, 3:DISC1, 4:DISC2, 5:eARC, 6:ARC)\n", _gHdmi21EARCConnectionInfo.earcStatus);
			gHDMI21DevEARCControler[HDMI21_EARC__INFO__CONNECTION].value--;
		}
	
	}while(0);
}

void __HDMI21_Tx_eARC_SetHpdBit(void){
	int ret = RET_ERROR;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}
		
		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		if((_gHdmi21EARCHpdBitResetEn == TRUE) && (_gHdmi21EARCIsHpdBitReset == FALSE)){
			if(_gHdmi21EARCHpdBitWaitOnCnt < gHDMI21DevEARCControler[HDMI21_EARC__CNT__HPD_BIT_WAIT_ON].value){
				_gHdmi21EARCHpdBitWaitOnCnt++;
				HDMI20_INFO("HDMI eARC : HPD Bit On Count : %d \n", _gHdmi21EARCHpdBitWaitOnCnt);
			}else{
				/* [Set]HPD Bit On */
				HDMI20_INFO("HDMI eARC : Set HPD Bit On!!!\n");
				_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);
				_gHdmi21EARCIsHpdBitReset = TRUE;
			}
		}else if((_gHdmi21EARCHpdBitResetEn == TRUE) && (_gHdmi21EARCIsHpdBitReset == TRUE)){
			if(_gHdmi21EARCHpdBitWaitOffCnt < gHDMI21DevEARCControler[HDMI21_EARC__CNT__HPD_BIT_WAIT_OFF].value){
				_gHdmi21EARCHpdBitWaitOffCnt++;
				HDMI20_INFO("HDMI eARC : HPD Bit Off Count : %d \n", _gHdmi21EARCHpdBitWaitOffCnt);
			}else{
				/* [Set]HPD Bit Off */
				HDMI20_INFO("HDMI eARC : Set HPD Bit Off!!!\n");
				_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
				_gHdmi21EARCHpdBitWaitOnCnt = 0;
				_gHdmi21EARCHpdBitWaitOffCnt = 0;
				_gHdmi21EARCHpdBitResetEn = FALSE;
				_gHdmi21EARCIsHpdBitReset = FALSE;
			}
		}
		
		ret = RET_OK;
	}while(0);
}
void HDMI21_Set_EARC_Line_Debugger(UINT32 value)
{
	gHDMI21DevEARCControler[HDMI21_EARC__LINE_DBG].value = value;
	return;
}

UINT32 HDMI21_Get_EARC_Line_Debugger(void)
{
	return gHDMI21DevEARCControler[HDMI21_EARC__LINE_DBG].value; 
}

int HDMI21_HAL_Rx_DBG_AccessDevEARCController(HDMI21_DEV_EARC_CONTROL_LIST_T index, UINT8 isSet, UINT32 *data, int isInternalCall)
{
	int ret = RET_OK;

	do{
		if(index >= HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM){
			HDMI20_ERROR("ERR : Unknown index[%d]\n", index);
			break;
		}

		if(isSet){
			if(isInternalCall) {
				memcpy((void *)&gHDMI21DevEARCControler[index].value, (void  *)data, sizeof(UINT32));
			}
			else{
				if(copy_from_user((void *)&gHDMI21DevEARCControler[index].value, (void __user *)data, sizeof(UINT32))){
					HDMI20_ERROR("Cannot copy gHDMI21DevEARCControler from user\n");
					break;
				}
			}
		}
		else{
			if(isInternalCall) {
				memcpy((void *)data, (void *)&gHDMI21DevEARCControler[index].value, sizeof(UINT32));
			}
			else{
				ret = copy_to_user((void __user *)data, (void *)&gHDMI21DevEARCControler[index].value, sizeof(UINT32));
				if(ret) {
					HDMI20_ERROR("Copy Error to USER space for AccessDevController .\n");
					break;
				}
			}
		}

		ret = RET_OK;
	} while(0);

	return ret;
}

int HDMI21_HAL_Rx_DBG_PrintDevEARCController(HDMI21_DEV_EARC_CONTROL_LIST_T index)
{
	int ret = RET_OK;
	int i;

	do{
		if(index >= HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM){
			HDMI20_VIDEO("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev eARC Controller]\n");
			printk("----------------------------------------------------------\n");
			for(i=0;i<HDMI21__DEV_EARC_CONTROL_LIST_MAXNUM;i++){
				printk("[#%2d]. [%-54s] => [0x%08x] : %s \n", i,\
						gHDMI21DevEARCControler[i].index, gHDMI21DevEARCControler[i].value, gHDMI21DevEARCControler[i].description);
			}
			HDMI20_VIDEO("---------------------------------------------------------\n");

		}
		else{
			printk("\n");	
			printk("----------------------------------------------------------\n");
			printk("[HDMI2.0 Dev eARC Controller]\n");
			printk("----------------------------------------------------------\n");
			printk("[#%2d]. [%-52s] => [0x%08x] : %s \n", index,\
					gHDMI21DevEARCControler[index].index, gHDMI21DevEARCControler[index].value, gHDMI21DevEARCControler[index].description);
			printk("---------------------------------------------------------\n");
		}

		ret = RET_OK;
	} while(0);
	
	return ret;
}

/* STATIC FUNCTION */
static void __HDMI21_EARC_Get_Status(void){
	UINT32 cmdc_status = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	HDMI21_HAL_RX_DEVICE_DATA *_p_out;

	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}
		
		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
			_p_out = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Get]Status */
		if(_p_out->is5Vconnected && _p_out->isHPD){
			cmdc_status = _p->link_read(HDMI21_TX_EARC_CMDC_STATUS);
			_gHdmi21EARCConnectionInfo.earcStatus = ((cmdc_status & HDMI21_TX_EARC_CMDC_STATUS__DISCOVERY_STATE) >> 1);
		}else{
			_gHdmi21EARCConnectionInfo.earcStatus = HDMI21_EARC_STATUS__OFF;
		}
	}while(0);
}

static void __HDMI21_EARC_Get_Xact_Control(void){
	
	UINT32 xact_ctrl = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */ 
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Set]Xact Control */
		if(_gHdmi21EARCStatChngFlag){
			xact_ctrl =  (HDMI21_TX_EARC_CMDC_XACT_CTRL__TYPE__READ \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__DEVICEID__LATENCY \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__RX_LATENCY \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__SIZE__LATENCY);
			HDMI20_AUDIO("HDMI eARC Get Latency xact : 0x%x\n", xact_ctrl);
		}else if(_gHdmi21EARCCapChngFlag){
			xact_ctrl =  (HDMI21_TX_EARC_CMDC_XACT_CTRL__TYPE__READ \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__DEVICEID__CAP \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__OFFSET__CAP \
							| HDMI21_TX_EARC_CMDC_XACT_CTRL__SIZE__CAP);
			HDMI20_AUDIO("HDMI eARC Get Capability xact : 0x%x\n", xact_ctrl);
		}else{
			HDMI20_ERROR("Xact Status Error\n");
			break;
		}
		_p->link_write(HDMI21_TX_EARC_CMDC_XACT_CTRL, xact_ctrl);
		_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__LOADING;
	}while(0);
}

static void __HDMI21_EARC_Get_Xact_Read(void){
	int i;
	UINT32 rd0 = 0;
	UINT32 addr;
	UINT32 rx_cap[(HDMI21_EARC_SIZE_OF_CAPS >> 2)];
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */ 
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Get]Read */
		addr = (UINT32)HDMI21_TX_EARC_CMDC_XACT_RD0;
		if(_gHdmi21EARCStatChngFlag){
			rd0 = _p->link_read(addr);
			HDMI20_AUDIO("HDMI eARC Get Latency : 0x%x\n", rd0);
			_gHdmi21EARCConnectionInfo.latency =  ((rd0 & HDMI21_TX_EARC_CMDC_XACT_LATENCY) >> 8);
			_gHdmi21EARCStatChngFlag = FALSE;
		}else if(_gHdmi21EARCCapChngFlag){
			for(i=0; i<(HDMI21_EARC_SIZE_OF_CAPS >>2); i++){
				rx_cap[i] = _p->link_read(addr);

				if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__CAP].value == 0){
					HDMI20_INFO("HDMI eARC Get Capability : BYTE [%d] -- [0x%x]<=[0x%08x]\n", i, addr, rx_cap[i]);
				}
				addr += 4;
			}
			memcpy((UINT8 *)&_gHdmi21EARCConnectionInfo.capability, (UINT8 *)&rx_cap, HDMI21_EARC_SIZE_OF_CAPS);
			if((_gHdmi21EARCConnectionInfo.capability[0] != 0) && (_gHdmi21EARCConnectionInfo.capability[1] != 0)){
				_gHdmi21EARCCapChngFlag = FALSE;
			}else{
				HDMI20_INFO("HDMI eARC Cap read fail!! cap if 0\n");
			}
		}else{
			HDMI20_ERROR("Xact Status Error\n");
			break;
		}
		
		_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__READY;
	}while(0);
}

static void __HDMI21_EARC_Get_Xact_Status(void){
	UINT32 cmdc_xact_status = 0;
	UINT32 cmdc_xact_status_finish = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Get]Xact Status */
		cmdc_xact_status = _p->link_read(HDMI21_TX_EARC_CMDC_STATUS);
		cmdc_xact_status_finish = ((cmdc_xact_status & HDMI21_TX_EARC_CMDC_STATUS__XACT_FINISHED));

		/* [Set]Update Xact Status */
		if(cmdc_xact_status_finish){
			_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__FINISH;
			HDMI20_INFO("HDMI eARC Xact Status Finish(0x%x)!!!\n", cmdc_xact_status);
			if(cmdc_xact_status & HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_MASK){
				//_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__READY;
				//HDMI20_INFO("Xact Status Finish but Fail!!!(0x%x)!!!\n", cmdc_xact_status);
			}
		}else{
			_gHdmi21EARCXactStatus = HDMI21_EARC_XACT_STATUS__LOADING;
			HDMI20_INFO("HDMI eARC Xact Status Still Loading!!!\n");
		}
	}while(0);
}

static void __HDMI21_EARC_Get_Xact_Result(void){
	UINT32 cmdc_xact_result = 0;
	UINT32 cmdc_xact_result_success = 0;
	UINT32 cmdc_xact_result_fail = 0;
	HDMI21_HAL_RX_DEVICE_DATA *_p;
	
	do{
		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Get]Xact Result */
		cmdc_xact_result = _p->link_read(HDMI21_TX_EARC_CMDC_STATUS);
		cmdc_xact_result_success = (cmdc_xact_result & HDMI21_TX_EARC_CMDC_STATUS__XACT_SUCCESSFUL);
		cmdc_xact_result_fail = (cmdc_xact_result & HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_MASK);
		HDMI20_AUDIO("HDMI eARC xact result : 0x%x", cmdc_xact_result);

		/* [Set]Update Xact Result */
		if(cmdc_xact_result_success){
			_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__SUCECSS;
		}else if(cmdc_xact_result_fail){
			if(cmdc_xact_result&HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_UNEXPRESP){
				_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__FAILED_UNEXPRESP;
			}else if(cmdc_xact_result&HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_UNCORRECTER){
				_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__FAILED_UNCORRECTER;
			}else if(cmdc_xact_result&HDMI21_TX_EARC_CMDC_STATUS__XACT_FAILED_RESPTIMEOUT){
				_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__FAILED_RESPTIMEOUT;
			}else{
				_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__INIT;
			}
		}else{
			_gHdmi21EARCXactResult = HDMI21_EARC_XACT_RESULT__INIT;
		}
	}while(0);
}

static void __HDMI21_EARC_Debug(void){
	int ret = RET_ERROR;
	UINT32 cmdc_control = 0;
	UINT32 cmdc_config = 0;
	UINT32 data;
	HDMI21_HAL_RX_DEVICE_DATA *_p;

	/* [Get]Handler */
	if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
	}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
	}else{
		_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
	}

	/* [Debug]I2C Reset */
	if(gHDMI21DevEARCControler[HDMI21_EARC__SET__I2C].value != 0){
		if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) ){
#if 0		
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_M23_RESET, data)
			if(data != HDMI21_TX_EARC__I2C_M23_RESET_DISABLE){
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_M23_RESET, HDMI21_TX_EARC__I2C_M23_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_M23_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
#endif			
			_gHdmi21EARCIsInit = TRUE;
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) ){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_O22_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_O22_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, B0) ){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_B0_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_B0_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_B0_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
		}else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_RESET, data)
			if((data & HDMI21_TX_EARC__I2C_RESET_DISABLE) != HDMI21_TX_EARC__I2C_RESET_DISABLE){
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_RESET, HDMI21_TX_EARC__I2C_RESET_ENABLE);
				HDMI21_EARC_REG_WR(HDMI21_TX_EARC__I2C_RESET, HDMI21_TX_EARC__I2C_RESET_DISABLE);
				_gHdmi21EARCIsInit = TRUE;
			}
		}

		HDMI20_INFO("HDMI eARC TEST : I2C reset !!!\n");
		gHDMI21DevEARCControler[HDMI21_EARC__SET__I2C].value = 0;
	}

	/* [Debug]PHY Reset */
	if(gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY].value != 0){
		//HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF);			// USER_CMDC_BP_MODE USER_CMDC_OUT_SEL
		if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value == TRUE){
			if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
			}else{
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
			}
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC);		//USER_EARC_eARC_SEL
		}else{
			if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__O26_NON_ODT_MODE);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
			}else{
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__NON_ODT_MODE);// ODT(eARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
			}
			HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC);			//USER_EARC_ARC_SEL
		}
	
		HDMI20_INFO("HDMI eARC TEST : PHY setting !!!\n");
		gHDMI21DevEARCControler[HDMI21_EARC__SET__PHY].value = 0;
	}

	/* [Debug]Link Reset */
	if(gHDMI21DevEARCControler[HDMI21_EARC__SET__LINK].value != 0){
		if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			ret = HDMI21_HAL_Rx_Set_RestartHPD(HDMI21_EARC_OUTPUT_PORT);
		}else{
			ret = HDMI21_HAL_Rx_Set_RestartHPD(HDMI21_EARC_M23_OUTPUT_PORT);
		}
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_DISABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
		}else{
			cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_CADENCE_50|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_DEVICEID|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_RDOFFSET|HDMI21_TX_EARC_CMDC_CONFIG__HEARTBEAT_WROFFSET);
		}
		if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 1){
			cmdc_config |= (HDMI21_TX_EARC_CMDC_CONFIG__ECC_ENABLE);
		}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ECC_EN].value == 2){
			cmdc_config &= (0xFFFFFFFFB);
		}
		_p->link_write(HDMI21_TX_EARC_CMDC_CONFIG, cmdc_config);

		cmdc_control = HDMI21_TX_EARC_CMDC_CONTROL__RESET;
		_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, cmdc_control);
		cmdc_control |=  (HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
		if(_gHdmi21EARCIsHpdBitReset){
			_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_BIT_ON);
		}else{
			_p->link_write(HDMI21_TX_EARC_CMDC_CONTROL, HDMI21_TX_EARC_CMDC_CONTROL__HPD_ON);
		}
		gHDMI21DevEARCControler[HDMI21_EARC__LINE_DBG].value = 0;
		HDMI20_INFO("HDMI eARC Debug : Reset eARC!!\n");

		gHDMI21DevEARCControler[HDMI21_EARC__SET__LINK].value = 0;
	}

	/* [Debug]Mode Set */
	if(gHDMI21DevEARCControler[HDMI21_EARC__SET__EARC_MODE].value == 1){
		gHDMI21DevEARCControler[HDMI21_EARC__SET__EARC_MODE].value = 0;
		HDMI21_Tx_eARC_SetEARCMode(FALSE);		
		HDMI20_INFO("HDMI eARC Debug : Set ARC\n");
	}else if(gHDMI21DevEARCControler[HDMI21_EARC__SET__EARC_MODE].value == 2){
		gHDMI21DevEARCControler[HDMI21_EARC__SET__EARC_MODE].value = 0;
		HDMI21_Tx_eARC_SetEARCMode(TRUE);
		HDMI20_INFO("HDMI eARC Debug : Set eARC\n");
	}

	/* [Debug]Mode Set */
	if(gHDMI21DevEARCControler[HDMI21_EARC__SET__HPDBIT_RESET_EN].value != 0){
		gHDMI21DevEARCControler[HDMI21_EARC__SET__HPDBIT_RESET_EN].value = 0;
		HDMI21_Tx_eARC_SetHpdBitOn();		
		HDMI20_INFO("HDMI eARC Debug : Set eARC HPD Reset Enable\n");
	}

	/* [Debug]ARC Set */
	if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ARC].value == 1){
		gHDMI21DevEARCControler[HDMI21_EARC__SET__ARC].value = 0;
		ret = HDMI21_Rx_Set_ARC(_p->port, TRUE);		
		HDMI20_INFO("HDMI eARC Debug : Set ARC (arcOutEn:%d, arcOut:%d, eARCDetectEn:%d, eARCDetect:%d)\n",_gHdmi21EARCIsOutEn, _gHdmi21EARCIsOut, _gHdmi21EARCIsDetectEn, _gHdmi21EARCIsDetect);
	}if(gHDMI21DevEARCControler[HDMI21_EARC__SET__ARC].value == 2){
		gHDMI21DevEARCControler[HDMI21_EARC__SET__ARC].value = 0;
		ret = HDMI21_Rx_Set_ARC(_p->port, FALSE);		
		HDMI20_INFO("HDMI eARC Debug : Set ARC Disable(arcOutEn:%d, arcOut:%d, eARCDetectEn:%d, eARCDetect:%d)\n",_gHdmi21EARCIsOutEn, _gHdmi21EARCIsOut, _gHdmi21EARCIsDetectEn, _gHdmi21EARCIsDetect);
	}

	/* [Debug]Info */
	if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__STATUS].value != 0){
		HDMI20_INFO("=== eARC Info === \n");
		HDMI20_INFO("Port 	: %d\n", _gHdmi21EARCConnectionInfo.portNum);
		HDMI20_INFO("Status 	: %d  \n", _gHdmi21EARCConnectionInfo.earcStatus);
		HDMI20_INFO("Tx letency : %d \n", _gHdmi21EARCConnectionInfo.latency_req);
		HDMI20_INFO("Rx latency : %d\n", _gHdmi21EARCConnectionInfo.latency);
		HDMI20_INFO("isOutEn 	: %d\n", _gHdmi21EARCIsOutEn);
		HDMI20_INFO("isOut 		: %d\n", _gHdmi21EARCIsOut);
		HDMI20_INFO("isDetectEn : %d\n", _gHdmi21EARCIsDetectEn);
		HDMI20_INFO("isDetect	: %d\n", _gHdmi21EARCIsDetect);
		gHDMI21DevEARCControler[HDMI21_EARC__INFO__STATUS].value = 0;
	}

	/* [Debug]Reg Info */
	if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__REG].value != 0){
		HDMI20_INFO("=== eARC Reg Info === \n");
		HDMI20_INFO("eARC Enable : %d(0:ARC, 1:eARC)\n", gHDMI21DevEARCControler[HDMI21_EARC__INFO__MODE].value);	
		if(lx_chip_rev( ) >= LX_CHIP_REV( M23, A0)){
			//HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_M23_RESET, data);
			//HDMI20_INFO("I2C [0x%08x] : [0x%08x]/[0x%08x] \n", HDMI21_TX_EARC__I2C_M23_RESET, data, HDMI21_TX_EARC__I2C_RESET_DISABLE);
		}else if(lx_chip_rev( ) >= LX_CHIP_REV( O22, A0)){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_O22_RESET, data);
			HDMI20_INFO("I2C [0x%08x] : [0x%08x]/[0x%08x] \n", HDMI21_TX_EARC__I2C_O22_RESET, data, HDMI21_TX_EARC__I2C_RESET_DISABLE);
		}else if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_RESET, data)
			HDMI20_INFO("I2C [0x%08x] : [0x%08x]/[0x%08x] \n", HDMI21_TX_EARC__I2C_RESET, data, HDMI21_TX_EARC__I2C_RESET_DISABLE);
		}else{
			HDMI21_EARC_REG_RD(HDMI21_TX_EARC__I2C_B0_RESET, data);
			HDMI20_INFO("I2C [0x%08x] : [0x%08x]/[0x%08x] \n", HDMI21_TX_EARC__I2C_B0_RESET, data, HDMI21_TX_EARC__I2C_RESET_DISABLE);
		}
		HDMI20_INFO("=== PHY === \n");
		HDMI20_INFO("DMAC_PDB[0x%08x] : [0x%08x]/[0x%08x] \n", HDMI21_TX_EARC_PHY_DMAC_PDB, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_DMAC_PDB), HDMI21_TX_EARC_PHY_DMAC_PDB__8PHASE_EN);
		HDMI20_INFO("DRV_ICON[0x%08x] : [0x%08x]/[0x%08x],[0x%08x] \n", HDMI21_TX_EARC_PHY_CMDC_DRV_ICON, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_CMDC_DRV_ICON),HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_SEL,HDMI21_TX_EARC_PHY_CMDC_DRV_ICON__OUT_ARC);
		HDMI20_INFO("ODT_CTL[0x%08x] : [0x%08x]/[0x%08x],[0x%08x]\n", HDMI21_TX_EARC_PHY_CMDC_ODT_CTL, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_CMDC_ODT_CTL),HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__NON_ODT_MODE,HDMI21_TX_EARC_PHY_CMDC_ODT_CTL__PLL_RSTB);
		HDMI20_INFO("ARC_SEL[0x%08x] : [0x%08x]/[0x%08x],[0x%08x]\n", HDMI21_TX_EARC_PHY_CMDC_ARC_SEL, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_CMDC_ARC_SEL),HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__EARC,HDMI21_TX_EARC_PHY_CMDC_ARC_SEL__ARC);
		HDMI20_INFO("BP_MODE[0x%08x] : [0x%08x]/[0x%08x],[0x%08x]\n", HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_CMDC_BP_MODE),HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_SEL,HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF);
		HDMI20_INFO("EXTR_RCTRL[0x%08x] : [0x%08x]\n", HDMI21_TX_EARC_PHY_CMDC_EXTR_RCTRL, HDMI21_EARC_I2cApbRead(HDMI21_TX_EARC_PHY_CMDC_EXTR_RCTRL));

		HDMI20_INFO("=== LINK === \n");
		HDMI20_INFO("CONFIG[0x%08x] : [0x%08x] \n", HDMI21_TX_EARC_CMDC_CONFIG, _p->link_read(HDMI21_TX_EARC_CMDC_CONFIG));
		HDMI20_INFO("CONTROL[0x%08x] : [0x%08x] \n", HDMI21_TX_EARC_CMDC_CONTROL, _p->link_read(HDMI21_TX_EARC_CMDC_CONTROL));
		HDMI20_INFO("STATUS[0x%08x] : [0x%08x] \n", HDMI21_TX_EARC_CMDC_STATUS, _p->link_read(HDMI21_TX_EARC_CMDC_STATUS));
		HDMI20_INFO("XACT_CTRL[0x%08x] : [0x%08x]\n", HDMI21_TX_EARC_CMDC_XACT_CTRL, _p->link_read(HDMI21_TX_EARC_CMDC_XACT_CTRL));
		HDMI20_INFO("XACT_WR0[0x%08x] : [0x%08x]\n", HDMI21_TX_EARC_CMDC_XACT_WR0, _p->link_read(HDMI21_TX_EARC_CMDC_XACT_WR0));
		HDMI20_INFO("XACT_RD0[0x%08x] : [0x%08x]\n", HDMI21_TX_EARC_CMDC_XACT_RD0, _p->link_read(HDMI21_TX_EARC_CMDC_XACT_RD0));
		gHDMI21DevEARCControler[HDMI21_EARC__INFO__REG].value = 0;
	}

	if(gHDMI21DevEARCControler[HDMI21_EARC__INFO__GLOBAL].value != 0){
		HDMI20_INFO("=== eARC Enable Info === \n");
		HDMI20_INFO("Open   : IsInit(%d) \n", _gHdmi21EARCIsInit);
		HDMI20_INFO("Enable : IsDetectEn(%d), IsDetect(%d), EARCIsOutEn(%d), EARCIsOut(%d) \n", _gHdmi21EARCIsDetectEn, _gHdmi21EARCIsDetect, _gHdmi21EARCIsOutEn, _gHdmi21EARCIsOut);
		HDMI20_INFO("Info   : IsStatChng(%d), IsCapChng(%d), StatChngFlag(%d), CapChngFlag(%d) \n", _gHdmi21EARCIsStatChng, _gHdmi21EARCIsCapChng, _gHdmi21EARCStatChngFlag, _gHdmi21EARCCapChngFlag);
		HDMI20_INFO("Count	: HPDStableCnt(%d), ForceReadCnt(%d), ReadCnt(%d) \n", _gHdmi21EARCHPDStableCnt, _gHdmi21EARCForceReadCnt, _gHdmi21EARCReadCnt);
		HDMI20_INFO("HPDbit	: ResetEn(%d), Reset(%d), WaitOnCnt(%d), WaitOffCnt(%d) \n", _gHdmi21EARCHpdBitResetEn, _gHdmi21EARCIsHpdBitReset, _gHdmi21EARCHpdBitWaitOnCnt, _gHdmi21EARCHpdBitWaitOffCnt);
		gHDMI21DevEARCControler[HDMI21_EARC__INFO__GLOBAL].value = 0;
	}

	/* [Debug]Line */
	if(gHDMI21DevEARCControler[HDMI21_EARC__LINE_DBG].value == 8){
		__HDMI21_EARC_Get_Xact_Status();
		__HDMI21_EARC_Get_Xact_Result();
		__HDMI21_EARC_UpdateInfo();
		gHDMI21DevEARCControler[HDMI21_EARC__LINE_DBG].value = 0;
	}
}

int HDMI21_Rx_Set_ARC(UINT8 port, BOOLEAN bOnOff)
{
	int ret = RET_OK;
#if 1
	do{
		HDMI21_HAL_RX_DEVICE_DATA *_p;

		/* [Check]Basic */
		if(HDMI21_EARC_PORT >= g_hdmi20_number_of_ports){
			HDMI20_ERROR("Error! Port exceeded max port size(%d)\n", HDMI21_EARC_PORT);
			break;
		}

		/* [Get]Handler */
		if(lx_chip_rev( ) < LX_CHIP_REV( E60, B0)){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_PORT];
		}else if( lx_chip_rev( ) < LX_CHIP_REV( M23, A0) ){
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_OUTPUT_PORT];
		}else{
			_p = (HDMI21_HAL_RX_DEVICE_DATA *)&gHDMI21RxHandler[HDMI21_EARC_M23_OUTPUT_PORT];
		}

		/* [Set]ARC Mode*/
		HDMI20_INFO("HDMI[%d] ARC SetHDMIARC : ARCmode(%d -> %d)", _p->port, _p->isAudioARCMode, bOnOff);
		_p->isAudioARCMode = bOnOff;
		if(bOnOff){
			if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_SEL);
			}else{
				HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_SEL);
			}
			_gHdmi21EARCIsOutEn = TRUE;
			_gHdmi21EARCIsOut = TRUE;
		}else{
			if((_gHdmi21EARCIsDetectEn == FALSE)\
				||((_gHdmi21EARCIsDetectEn == TRUE) && ((_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__IDLE2) || (_gHdmi21EARCConnectionInfo.earcStatus == HDMI21_EARC_STATUS__ARC)))){
				if ( lx_chip_rev( ) >= LX_CHIP_REV(O26, A0)) {
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__O26_OUT_OFF);
				}else{
					HDMI21_EARC_I2cApbWrite(HDMI21_TX_EARC_PHY_CMDC_BP_MODE, HDMI21_TX_EARC_PHY_CMDC_BP_MODE__OUT_OFF);
				}
				_gHdmi21EARCIsOut = FALSE;
			}
			_gHdmi21EARCIsOutEn = FALSE;
		}
	} while(0);
#endif
	return ret;
}

EXPORT_SYMBOL (HDMI21_Rx_Set_ARC);

