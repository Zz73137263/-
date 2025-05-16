#include "stm32f10x.h"                  // Device header
#include "PWM.h"

void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(PWM_RCCTIM, ENABLE);	// ע��tim1��apb2��
	RCC_APB2PeriphClockCmd(PWM_RCCGPIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = MotorA_PWM|MotorB_PWM|MotorC_PWM|MotorD_PWM;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_GPIO, &GPIO_InitStructure);
	
//	TIM_InternalClockConfig(PWM_TIM);
	/*ʱ����Ԫ*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;			//����1ms
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;		//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseInitStructure);
	
	TIM_ARRPreloadConfig(PWM_TIM,ENABLE);
	
	TIM_Cmd(PWM_TIM, ENABLE);
	/*����Ƚϵ�Ԫ*/
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC1Init(PWM_TIM, &TIM_OCInitStructure);				
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC2Init(PWM_TIM, &TIM_OCInitStructure);	
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC3Init(PWM_TIM, &TIM_OCInitStructure);				
	TIM_OCInitStructure.TIM_Pulse = 0;		//CCR
	TIM_OC4Init(PWM_TIM, &TIM_OCInitStructure);	
	//�߼���ʱ������
	TIM_CtrlPWMOutputs(PWM_TIM,ENABLE);
	
	TIM_OC1PreloadConfig(PWM_TIM,TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(PWM_TIM,TIM_OCPreload_Enable); 
	TIM_OC3PreloadConfig(PWM_TIM,TIM_OCPreload_Enable); 
	TIM_OC4PreloadConfig(PWM_TIM,TIM_OCPreload_Enable); 
			
}

void PWM_SetCompareA(uint16_t Compare)
{
	TIM_SetCompare1(PWM_TIM, Compare);
}

void PWM_SetCompareB(uint16_t Compare)
{
	TIM_SetCompare2(PWM_TIM, Compare);
}

void PWM_SetCompareC(uint16_t Compare)
{
	TIM_SetCompare3(PWM_TIM, Compare);
}

void PWM_SetCompareD(uint16_t Compare)
{
	TIM_SetCompare4(PWM_TIM, Compare);
}

