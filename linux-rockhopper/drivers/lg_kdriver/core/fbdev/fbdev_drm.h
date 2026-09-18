/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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
 *  driver interface header for fbdev device. ( used only within kdriver )
 *  fbdev device will teach you how to make device driver with new platform.
 *
 *  @author     raxis
 *  @version    1.0
 *  @date       2009.11.15
 *
 *  @addtogroup lg1150_fbdev
 *  @{
 */

#ifndef _FBDEV_DRM_H_
#define _FBDEV_DRM_H_

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif              /* __cplusplus */

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
    osd_drm_id_graphic0 = 0, // UI
    osd_drm_id_graphic1 = 1, // E-Streamer etc
    osd_drm_id_graphic2 = 2, // rsvd
    osd_drm_id_graphic3 = 3, // rsvd
    osd_drm_id_cursor,       // cursor
}
osd_drm_id;

typedef enum
{
    osd_drm_pxlfmt_xrgb,
    osd_drm_pxlfmt_xbgr,
    osd_drm_pxlfmt_comp_order_mask = 0x07,

    osd_drm_pxlfmt_axxx = 0x08,
    osd_drm_pxlfmt_argb = osd_drm_pxlfmt_xrgb | osd_drm_pxlfmt_axxx,
    osd_drm_pxlfmt_abgr = osd_drm_pxlfmt_xbgr | osd_drm_pxlfmt_axxx,

    osd_drm_pxlfmt_afbc = 0x10,

    osd_drm_pxlfmt_afbc_xrgb = osd_drm_pxlfmt_xrgb | osd_drm_pxlfmt_afbc,
    osd_drm_pxlfmt_afbc_xbgr = osd_drm_pxlfmt_xbgr | osd_drm_pxlfmt_afbc,
    osd_drm_pxlfmt_afbc_argb = osd_drm_pxlfmt_argb | osd_drm_pxlfmt_afbc,
    osd_drm_pxlfmt_afbc_abgr = osd_drm_pxlfmt_abgr | osd_drm_pxlfmt_afbc,

    osd_drm_pxlfmt_afrc = 0x20,

    osd_drm_pxlfmt_afrc_xrgb = osd_drm_pxlfmt_xrgb | osd_drm_pxlfmt_afrc,
    osd_drm_pxlfmt_afrc_xbgr = osd_drm_pxlfmt_xbgr | osd_drm_pxlfmt_afrc,
    osd_drm_pxlfmt_afrc_argb = osd_drm_pxlfmt_argb | osd_drm_pxlfmt_afrc,
    osd_drm_pxlfmt_afrc_abgr = osd_drm_pxlfmt_abgr | osd_drm_pxlfmt_afrc,

    osd_drm_pxlfmt_compress_type_mask = 0x30,

    osd_drm_pxlfmt_raw_xrgb = osd_drm_pxlfmt_xrgb,
    osd_drm_pxlfmt_raw_xbgr = osd_drm_pxlfmt_xbgr,
    osd_drm_pxlfmt_raw_argb = osd_drm_pxlfmt_argb,
    osd_drm_pxlfmt_raw_abgr = osd_drm_pxlfmt_abgr,
}
osd_drm_pxlfmt;

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
struct osd_drm_framebuffer
{
    phys_addr_t fbmem;
    osd_drm_pxlfmt fmt;
    unsigned int stride;
    unsigned int width;
    unsigned int height;

    unsigned int hotspot_x; // cursor only
    unsigned int hotspot_y; // cursor only
};

// fbdev kdriver 의 경우 open 시에 필요한 추가 리소스를 할당하게 되는데, DRM 단독으로도
// open 에 준하는 동작을 할 수 있어야 한다.
// DRM 초기화시에 아래 함수를 호출해 주어야 한다.
//
int osd_drm_initialize(struct platform_device* pdev);

// 현재 HW 설정 기준으로 출력 모드 (해상도) 를 지원할 수 있는지 여부를 판단한다.
// 가령 2K TV 의 경우 1920x1080 까지 지원함으로 리턴함
// 가령 4K TV 의 경우 3840x2160 까지 지원함으로 리턴함
// 가령 8K TV 의 경우 7680x4320 까지 지원함으로 리턴함
//
bool osd_drm_check_mode(int hdisplay, int vdisplay);

// UI, 커서 이미지 업데이트 목적
// 각 OSD layer 에 적합한 pixel format 을 설정해야 한다.
//
// x, y 값은 cursor 와 E-streamer 부분에서 의미있게 사용됨
// 특히 아래 함수를 통해 cursor 출력이 필요한 모든 정보가 전달되므로, 별도의 move_cursor 함수는 삭제한다.
//
int osd_drm_flip_image(osd_drm_id id, struct osd_drm_framebuffer* framebuffer, unsigned int x, unsigned int y);

// osd plane 을 on/off 시킬수 있다.
//
int osd_drm_enable(osd_drm_id id, bool en);

// 테스트 목적 등으로 drm 동작을 잠시 중지 시키도록 한다.
void osd_drm_freeze(bool en);

//  등록된 vsync handler 는 매 HW vsync 발생시마다 호출됨
//  interrupt 받기 싫으면 NULL 로 설정해 주면 됨
//
void osd_drm_register_vsync_handler(void(*handler)(void));

// 커서 영역의 동작 영역 정보를 전달한다.
// 가령 커서 좌표 움직임이 FHD 영역내에서 움직인다면 osd_drm_set_region(1920,1080) 설정 필요
// 보통은 primary plane 의 해상도와 동일하게 입력이 된다.
//
int osd_drm_set_cursor_region(unsigned int w, unsigned int h);

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef  __cplusplus
}
#endif              /* __cplusplus */
#endif              /* _FBDEV_DRV_H_ */
/** @} */
