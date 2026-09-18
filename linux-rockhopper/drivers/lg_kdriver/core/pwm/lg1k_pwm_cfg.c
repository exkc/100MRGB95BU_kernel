/*****************************************************************************************
 * SIC R&D LAB, LG ELECTRONICS INC., SEOUL, KOREA
 * COPYRIGHT(c) 2011,2012 by LG Electronics Inc.
 *
 * All rights reserved. No part of this work covered by this copyright hereon
 * may be reproduced, stored in a retrieval system, in any form
 * or by any means, electronic, mechanical, photocopying, recording
 * or otherwise, without the prior written  permission of LG Electronics.
 ****************************************************************************************/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author     raxis.lim
 *  @version    1.0
 *  @date       2021-08-26
 *  @note       Additional information.
 */

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "lg1k_pwm_impl.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/
#define DEFINE_PWM_DEVICE(idx, pid, str, clk, val, handler) \
    [idx] = {   \
        .hwpwm = idx,   \
        .name = str,    \
        .pwm_id = pid,  \
        .base_clk = clk,    \
        .max_hw_period = val,    \
        .status = { .enabled = false, .duty = 0, .period = 0 }, \
        .cb = &handler, \
    }

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void lg1k_pwm_fan_config(struct lg1k_pwm_dev* my_dev, int duty_val, int period_val);
extern void lg1k_pwm_fan_enable(struct lg1k_pwm_dev* my_dev, bool en);
extern int lg1k_pwm_fan_pm(struct lg1k_pwm_dev* my_dev, char* command);
extern void lg1k_pwm_fan_proc(struct lg1k_pwm_dev* my_dev, struct seq_file* m, char* command);

/*----------------------------------------------------------------------------------------
    External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Static Variables
----------------------------------------------------------------------------------------*/
static struct lg1k_pwm_callback lg1k_pwm_fan_handler =
{
    .do_pm = lg1k_pwm_fan_pm,
    .do_config = lg1k_pwm_fan_config,
    .do_enable = lg1k_pwm_fan_enable,
    .do_proc = lg1k_pwm_fan_proc,
};

#ifdef INCLUDE_O26_CHIP_KDRV

static struct lg1k_pwm_dev lg1k_o26_pwm_dev_list[] =
{
    DEFINE_PWM_DEVICE(0, PWM_ID_FAN(0), "pwm0", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(1, PWM_ID_FAN(1), "pwm1", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(2, PWM_ID_FAN(2), "pwm2", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz

    DEFINE_PWM_DEVICE(3 + 0, PWM_ID_RPM(0), "rpm0", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 1, PWM_ID_RPM(1), "rpm1", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 2, PWM_ID_RPM(2), "rpm2", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 3, PWM_ID_RPM(3), "rpm3", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 4, PWM_ID_RPM(4), "rpm4", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 5, PWM_ID_RPM(5), "rpm5", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 6, PWM_ID_RPM(6), "rpm6", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 7, PWM_ID_RPM(7), "rpm7", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 8, PWM_ID_RPM(8), "rpm8", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 9, PWM_ID_RPM(9), "rpm9", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
};

#endif

#ifdef INCLUDE_O24_CHIP_KDRV

static struct lg1k_pwm_dev lg1k_o24_pwm_dev_list[] =
{
    DEFINE_PWM_DEVICE(0, PWM_ID_FAN(0), "pwm0", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(1, PWM_ID_FAN(1), "pwm1", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(2, PWM_ID_FAN(2), "pwm2", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz

    DEFINE_PWM_DEVICE(3 + 0, PWM_ID_RPM(0), "rpm0", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 1, PWM_ID_RPM(1), "rpm1", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 2, PWM_ID_RPM(2), "rpm2", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 3, PWM_ID_RPM(3), "rpm3", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 4, PWM_ID_RPM(4), "rpm4", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 5, PWM_ID_RPM(5), "rpm5", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 6, PWM_ID_RPM(6), "rpm6", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 7, PWM_ID_RPM(7), "rpm7", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 8, PWM_ID_RPM(8), "rpm8", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(3 + 9, PWM_ID_RPM(9), "rpm9", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
};
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
// see http://clm.lge.com/issue/browse/SCDCR-4364
// see http://clm.lge.com/issue/browse/SCDCRID-3357

static struct lg1k_pwm_dev lg1k_o22_pwm_dev_list[] =
{
    DEFINE_PWM_DEVICE(0, PWM_ID_FAN(0), "pwm0", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(1, PWM_ID_FAN(1), "pwm1", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(2, PWM_ID_FAN(2), "pwm2", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz

    DEFINE_PWM_DEVICE(3, PWM_ID_FAN(3), "pwm3", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(4, PWM_ID_FAN(4), "pwm4", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz
    DEFINE_PWM_DEVICE(5, PWM_ID_FAN(5), "pwm5", 50000000, 0xfff, lg1k_pwm_fan_handler),   // 50Mhz

    DEFINE_PWM_DEVICE(6 + 0, PWM_ID_RPM(0), "rpm0", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 1, PWM_ID_RPM(1), "rpm1", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 2, PWM_ID_RPM(2), "rpm2", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 3, PWM_ID_RPM(3), "rpm3", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 4, PWM_ID_RPM(4), "rpm4", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 5, PWM_ID_RPM(5), "rpm5", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 6, PWM_ID_RPM(6), "rpm6", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 7, PWM_ID_RPM(7), "rpm7", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 8, PWM_ID_RPM(8), "rpm8", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 9, PWM_ID_RPM(9), "rpm9", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk

    DEFINE_PWM_DEVICE(6 + 10, PWM_ID_RPM(10), "rpm10", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 11, PWM_ID_RPM(11), "rpm11", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 12, PWM_ID_RPM(12), "rpm12", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 13, PWM_ID_RPM(13), "rpm13", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 14, PWM_ID_RPM(14), "rpm14", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 15, PWM_ID_RPM(15), "rpm15", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 16, PWM_ID_RPM(16), "rpm16", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 17, PWM_ID_RPM(17), "rpm17", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 18, PWM_ID_RPM(18), "rpm18", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
    DEFINE_PWM_DEVICE(6 + 19, PWM_ID_RPM(19), "rpm19", 50000000, 0xfff, lg1k_pwm_fan_handler), // dummy clk
};
#endif

#ifdef INCLUDE_M19_CHIP_KDRV

// see http://clm.lge.com/issue/browse/SCDCRID-2943
static struct lg1k_pwm_dev lg1k_m19_pwm_dev_list[] =
{
    DEFINE_PWM_DEVICE(0, PWM_ID_FAN(0), "pwm0", 24000000, 0xfff, lg1k_pwm_fan_handler),   // 24Mhz
    DEFINE_PWM_DEVICE(1, PWM_ID_FAN(1), "pwm1", 24000000, 0xfff, lg1k_pwm_fan_handler),   // 24Mhz
    DEFINE_PWM_DEVICE(2, PWM_ID_FAN(2), "pwm2", 24000000, 0xfff, lg1k_pwm_fan_handler),   // 24Mhz

    DEFINE_PWM_DEVICE(3 + 0, PWM_ID_RPM(0), "rpm0", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 1, PWM_ID_RPM(1), "rpm1", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 2, PWM_ID_RPM(2), "rpm2", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 3, PWM_ID_RPM(3), "rpm3", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 4, PWM_ID_RPM(4), "rpm4", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 5, PWM_ID_RPM(5), "rpm5", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 6, PWM_ID_RPM(6), "rpm6", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 7, PWM_ID_RPM(7), "rpm7", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 8, PWM_ID_RPM(8), "rpm8", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
    DEFINE_PWM_DEVICE(3 + 9, PWM_ID_RPM(9), "rpm9", 24000000, 0xfff, lg1k_pwm_fan_handler), // 24Mhz
};
#endif

static struct lg1k_pwm_chip_desc g_lg1k_pwm_chip_desc;

/*========================================================================================
    Implementation Group
========================================================================================*/

struct lg1k_pwm_chip_desc lg1k_pwm_chip_config(void)
{
    memset(&g_lg1k_pwm_chip_desc, 0x0, sizeof(struct lg1k_pwm_chip_desc));

    if (0)
    {

    }

#ifdef INCLUDE_O26_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O26)
    {
        g_lg1k_pwm_chip_desc.npwm = NELEMENTS(lg1k_o26_pwm_dev_list);
        g_lg1k_pwm_chip_desc.dev_list = lg1k_o26_pwm_dev_list;
        g_lg1k_pwm_chip_desc.do_proc = lg1k_pwm_fan_proc;
        //g_lg1k_pwm_chip_desc.cb = &lg1k_o26_pwm_callback;
    }

#endif
#ifdef INCLUDE_O24_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O24)
    {
        g_lg1k_pwm_chip_desc.npwm = NELEMENTS(lg1k_o24_pwm_dev_list);
        g_lg1k_pwm_chip_desc.dev_list = lg1k_o24_pwm_dev_list;
        g_lg1k_pwm_chip_desc.do_proc = lg1k_pwm_fan_proc;
        //g_lg1k_pwm_chip_desc.cb = &lg1k_o24_pwm_callback;
    }

#endif
#ifdef INCLUDE_O22_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O22)
    {
        g_lg1k_pwm_chip_desc.npwm = NELEMENTS(lg1k_o22_pwm_dev_list);
        g_lg1k_pwm_chip_desc.dev_list = lg1k_o22_pwm_dev_list;
        g_lg1k_pwm_chip_desc.do_proc = lg1k_pwm_fan_proc;
        //g_lg1k_pwm_chip_desc.cb = &lg1k_o22_pwm_callback;
    }

#endif
#ifdef INCLUDE_O20_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_O20)
    {
        g_lg1k_pwm_chip_desc.npwm = NELEMENTS(lg1k_o20_pwm_dev_list);
        g_lg1k_pwm_chip_desc.dev_list = lg1k_o20_pwm_dev_list;
        g_lg1k_pwm_chip_desc.do_proc = lg1k_pwm_fan_proc;
        //g_lg1k_pwm_chip_desc.cb = &lg1k_o20_pwm_callback;
    }

#endif
#ifdef INCLUDE_M19_CHIP_KDRV
    else if (lx_chip() == LX_CHIP_M19)
    {
        g_lg1k_pwm_chip_desc.npwm = NELEMENTS(lg1k_m19_pwm_dev_list);
        g_lg1k_pwm_chip_desc.dev_list = lg1k_m19_pwm_dev_list;
        g_lg1k_pwm_chip_desc.do_proc = lg1k_pwm_fan_proc;
        //g_lg1k_pwm_chip_desc.cb = &lg1k_m19_pwm_callback;
    }

#endif
    else
    {
        pr_err("unknown chip: 0x%x\n", lx_chip());
    }

    return g_lg1k_pwm_chip_desc;
}

