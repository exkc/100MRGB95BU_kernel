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
 *  @date       2014-05-07
 *  @note       Additional information.
 */

#ifndef	_HDMI20_MODULE_H_
#define	_HDMI20_MODULE_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "hdmi20_kapi.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define HDMi20_MODULE_PHY_DEFAULT_NAME_MAX_SIZE		(30)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/* PHY Setting Table */
typedef struct
{
	char index[HDMi20_MODULE_PHY_DEFAULT_NAME_MAX_SIZE];
	UINT32 regAddr;
	UINT32 subAddr;
	UINT32 h14Mode01;
	UINT32 h14Mode2;
	UINT32 h14Mode3;
	UINT32 h20Mode;
	UINT32 h21Frl1;
	UINT32 h21Frl24;
	UINT32 h21Frl5;
	UINT32 h21Frl6;
} HDMI20_MODULE_PHY_DEFAULT_TABLE_T;
	
/* For ESM */
typedef struct 
{
	int 	(*HDMI21_HDCP23_FP_Set_HlcReset)(unsigned int port, int isPllLocked);
	int 	(*HDMI21_HDCP23_FP_Set_HlcAuthenticate)(unsigned int port, int reauth);
	int 	(*HDMI21_HDCP23_FP_Set_Close)(void);
	int 	(*HDMI21_HDCP23_FP_Set_Open)(UINT8 *pData, int size, int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr);
	int 	(*HDMI21_HDCP23_FP_Get_IsRepeater)(void);
	int 	(*HDMI21_HDCP23_FP_Set_IsRepeater)(int isRepeater);
	int 	(*HDMI21_HDCP23_FP_Get_RxId)(unsigned char* pData, int size);
	int 	(*HDMI21_HDCP23_FP_Set_RxId)(unsigned char* pData, int size, int count, int depth);
	void 	(*HDMI21_HDCP23_FP_TestApp)(int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr);
	int 	(*HDMI21_HDCP23_FP_Get_HlcMonitor)(unsigned int port);
	void 	(*HDMI21_HDCP23_FP_SetLogDump)(char *pData, int *pSize);
	void 	(*HDMI21_HDCP23_FP_PROC_GetEsmLog)(struct seq_file* m);
	int		(*HDMI21_HDCP23_FP_GetContentType)(unsigned int port);
} HDMI21_HDCP23_MODULE_FUNC_POINTER_T;
	
typedef struct
{
	UINT32 aled_top_ADDR;
	UINT32 aled_top_SIZE;

	UINT32 isol_1_ADDR;
	UINT32 isol_1_VAL;
	UINT32 isol_2_ADDR;
	UINT32 isol_2_VAL;
	UINT32 isol_3_ADDR;
	UINT32 isol_3_VAL;
	
	/* HW mapped address */
	UINT32 phyI2CSlaveAddr[HDMI20_NUM_OF_RX_PORTS];
	UINT32 phyI2CSlaveAddr_B1[HDMI20_NUM_OF_RX_PORTS];

	/* RX : PORT 0~3 */
	UINT32 ctrl_ADDR[HDMI20_NUM_OF_RX_PORTS];	
	UINT32 ctrl_SIZE[HDMI20_NUM_OF_RX_PORTS];	
	UINT32 top_ADDR[HDMI20_NUM_OF_RX_PORTS];	
	UINT32 top_SIZE[HDMI20_NUM_OF_RX_PORTS];	
	UINT32 aled_ADDR[HDMI20_NUM_OF_RX_PORTS];	
	UINT32 aled_SIZE[HDMI20_NUM_OF_RX_PORTS];	

	/* Interrupt Number */
	UINT32 irq_TOP[HDMI20_NUM_OF_RX_PORTS];	
	UINT32 irq_LINK[HDMI20_NUM_OF_RX_PORTS];
} HDMI20_MODULE_CHIP_ADDR_DATA_T;


typedef struct
{
	UINT32 aled_top_ADDR;
	UINT32 aled_top_SIZE;

	/* M23 only : M23 has splited ALED Tops for port0,1 & Port2,3 */
	UINT32 aled_top_P23_ADDR;
	UINT32 aled_top_P23_SIZE;

	UINT32 dsc_top_ADDR;
	UINT32 dsc_top_SIZE;

	UINT32 dsc_core_ADDR;
	UINT32 dsc_core_SIZE;

	UINT32 fec_top_ADDR;
	UINT32 fec_top_SIZE;

	/* RX : PORT 0~4 */
	UINT32 ctrl_ADDR[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 ctrl_SIZE[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 top_ADDR[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 top_SIZE[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 aled_ADDR[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 aled_SIZE[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 phyPdc_ADDR[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 phyPdc_SIZE[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 phyPostDr_ADDR[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 phyPostDr_SIZE[HDMI21_NUM_OF_MAX_PORTS];	

	/* Interrupt Number */
	UINT32 irq_TOP[HDMI21_NUM_OF_MAX_PORTS];	
	UINT32 irq_LINK[HDMI21_NUM_OF_MAX_PORTS];
} HDMI21_MODULE_CHIP_ADDR_DATA_T;



/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int 	HDMI20_Module_InitChipRev(void);
int 	HDMI20_Module_Process_Cmd(LX_HDMI20_CMD_T* cmd);
int 	HDMI20_Module_Suspend(void);
int 	HDMI20_Module_Resume(void);
void 	HDMI20_Module_PreInit(void);

// V4L2
int		HDMI20_Module_Set_ExecuteDscMode(UINT8 port);
int 	HDMI20_Module_Get_TimingInfo(UINT8 port, LX_HDMI_TIMING_INFO_T *pData, int size, int isInternalCall);
int 	HDMI20_Module_Get_DRMInfo(UINT8 port, LX_HDMI20_RX_DRM_PACKET_T *pData, int size, int isInternalCall);
int 	HDMI20_Module_Get_VSIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall, LX_HDMI20_VSI_TYPE_T type);
int 	HDMI20_Module_Get_AVIInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int 	HDMI20_Module_Get_SPDInfo(UINT8 port, LX_HDMI_INFO_PACKET_T *pData, int size, int isInternalCall);
int 	HDMI20_Module_Get_EMPInfo(UINT8 port, UINT8 *pData, LX_HDMI20_EMP_TYPE_T type, int isInternalCall);
int 	HDMI20_Module_Get_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall);
int 	HDMI20_Module_Set_EDID(UINT8 port, UINT8 *pData, int size, int isInternalCall);
int 	HDMI20_Module_Set_EDID_Enable(UINT8 port, BOOLEAN enable);
int 	HDMI20_Module_Get_PHYStatus(LX_HDMI_PHY_INFORM_T *pData, int size, int updatePhyI2C, int isInternalCall);
int 	HDMI20_Module_Set_RestartHPD(UINT8 port);
int 	HDMI20_Module_Set_HDCP14(UINT8 port, UINT32 *pData, int size, int isInternalCall);
// KWRP
int 	HDMI20_Module_Open(void);
int 	HDMI20_Module_Initialize(LX_HDMI20_INIT_T *pData, int size, int isInternalCall);
int 	HDMI20_Module_Get_COLORInfo(UINT8 port, LX_HDMI_COLOR_DOMAIN_T *pData, int size, int isInternalCall);
int 	HDMI20_Module_Get_AspectRatio(UINT8 port, LX_HDMI_ASPECTRATIO_T *pData, int size, int isInternalCall);
LX_HDMI_DOLBY_STATE_T HDMI20_Module_Get_IsDolbyHDR(UINT8 port);
int	HDMI20_Module_Get_OperationStatus(UINT8 port, LX_HDMI20_OP_STATUS_T *pData);

/* Proc */
int 	HDMI20_Module_ProcHandler_ReadLGTVStatus(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadPhy28(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadPhy38(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadPhy48(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadLinkAPB(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadTopAPB(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadAledAPB(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadEye(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadPhyDefault(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadIsr(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadPkt(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadEmPkt(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadEDID(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_FILE_ReadEDID(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ReadPort(struct seq_file* m, int port);
int 	HDMI20_Module_ProcHandler_ReadHDCPStatus(int port, struct seq_file* m);
int 	HDMI20_Module_ProcHandler_WriteHDCPStatus(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_Module_ProcHandler_ReadDevCon(struct seq_file* m,  HDMI20_DEV_CONTROL_TYPE_T	type);
int		HDMI20_Module_ProcHandler_WriteIsr(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WritePkt(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WriteEmPkt(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WriteEDID(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_FILE_WriteEDID(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WritePort(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_Module_ProcHandler_WriteDevCon(HDMI20_DEV_CONTROL_TYPE_T	type, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WriteEye(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WritePhyDefault(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WriteAledAPB(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WriteTopAPB(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WriteLinkAPB(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WritePhy28(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WritePhy38(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int		HDMI20_Module_ProcHandler_WritePhy48(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_Module_ProcHandler_ESM_GetVersion(struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ESM_GetLog(struct seq_file* m);
int 	HDMI20_Module_ProcHandler_ESM_SetVersion(struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_Module_ProcHandler_ESM_SetLog(struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_Module_ProcHandler_ReadCalOS(int port, struct seq_file *m);
int 	HDMI20_Module_ProcHandler_ReadDdcMon(int port, struct seq_file *m);
int 	HDMI20_Module_ProcHandler_WriteDdcMon(int port, struct file *file, const char __user *buf, size_t size, loff_t *off);

int 	HDMI20_DevCtrl_PrintPhyRegTable(struct seq_file *m);
int 	HDMI20_DevCtrl_WritePhyRegTable(struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_DevCtrl_ReadPhyRegTableMode(struct file *file, const char __user *buf, size_t size, loff_t *off);
int 	HDMI20_DevCtrl_WritePhyRegTableMode(struct file *file, const char __user *buf, size_t size, loff_t *off);

/* DBG */
int 	HDMI20_Module_SwVersion(void);
void 	HDMI20_Module_Set_Line_Debugger(UINT32 value);
UINT32	HDMI20_Module_Get_Line_Debugger(void);
void 	HDMI20_Module_Set_Audio_Line_Debugger(UINT32 value);
UINT32	HDMI20_Module_Get_Audio_Line_Debugger(void);
int 	HDMI20_Module_Get_DevConCnt(HDMI20_DEV_CONTROL_TYPE_T type, int *pCnt);
int 	HDMI20_Module_Get_DevCon(HDMI20_DEV_CONTROL_TYPE_T type, HDMI20_DEV_CONTROL_T *pDevCon, int size);
int		HDMI20_Module_Set_DevCon(HDMI20_DEV_CONTROL_TYPE_T type, UINT32 index, UINT32 data);
int		HDMI20_Module_Set_DBGTool(int type, UINT8 port, int data);
UINT32	HDMI20_Module_Get_VrrFrequency(UINT8 port);
int		HDMI20_Module_Set_Calculate_EDID_CheckSum(int port, bool *isChangeD);

/* ESM */
int 	HDMI21_HDCP23_Module_Set_HlcReset(unsigned int port, int isPllLocked);
int 	HDMI21_HDCP23_Module_Set_HlcAuthenticate(unsigned int port, int reauth);
int 	HDMI21_HDCP23_Module_Set_Close(void);
int 	HDMI21_HDCP23_Module_Set_Open(UINT8 *pData, int size, int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr);
int 	HDMI21_HDCP23_Module_Get_IsRepeater(void);
int 	HDMI21_HDCP23_Module_Set_IsRepeater(int isRepeater);
int 	HDMI21_HDCP23_Module_Get_RxId(unsigned char* pData, int size);
int 	HDMI21_HDCP23_Module_Set_RxId(unsigned char* pData, int size, int count, int depth);
int 	HDMI21_HDCP23_Module_TestApp(int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr);
int 	HDMI21_HDCP23_Module_Get_HlcMonitor(unsigned int port);
void 	HDMI21_HDCP23_Module_SetLogDump(char *pData, int *pSize);
int		HDMI21_HDCP23_Module_Get_ContentType(unsigned int port); 
void 	HDMI21_HDCP23_Module_PROC_GetEsmLog(struct seq_file* m);

void 	HDMI21_Module_Set_RegisterCB_HlcReset(int (*function)(unsigned int port, int isPllLocked));
void 	HDMI21_Module_Set_RegisterCB_HlcAuthenticate(int (*function)(unsigned int port, int reauth));
void 	HDMI21_Module_Set_RegisterCB_Close(int (*function)(void));
void 	HDMI21_Module_Set_RegisterCB_Open(int (*function)(UINT8 *pData, int size, int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr));
void 	HDMI21_Module_Set_RegisterCB_GetRepeater(int (*function)(void));
void 	HDMI21_Module_Set_RegisterCB_SetRepeater(int (*function)(int isRepeater));
void 	HDMI21_Module_Set_RegisterCB_GetRxId(int (*function)(unsigned char* pData, int size));
void 	HDMI21_Module_Set_RegisterCB_SetRxId(int (*function)(unsigned char* pData, int size, int count, int depth));
void 	HDMI21_Module_Set_RegisterCB_TestApp(void (*function)(int chipType, dma_addr_t codebase, UINT8 *codeVirtAddr, dma_addr_t database, UINT8 *dataVirtAddr));
void 	HDMI21_Module_Set_RegisterCB_HlcMonitor(int (*function)(unsigned int port));
void 	HDMI21_Module_Set_RegisterCB_LogDump(void (*function)(char *pData, int *pSize));
void 	HDMI21_Module_Set_RegisterCB_GetEsmLog(void (*function)(struct seq_file* m));
void	HDMI21_Module_Set_RegisterCB_GetContentType(int (*function)(unsigned int port));
void    HDMI21_Module_Set_EsmOfDmaConfigure(struct device *dev, struct device_node *np);

	/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PROTOS_H_ */

