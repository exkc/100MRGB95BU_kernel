#ifndef __DEMOD_FIRMWARE_E60_H__
#define __DEMOD_FIRMWARE_E60_H__

int DEMOD_E60_FW_Initialize(void);
int DEMOD_E60_SAT_FW_Initialize(void);
int DEMOD_E60_ALL_FW_Initialize(void);
int DEMOD_E60_FW_ReInitalize (int mode);

int DEMOD_E60_FW_Error_Handler (int errcode);
#endif
