#ifndef __DEMOD_FIRMWARE_M23_H__
#define __DEMOD_FIRMWARE_M23_H__

int DEMOD_M23_FW_Initialize(void);
int DEMOD_M23_SAT_FW_Initialize(void);
int DEMOD_M23_ALL_FW_Initialize(void);
int DEMOD_M23_FW_ReInitalize (int mode);

int DEMOD_M23_FW_Get_Info(const UINT8 * p_fw_bin, UINT32 * p_fw_date, UINT32 * p_fw_ver, char * p_fw_builder, UINT8 * p_fw_buildtime);
#endif
