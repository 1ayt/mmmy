/*
 * Balance.h
 *
 *  Created on: 2022Äê2ÔÂ4ÈÕ
 *      Author: xqx
 */

#ifndef CODE_BALANCE_H_
#define CODE_BALANCE_H_

#include "Angle_Calculate.h"
#include "SEEKFREE_MPU6050.h"
#include "zf_gtm_pwm.h"
#include "zf_gpio.h"
#include "zf_uart.h"
#include "encoder.h"

void Balance(void);
float X_Balance_Control(float Angle,float Angle_Zero,float Gyro);
float X_Balance_Control_P(float Angle,float Angle_Zero,float Gyro,float Accel);
float Speed_Control(int encoder);
int SBB_Get_BalancePID(float Angle,float Gyro);

#endif /* CODE_BALANCE_H_ */
