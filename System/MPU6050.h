#ifndef __MPU6050_H
#define __MPU6050_H
#include "stm32f10x.h"

//void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);//MPU6050写寄存器
//uint8_t MPU6050_ReadReg(uint8_t RegAddress);//MPU6050读寄存器
static void reg_write(uint8_t reg, uint8_t value);
static uint8_t reg_read(uint8_t reg);

void MPU6050_Init(void);//MPU6050初始化
void MPU6050_CalEularAngle(void);//计算欧拉角

uint8_t MPU6050_GetID(void);//MPU6050获取ID号

void MPU6050_UpDate(void);//MPU6050获取数据

float MPU6050_GetAx(void);
float MPU6050_GetAy(void);
float MPU6050_GetAz(void);
float MPU6050_GetGx(void);
float MPU6050_GetGy(void);
float MPU6050_GetGz(void);

float MPU6050_GetYaw(void);//偏航角 俯仰角 翻滚角
float MPU6050_GetPitch(void);
float MPU6050_GetRoll(void);

void MPU6050_Angle_Init(void);//获得初始角度值
void MPU6050_Angle(void);//更新角度值，读取MPU6050的数值

void MPU6050_DataTest(void);//测试读取ax ay az gx gy gz
void MPU6050_EularAngleTest(void);//测试读取欧拉角

extern float yaw ,pitch, roll;
extern float ax,ay,az,gx,gy,gz;
#endif
