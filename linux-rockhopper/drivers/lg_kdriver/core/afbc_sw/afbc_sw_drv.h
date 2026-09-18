/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2021 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/
#ifndef _AFBC_SW_DRV_H_
#define _AFBC_SW_DRV_H_

/*  ----------------------------------------------------------------------------------------
    Control Constants
    ----------------------------------------------------------------------------------------*/
// SW 연산 동작이 필요한 경우 cache operation 이 되도록 한다.
// non cache operation 은 검증되지 않았아므로, 추후 필요한 경우 검증 하고 사용할것
#define AFBC_SW_USE_CAHCE_OP

/*  ----------------------------------------------------------------------------------------
    File Inclusions
    ----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/module.h>
#include "os_util.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*  ----------------------------------------------------------------------------------------
    Constant Definitions
    ----------------------------------------------------------------------------------------*/
#define AFBC_HDR_BLK_SZ 16
#define AFBC_DAT_BLK_SZ 1024

/*  ----------------------------------------------------------------------------------------
    Macro Definitions
    ----------------------------------------------------------------------------------------*/
#define afbc_default_ctx NULL

/*  ----------------------------------------------------------------------------------------
    Type Definitions
    ----------------------------------------------------------------------------------------*/
struct afbc_framebuffer
{
    phys_addr_t paddr;

#ifdef AFBC_SW_USE_CAHCE_OP
    OS_CACHE_MAP_T cmap;
#else
    unsigned char* vaddr;
#endif

    int w;
    int h;

    unsigned int fb_size;
    unsigned int header_size;
    unsigned int payload_size;
};

enum afbc_sw_transform_opt
{
    AFBC_TRANSFORM_TB_TO_SS, // top_bottom to side by side
    // future use
};

struct afbc_ctx
{
#define AFBC_SW_VER_NONE    0x00000000 // invalid
#define AFBC_SW_VER_1_0     0x00000010 // AFBC 0x10 (16x16 encoding)
#define AFBC_SW_VER_1_1     0x00000011 // AFBC 0x11 ( 32x8 encoding)
#define AFBC_SW_VER_AFRC    0x00000020 // AFRC (CU 32Byte fixed)
    unsigned int version;
};

/*  ----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
    ----------------------------------------------------------------------------------------*/
struct afbc_ctx afbc_sw_init_context(unsigned int afbc_version);

void afbc_sw_set_default_context(struct afbc_ctx* afbc_ctx);

int afbc_sw_get_header_size(struct afbc_ctx* ctx, int w, int h);
int afbc_sw_get_payload_size(struct afbc_ctx* ctx, int w, int h);
int afbc_sw_get_image_size(struct afbc_ctx* ctx, int w, int h);

struct afbc_framebuffer* afbc_sw_alloc_framebuffer(struct afbc_ctx* ctx,
        phys_addr_t paddr, int w, int h,
        unsigned int header_size, unsigned int payload_size, unsigned int fb_size);

void afbc_sw_free_framebuffer(struct afbc_ctx* ctx, struct afbc_framebuffer* fb);

int afbc_sw_fill(struct afbc_ctx* ctx, struct afbc_framebuffer* fb, unsigned int color);

int afbc_sw_blit(struct afbc_ctx* ctx, struct afbc_framebuffer* src_fb, struct afbc_framebuffer* dst_fb);

int afbc_sw_transform(struct afbc_ctx* ctx, struct afbc_framebuffer* src_fb, struct afbc_framebuffer* dst_fb,
                      enum afbc_sw_transform_opt opt);

const char* afbc_sw_get_fbc_fmt_string(struct afbc_ctx* ctx);
const char* afbc_sw_get_version_string(struct afbc_ctx* ctx);

// internal use only. called by base_device.c
void    afbc_sw_preinit(void);
int     afbc_sw_init(void);
void    afbc_sw_cleanup(void);

/*  ----------------------------------------------------------------------------------------
    Extern Variables (module param)
    ----------------------------------------------------------------------------------------*/

/*  ----------------------------------------------------------------------------------------
    Extern Variables
    ----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _afbc_sw_drv_h */

/** @} */
