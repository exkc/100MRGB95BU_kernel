#ifndef __DEMOD_UTIL_O22_H__
#define __DEMOD_UTIL_O22_H__

int DEMOD_O26_Get_UART(BOOLEAN *pStatus);
int DEMOD_O26_Set_UART(int enable);
int DEMOD_O26_Get_JTAG(BOOLEAN *pStatus);
int DEMOD_O26_Set_JTAG(int enable);
int DEMOD_O26_Get_Trace(char * pDbglog, int * pDbgidx);
int DEMOD_O26_Set_Trace(int enable);

int DEMOD_O26_MCU_Set_UART_Speed(int speed);
int DEMOD_O26_MCU_Set_UART(int enable);
int DEMOD_O26_MCU_Set_UART_HEX(int enable);

void DEMOD_CHIP_PROC_Init(void);
void DEMOD_CHIP_PROC_cleanup(void);


#endif

