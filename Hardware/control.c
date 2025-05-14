#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "math.h"
#include "control.h"
#include "OLED.h"
#include "LED.h"
#include "Timer.h"	
#include "Key.h"
#include "RP.h"
#include "Motor.h"
#include "Encoder.h"
#include "Serial.h"
#include "PWM.h"
#include "PID.h"
#include "MPU6050.h"

ChassisMotor_t          ChassisMotor; 
uint8_t red_stop ;											
uint8_t qr_11    ;	
uint8_t qr_12    ;



void ALL_Init(void){
	ChassisMotor.maxVx = 79000.2f ;		
	ChassisMotor.maxVy = 79000.2f ;		
	
	ChassisMotor.maxRpm_Left[0] = 307; 
	ChassisMotor.maxRpm_Left[1] = 360; 
	ChassisMotor.maxRpm_Left[2] = 350; 
	ChassisMotor.maxRpm_Left[3] = 345;
	
	ChassisMotor.maxRpm_Right[0] = 330;
	ChassisMotor.maxRpm_Right[1] = 360;
	ChassisMotor.maxRpm_Right[2] = 350;
	ChassisMotor.maxRpm_Right[3] = 345;
	
	
	OLED_Init();
	Motor_Init();
	Encoder_Init();
	Serial_Init();
	PWM_Init();
	MPU6050_Init();
	Timer_Init();
	
	//��ݮ���������ų�ʼ
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = redclose | QR_Code1 | QR_Code2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//�����ƺ���
void Chassis_Task(void)
{
	ALL_Init();
	while (1) {
        // ��� GPIO ��ƽ
		qr_11    = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);    // ��ά��11
		qr_12    = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);    // ��ά��12

		float T1,T2,T3;
		
        if (qr_11) 
			{
			//ʶ����Ŵ򿪲���LED	
			//���ջ���1	
			//�����Źر�	
            Chassis_Move(0, MAXVy/2, T1);//����ȴ���
			while(red_stop == 0){Chassis_Move(0,0,0);}//�ȴ�
			Chassis_Move(0, MAXVy/2, T2);
			Chassis_Move(MAXVx/2,0, T3);//ת�䵽���ջ���
			//�򿪲���
			//�����Źر�
			Chassis_Move(-MAXVx/2,0, T3);
			Chassis_Move(0,-MAXVy/2, T2+T1);
			} 
		else if (qr_12) 
			{
			//ʶ����Ŵ򿪲���LED	
			//�򿪲���2	
			//�����Źر�	
            Chassis_Move(0, MAXVy/2, T1);//����ȴ���
			while(red_stop == 0){Chassis_Move(0,0,0);}//�ȴ�
			Chassis_Move(0, MAXVy/2, T2);
			Chassis_Move(MAXVx/2,0, T3);//ת�䵽���ջ���
			//�򿪲���2
			//�����Źر�
			Chassis_Move(-MAXVx/2,0, T3);
			Chassis_Move(0,-MAXVy/2, T2+T1);
			} 
    }
	
	


}

//�����ƶ�
void Chassis_Move(float x,float y,float t)
{
	ChassisCalculate(x,y,&ChassisMotor);
	Motor_Control(ChassisMotor.motor.motor_set[0].current_set, ChassisMotor.motor.motor_set[1].current_set, 
                  ChassisMotor.motor.motor_set[2].current_set, ChassisMotor.motor.motor_set[3].current_set);
	Delay_s(t);
	Motor_Control(0,0,0,0);
}



//���̽���->Ŀ��ת��->Ŀ�����
void ChassisCalculate(float Vx, float Vy,  ChassisMotor_t *speedcalc)
{
	//���ٶ�->ת��												mm/min						 			
    speedcalc->motor.motor_set[0].speed_set = ((sqrt(2) / 2) * Vx - (sqrt(2) / 2) * Vy  )* K;
    speedcalc->motor.motor_set[1].speed_set = (((-1) * sqrt(2) / 2) * Vx - (sqrt(2) / 2) * Vy  ) * K;
    speedcalc->motor.motor_set[2].speed_set = (-(sqrt(2) / 2) *Vx + (sqrt(2) / 2) * Vy  ) * K;
    speedcalc->motor.motor_set[3].speed_set = ((sqrt(2) / 2) * Vx + (sqrt(2) / 2) * Vy  ) * K;
    for(int i = 0; i < 4; i++)
    {
        speedcalc->motor.motor_set[i].speed_set = speedcalc->motor.motor_set[i].speed_set * ChassisMotor.speedtap[ChassisMotor.gear - 1];
		if(speedcalc->motor.motor_set[i].speed_set > 0)
        {
            if(speedcalc->motor.motor_set[i].speed_set > ChassisMotor.maxRpm_Left[i]){speedcalc->motor.motor_set[i].speed_set = ChassisMotor.maxRpm_Left[i];}
        }
        if(speedcalc->motor.motor_set[i].speed_set < 0)
        {
            if(speedcalc->motor.motor_set[i].speed_set < -ChassisMotor.maxRpm_Right[i]){speedcalc->motor.motor_set[i].speed_set = -ChassisMotor.maxRpm_Right[i];}
        }
	}
	
	for(int j = 0; j < 4; j++)
   {
	    //ת��->PWM��������
	   if(speedcalc->motor.motor_set[j].speed_set > 0)
			{
			speedcalc->motor.motor_set[j].current_set = ((uint16_t)((speedcalc->motor.motor_set[j].speed_set / ChassisMotor.maxRpm_Left[j]) * 100));}
		    if(speedcalc->motor.motor_set[j].current_set > 100){speedcalc->motor.motor_set[j].current_set = 100;	}
       if(speedcalc->motor.motor_set[j].speed_set < 0)
		    {
			speedcalc->motor.motor_set[j].current_set = ((uint16_t)((speedcalc->motor.motor_set[j].speed_set / ChassisMotor.maxRpm_Right[j]) * 100));}
		    if(speedcalc->motor.motor_set[j].current_set > 100){speedcalc->motor.motor_set[j].current_set = 100;	}
   }
}


//�������
void Motor_Control(int8_t current_1,int8_t current_2,int8_t current_3,int8_t current_4)
{
    MotorA_SetPWM(current_1);
	MotorB_SetPWM(current_2);
	MotorC_SetPWM(current_3);
	MotorD_SetPWM(current_4);
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)		
	{
		red_stop = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
		qr_11    = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1);		
		qr_12    = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);													
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);													
	}


}


