/*
 * encoder.c
 *
 *  Created on: 2022��1��15��
 *      Author: xqx
 */

#include "encoder.h"

int count;
int count_speed;

void encoder_init(void)
{
    eru_init(ERU_CH5_REQ1_P15_8,RISING);            //��ʼ��eru�ж����ڶ�ȡ������������
    gpio_init(P15_6, GPI, 0, NO_PULL);             //��ʼ��P00_12�������ڶ�ȡ��������ת����
    eru_enable_interrupt(ERU_CH5_REQ1_P15_8);       //ʹ��eru�ж�

    pit_init(CCU6_0,PIT_CH0,100000);                //��ʼ��pit�ж����ڴ����������ֵ
    pit_enable_interrupt(CCU6_0,PIT_CH0);           //ʹ��pit�ж�
    pit_start(CCU6_0,PIT_CH0);                      //pit�жϿ�ʼ
}

void encoder_read(void)
{
    count_speed = count;
    count = 0;
}




