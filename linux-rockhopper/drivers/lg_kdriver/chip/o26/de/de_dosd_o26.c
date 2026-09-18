/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/


/** @file
 *
 * main driver implementation for de device.
 * de device will teach you how to make device driver with new platform.
 *
 * author	  jaemo.kim (jaemo.kim@lge.com)
 * version	  1.0
 * date		  2011.02.18
 * note		  Additional information.
 *
 * @addtogroup lg1150_de
 * @{
 */

/*----------------------------------------------------------------------------------------
 *	 Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"

#include "de_model.h"
#include "de_ver_def.h"

#ifdef USE_KDRV_CODES_FOR_O26
#include "de_def.h"

/*----------------------------------------------------------------------------------------
 *	 Constant Definitions
 *---------------------------------------------------------------------------------------*/
#define DE_DOSD_O26_BASE (0xCC880900)
#define DSD_MAX_LEN      (6144/4)
#define DSD_MAX_LINE_LEN (24)
#define DSD_MAX_LINE_NUM (24)

/*----------------------------------------------------------------------------------------
 *	 Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Type Definitions
 *---------------------------------------------------------------------------------------*/
 struct de_dosd_o26_ctx {
	int init;
	int onoff;
	int big;
	int r;
	int g;
	int b;
};

typedef union {
	UINT32 udata32;
	struct {						//0xCC880900 RW 0x0706_4030
	UINT32 reg_canvas_y_size                :12;	//(11:00,RW,0x30) //Canvas Vertical Size - 제약 없음	Canvas_H*V =< 6144 조건 있음(Memory Size)	ex> 128x48(O), 132x48(X), 12x10(O)
	UINT32 reg_canvas_x_size                :12;	//(23:12,RW,0x64) //Canvas Horizontal Size - 4의 배수 제약	8K : 16x16(Max 480), 32x32(Max 240)	4K : 16x16(Max 240), 32x32(Max 120)	2K : 16x16(Max 120), 32x32(Max 60)
	UINT32 reg_dsd_bypass                   :1;	//(24,RW,0x1) //0: use Debug OSD , 1: Bypass Debug OSD
	UINT32 reg_in_cavas_back                :1;	//(25,RW,0x1) //0: All Image, 1: In Canvas
	UINT32 reg_font_size                    :2;	//(27:26,RW,0x1) //0: 16x16, 1: 32x32
	UINT32 reg_reset_select                 :2;	//(29:28,RW,0x0) //0: vsync_falling , 1: vactive_falling	2: vsync_rising  , 3: vactive_rising
	UINT32 resvd                            :1;
	UINT32 reg_dsd_detour                   :1;	//(31,RW,0x0) //0: use Debug OSD , 1: detour Debug OSD
	};
}DE_DOSD_O26_REG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880904 RW 0x0000_0000
	UINT32 reg_offset_y                     :14;	//(13:0,RW,0x0) //Canvas Vertical Offset	(제약 조건 없음)
	UINT32 resvd0                           :2;
	UINT32 reg_offset_x                     :14;	//(29:16,RW,0x0) //Canvas Horizontal Offset	(Input 2P, 4P, 8P에 따라 2, 4, 8의 배수 제약)
	UINT32 resvd1                           :2;
	};
}DE_DOSD_O26_REG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880908 RW 0xFFFF_FFFF
	UINT32 reg_fore_blue                    :8;	//(7:0,RW,0xFF) //Letter Blue Color
	UINT32 reg_fore_green                   :8;	//(15:8,RW,0xFF) //Letter Green Color
	UINT32 reg_fore_red                     :8;	//(23:16,RW,0xFF) //Letter Red Color
	UINT32 reg_fore_alpha                   :8;	//(31:24,RW,0xFF) //Letter RGB Alpha
	};
}DE_DOSD_O26_REG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88090C RW 0x0000_0000
	UINT32 reg_back_blue                    :8;	//(7:0,RW,0x0) //Background Blue Color
	UINT32 reg_back_green                   :8;	//(15:8,RW,0x0) //Background Green Color
	UINT32 reg_back_red                     :8;	//(23:16,RW,0x0) //Background Red Color
	UINT32 reg_back_alpha                   :8;	//(31:24,RW,0x0) //Background RGB Alpha
	};
}DE_DOSD_O26_REG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880910 RW 0x0F00_0870
	UINT32 reg_image_height                 :14;	//(13:0,RW,0x0870) //Image_height
	UINT32 resvd0                           :2;
	UINT32 reg_image_width                  :14;	//(29:16,RW,0x0F00) //Image_width
	UINT32 resvd1                           :2;
	};
}DE_DOSD_O26_REG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880914 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}DE_DOSD_O26_REG_IREG_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880918 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}DE_DOSD_O26_REG_IREG_DATA_T;

struct de_dosd_o26_reg {
	DE_DOSD_O26_REG_CTRL_00_T                        reg_dsd_ctrl_00;	//0xCC880900
	DE_DOSD_O26_REG_CTRL_01_T                        reg_dsd_ctrl_01;	//0xCC880904
	DE_DOSD_O26_REG_CTRL_02_T                        reg_dsd_ctrl_02;	//0xCC880908
	DE_DOSD_O26_REG_CTRL_03_T                        reg_dsd_ctrl_03;	//0xCC88090C
	DE_DOSD_O26_REG_CTRL_04_T                        reg_dsd_ctrl_04;	//0xCC880910
	DE_DOSD_O26_REG_IREG_CTRL_T                    reg_dsd_ireg_ctrl;	//0xCC880914
	DE_DOSD_O26_REG_IREG_DATA_T                    reg_dsd_ireg_data;	//0xCC880918
};

/*----------------------------------------------------------------------------------------
 *	 External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 External Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 global Functions
 *---------------------------------------------------------------------------------------*/
int de_dosd_o26_set_color(int r, int g, int b);
int de_dosd_o26_set_size(int big);
int de_dosd_o26_enable(int onoff);
int de_dosd_o26_print(const char *fmt, ...);

/*----------------------------------------------------------------------------------------
 *	 global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *	 Static Variables
 *---------------------------------------------------------------------------------------*/
static char *_gp_de_dosd_o26_buf = NULL;
static struct de_dosd_o26_ctx _g_de_dosd_o26_ctx = {.init=0,.onoff=0,.big=1};
static volatile struct de_dosd_o26_reg *_gp_de_dosd_o26_reg = NULL;

/*========================================================================================
 *	 Implementation Group
 *=======================================================================================*/
int de_dosd_o26_set_color(int r, int g, int b)
{
	struct de_dosd_o26_ctx *p_ctx = &_g_de_dosd_o26_ctx;
	DE_DOSD_O26_REG_CTRL_02_T reg_dsd_ctrl_02;	//0xCC860908

	if (!_gp_de_dosd_o26_reg) {
		DE_NOTI("reg null\n");
		return -1;
	}

	if (p_ctx->r == r && p_ctx->g == g && p_ctx->b == b) {
		DE_NOTI("already r:%d,g:%d,b:%d\n",r,g,b);
		return 0;
	}

	p_ctx->r = r;
	p_ctx->g = g;
	p_ctx->b = b;

	reg_dsd_ctrl_02.reg_fore_alpha = 0xF0;
	reg_dsd_ctrl_02.reg_fore_red   = (p_ctx->r == 1)? 0xFF:0x0;
	reg_dsd_ctrl_02.reg_fore_green = (p_ctx->g == 1)? 0xFF:0x0;
	reg_dsd_ctrl_02.reg_fore_blue  = (p_ctx->b == 1)? 0xFF:0x0;

	_gp_de_dosd_o26_reg->reg_dsd_ctrl_02.udata32 = reg_dsd_ctrl_02.udata32;

	return 0;
}

int de_dosd_o26_set_size(int big)
{
	struct de_dosd_o26_ctx *p_ctx = &_g_de_dosd_o26_ctx;
	DE_DOSD_O26_REG_CTRL_00_T reg_dsd_ctrl_00;	//0xCC880900

	if (!_gp_de_dosd_o26_reg) {
		DE_NOTI("reg null\n");
		return -1;
	}

	if (p_ctx->big == big) {
		DE_NOTI("already big:%d\n",big);
		return 0;
	}

	p_ctx->big = big;

	reg_dsd_ctrl_00.udata32 = _gp_de_dosd_o26_reg->reg_dsd_ctrl_00.udata32;

	reg_dsd_ctrl_00.reg_font_size = (p_ctx->big == 1)? 1:0;

	_gp_de_dosd_o26_reg->reg_dsd_ctrl_00.udata32 = reg_dsd_ctrl_00.udata32;

	return 0;
}

int de_dosd_o26_enable(int onoff)
{
	struct de_dosd_o26_ctx *p_ctx = &_g_de_dosd_o26_ctx;
	DE_DOSD_O26_REG_CTRL_00_T reg_dsd_ctrl_00;	//0xCC880900

	if (p_ctx->onoff == onoff) {
		DE_NOTI("already onoff:%d\n",onoff);
		return 0;
	}

	p_ctx->onoff = onoff;

	if (p_ctx->init == 0) {
		_gp_de_dosd_o26_buf = (char *)OS_KMalloc(4*DSD_MAX_LEN);
		if (!_gp_de_dosd_o26_buf) return -1;
		_gp_de_dosd_o26_reg = (volatile struct de_dosd_o26_reg *)ioremap(DE_DOSD_O26_BASE, sizeof(struct de_dosd_o26_reg));
		if (!_gp_de_dosd_o26_reg) return -1;

		reg_dsd_ctrl_00.udata32 = 0x80050018;
		reg_dsd_ctrl_00.reg_canvas_x_size = DSD_MAX_LINE_LEN*4;
		reg_dsd_ctrl_00.reg_canvas_y_size = DSD_MAX_LINE_NUM;
		reg_dsd_ctrl_00.reg_font_size = (p_ctx->big == 1)? 1:0;
		reg_dsd_ctrl_00.reg_dsd_detour = (p_ctx->onoff == 1)? 0:1;
		_gp_de_dosd_o26_reg->reg_dsd_ctrl_00.udata32 = reg_dsd_ctrl_00.udata32;
		_gp_de_dosd_o26_reg->reg_dsd_ctrl_01.udata32 = 0x00400080;
		de_dosd_o26_set_color(1,0,0);//red
		_gp_de_dosd_o26_reg->reg_dsd_ctrl_03.udata32 = 0x00000000;

		memset(_gp_de_dosd_o26_buf,0x20,sizeof(UINT32)*DSD_MAX_LEN);
		p_ctx->init = 1;
		DE_NOTI("init done\n");
	}
	else {
		reg_dsd_ctrl_00.udata32 = _gp_de_dosd_o26_reg->reg_dsd_ctrl_00.udata32;

		reg_dsd_ctrl_00.reg_dsd_detour = (p_ctx->onoff == 1)? 0:1;

		_gp_de_dosd_o26_reg->reg_dsd_ctrl_00.udata32 = reg_dsd_ctrl_00.udata32;

		DE_NOTI("onoff:%d\n",p_ctx->onoff);
	}

	//if (_gp_de_dosd_o26_buf) OS_Free((void *)_gp_de_dosd_o26_buf);
	//if (_gp_de_dosd_o26_reg) iounmap((void *)_gp_de_dosd_o26_reg);
	return 0;
}

int de_dosd_o26_print(const char *fmt, ...)
{
	va_list ap;
	int i, n, len, curr_pos, next_pos, line_len;
	UINT32 reg_data;
	char print_buf[128];
	__attribute__((unused)) struct de_dosd_o26_ctx *p_ctx = &_g_de_dosd_o26_ctx;

	de_dosd_o26_enable(1);

	do {
		line_len = DSD_MAX_LINE_LEN*4;

		va_start(ap, fmt);
		len = vsnprintf(print_buf, 128, fmt, ap);
		va_end(ap);
		if (len <= 0 || len >= line_len) break;

		//DE_NOTI("print_buf(%s)\n",print_buf);
		if (print_buf[len-1] == '\n') len--;

		//scroll
		for(i = (DSD_MAX_LINE_NUM-2); i >=0 ; i--)
		{
			curr_pos = i*line_len;
			next_pos = (i+1)*line_len;
			memcpy(&_gp_de_dosd_o26_buf[next_pos],&_gp_de_dosd_o26_buf[curr_pos],line_len);
		}
		memset(&_gp_de_dosd_o26_buf[0],0x20,line_len);
		strncpy(&_gp_de_dosd_o26_buf[0],print_buf,len);

		for(i = 0; i < DSD_MAX_LEN; i++)
		{
			n = 4*i;
			reg_data = ((_gp_de_dosd_o26_buf[n]&0xff)<<24) | ((_gp_de_dosd_o26_buf[n+1]&0xff)<<16) | ((_gp_de_dosd_o26_buf[n+2]&0xff)<<8) | (_gp_de_dosd_o26_buf[n+3]&0xff);
			_gp_de_dosd_o26_reg->reg_dsd_ireg_ctrl.udata32 = i;
			_gp_de_dosd_o26_reg->reg_dsd_ireg_data.udata32 = reg_data;
		}
	} while(0);

	return 0;
}

#endif
/**  @} */
