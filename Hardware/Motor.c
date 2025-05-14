#include "stm32f10x.h"                  // Device header
#include "PWM.h"


void MotorA_Init(void)
{
	RCC_APB2PeriphClockCmd(MotorA_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = AIN1 | AIN2 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MotorA_GPIO, &GPIO_InitStructure);
	
}

void MotorB_Init(void)
{
	RCC_APB2PeriphClockCmd(MotorB_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = BIN1 | BIN2 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MotorB_GPIO, &GPIO_InitStructure);
	
}
void MotorC_Init(void)
{
	RCC_APB2PeriphClockCmd(MotorC_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = CIN1 | CIN2 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MotorC_GPIO, &GPIO_InitStructure);
	
}

void MotorD_Init(void)
{
	RCC_APB2PeriphClockCmd(MotorD_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = DIN1 | DIN2 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MotorD_GPIO, &GPIO_InitStructure);
	
}

void Motor_Init(void)
{
	 MotorA_Init();
	 MotorB_Init();
	 MotorC_Init();
	 MotorD_Init();
}
void MotorA_SetPWM(int8_t Compare)
{
	if (Compare >= 0)
	{
		GPIO_SetBits(MotorA_GPIO, AIN1 );
		GPIO_ResetBits(MotorA_GPIO, AIN2 );
		PWM_SetCompareA(Compare);
	}
	else
	{
		GPIO_SetBits(MotorA_GPIO, AIN2);
		GPIO_ResetBits(MotorA_GPIO, AIN1);
		PWM_SetCompareA(-Compare);
	}
}
void MotorB_SetPWM(int8_t Compare)
{
	if (Compare >= 0)
	{
		GPIO_SetBits(MotorB_GPIO, BIN1);
		GPIO_ResetBits(MotorB_GPIO, BIN2);
		PWM_SetCompareB(Compare);
	}
	else
	{
		GPIO_SetBits(MotorB_GPIO, BIN2);
		GPIO_ResetBits(MotorB_GPIO, BIN1);
		PWM_SetCompareB(-Compare);
	}
}
void MotorC_SetPWM(int8_t Compare)
{
	if (Compare >= 0)
	{
		GPIO_SetBits(MotorC_GPIO, CIN1 );
		GPIO_ResetBits(MotorC_GPIO, CIN2 );
		PWM_SetCompareC(Compare);
	}
	else
	{
		GPIO_SetBits(MotorA_GPIO, AIN2);
		GPIO_ResetBits(MotorA_GPIO, AIN1);
		PWM_SetCompareC(-Compare);
	}
}
void MotorD_SetPWM(int8_t Compare)
{
	if (Compare >= 0)
	{
		GPIO_SetBits(MotorD_GPIO, DIN1);
		GPIO_ResetBits(MotorD_GPIO,DIN2);
		PWM_SetCompareD(Compare);
	}
	else
	{
		GPIO_SetBits(MotorD_GPIO, DIN2);
		GPIO_ResetBits(MotorD_GPIO, DIN1);
		PWM_SetCompareD(-Compare);
	}
}
