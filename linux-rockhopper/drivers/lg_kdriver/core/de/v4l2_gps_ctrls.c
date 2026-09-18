
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/kthread.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include <media/videobuf2-vmalloc.h>

#include "gps_if.h"
#include "v4l2_gps.h"


#define V4L2_GPS_MAX_CTRL_NUM	10



#define ctrl_to_ctx(__ctrl) \
	    container_of((__ctrl)->handler, struct gps_priv, ctrl_handler)



static int v4l2_gps_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct gps_priv *ctx = ctrl_to_ctx(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_ALPHA_COMPONENT:
    	ctx->alpha = ctrl->val;
		break;
	}

	return 0;
}


static const struct v4l2_ctrl_ops v4l2_gps_ctrl_ops = {
	    .s_ctrl = v4l2_gps_s_ctrl,
};

int v4l2_gps_ctrls_create(struct gps_priv *ctx)
{
   	if (ctx->ctrls_rdy) {
		pr_err("Control handler of this context was created already");
		        return 0;
	}
   	
   	v4l2_ctrl_handler_init(&ctx->ctrl_handler, V4L2_GPS_MAX_CTRL_NUM);
		
	ctx->ctrl_alpha = v4l2_ctrl_new_std(&ctx->ctrl_handler,
	            &v4l2_gps_ctrl_ops, V4L2_CID_ALPHA_COMPONENT, 0, 255, 1, 0);
			
	ctx->ctrls_rdy = ctx->ctrl_handler.error == 0;
				
	if (ctx->ctrl_handler.error) {
		int err = ctx->ctrl_handler.error;

		v4l2_ctrl_handler_free(&ctx->ctrl_handler);
		pr_err("Failed to create G-Scaler control handlers");

		return err;
	}

	return 0;
}

void v4l2_gps_ctrls_delete(struct gps_priv *ctx)
{
    if (ctx->ctrls_rdy) {
        v4l2_ctrl_handler_free(&ctx->ctrl_handler);
        ctx->ctrls_rdy = false;
    }
}

