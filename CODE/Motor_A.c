/*
 * Motor_A.c
 *
 *  Created on: 2022年2月4日
 *      Author: xx
 */

#include "Motor_A.h"

void Motor_A_Init(void)
{
    //动量轮ATOM3_CH7_P13_2
    gtm_pwm_init(ATOM3_CH5_P11_10,125,0);         //初始化pwm用于控制电机转速
    gpio_init(P11_6,GPO,0,PUSHPULL);

    //电机PWM
    gtm_pwm_init(ATOM3_CH7_P13_2,125,0);
    gpio_init(P13_0,GPO,0,PUSHPULL);

    //舵机PWM
    gtm_pwm_init(ATOM3_CH4_P14_1,125,1600);
}

