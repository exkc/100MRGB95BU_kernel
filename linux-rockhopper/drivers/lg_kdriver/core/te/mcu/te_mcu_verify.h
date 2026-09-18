#ifndef TE_MCU_VERIFY_H
#define TE_MCU_VERIFY_H

#define MCU_SIGNATURE_LEN		256

int te_mcu_verify_mcu_binary(const void *data, u32 size);

#endif
