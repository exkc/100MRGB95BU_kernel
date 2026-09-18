#include "v4l2_lg_dev_configs.h"

/* Need to define LG Capture device informations Here */
struct frame_interval_info	frame_intervals[MAX_FRAME_INTER_CNT] = \
{
	{
		.type = V4L2_FRMIVAL_TYPE_DISCRETE,
		{
			.disc_intrval.numerator = 1,
			.disc_intrval.denominator = 60,
		}

	}
};
#if 0
struct frame_size_info frame_sizes[MAX_FRAME_SIZE_CNT] = \
{
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 1920,
			.disc_frm.height= 1080,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 1600,
			.disc_frm.height= 900,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 1440,
			.disc_frm.height= 810,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 1280,
			.disc_frm.height= 720,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 960,
			.disc_frm.height= 540,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 800,
			.disc_frm.height= 600,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 720,
			.disc_frm.height= 480,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 640,
			.disc_frm.height= 480,
		},
		{0,1}
	},
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_DISCRETE,
		{
			.disc_frm.width = 320,
			.disc_frm.height= 240,
		},
		{0,1}
	},
};
#else
struct frame_size_info frame_sizes[MAX_FRAME_SIZE_CNT] = \
{
	{
		.type = (__u32)V4L2_FRMSIZE_TYPE_STEPWISE,
		{
			.step_frm.max_width   = 1920,
			.step_frm.max_height  = 1080,
			.step_frm.step_width  = 1,
			.step_frm.step_height = 1,
			.step_frm.min_width   = 64, //  320->64 : request from SCDCR-2990
			.step_frm.min_height  = 64, //  240->64 : request from SCDCR-2990
		},
		{0,1}
	},
};
#endif
struct pixel_format_info pixel_formats_mp[MAX_FORMAT_CNT_MP] = \
{
	{
		.pixel_format = V4L2_PIX_FMT_NV12M,
		.desc = "YUV 4:2:0 [Non contiguous]",
		.frame_size_indexes = {0},
		.num_planes = 2
	},
    {
        .pixel_format = V4L2_PIX_FMT_ARGB32,
        .desc = "ARGB32 32 bit [contiguous]",
        .frame_size_indexes = {0},
        .num_planes = 1
    },
    {
        .pixel_format = V4L2_PIX_FMT_ABGR32,
        .desc = "ABGR32 32 bit [contiguous]",
        .frame_size_indexes = {0},
        .num_planes = 1
    }
};

struct pixel_format_info pixel_formats_sp[MAX_FORMAT_CNT_SP] = \
{
	{
		.pixel_format = V4L2_PIX_FMT_ARGB32,
		.desc = "ARGB32 32 bit [contiguous]",
		.frame_size_indexes = {0},
		.num_planes = 1
	},
	{
		.pixel_format = V4L2_PIX_FMT_ABGR32,
		.desc = "ABGR32 32 bit [contiguous]",
		.frame_size_indexes = {0},
		.num_planes = 1
	}
};

struct capture_device_info capture_devs[MAX_CAPTURE_DEVS] =
{
	{
		.name = "VDEC0",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC1",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC2",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC3",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC4",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC5",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC6",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	},
	{
		.name = "VDEC7",
		.type = V4L2_INPUT_TYPE_CAMERA,
		.std  = V4L2_STD_UNKNOWN,
		.status = V4L2_IN_ST_NO_POWER,
		.capabilities = V4L2_IN_CAP_NATIVE_SIZE,
		.cap_format_indexes = {0},
	}
};

/* Need to store control in increasing order of id */
struct v4l2_queryctrl gps_v4l2_queryctrl[MAX_CNTRL_CNT] = {
	{
		.id = V4L2_CID_MIN_BUFFERS_FOR_CAPTURE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Min capture buffers",
		.minimum = MIN_GPS_BUF,
		.maximum = MAX_GPS_BUF,
		.step = 0,
		.default_value = MIN_GPS_BUF,
		.flags = V4L2_CTRL_FLAG_READ_ONLY,
		.reserved = {0,0},
	},
};

struct v4l2_querymenu gps_v4l2_querymenu[MAX_MENU_CNT] = {
	{
		.id = V4L2_CID_MIN_BUFFERS_FOR_CAPTURE,
		.index = 0,
		.value = MIN_GPS_BUF,
		.reserved = 0,
	},
};
