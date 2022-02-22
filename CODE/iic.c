/*
 * iic.c
 *
 *  Created on: 2022年2月6日
 *      Author: xqx
 */
#include "iic.h"
#include "zf_gpio.h"
#include "zf_stm_systick.h"

#define SDA_vice             gpio_get (AYT_SDA)
#define SDA0_vice()          gpio_set (AYT_SDA, 0)      //IO口输出低电平
#define SDA1_vice()          gpio_set (AYT_SDA, 1)      //IO口输出高电平
#define SCL0_vice()          gpio_set (AYT_SCL, 0)      //IO口输出低电平
#define SCL1_vice()          gpio_set (AYT_SCL, 1)      //IO口输出高电平
#define DIR_OUT_vice()       gpio_dir (AYT_SDA, GPO, PUSHPULL)   //输出方向
#define DIR_IN_vice()        gpio_dir (AYT_SDA, GPI, NO_PULL)    //输入方向

uint16 iic_delay_time = AYT_DELAY_TIME;   //ICM等传感器应设置为20


//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC延时 时间设置
//  @return     void
//  @since      v1.0
//  Sample usage:               如果IIC通讯失败可以尝试增加simiic_delay_time的值
//-------------------------------------------------------------------------------------------------------------------
void iic_delay_set(uint16 time)
{
    iic_delay_time = time;           //ICM等传感器应设置为100
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC延时
//  @return     void
//  @since      v1.0
//  Sample usage:               如果IIC通讯失败可以尝试增加simiic_delay_time的值
//-------------------------------------------------------------------------------------------------------------------
void iic_delay(void)
{
    uint16 delay_time;
    delay_time = iic_delay_time;
    while(delay_time--);
}

//内部使用，用户无需调用
void iic_start(void)
{
    SDA1_vice();
    SCL1_vice();
    iic_delay();
    SDA0_vice();
    iic_delay();
    SCL0_vice();
}

//内部使用，用户无需调用
void iic_stop(void)
{
    SDA0_vice();
    SCL0_vice();
    iic_delay();
    SCL1_vice();
    iic_delay();
    SDA1_vice();
    iic_delay();
}

int iic_waitack(void)
{
    SCL0_vice();
    DIR_IN_vice();
    iic_delay();

    SCL1_vice();
    iic_delay();

    if(SDA_vice)           //应答为高电平，异常，通信失败
    {
        DIR_OUT_vice();
        SCL0_vice();
        return 0;
    }
    DIR_OUT_vice();
    SCL0_vice();
    iic_delay();
    return 1;
}

//字节发送程序
//发送c(可以是数据也可是地址)，送完后接收从应答
//不考虑从应答位
//内部使用，用户无需调用
void iic_send_ch(uint8 c)
{
    uint8 i = 8;
    while(i--)
    {
        if(c & 0x80)    SDA1_vice();//SDA 输出数据
        else            SDA0_vice();
        c <<= 1;
        iic_delay();
        SCL1_vice();                //SCL 拉高，采集信号
        iic_delay();
        SCL0_vice();                //SCL 时钟线拉低
    }

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      模拟IIC端口初始化
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void iic_init(void)
{
    gpio_init (AYT_SCL, GPO, 1, PUSHPULL);
    gpio_init (AYT_SDA, GPO, 1, PUSHPULL);
}
