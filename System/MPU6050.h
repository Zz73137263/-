#ifndef __MPU6050_H
#define __MPU6050_H
#include "stm32f10x.h"

//void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);//MPU6050д�Ĵ���
//uint8_t MPU6050_ReadReg(uint8_t RegAddress);//MPU6050���Ĵ���
static void reg_write(uint8_t reg, uint8_t value);
static uint8_t reg_read(uint8_t reg);

void MPU6050_Init(void);//MPU6050��ʼ��
void MPU6050_CalEularAngle(void);//����ŷ����

uint8_t MPU6050_GetID(void);//MPU6050��ȡID��

void MPU6050_UpDate(void);//MPU6050��ȡ����

float MPU6050_GetAx(void);
float MPU6050_GetAy(void);
float MPU6050_GetAz(void);
float MPU6050_GetGx(void);
float MPU6050_GetGy(void);
float MPU6050_GetGz(void);

float MPU6050_GetYaw(void);//ƫ���� ������ ������
float MPU6050_GetPitch(void);
float MPU6050_GetRoll(void);

void MPU6050_Angle_Init(void);//��ó�ʼ�Ƕ�ֵ
void MPU6050_Angle(void);//���½Ƕ�ֵ����ȡMPU6050����ֵ

void MPU6050_DataTest(void);//���Զ�ȡax ay az gx gy gz
void MPU6050_EularAngleTest(void);//���Զ�ȡŷ����

extern float yaw ,pitch, roll;
extern float ax,ay,az,gx,gy,gz;
#endif
