/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

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
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		jun.kong
 *  @version	0.9
 *  @date		2018-06-04
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
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

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>

#include "spi_drv.h"
#include "os_util.h"
#include "base_device.h"
#include "v4l2-lge-spi.h"

#include <linux/spi/spi.h>
#include <linux/amba/pl022.h>
#include <asm/io.h>

DEFINE_MUTEX(spikdrv_mutex);
/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define V4L2_SPI_DEV_NUMBER  60


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static struct v4l2_device v4l2_spi_dev;
//struct mutex v4l2_spi_video_device_lock;
void __iomem *spi_ctop_base ;
static char devicename[100];
unsigned int v4l2_spi_init[SPI_KDRV_HW_NUM];
struct __maybe_unused spi_device *pv4l2_spi_device[SPI_KDRV_HW_NUM]= {NULL,};

static __maybe_unused int v4l2_spi_send (unsigned char ch, unsigned char  *data, int len, int cmdlen);
struct spi_fh {
	struct v4l2_fh fh;
	UINT32 init[SPI_KDRV_HW_NUM];
	UINT32 clock[SPI_KDRV_HW_NUM];
// need to add some private data
//	struct spi_priv *spi_priv;
};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static char *ctrl_id_to_str(int id);
static int v4l2_spi_probe(struct platform_device *pdev);
static int v4l2_spi_remove(struct platform_device *pdev);
static int v4l2_spi_resume(struct device *dev);
static int v4l2_spi_suspend(struct device *dev);

/* FOPS releated to V4L2 */
static int v4l2_spi_register(void *arg);


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
static __maybe_unused int v4l2_spi_config (unsigned char ch, unsigned char	mode ,unsigned int speed )
{
	struct spi_device * spi;
	int retval = 0;
	unsigned int tmp = 0;
	unsigned int mode_save;
	unsigned int speed_save ;

	if(pv4l2_spi_device[ch] != NULL)
	{
		spi = pv4l2_spi_device[ch];
		mode_save = spi->mode;
		speed_save = spi->max_speed_hz;

		tmp |= spi->mode & ~SPI_MODE_MASK;
		spi->mode = (u16)tmp;
		spi->max_speed_hz = speed;
		retval = spi_setup(spi);

		printk( "spi speed %d\n", speed_save);
		printk( "spi mode %x\n", mode_save);
	}
	else
		SPI_ERROR( "check config param  %d\n", retval);

	return 0;

}

int v4l2_spi_write(UINT8 u8channel, UINT32 u32addr, UINT8* u8dataToWrite,
	UINT32 u32size)
{
	int ret = 0;
	UINT8 sbuf[10 + ADDR_SIZE_IN_BYTE]={0,};
	UINT8 * buf =NULL;

	if(!v4l2_spi_init[u8channel])
	{
		SPI_ERROR("Need INIT\n");
		return -1;
	}

	if(u32size  > SPI_MSG_MAX + 4 )
	{
		SPI_ERROR("check u32size[%x] n",u32size);
		return -1;
	}

	buf = sbuf;

	if( u32size > 10 )
	{
		buf = (UINT8*) kmalloc(sizeof(UINT8)*(u32size + ADDR_SIZE_IN_BYTE),GFP_KERNEL);
		if(buf != NULL)
		{
			memset(buf,0x0,sizeof(UINT8)*(u32size + ADDR_SIZE_IN_BYTE));
		}
		else
		{
			SPI_ERROR("check write buf\n");
			return -1;
		}
	}


	buf[0] = (UINT8)( (u32addr >> 24) & 0xff);
	buf[1] = (UINT8)( (u32addr >> 16) & 0xff);
	buf[2] = (UINT8)( (u32addr >>  8) & 0xff);
	buf[3] = (UINT8)( (u32addr >>  0) & 0xff);

	memcpy(buf + ADDR_SIZE_IN_BYTE, u8dataToWrite, u32size);
	ret = v4l2_spi_send(u8channel,buf, ADDR_SIZE_IN_BYTE + u32size,0);

	if( u32size > 10)
	{
		kfree(buf);
	}

	return ret;

}

int v4l2_spi_read(UINT8 u8channel, UINT32 u32addrToRead, UINT8* u8dataToRead,
	UINT32 u32size)
{
	int ret = 0;
	UINT8 sbuf[10 + ADDR_SIZE_IN_BYTE ]={0,};
	UINT8 * buf =NULL;

	if(!v4l2_spi_init[u8channel])
	{
		SPI_ERROR("Need INIT\n");
		return -1;
	}

	buf = sbuf;

	if( u32size  > SPI_MSG_MAX + 4 )
	{
		SPI_ERROR("check u32size[%x] n",u32size);
		return -1;
	}

	if( u32size > 10)
	{
		buf = (UINT8*) kmalloc(sizeof(UINT8)*(u32size + ADDR_SIZE_IN_BYTE),GFP_KERNEL);
		if(buf != NULL)
		{
			memset(buf,0x0,sizeof(UINT8)*(u32size + ADDR_SIZE_IN_BYTE));
		}
		else
		{
			SPI_ERROR("check read buf\n");
			return -1;
		}

	}


	buf[0] = (UINT8)( (u32addrToRead >> 24) & 0xff);
	buf[1] = (UINT8)( (u32addrToRead >> 16) & 0xff);
	buf[2] = (UINT8)( (u32addrToRead >>  8) & 0xff);
	buf[3] = (UINT8)( (u32addrToRead >>  0) & 0xff);

	ret = v4l2_spi_send(u8channel,buf, ADDR_SIZE_IN_BYTE + u32size,ADDR_SIZE_IN_BYTE);

	if(u32size)
		memcpy(u8dataToRead, buf + ADDR_SIZE_IN_BYTE, u32size);

	if( u32size > 10)
	{
		kfree(buf);
	}

	return ret;

}

static __maybe_unused int v4l2_spi_send (unsigned char ch, unsigned char  *data, int len, int cmdlen)
{
    int ret,i;
    UINT32  val= 0;
	UINT8 * rxBuf = NULL;
	UINT8 sbuf[10 + ADDR_SIZE_IN_BYTE ]={0,};
	struct spi_device * spi;
    struct spi_transfer t;
    struct spi_message m;

	rxBuf = sbuf;
	memset( &t,0x0,sizeof( struct spi_transfer));
	memset( &m,0x0,sizeof( struct spi_message));

	if(pv4l2_spi_device[ch] == NULL)
	{
        SPI_ERROR ("check spi[%d] allocation\n",ch);
		return -1;
	}

	spi = pv4l2_spi_device[ch];

	if(len > 10)
	{
		rxBuf =  (UINT8*) kmalloc(sizeof(UINT8)*len,GFP_KERNEL);
	}

    t.tx_buf = data;
    t.rx_buf = rxBuf;
    t.len = len;
    t.delay_usecs = 100;
    t.bits_per_word = 8;
    t.speed_hz = spi->max_speed_hz;

    if(v4l2_spi_init[ch] == 0)
    {
		if(0){}
#ifdef INCLUDE_M19_CHIP_KDRV
		else if(lx_chip() == LX_CHIP_M19)
		{
			mutex_lock(&spikdrv_mutex);
			val = readl(spi_ctop_base);
			val = val | (1 << 27);
			writel(val,spi_ctop_base);

			val = readl(spi_ctop_base + 0x10);
			val = val & (~(0xE << (28 - 4*ch)));    /* M19 gpio 33,34,35 37,38,39 disable */
			writel(val,spi_ctop_base+0x10);
			mutex_unlock(&spikdrv_mutex);
			v4l2_spi_init[ch] = 1;
		}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
		else if(lx_chip() == LX_CHIP_M17)
		{
			mutex_lock(&spikdrv_mutex);
			val = readl(spi_ctop_base);
			val = val | (1 << 27);
			writel(val,spi_ctop_base);

			val = readl(spi_ctop_base + 0x10);
			val = val & (~(0xE << (28 - 4*ch)));    /* M19 gpio 33,34,35 37,38,39 disable */
			writel(val,spi_ctop_base+0x10);
			mutex_unlock(&spikdrv_mutex);
			v4l2_spi_init[ch] = 1;
		}
#endif
     }

    if(ch < SPI_KDRV_HW_NUM)
    {
        mutex_lock(&spikdrv_mutex);
        spi_message_init (&m);
        spi_message_add_tail (&t, &m);
        ret = spi_sync (pv4l2_spi_device[ch], &m);
        mutex_unlock(&spikdrv_mutex);

        if (ret < 0)
        {
            SPI_ERROR ("spi sync failed. [%d]\n",ret);
            return -1;
        }

        SPI_DEBUG ("spi ret[%d]\n",ret);
		for(i= 0; i < len; i++)
		{
			SPI_DEBUG("[%d]=tx[%x]rx[%x]\n",i,data[i],rxBuf[i]);
		}

		for(i= cmdlen; i < len; i++)
		{
			data[i]= rxBuf[i];
		}

		if( len > 10)
		{
			kfree(rxBuf);
		}
        return ret;

    }
	else
	{
        SPI_ERROR("check ch[%d]\n",ch);
        return -1;
    }
}

#if 0
static __maybe_unused int v4l2_spi_recv (unsigned int ch, unsigned char *data,int len)
{
    int ret = 0;
    unsigned int val= 0;
    unsigned char r[9];
    struct spi_transfer t =
    {
        .tx_buf = data,
        .rx_buf = r,
        .len = len,
        .delay_usecs = 100, //us
        .bits_per_word = 8,
    };

    struct spi_message m;

    if(v4l2_spi_init[ch] == 0)
    {
        mutex_lock(&spikdrv_mutex);
        val = readl(spi_ctop_base);
        val = val | (1 << 27);
        writel(val,spi_ctop_base+0x10);

        val = readl(spi_ctop_base + 0x10);
        val = val & (~(0xE << (28 - 4*ch)));    /* M19 gpio 33,34,35 37,38,39 disable */
        writel(val,spi_ctop_base+0x10);
        mutex_unlock(&spikdrv_mutex);
        v4l2_spi_init[ch] = 1;
     }

    if(ch < SPI_KDRV_HW_NUM)
    {
        mutex_lock(&spikdrv_mutex);
        spi_message_init (&m);
        spi_message_add_tail (&t, &m);

        ret = spi_sync (pv4l2_spi_device[ch], &m);
        mutex_unlock(&spikdrv_mutex);

        if (ret < 0)
        {
            printk ("spi sync failed.\n");
            return -1;
        }
        data[8] = r[8];
        data[7] = r[7];
        data[6] = r[6];
        data[5] = r[5];
        return ret ;

    }else{
        printk("check ch[%d]\n",ch);
        return -1;
    }

}
#endif

static struct platform_device v4l2_spi_pdev = {
	.name = "v4l2_spi",
	.id = -1,
};

static struct dev_pm_ops const spi_pm_ops = {
        .resume = v4l2_spi_resume,
        .suspend = v4l2_spi_suspend,
};

static struct platform_driver v4l2_spi_driver = {
	.probe      = v4l2_spi_probe,
	.driver     = {
		.name   = "v4l2_spi",
		.owner  = THIS_MODULE,
		.pm     = &spi_pm_ops,
	},
	.remove		= v4l2_spi_remove,
};



int v4l2_spi_device_init(void)
{
	int drvret = 0,devret =0;

	drvret = platform_driver_register(&v4l2_spi_driver);
	devret = platform_device_register(&v4l2_spi_pdev);
	SPI_NOTI("check drv %d dev %d register\n",drvret,devret);

	//mutex_init(&v4l2_spi_video_device_lock);
	//video_set_drvdata(&v4l2_spi_video_dev, &spi_pdev);
	v4l2_spi_register(NULL);

	return 0;
}
#if 0
static void  __exit v4l2_spi_device_exit(void)
{
	SPI_NOTI("spi  %s\n", __func__);

	platform_device_unregister(&v4l2_spi_pdev);
	platform_driver_unregister(&v4l2_spi_driver);
}
#endif

static int v4l2_spi_probe(struct platform_device *pdev)
{
	SPI_NOTI("spi  %s\n", __func__);
	return 0;
}

static int v4l2_spi_remove(struct platform_device *pdev)
{
	//SPI_NOTI("spi  %s\n", __func__);
	return 0;
}

static int v4l2_spi_resume(struct device *dev)
{
	SPI_NOTI("%s\n", __func__);
	return 0;
}

static int v4l2_spi_suspend(struct device *dev)
{
	SPI_NOTI("%s\n", __func__);
	return 0;
}


static int v4l2_spi_fh_open(struct file *flie)
{
	int ret = 0;
	return ret;

}

static int v4l2_spi_fh_release(struct file *flie)
{
	int ret = 0;
	return ret;
}

#if 0
static int v4l2_spi_vidioc_s_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{
	return 0;
}

static int v4l2_spi_vidioc_g_ctrl(struct file *file, void *__fh,
				struct v4l2_control *ctrl)
{

	return 0;
}
#endif
static int v4l2_spi_vidioc_s_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{

	int ret = 0;
	UINT8 sbuf[32];
	UINT8* mbuf = NULL;
	UINT8* ubuf;
	UINT8* kbuf;
	struct spi_fh *fh = __fh;
	struct V4L2_SPI_CFG cfg;
	struct V4L2_SPI_PARAM param;
	int i;
	struct device * dev ;

	for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;


		switch (ctrl->id)
		{
			case V4L2_CID_SPI_INIT:
				SPI_NOTI("spi init\n");

				if(spi_ctop_base == NULL)
				{
					if(0){}
					#ifdef INCLUDE_M19_CHIP_KDRV
					else if(lx_chip() == LX_CHIP_M19)
					{
						spi_ctop_base = ioremap( 0xc930e400, 0x30);
					}
					#endif
					#ifdef INCLUDE_M17_CHIP_KDRV
					else if(lx_chip() == LX_CHIP_M17)
					{
						spi_ctop_base = ioremap( 0xc9305400, 0x30);
					}
					#endif
				}

				for( i= 0 ; i < SPI_KDRV_HW_NUM ; i++)
				{
					if(pv4l2_spi_device[i] == NULL)
					{
						snprintf(devicename,40,"spi%d.0",i);

						dev = bus_find_device_by_name(&spi_bus_type, NULL, devicename);
						if (!dev){
								printk("no spi device[%d]\n",i);
								return -ENODEV;
						}
						pv4l2_spi_device[i]= to_spi_device(dev);
					}
					v4l2_spi_init[i] = 1;
				}
				break;
			case V4L2_CID_SPI_CONF:
				SPI_NOTI("spi config\n");

				memset(&cfg,0x0,sizeof(struct V4L2_SPI_CFG));
				if(copy_from_user(&cfg,\
					(void __user *)ctrl->string,\
					sizeof(struct V4L2_SPI_CFG)))
				{
						SPI_ERROR("copy from user error\n");
						return -1;
				}

				v4l2_spi_config(cfg.u8channel,0,cfg.u32speed);
				SPI_NOTI("vsc:id 0x%x(%s) spi cfg ch(%d) speed(%d)\n",
				ctrl->id,ctrl_id_to_str(ctrl->id),cfg.u8channel, cfg.u32speed );
				fh->clock[cfg.u8channel]=cfg.u32speed;
				break;
			case V4L2_CID_SPI_WRITE:

				memset(&param,0x0,sizeof(struct V4L2_SPI_PARAM));
				if(copy_from_user(&param,\
					(void __user *)ctrl->string,\
					sizeof(struct V4L2_SPI_PARAM)))
				{
						SPI_ERROR("copy from user pararm error\n");
						return -1;

				}

				ubuf = param.u8dataToWrite;

				if(param.u32size > 32  && param.u32size <= SPI_MSG_MAX + 4)
				{
					mbuf = (UINT8*) kmalloc(sizeof(UINT8)*(param.u32size + ADDR_SIZE_IN_BYTE),GFP_KERNEL);
					if(mbuf == NULL) return -1;
					kbuf = mbuf;
				}
				else
				{
					kbuf = sbuf;
				}

				if(copy_from_user(kbuf,\
					(void __user *)ubuf,\
					sizeof(param.u32size)))
				{
						SPI_ERROR("copy from user buf error\n");
						if(mbuf != NULL)
							kfree(mbuf);
						return -1;
				}

				param.u8dataToWrite = kbuf;
				ret = v4l2_spi_write(param.u8channel,param.u32addr,param.u8dataToWrite,param.u32size);
				SPI_DEBUG("spi write[%d]\n",ret);
				return ret;
			case V4L2_CID_SPI_READ:
				memset(&param,0x0,sizeof(struct V4L2_SPI_PARAM));
				if(copy_from_user(&param,\
					(void __user *)ctrl->string,\
					sizeof(struct V4L2_SPI_PARAM)))
				{
						SPI_ERROR("copy from user pararm error\n");
						return -1;
				}

				ubuf = param.u8dataToRead;

				if(param.u32size > 32  && param.u32size <= SPI_MSG_MAX + 4 )
				{
					mbuf = (UINT8*) kmalloc(sizeof(UINT8)*(param.u32size + ADDR_SIZE_IN_BYTE),GFP_KERNEL);
					if(mbuf == NULL) return -1;
					kbuf = mbuf;
				}
				else
				{
					kbuf = sbuf;
				}

				if(copy_from_user(kbuf,\
					(void __user *)ubuf,\
					sizeof(param.u32size)))
				{
						SPI_ERROR("copy from user buf error\n");
						if(mbuf != NULL)
							kfree(mbuf);
						return -1;
				}

				param.u8dataToRead = kbuf;
				ret = v4l2_spi_read(param.u8channel,param.u32addr,param.u8dataToRead,param.u32size);
				if( ret >= 0)
				{
						if(copy_to_user((void __user *)ubuf, (void *)kbuf, param.u32size))
						{
							SPI_ERROR("copy_to_user  buferror ret[%d] size[%d]\n",ret,param.u32size);
							if(mbuf != NULL)
								kfree(mbuf);
						return -1;
						}
				}

				SPI_DEBUG("spi read[%d]\n",ret);
				return ret;
			default:
				SPI_NOTI("spi default\n");
				break;

				SPI_NOTI("vsc:id 0x%x \n",ctrl->id );
		}


	}
	return 0;

}

static int v4l2_spi_vidioc_g_ext_ctrls(struct file *file, void *__fh,
				struct v4l2_ext_controls *ctrls)
{
	return 0;
}

static int v4l2_spi_vidioc_subscribe_event(struct v4l2_fh *__fh,
				const struct v4l2_event_subscription *sub)
{
	SPI_NOTI("spi type 0x%x, id 0x%x\n", sub->type, sub->id);
	switch (sub->type)
	{
		/*
		case V4L_VSC_1_EVENT:  // internal mute off
		case V4L_VSC_2_EVENT:  // active window
			return v4l2_event_subscribe(__fh, sub, 32, NULL);
			*/
		default:
			return -EINVAL;
	}
}

static unsigned int v4l2_spi_poll(struct file *file, poll_table *wait)
{
	return 0;
}

static char *ctrl_id_to_str(int id)
{
    switch (id)
	{
		default:
			return "Unkown";
	}
}

struct v4l2_file_operations v4l2_spi_fops = {
	.owner		= THIS_MODULE,
	.open		= v4l2_spi_fh_open,
	.release	= v4l2_spi_fh_release,
	.unlocked_ioctl = video_ioctl2,
	.poll = v4l2_spi_poll,
};

struct v4l2_ioctl_ops v4l2_spi_ioctl_ops = {
//	.vidioc_s_ctrl			= v4l2_spi_vidioc_s_ctrl,
//	.vidioc_g_ctrl			= v4l2_spi_vidioc_g_ctrl,
	.vidioc_s_ext_ctrls		= v4l2_spi_vidioc_s_ext_ctrls,
	.vidioc_g_ext_ctrls		= v4l2_spi_vidioc_g_ext_ctrls,
	.vidioc_log_status = v4l2_ctrl_log_status,
	.vidioc_subscribe_event = v4l2_spi_vidioc_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
};

static struct video_device v4l2_spi_video_dev = {

	.v4l2_dev  = &v4l2_spi_dev,
	.fops      = &v4l2_spi_fops,
	.ioctl_ops = &v4l2_spi_ioctl_ops,
	.release   = video_device_release_empty,
	//.lock      = &v4l2_spi_video_device_lock,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	.device_caps = V4L2_CAP_VIDEO_CAPTURE,
#endif
};

static int v4l2_spi_register(void *arg)
{
	int ret;

	SPI_NOTI("spi  %s\n", __func__);


	do{
		/* Won Hur Note : I followed the steps mention at https://lwn.net/Articles/313784/ */
		ret = v4l2_device_register(&v4l2_spi_pdev.dev, &v4l2_spi_dev);
		if(ret < 0){
			SPI_NOTI(" spi : v4l2_device_register error[%d]\n", ret);
			break;
		}

		ret = video_register_device(&v4l2_spi_video_dev, VFL_TYPE_GRABBER, V4L2_SPI_DEV_NUMBER);
		if (ret < 0) {
			SPI_NOTI("video device register error: %d\n", ret);
			return -1;
		}

	} while(0);

	return ret;
}

