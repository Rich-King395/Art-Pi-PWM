/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-12-08     wanghaijing  first version.
 */
/*
 * 程序清单：这是一个 PWM 设备使用例程
 * 例程导出了 pwm_sample 命令到控制终端
 * 命令调用格式：pwm_sample
 * 程序功能：通过逻辑分析仪能看到 PH.10 引脚的电平变化。
*/

#include <rtthread.h>
#include <rtdevice.h>

#define PWM_DEV_NAME        "pwm3"  /* PWM设备名称 */
#define PWM_DEV_CHANNEL     3       /* PWM通道 */

struct rt_device_pwm *pwm_dev;      /* PWM设备句柄 */

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir,pulse1,pulse2,pulse3;

    period = 20000000;    /* 周期为0.5ms，单位为纳秒ns */
    dir = 1;            /* PWM脉冲宽度值的增减方向 */
    pulse = 0;          /* PWM脉冲宽度值，单位为纳秒ns */
    pulse1=1700000;
           pulse2=2100000;
           pulse3=1200000;
           /* 查找设备 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* 设置PWM周期和脉冲宽度默认值 */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    
    while (1)
    {
        rt_thread_mdelay(50);

        /* 设置PWM周期和脉冲宽度 */
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse1);
        rt_thread_mdelay(2000);
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse2);
        rt_thread_mdelay(2000);
        rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse3);
        rt_thread_mdelay(2000);
    }

}
//void openfirst(pwm_dev,PWN_DEV_C,){
//    pulse=1700000;
//    rt_pwm_set(pwm_dev,PWM_DEV_CHANNEL,period,pulse);
//}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(pwm_sample, pwm sample);
