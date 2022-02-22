/*
 * PIT_Init.c
 *
 *  Created on: 2022年2月16日
 *      Author: xqx
 */
#include "PIT_Init.h"

void PIT_Init(void)
{
    //用于处理Balance函数
    pit_init(CCU6_1,PIT_CH0,9000);                  //每隔9ms读取一次数据
    pit_enable_interrupt(CCU6_1,PIT_CH0);           //使能pit中断
    pit_start(CCU6_1,PIT_CH0);                      //pit中断开始

    //用于处理mpu6050函数
    pit_init(CCU6_0,PIT_CH1,9000);                  //每隔9ms读取一次数据
    pit_enable_interrupt(CCU6_0,PIT_CH1);           //使能pit中断
    pit_start(CCU6_0,PIT_CH1);                      //pit中断开始

    gpio_init(P11_6,GPO,0,PUSHPULL);
}

