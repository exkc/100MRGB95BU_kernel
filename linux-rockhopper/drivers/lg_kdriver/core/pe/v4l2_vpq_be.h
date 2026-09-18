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

/** @file v4l2_vpq_be.h
 *
 *  It is the header file for controling v4l2 PQ driver.
 *
 *  @author youngin.choi@lge.com
 *  @version 1.0
 *  @date  2018.06.14
 *  @see
 */

#ifndef _V4L2_VPQ_BE_H
#define _V4L2_VPQ_BE_H

#include <media/v4l2-ctrls.h>

int v4l2_vpq_compat_vidioc_ext_ctrls_be(struct v4l2_ext_control *ctrl);
int v4l2_vpq_vidioc_s_ctrl_be(struct file *file, void *__fh, struct v4l2_control *ctrl);
int v4l2_vpq_vidioc_g_ctrl_be(struct file *file, void *__fh, struct v4l2_control *ctrl);
int vpq_set_ext_ctrl_be(struct v4l2_ext_control *ctrl);
int vpq_get_ext_ctrl_be(struct v4l2_ext_control *ctrl);
int vpq_proc_show_status_be(struct seq_file *m, void *v, int id);
extern void v4l2_vpq_detect_vFreq(UINT32 v_freq);

#endif  /* _V4L2_VPQ_BE_H */

