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
 * �����嵥������һ�� PWM �豸ʹ������
 * ���̵����� pwm_sample ��������ն�
 * ������ø�ʽ��pwm_sample
 * �����ܣ�ͨ���߼��������ܿ��� PH.10 ���ŵĵ�ƽ�仯��
*/

#include <rtthread.h>
#include <rtdevice.h>

#define PWM_DEV_NAME        "pwm3"  /* PWM�豸���� */
#define PWM_DEV_CHANNEL     3       /* PWMͨ�� */

struct rt_device_pwm *pwm_dev;      /* PWM�豸��� */

static int pwm_sample(int argc, char *argv[])
{
    rt_uint32_t period, pulse, dir,pulse1,pulse2,pulse3;

    period = 20000000;    /* ����Ϊ0.5ms����λΪ����ns */
    dir = 1;            /* PWM������ֵ���������� */
    pulse = 0;          /* PWM������ֵ����λΪ����ns */
    pulse1=1700000;
           pulse2=2100000;
           pulse3=1200000;
           /* �����豸 */
    pwm_dev = (struct rt_device_pwm *)rt_device_find(PWM_DEV_NAME);
    if (pwm_dev == RT_NULL)
    {
        rt_kprintf("pwm sample run failed! can't find %s device!\n", PWM_DEV_NAME);
        return RT_ERROR;
    }

    /* ����PWM���ں�������Ĭ��ֵ */
    rt_pwm_set(pwm_dev, PWM_DEV_CHANNEL, period, pulse);
    /* ����PWM���ں�������Ĭ��ֵ */
    rt_pwm_enable(pwm_dev, PWM_DEV_CHANNEL);
    
    while (1)
    {
        rt_thread_mdelay(50);

        /* ����PWM���ں������� */
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
/* ������ msh �����б��� */
MSH_CMD_EXPORT(pwm_sample, pwm sample);
