#ifndef _BLIND_H_
#define _BLIND_H_

#include <linux/init.h>

int __init ablind_init (void);
int ablind_post (const char *name, unsigned int num_args, ...);

int ablind_callv_timeout (int timeout, int *callret, const char *name, int num_args, int *args);
int ablind_callv (int *callret, const char *name, int num_args, int *args);

int ablind_call_timeout (int timeout, int *callret, const char *name, int num_args, ...);
int ablind_call (int *callret, const char *name, int num_args, ...);

#endif
