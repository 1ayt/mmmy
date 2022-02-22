/*
 * encoder.c
 *
 *  Created on: 2022年1月15日
 *      Author: xqx
 */

#include "encoder.h"

int count;
int count_speed;

void encoder_init(void)
{
    eru_init(ERU_CH5_REQ1_P15_8,RISING);            //初始化eru中断用于读取编码器脉冲数
    gpio_init(P15_6, GPI, 0, NO_PULL);             //初始化P00_12引脚用于读取编码器旋转方向
    eru_enable_interrupt(ERU_CH5_REQ1_P15_8);       //使能eru中断

    pit_init(CCU6_0,PIT_CH0,100000);                //初始化pit中断用于处理编码器数值
    pit_enable_interrupt(CCU6_0,PIT_CH0);           //使能pit中断
    pit_start(CCU6_0,PIT_CH0);                      //pit中断开始
}

void encoder_read(void)
{
    count_speed = count;
    count = 0;
}




