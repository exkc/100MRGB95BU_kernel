#ifndef __DEMOD_UTIL_E60_H__
#define __DEMOD_UTIL_E60_H__

int DEMOD_E60_Get_UART(BOOLEAN *pStatus);
int DEMOD_E60_Set_UART(int enable);
int DEMOD_E60_Get_JTAG(BOOLEAN *pStatus);
int DEMOD_E60_Set_JTAG(int enable);
int DEMOD_E60_Get_Trace(char * pDbglog, int * pDbgidx);
int DEMOD_E60_Set_Trace(int enable);

int DEMOD_E60_MCU_Set_UART_Speed(int speed);
int DEMOD_E60_MCU_Set_UART(int enable);
int DEMOD_E60_MCU_Set_UART_HEX(int enable);

#endif

