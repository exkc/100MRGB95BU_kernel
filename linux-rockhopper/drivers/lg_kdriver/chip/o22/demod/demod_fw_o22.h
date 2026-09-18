#ifndef __DEMOD_FIRMWARE_O22_H__
#define __DEMOD_FIRMWARE_O22_H__

int DEMOD_O22_FW_Initialize(void);
int DEMOD_O22_SAT_FW_Initialize(void);
int DEMOD_O22_ALL_FW_Initialize(void);
int DEMOD_O22_FW_ReInitalize (int mode);

int DEMOD_O22_FW_Get_Info(const UINT8 * p_fw_bin, UINT32 * p_fw_date, UINT32 * p_fw_ver, char * p_fw_builder, UINT8 * p_fw_buildtime);
#endif
