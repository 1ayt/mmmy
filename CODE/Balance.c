/*
 * Balance.c
 *
 *  Created on: 2022��2��4��
 *      Author: xqx
 */
#include "Balance.h"

int Start_Flag = 0;

/*����������*/
extern int count;
extern int count_speed;

/*mpu6050����*/
extern int16 mpu_gyro_x;
extern int16 mpu_acc_x;
extern float Roll;

/*PIDx����Ʋ���*/
float X_Balance_KP = 500.001;
float X_Balance_KI = 30.001;//3.0001;
float X_Balance_KD = 3.001;//30.001;

/*����PIDx����Ʋ���*/
float X_Balance_KP_P = 2000.001;
float X_Balance_KI_P = 30.001;
float X_Balance_KD_P = 3.001;

/*PI�����ֿ��Ʋ���*/
float X_Speed_KP = 90;
float X_Speed_KI = 90;

/*���ƽ����Ʋ���*/
int Servo_PWM;
int PWMServo;
float Zero_error = 7.6;
float Integration;
float Balance_Kp = 32.0;
float Balance_Ki = 0.03;
float Balance_Kd = 0.002;
#define Servo_Center_Mid  1600

/*����ƽ���е���*/
float Roll_Zero =7.6;

/*PWM�м���*/
int PWM_X;
int PWM_Accel;
int MotorDutyA;
int MotorDutyB;

void Balance(void)
{
    Angle_Roll();
    encoder_read();
    if(Roll < -(5+Roll_Zero) | Roll > +(5+Roll_Zero) ) Start_Flag = 1;

    if(Start_Flag == 0)
    {
        //--------------------�����ֿ���----------------------//
        PWM_X = X_Balance_Control(Roll,Roll_Zero,Gyro_x((float)mpu_gyro_x));
        //PWM_X = X_Balance_Control_P(Roll,Roll_Zero,Gyro_x((float)mpu_gyro_x),Accel_x((float)mpu_acc_x));
        //PWM_Accel = -Speed_Control(-count_speed);
        MotorDutyA = -(PWM_X - PWM_Accel);
        if(MotorDutyA>5000) MotorDutyA=5000;        // �����ֵ���޷�
        if(MotorDutyA<-5000) MotorDutyA=-5000; // �����ֵ���޷�
        if(MotorDutyA < 0 && MotorDutyA > -1000) MotorDutyA = -800;
        if(MotorDutyA > 0 && MotorDutyA < +1000) MotorDutyA = +800;
        //if((PWM_X<1000)&&(PWM_X>-1000)) PWM_X=0;

        if(MotorDutyA >= 0)
        {
            pwm_duty(ATOM3_CH5_P11_10,MotorDutyA);
            gpio_set(P11_6,0);
        }
        else
        {
            pwm_duty(ATOM3_CH5_P11_10,(-MotorDutyA));
            gpio_set(P11_6,1);
        }

        //---------------------�������-----------------------//
        //Servo_PWM = SBB_Get_BalancePID(Roll,Gyro_x((float)mpu_gyro_x));
        //if(Servo_PWM > +400) Servo_PWM = +400;
        //if(Servo_PWM < -400) Servo_PWM = -400;
        //PWMServo = Servo_Center_Mid - Servo_PWM;
        //pwm_duty(ATOM3_CH4_P14_1,PWMServo);

        //---------------------���ֵ������-------------------//
        //pwm_duty(ATOM3_CH7_P13_2,MotorDutyB);
        //gpio_set(P13_0,1);

    }

    else if(Start_Flag == 1)
    {
        pwm_duty(ATOM3_CH5_P11_10,0);
        PWMServo = 1600;
        MotorDutyB = 0;
    }

}

//x��PIDƽ�����
float X_Balance_Control(float Angle,float Angle_Zero,float Gyro)
{
    static float PWM,Bias;
    static float error;
    Bias = Angle - Angle_Zero;
    error = error + Bias;
    if(error > +30) error = +30;
    if(error < -30) error = -30;
    PWM = X_Balance_KP * Bias + X_Balance_KI * error + Gyro * X_Balance_KD;
    return PWM;
}

//x�ᴮ��PIDƽ�����
float X_Balance_Control_P(float Angle,float Angle_Zero,float Gyro,float Accel)
{
    static float PWM1,PWM2,Bias1,Bias2;
    static float error1,error2;
    Bias1 = Angle -Angle_Zero;
    error1 = error1 + Bias1;
    if(error1 > +30) error1 = +30;
    if(error1 < -30) error1 = -30;
    PWM1 = X_Balance_KP * Bias1 + X_Balance_KI * error1 + Gyro * X_Balance_KD;

    Bias2 = Gyro - PWM1;
    error2 = error2 + Bias2;
    if(error2 > +30) error2 = +30;
    if(error2 < -30) error2 = -30;
    PWM2 = X_Balance_KP_P * Bias2 + X_Balance_KI_P * error2 + Accel * X_Balance_KD_P;

    return PWM2;
}

//�������ٶ�PI����
float Speed_Control(int encoder)
{
    static float Encoder,Encoder_Integral;
    int Encoder_Least;
    float Speed;

    Encoder_Least = encoder;
    Encoder = Encoder * 0.7;
    Encoder = Encoder + Encoder_Least * 0.3;
    Encoder_Integral = Encoder_Integral + Encoder;
    if(Encoder_Integral > +2000) Encoder_Integral = +2000;
    if(Encoder_Integral < -2000) Encoder_Integral = -2000;
    Speed = Encoder * X_Speed_KP + Encoder_Integral * X_Speed_KI/100;
    if(Start_Flag==0) Encoder_Integral=0,Encoder=0,Speed=0;
    return Speed;
}

int SBB_Get_BalancePID(float Angle,float Gyro)
{
    float  Bias;
    int SBB_BalancePID;
    Bias = Angle - Zero_error;
    Integration += Bias;
    if(Integration<-200)      Integration=-200;
    else if(Integration>200)  Integration= 200;
    SBB_BalancePID = Balance_Kp * Bias + Balance_Ki*Integration + Balance_Kd*Gyro;
    return SBB_BalancePID;
}
