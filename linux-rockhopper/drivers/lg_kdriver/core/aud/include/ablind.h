#ifndef _ABLIND_INF_H_
#define _ABLIND_INF_H_

#include <linux/kernel.h>
#include <linux/ioctl.h>

struct ablind_canhandle
{
	unsigned int len;	// strlen(name), without zero
	union {
		long long _sizer;
		char *name;
	} n;
};

#define ABLIND_IOCTL_TYPE		'B'
#define ABLIND_IOCTL_SET_CANHANDLE	_IOW (ABLIND_IOCTL_TYPE, 1, struct ablind_canhandle)
#define ABLIND_IOCTL_SET_RETURN		_IO  (ABLIND_IOCTL_TYPE, 2)

#endif
