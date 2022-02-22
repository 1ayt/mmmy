/*
 * oled_iic.h
 *
 *  Created on: 2022年2月6日
 *      Author: xqx
 */

#ifndef CODE_OLED_IIC_H_
#define CODE_OLED_IIC_H_

#include "iic.h"
#include "zf_stm_systick.h"

#define low 0
//#define Brightness  0xCF
#define X_WIDTH     128
#define Y_WIDTH     64

/*OLED IIC通讯相关宏定义*/
#define OLED_CMD                0       //写命令
#define OLED_DATA               1       //写数据
#define IIC_ADD_WC              0x78    //IIC通讯写命令时的地址
#define IIC_ADD_WD              0x78    //IIC通讯写数据时的地址
#define IIC_CONC                0x00    //控制字节指定下一个字节为命令
#define IIC_COND                0x40    //控制字节指定下一个字节为数据SS

/*SSD1306 基础命令定义*/
#define SET_CONTRAST_CONTROL                0x81    //对比度设置命令，取值范围1-255，复位值：0x7F
#define SET_DISPLAY_ON              0xAF    //开显示命令
#define SET_DISPLAY_OFF             0xAE    //关显示命令
#define ENTIRE_DISPLAY_ON_A4                0xA4    //全局显示关闭
#define ENTIRE_DISPLAY_ON_A5                0xA5    //全局显示开启
#define NORMAL_DISPLAY              0xA6    //给GDDRAM值为0，熄灭像素；给GDDRAM值为1，点亮像素
#define INVERSE_DISPLAY             0xA7    //给GDDRAM值为0，点亮像素；给GDDRAM值为1，熄灭像素

void OLED_WR_Byte(uint8 dat,uint8 cmd);
void OLED_Clear(void);
void OLED_Init(void);
void OLED_Draw_Point(uint8 x,uint8 y,uint8 c);
void OLED_Fill(void);
void OLED_Display_Off(void);
void OLED_Display_On(void);
void OLED_SetCursorAddrese(uint8 x,uint8 y);
void OLED_PageClear(uint8 page);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowNum(unsigned char x, unsigned char y, int Num);

#endif /* CODE_OLED_IIC_H_ */
