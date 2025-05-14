
#include "stm32f10x.h"                  // Device header


#ifndef __CONTROL_H
#define __CONTROL_H


/*       �� �� �� �� ��      */

// ���Ŀ��ֵ���ٶ� ������
typedef struct {
    int16_t speed_set;      //Ŀ��ת�٣�RPM��r/min
    uint16_t current_set;   // Ŀ�����(PWMռ�ձ�)
	float pid_speed;
} MOTOR_SET;

// ��������ֵ�
typedef struct {
    int16_t speed_fdb;      // ʵ��ת��(RPM)r/min
    int16_t coder_fdb;      // ������������
    uint16_t current_fdb;   // ʵ�ʵ���
} MOTOR_FDB;

// ���GPIO����(����ת��)
typedef struct {
    GPIO_TypeDef *gpio;     // GPIO�˿�(��GPIOA)
    uint16_t in1;           //��������1(��GPIO_Pin_0)
    uint16_t in2;           //��������2(��GPIO_Pin_1)
} MOTOR_GPIO;

// ���������(4�����)
typedef struct {
    MOTOR_SET   motor_set[4];   // 4�������Ŀ��ֵ
    MOTOR_FDB   motor_fdb[4];   // 4������ķ���ֵ
    MOTOR_GPIO  motor_gpio[4];  // 4�����GPIO����
} MOTOR_T;

// ����ȫ�ֲ���
typedef struct {
    MOTOR_T motor;               // ���������
    float chassisVx;             // ����x�����ٶ�(mm/min)
    float chassisVy;             // ����y�����ٶ�(mm/min)
    float chassisOmega;          // ������ת���ٶ�(rad/s)
    float maxOmega;              // �����ת���ٶ�
    float maxRpm_Left[4];
    float maxRpm_Right[4];
    float maxVx;                 // ����x��������ٶ�
    float maxVy;                 // ����Y��������ٶ�
    float pidMode;               // PIDģʽ(����ʽ/λ��ʽ)
    int8_t gear;                 // ��λ(1/2/3)
    float speedtap[3];           // ��λ�ٶȱ���(0.5, 0.75, 1)
    float chassisOmega_fdb;      // �����Ƿ����Ľ��ٶȣ����ھ�ƫ��
} ChassisMotor_t;

extern ChassisMotor_t ChassisMotor;

/*          �� �� ��         */

#define timeHz    100          //10ms, ����Ƶ��
#define NULL    0
#define Wheel_R 30.0f       //���Ӱ뾶
#define PI      3.1415926f  //PI
#define Motor_i 30.0f       //���ٱ�
#define NPN     13.0f       //���ٺ�����������
#define T   100             //������arr
#define r   188.14  		//�뾶  
#define MotorMAXspeed   56520 //���ٶ�
#define MAXOmega        200.0f		
#define MAXVx           79000.4  //mm/min
#define MAXVy           79000.4
#define K              1 / (2 * PI * Wheel_R)          //���̽���ת��ϵ�� 188.4

#define redclose    GPIO_Pin_0		//��̬�ߣ����С��80mm���ͣ��̵ƻظ�
#define QR_Code1	GPIO_Pin_1
#define QR_Code2    GPIO_Pin_2



void ALL_Init(void);       
void Chassis_Move(float x,float y,float t);
void ChassisCalculate(float Vx, float Vy,  ChassisMotor_t *speedcalc);
void Motor_Control(int8_t current_1,int8_t current_2,int8_t current_3,int8_t current_4);

#endif
