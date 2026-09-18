// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2023 LG Electronics
 */

#include <linux/kernel.h>
#include "ptmanip.h"

/*
 * d65f03c0 ret
 * d503201f nop
 * d503201f nop
 * d503201f nop
 */
static unsigned long shellcode[] = {
	0xd503201fd65f03c0,
	0xd503201fd503201f,
};

typedef void (*shell_func)(void);

void ekp_ptm_execute_shellcode(void *mem)
{
	unsigned long *ptr = (unsigned long *)mem;
	shell_func func = (shell_func)mem;
	int size = ARRAY_SIZE(shellcode);
	int i;

	for (i = 0; i < size; ++i, ++ptr)
		*ptr = shellcode[i];

	func();
}
