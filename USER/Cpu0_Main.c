/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

#include "headfile.h"
#include "Angle_Calculate.h"
#include "oled_iic.h"
#include "Motor_A.h"
#include "Balance.h"
#include "encoder.h"
#include "image.h"
#include "PIT_Init.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_MPU6050.h"
#pragma section all "cpu0_dsram"

//姿态角参数
extern float Roll;
extern float Roll_Zero;

//动量轮编码器参数
extern int count_speed;

//电机控制参数
extern int MotorDutyA;
extern int MotorDutyB;
int time;

//图像数组(测试)
uint8 data[120][188];
uint8 img[120*188];
int i,j,k=0,m=0;

int core0_main(void)
{
	disableInterrupts();
    get_clk();//获取时钟频率  务必保留

    //用户在此处调用各种初始化函数
    PIT_Init();
    mpu6050_init();
    encoder_init();
    Motor_A_Init();
    OLED_Init();
    //mt9v03x_init();

	enableInterrupts();                             //使能全局中断

	//OLED显示部分数据
	OLED_ShowStr(0,0,(unsigned char*)"Roll :",2);
	OLED_ShowStr(0,2,(unsigned char*)"PWM1 :",2);
	OLED_ShowStr(0,4,(unsigned char*)"PWM2 :",2);
	//OLED_ShowStr(0,6,(unsigned char*)"Speed :",2);

    while (TRUE)
    {

        OLED_ShowNum(56,0,Roll);
        OLED_ShowNum(56,2,MotorDutyA);
        OLED_ShowNum(56,4,MotorDutyB);
        systick_delay_ms(STM0,50);
        printf("%d,%f\n",MotorDutyA,Roll);
        //Send_Gray_image(mt9v03x_image,188,120);

    }
}

#pragma section all restore
