/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  interface header for lne device
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.06.18
 *
 */

#ifndef _LNE_H
#define _LNE_H

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define LNE_IOCTL_TYPE              'L'
#define LNE_IOCTL_RESET             _IO  (LNE_IOCTL_TYPE, 1)
#define LNE_IOCTL_INITIALIZE        _IOW (LNE_IOCTL_TYPE, 2, struct lne_init_param)
#define LNE_IOCTL_FINALIZE          _IO  (LNE_IOCTL_TYPE, 3)
#define LNE_IOCTL_NET_ONOFF         _IOW (LNE_IOCTL_TYPE, 4, unsigned int)


/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define LNE_IOCTL_PTR_FOR_COMPAT(name)   \
union {                                 \
    const unsigned char *name;          \
    unsigned int compat_##name;         \
    unsigned long long sizer_##name;    \
}

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct lne_init_param {
    /* first network info */
    LNE_IOCTL_PTR_FOR_COMPAT (firmware);
    LNE_IOCTL_PTR_FOR_COMPAT (weight);
    unsigned int firmware_size;
    unsigned int weight_size;
    unsigned int number_of_input;
    unsigned int number_of_output;

    /* second network info */
    LNE_IOCTL_PTR_FOR_COMPAT (firmware2);
    LNE_IOCTL_PTR_FOR_COMPAT (weight2);
    unsigned int firmware2_size;
    unsigned int weight2_size;
    unsigned int number_of_input2;
    unsigned int number_of_output2;
};

#endif  /* _LNE_H */
