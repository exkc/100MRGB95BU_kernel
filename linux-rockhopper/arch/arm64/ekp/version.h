/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2017 LG Electronics
 */

#ifndef __ARM64_EKP_VERSION_H
#define __ARM64_EKP_VERSION_H

/* EKP F/W version */
#define EKP_VER_MAJOR		2
#define EKP_VER_MINOR		8

#define VERSION_MAKE(a, b, c)	(((a) << 16) | ((b) << 8) | (c))
#define ekp_ver_major(v)	(((v) >> 16) & 0xFF)
#define ekp_ver_minor(v)	(((v) >> 8) & 0xFF)
#define ekp_ver_revision(v)	((v) & 0xFF)

#define EKP_VERSION		VERSION_MAKE(EKP_VER_MAJOR, EKP_VER_MINOR, 0)

extern unsigned int fw_ver __ro_after_init;

#endif /* __ARM64_EKP_VERSION_H */
