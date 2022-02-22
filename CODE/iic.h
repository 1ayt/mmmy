/*
 * iic.h
 *
 *  Created on: 2022年2月6日
 *      Author: xqx
 */

#ifndef CODE_IIC_H_
#define CODE_IIC_H_

#include "common.h"

#define AYT_SCL    P14_3                           //定义SCL引脚  可任意更改为其他IO
#define AYT_SDA    P14_5                           //定义SDA引脚  可任意更改为其他IO

#define AYT_DELAY_TIME   20
extern uint16 iic_delay_time;   //ICM等传感器应设置为20


void  iic_delay_set(uint16 time);
void  iic_delay(void);
void  iic_start(void);
void  iic_stop(void);
int   iic_waitack(void);
void  iic_send_ch(uint8 c);
void  iic_init(void);

#endif /* CODE_IIC_H_ */
