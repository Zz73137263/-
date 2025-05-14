/**
 * @platform	keil5ƽ̨STM32F103C8T6�ͺŵ�Ƭ��
 * @mainpage	������ѧԺʮ�ڻ�����������R1��������Ƭ��(�ͺ�F103RCT6)
 * @author		ɣ��
 * @date		2025��4��11��
 */


#ifndef __ATK_IMU901_API_h
#define __ATK_IMU901_API_h


#include <stdint.h>


/**
  * @brief  �洢��ȡATK_IMU901�����ݵĽṹ��
  */
typedef struct
{
	float Roll;			// ��ת�ǣ�X�ᣩ��Roll������Χ��-180��-+180�ȣ���λ���ȣ�������λС������
	float Pitch;		// �����ǣ�Y�ᣩ��Pitch������Χ��-90��-+90�ȣ���λ���ȣ�������λС������
	float Yaw;			// ƫ���ǣ�Z�ᣩ��Yaw������Χ��-180��-+180�ȣ���λ���ȣ�������λС������
	float AccX;			// ���ٶȼ�X�����ݣ���λ��G��������λС������
	float AccY; 		// ���ٶȼ�Y�����ݣ���λ��G��������λС������
	float AccZ;			// ���ٶȼ�Z�����ݣ���λ��G��������λС������
	float GyroX;		// ������X�����ݣ���λ����/s��������λС������
	float GyroY; 		// ������Y�����ݣ���λ����/s��������λС������
	float GyroZ;		// ������Z�����ݣ���λ����/s��������λС������
}ATK_IMU901_DataTypeDef;


void ATK_IMU901_Init(void);
ATK_IMU901_DataTypeDef* ATK_IMU901_GetPoint_Data(void);
void ATK_IMU901_ReadData(void);


void ATK_IMU901_Demo(void);


#endif
