#include "stm32f10x.h"                  // Device header
#include "MPU6050_Reg.h"
#include "math.h"
#include "Delay.h"
#include "MPU6050.h"
#include "OLED.h"
#include "Serial.h"
#include "control.h"

float ax,ay,az,gx,gy,gz;
float yaw, pitch, roll;//yawƫ���� pitch������ roll������

#define MPU6050_ADDRESS		0xD0		//MPU6050��I2C�ӻ���ַ

///*�����������Ĳ���*/
//extern float ax,ay,az,gx,gy,gz;
//extern float p,pa,GY,GZ;
#define pi 3.1415927
#define lb 0.95238

int16_t gx_offset_raw = 0, gy_offset_raw = 0, gz_offset_raw = 0;


/** ��    ����MPU6050�ȴ��¼�
  * ��    ����ͬI2C_CheckEvent
  * �� �� ֵ����
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT){
	uint32_t Timeout;
	Timeout = 10000;									//������ʱ����ʱ��
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)	//ѭ���ȴ�ָ���¼�
	{
		Timeout --;										//�ȴ�ʱ������ֵ�Լ�
		if (Timeout == 0)								//�Լ���0�󣬵ȴ���ʱ
		{
			/*��ʱ�Ĵ�������룬������ӵ��˴�*/
			break;										//�����ȴ���������
		}
	}
}

/** ��    ����MPU6050д�Ĵ���
  * ��    ����RegAddress �Ĵ�����ַ����Χ���ο�MPU6050�ֲ�ļĴ�������
  * ��    ����Data Ҫд��Ĵ��������ݣ���Χ��0x00~0xFF
  * �� �� ֵ����
  */
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data){
	I2C_GenerateSTART(I2C2, ENABLE);										//Ӳ��I2C������ʼ����
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//�ȴ�EV6
	
	I2C_SendData(I2C2, RegAddress);											//Ӳ��I2C���ͼĴ�����ַ
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);			//�ȴ�EV8
	
	I2C_SendData(I2C2, Data);												//Ӳ��I2C��������
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//�ȴ�EV8_2
	
	I2C_GenerateSTOP(I2C2, ENABLE);											//Ӳ��I2C������ֹ����
}

/** ��    ����MPU6050���Ĵ���
  * ��    ����RegAddress �Ĵ�����ַ����Χ���ο�MPU6050�ֲ�ļĴ�������
  * �� �� ֵ����ȡ�Ĵ��������ݣ���Χ��0x00~0xFF
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress){
	uint8_t Data;
	
	I2C_GenerateSTART(I2C2, ENABLE);										//Ӳ��I2C������ʼ����
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);	//Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);	//�ȴ�EV6
	
	I2C_SendData(I2C2, RegAddress);											//Ӳ��I2C���ͼĴ�����ַ
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);				//�ȴ�EV8_2
	
	I2C_GenerateSTART(I2C2, ENABLE);										//Ӳ��I2C�����ظ���ʼ����
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);					//�ȴ�EV5
	
	I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);		//Ӳ��I2C���ʹӻ���ַ������Ϊ����
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);		//�ȴ�EV6
	
	I2C_AcknowledgeConfig(I2C2, DISABLE);									//�ڽ������һ���ֽ�֮ǰ��ǰ��Ӧ��ʧ��
	I2C_GenerateSTOP(I2C2, ENABLE);											//�ڽ������һ���ֽ�֮ǰ��ǰ����ֹͣ����
	
	MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);				//�ȴ�EV7
	Data = I2C_ReceiveData(I2C2);											//�������ݼĴ���
	
	I2C_AcknowledgeConfig(I2C2, ENABLE);									//��Ӧ��ָ�Ϊʹ�ܣ�Ϊ�˲�Ӱ��������ܲ����Ķ�ȡ���ֽڲ���
	
	return Data;
}

/** ��    ����MPU6050��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void MPU6050_Init(void){//(PB10,PB11)
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);		//����I2C2��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//����GPIOB��ʱ��
	
	/*GPIO��ʼ��*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					//��PB10��PB11���ų�ʼ��Ϊ���ÿ�©���
	
	/*I2C��ʼ��*/
	I2C_InitTypeDef I2C_InitStructure;						//����ṹ�����
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;				//ģʽ��ѡ��ΪI2Cģʽ
	I2C_InitStructure.I2C_ClockSpeed = 400000;				//ʱ���ٶȣ�ѡ��Ϊ400KHz
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;		//ʱ��ռ�ձȣ�ѡ��Tlow/Thigh = 2
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;				//Ӧ��ѡ��ʹ��
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;	//Ӧ���ַ��ѡ��7λ���ӻ�ģʽ�²���Ч
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;				//�����ַ���ӻ�ģʽ�²���Ч
	I2C_Init(I2C2, &I2C_InitStructure);						//���ṹ���������I2C_Init������I2C2
	
	/*I2Cʹ��*/
	I2C_Cmd(I2C2, ENABLE);									//ʹ��I2C2����ʼ����
	
	/*MPU6050�Ĵ�����ʼ������Ҫ����MPU6050�ֲ�ļĴ����������ã��˴��������˲�����Ҫ�ļĴ���*/
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x80);
	Delay_ms(100);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x00);				//��Դ����Ĵ���1��ȡ��˯��ģʽ��ѡ��ʱ��ԴΪX��������
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);				//��Դ����Ĵ���2������Ĭ��ֵ0���������������
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);					//���üĴ���������DLPF
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x04);				//�����ʷ�Ƶ�Ĵ��������ò����� 200hZ		
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);			//���������üĴ�����ѡ������Ϊ��2000��/s
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x00);			//���ٶȼ����üĴ�����ѡ��������Ϊ��2g
}


/** ��    ����MPU6050ŷ���Ǽ���
  * ��    ������
  * �� �� ֵ��
  */
void MPU6050_CalEularAngle(void)
{

	MPU6050_UpDate();		//���´�����ֵ
	//ͨ�������ǲ����������ŷ���� ��1  ����Ƶ��200hz
	float yaw_g = yaw + gx * 0.005*90/4 + 0.00685;
	float pitch_g = pitch + gy *0.005*90/4;
	float roll_g = roll + gz * 0.005*90/4;

	//���ٶȼƼ���ŷ����
	float pitch_a = atan2(az,ax)/3.1415927 * 180.0f;
	float roll_a = atan2(ay,ax)/3.1415927 * 180.0f;
	//�����˲�
	yaw = yaw_g;
	pitch =0.95238*pitch_g + (1-0.95238) * pitch_a;
	roll =0.95238 *roll_g + (1-0.95238) *  roll_a;
	
}

/** ��    ����MPU6050��ȡID��
  * ��    ������
  * �� �� ֵ��MPU6050��ID��
  */


uint8_t MPU6050_GetID(void){
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);		//����WHO_AM_I�Ĵ�����ֵ
}

 /** ��    ����MPU6050��ȡ����
  * ��    ����ax ay az ���ٶȼ�X��Y��Z������ݣ�ʹ�������������ʽ���أ���Χ:+-2g
  * ��    ����gx gy gz ������X��Y��Z������ݣ�ʹ�������������ʽ���أ���Χ����2000��/s
  * �� �� ֵ����
  */
void MPU6050_UpDate(void){
	uint8_t DataH, DataL;								//�������ݸ�8λ�͵�8λ�ı���
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);		//��ȡ���ٶȼ�X��ĸ�8λ����
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);		//��ȡ���ٶȼ�X��ĵ�8λ����
	int16_t ax_raw = (int16_t)((DataH << 8) | DataL);						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);		//��ȡ���ٶȼ�Y��ĸ�8λ����
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);		//��ȡ���ٶȼ�Y��ĵ�8λ����
	int16_t ay_raw = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);		//��ȡ���ٶȼ�Z��ĸ�8λ����
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);		//��ȡ���ٶȼ�Z��ĵ�8λ����
	int16_t az_raw = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);		//��ȡ������X��ĸ�8λ����
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);		//��ȡ������X��ĵ�8λ����
	int16_t gx_raw = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);		//��ȡ������Y��ĸ�8λ����
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);		//��ȡ������Y��ĵ�8λ����
	int16_t gy_raw = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);		//��ȡ������Z��ĸ�8λ����
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);		//��ȡ������Z��ĵ�8λ����
	int16_t gz_raw = (DataH << 8) | DataL;						//����ƴ�ӣ�ͨ�������������
	
	
	ax = ax_raw * 6.1035e-5f;
	ay = ay_raw * 6.1035e-5f;
	az = az_raw * 6.1035e-5f;
	
	gx = (gx_raw * 6.1035e-2f)+3.235;		//����ӵ������ֵ
	gy = (gy_raw * 6.1035e-2f)+0.38;
	gz = (gz_raw * 6.1035e-2f)-0.20;
}


float MPU6050_GetAx(void)
{
	return ax;
}
float MPU6050_GetAy(void)
{
	return ay;
}	
float MPU6050_GetAz(void)
{
	return az;
}	

float MPU6050_GetGx(void)
{
	return gx;
}	
float MPU6050_GetGy(void)
{
	return gy;
}	
float MPU6050_GetGz(void)
	{
	return gz;
}



void MPU6050_Angle_Init(void){//��ó�ʼ�Ƕ�ֵ
//	MPU6050_GetData(&ax, &ay, &az, &gx, &gy, &gz);//��ȡMPU6050����ֵ(Ƶ��:1000HZ,���ٶ�����:��2g,���ٶ����̡�2000��/s
//	p=atan2((float)ax,(float)az)/pi*180.f;//ͨ�����ٶ�ֵ�������ʼ�Ƕ�
}
void MPU6050_Angle(void){//���½Ƕ�ֵ����ȡMPU6050����ֵ
//	GY=(float)gy/32768.f*2000.f;//��GY����ֵת���ɽ��ٶ�ֵ
//	GZ=(float)gz/32768.f*2000.f;//��GZ����ֵת���ɽ��ٶ�ֵ
//	p-=GY*0.01;//��ԭ�ǶȵĻ����ϼӼ��ǶȲ�ֵ��0.01��ʱ����(10ms)��
//	pa=atan2((float)ax,(float)az)/pi*180.f;//ͨ�����ٶ�ֵ������Ƕ�
//	p=lb*p+(1-lb)*pa;//���˲�ֵ(lb)�������ں�
}

float MPU6050_GetYaw(void)
{
	return yaw;
	
}

float MPU6050_GetPitch(void)
{
	return pitch;
}

float MPU6050_GetRoll(void)
{
	return roll;
}


