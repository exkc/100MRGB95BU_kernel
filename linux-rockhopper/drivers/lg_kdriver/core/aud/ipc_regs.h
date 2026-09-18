#ifndef _AUD_IPC_REGS_H_
#define _AUD_IPC_REGS_H_

extern volatile unsigned int *aud_reg_ipc;

#include "common/ipc_reg_offs.h"

#define AUD_IPCREG(name)        (aud_reg_ipc[(AUD_IPCOFFS_##name)/4])
#define AUD_IPCREG_OFFS(offs)   (aud_reg_ipc[(offs)/4])

#define AUD_IPCREG_SIZE         0x1100

#endif
