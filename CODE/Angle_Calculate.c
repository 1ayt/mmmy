/*
 * Angle_Calculate.c
 *
 *  Created on: 2022年1月14日
 *      Author: xqx
 */

#include "Angle_Calculate.h"
#include "SEEKFREE_MPU6050.h"

//Yaw,Pitch,Roll 角度值
float Yaw,Pitch,Roll;

//声明mpu6050.h文件中的变量
extern int16 mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
extern int16 mpu_acc_x,mpu_acc_y,mpu_acc_z;

/* brief  : 返回x轴角加速度
 * Param1 : mpu_acc_x : mpu6050返回的x轴角加速度值
 */
float Accel_x(float mpu_acc_x)
{
    float Accel_x;

    Accel_x = 8*9.8*(mpu_acc_x)/32768;

    return Accel_x;
}

/* brief  : 返回y轴角加速度
 * Param1 : mpu_acc_y : mpu6050返回的y轴角加速度值
 */
float Accel_y(float mpu_acc_y)
{
    float Accel_y;

    Accel_y = 8*9.8*(mpu_acc_y)/32768;

    return Accel_y;
}

/* brief  : 返回z轴角加速度
 * Param1 : mpu_acc_z : mpu6050返回的z轴角加速度值
 */
float Accel_z(float mpu_acc_z)
{
    float Accel_z;

    Accel_z = 8*9.8*(mpu_acc_z)/32768;

    return Accel_z;
}

/* brief  : 返回x轴角速度
 * Param1 : mpu_gyro_x : mpu6050返回的x轴角速度值
 */
float Gyro_x(float mpu_gyro_x)
{
    float Gyro_x;

    Gyro_x = 2000*mpu_gyro_x/32768;

    return Gyro_x;
}

/* brief  : 返回y轴角速度
 * Param1 : mpu_gyro_y : mpu6050返回的y轴角速度值
 */
float Gyro_y(float mpu_gyro_y)
{
    float Gyro_y;

    Gyro_y = 2000*mpu_gyro_y/32768;

    return Gyro_y;
}

/* brief  : 返回z轴角速度
 * Param1 : mpu_gyro_z : mpu6050返回的z轴角速度值
 */
float Gyro_z(float mpu_gyro_z)
{
    float Gyro_z;

    Gyro_z = 2000*mpu_gyro_z/32768;

    return Gyro_z;
}
/* brief  : 返回Yaw角度
 * Param1 : mpu_gyro_z : mpu6050返回的z轴角速度值
 */



/*--------------------------------------------------------
 * float Kalman_filter_Pitch(float Gyro ,float Angle_See)
 * brief:卡尔曼滤波
 * param:
 *-------------------------------------------------------*/


float dt = 0.008;     //采样时间

float Angle;              //角度的先验估计值
float Gyro_bias = 0.1;          //角速度偏移值

float Cov_angle = 0.01;      //陀螺仪测量的角速度的协方差
float Cov_bias = 0.01;       //陀螺仪漂移值的协方差
float Cov_accel = 0.01;       //加速度计测量的加速度协方差

//P矩阵
float P00 = 1.0;
float P01 = 0.0;
float P10 = 0.0;
float P11 = 1.0;

//卡尔曼增益矩阵
float K0;
float K1;

float Angle_err;


//输入陀螺仪角速度和计算角度
float Kalman_filter_Pitch(float Gyro ,float Angle_See)
{
    /*状态方程
     * | Angle     |   | 1   -dt| | Angle     |   | dt|
     * |           | = |        | |           | + |   | Gyro;
     * | Gyro_bias |   | 0     1| | Gyro_bias |   | 0 |
     */
    Angle = Angle - Gyro_bias * dt + Gyro * dt;
    Gyro_bias = Gyro_bias;

    //P矩阵求解
    P00 = P00 - P10 * dt + (P11 * dt - P01) * dt + Cov_angle;
    P01 = P01 - P11 * dt;
    P10 = P10 - P11 * dt;
    P11 = P11 + Cov_bias;

    //求解卡尔曼增益矩阵
    K0 = P00 / (P00 + Cov_accel);
    K1 = P10 / (P00 + Cov_accel);

    Angle_err = Angle_See - Angle;

    //更新数据
    Angle = Angle + K0 * Angle_err;
    Gyro_bias = Gyro_bias + K1 * Angle_err;

    //更新P矩阵
    P00 = P00 - K0 * P00;
    P01 = P01 - K0 * P01;
    P10 = P10 - K1 * P00;
    P11 = P11 - K1 * P01;

    return Angle;
}

/*Roll滤波函数
 *
 *
 */
float dt_1 = 0.009;     //采样时间

float Angle_1;              //角度的先验估计值
float Gyro_bias_1 = 0.1;          //角速度偏移值

float Cov_angle_1 = 0.001;      //陀螺仪测量的角速度的协方差
float Cov_bias_1 = 0.001;       //陀螺仪漂移值的协方差
float Cov_accel_1 = 1500;       //加速度计测量的加速度协方差

//P矩阵
static float P001 = 1.0;
static float P011 = 0.0;
static float P101 = 0.0;
static float P111 = 1.0;

//卡尔曼增益矩阵
float K0_1;
float K1_1;

float Angle_err_1;

float Kalman_filter_Roll(float Gyro_1 ,float Angle_See_1)
{
    Angle_1 = Angle_1 - Gyro_bias_1 * dt_1 + Gyro_1 * dt;
    Gyro_bias_1 = Gyro_bias_1;

    //P矩阵求解
    P001 = P001 - P101 * dt_1 + (P111 * dt_1 - P011) * dt_1 + Cov_angle_1;
    P011 = P011 - P111 * dt_1;
    P101 = P101 - P111 * dt_1;
    P111 = P111 + Cov_bias_1;

    //求解卡尔曼增益矩阵
    K0_1 = P001 / (P001 + Cov_accel_1);
    K1_1 = P101 / (P001 + Cov_accel_1);

    Angle_err_1 = Angle_See_1 - Angle_1;

    //更新数据
    Angle_1 = Angle_1 + K0_1 * Angle_err_1;
    Gyro_bias_1 = Gyro_bias + K1_1 * Angle_err_1;

    //更新P矩阵
    P001 = P001 - K0_1 * P001;
    P011 = P011 - K0_1 * P011;
    P101 = P101 - K1_1 * P001;
    P111 = P111 - K1_1 * P011;

    return Angle_1;
}

//Yaw滤波函数
float dt_2 = 0.008;     //采样时间

float Angle_2;              //角度的先验估计值
float Gyro_bias_2 = 0.1;          //角速度偏移值

float Cov_angle_2 = 0.01;      //陀螺仪测量的角速度的协方差
float Cov_bias_2 = 0.01;       //陀螺仪漂移值的协方差
float Cov_accel_2 = 0.01;       //加速度计测量的加速度协方差

//P矩阵
static float P002 = 1.0;
static float P012 = 0.0;
static float P102 = 0.0;
static float P112 = 1.0;

//卡尔曼增益矩阵
float K0_2;
float K1_2;

float Angle_err_2;
float Gyro_calculate; //滤波后的角速度

float Kalman_filter_Yaw(float Gyro_2 ,float Angle_See_2) //输入陀螺仪角速度和计算角度
{
    /*状态方程
     * | Angle     |   | 1   -dt| | Angle     |   | dt|
     * |           | = |        | |           | + |   | Gyro;
     * | Gyro_bias |   | 0     1| | Gyro_bias |   | 0 |
     */
    Angle_2 = Angle_2 - Gyro_bias_2 * dt_2 + Gyro_2 * dt_2;
    Gyro_bias_2 = Gyro_bias_2;

    //P矩阵求解
    P002 = P002 - P102 * dt_2 + (P112 * dt_2 - P012) * dt_2 + Cov_angle_2;
    P012 = P012 - P112 * dt_2;
    P102 = P102 - P112 * dt_2;
    P112 = P112 + Cov_bias_2;

    //求解卡尔曼增益矩阵
    K0_2 = P002 / (P002 + Cov_accel_2);
    K1_2 = P102 / (P002 + Cov_accel_2);

    Angle_err_2 = Angle_See_2 - Angle_2;

    //更新数据
    Angle_2 = Angle_2 + K0_2 * Angle_err_2;
    Gyro_bias_2 = Gyro_bias_2 + K1_2 * Angle_err_2;
    Gyro_calculate = Gyro_2 - Gyro_bias_2;

    //更新P矩阵
    P002 = P002 - K0_2 * P002;
    P012 = P012 - K0_2 * P012;
    P102 = P102 - K1_2 * P002;
    P112 = P112 - K1_2 * P012;

    return Angle_2;
}

void Angle_Yaw(void)
{
    Yaw = Yaw + (2000*mpu_gyro_z/32768) * 0.008;
}


/* brief  : 返回Pitch角度
 * Param1 : mpu_acc_z : mpu6050返回的z轴角加速度值
 * Param2 : mpu_acc_x : mpu6050返回的x轴角加速度值
 */
void Angle_Pitch(void)
{
    Pitch = atan2(8*9.8*(mpu_acc_z)/32768,8*9.8*(mpu_acc_x)/32768)*180.0/3.14;
}


/* brief  : 返回Roll角度
 * Param1 : mpu_acc_z : mpu6050返回的z轴角加速度值
 * param2 : mpu_acc_y : mpu6050返回的y轴角加速度值
 */
void Angle_Roll(void)
{
    static float x;
    static float y;
    y = 2000*mpu_gyro_x/32768;
    x = atan2(8*9.8*(mpu_acc_y)/32768,8*9.8*(mpu_acc_z)/32768)*180.0/3.14;
    Roll = Kalman_filter_Roll(y,x);
}
