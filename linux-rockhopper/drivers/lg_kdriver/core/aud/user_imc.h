#ifndef _AUDIO_USER_IMC_H_
#define _AUDIO_USER_IMC_H_

#include <linux/init.h>

struct _IpcHeader;

int __init ausrimc_init (void);
void __exit ausrimc_exit (void);

int ausrimc_post_imc (int processor_number, struct _IpcHeader *header, void *param);
bool ausrimc_get_task_status_normal (int processor_number);

#endif
