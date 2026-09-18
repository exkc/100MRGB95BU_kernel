#ifndef _EMUL_TE_H_
#define _EMUL_TE_H_

int XEMUL_LOG_Write(const char *fmt, ...);

void XEMUL_MCU_IrqRequest(int num, void (*handler)(void));
void XEMUL_MCU_EnableIrq(unsigned int mask);
void XEMUL_MCU_DisableIrq(unsigned int mask);

void XEMUL_DataWrite(unsigned int addr, unsigned int value);
unsigned int XEMUL_DataRead(unsigned int addr);

extern unsigned char *xemul_reg_base;


#endif	// _EMUL_TE_H_
