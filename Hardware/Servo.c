#include "stm32f10x.h"                  // Device header
#include "Servo.h"

void TIM5_PWM_Init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
   
    TIM_TimeBaseStructure.TIM_Period = 19999;           
    TIM_TimeBaseStructure.TIM_Prescaler = 71;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
    
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 1500;               
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    
    
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);
    
   
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
    
   
    TIM_Cmd(TIM5, ENABLE);
}

void Servo_SetAngle1(uint16_t angle) {
	
    uint16_t pulse_width = 500 + (angle * 2000 / 180);
    TIM_SetCompare1(TIM5, pulse_width);
}

void Servo_SetAngle2(uint16_t angle) {
	
    uint16_t pulse_width = 500 + (angle * 2000 / 180);
    TIM_SetCompare2(TIM5, pulse_width);
}

