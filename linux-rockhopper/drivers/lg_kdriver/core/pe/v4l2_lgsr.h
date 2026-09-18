/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file v4l2_vpq.h
 *
 *  It is the header file for controling v4l2 PQ driver.
 *
 *  @author youngin.choi@lge.com
 *  @version 1.0
 *  @date  2018.06.14
 *  @see
 */

#ifndef _V4L2_LGSR_H
#define _V4L2_LGSR_H

extern char *lgsr_ctrl_id_to_str(int id);

int v4l2_lgsr_device_init(void);
//int v4l2_lgsr_register(void *arg);
int lgsr_proc_init_block_func_pe(void);
int lgsr_proc_show_func_status_lgsr(void);
int lgsr_proc_set_block_func_lgsr(int num_func);
int lgsr_proc_set_block_func_dftmode(int mode);
#endif  /* _V4L2_VPQ_H */

