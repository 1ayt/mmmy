/*
 * image.c
 *
 *  Created on: 2022年2月10日
 *      Author: xqx
 */
#include "image.h"

//-----------------------------------------------------------------------
// @brief       大津法计算灰度阈值(优化后)
// @param       image       图像数组首地址
// @param       col         图像列数
// @param       row         图像行数
//-----------------------------------------------------------------------
uint8 otsuThreshold(uint8 *image, uint16 col, uint16 row)
{
    #define GrayScale 256
    uint16 width = col;
    uint16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height/4;
    uint8 threshold = 0;
    uint8* data = image;  //指向像素数据的指针
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //统计灰度级中每个像素在整幅图像中的个数
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //将像素值作为计数数组的下标
        }
    }

    //计算每个像素在整幅图像中的比例
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
    }

    //遍历灰度级[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i作为阈值
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 100; j < GrayScale; j++)
        {
            if (j <= i)   //背景部分
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //前景部分
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = (uint8)i;
        }
    }

    return threshold;
}

//-----------------------------------------------------------------------
// @brief       串口发送二值化图像
// @param       image       二维图像数组首地址
// @param       col         图像列数
// @param       row         图像行数
// Sample usage:            在图像使用完毕后将mt9v03x_finish_flag置0
//-----------------------------------------------------------------------
void Send_Gray_image(uint8 *imag,uint16 col,uint16 row,int threshold)
{

    int i=0;
    uart_putchar(UART_0,0x00);uart_putchar(UART_0,0xff);uart_putchar(UART_0,0x01);uart_putchar(UART_0,0x01);//发送命令
    for(i=0;i<col*row;i++)
    {
        if(imag[i] < threshold) uart_putchar(UART_0,0x00);
        else uart_putchar(UART_0,0xff);
    }
}

//-----------------------------------------------------------------------
// @brief       单线直线寻中线
// @param       图像数组
//-----------------------------------------------------------------------
int Middle_Line(uint8 *imag)
{
    int i=0;
    int left=0,right=0;
    int pos=0;

    for(i=187+59*188+1;i<(187+59*188+188);i++)
    {
        if(imag[i] > imag[i+1]) left = i-(187+59*188+1);
        if(imag[i] < imag[i+1]) right = i-(187+59*188+1);
    }

    pos = (left + right)/2.0;
    return pos;
}

//------------------------------------------------------------------------
// @brief       双线直线寻中线
// @param       imag            图像数组
// @param       threshold       大津法计算阈值
//------------------------------------------------------------------------
int Middle_Line_P(uint8 *imag,uint8 threshold)
{
    static int i=0;
    static int left=0,right=0;
    int pos=0;

    for(i=0;i<93;i++)
    {
        if(imag[187+59*188+1+94-i] > threshold && imag[187+59*188+1+94-i-1] < threshold) left = 94-i;
        break;
    }

    for(i=0;i<93;i++)
    {
        if(imag[187+59*188+1+94+i] > threshold && imag[187+59*188+1+94+i+1] < threshold) right = 94+i;
        break;
    }

    pos = (left + right)/2.0;
    return pos;
}


//------------------------------------------------------------------------
//
//
//
//

/*
for(i=0;i<120;i++)
{
    for(j=86;j<103;j++)
    {
        data[i][j] = 0xff;
    }
}

for(i=0;i<120;i++)
{
    for(j=0;j<i;j++)
    {
        data[i][85-j] = 0xff;
    }
    for(j=0;j<i;j++)
    {
        data[i][103+j] = 0xff;
    }
}

for(i=0;i<120*188;i++)
{
    img[i] = data[k][m];
    m++;
    if(m == 188)
    {
        m = 0;
        k++;
    }

}
*/
/*
for(i=0;i<120;i++)
{
    for(j=0;j<i+1;j++)
    {
        data[i][j] = 0xff;
    }
}
for(i=0;i<120;i++)
{
    for(j=0;j<10;j++)
    {
        data[i][j] = 0x00;
    }
}
for(i=0;i<120*188;i++)
{
    img[i] = data[k][m];
    m++;
    if(m == 188)
    {
        m = 0;
        k++;
    }

}
*/
