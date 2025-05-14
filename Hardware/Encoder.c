#include "stm32f10x.h"                  // Device header
#include "Encoder.h"

void Encoder1_Init(void)
{
	//RCC
	RCC_APB2PeriphClockCmd(ChassisEC1_TIMRCC, ENABLE);
	RCC_APB2PeriphClockCmd(ChassisEC1_GPIORCC, ENABLE);
	
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = ChassisEC1_IN1 | ChassisEC1_IN2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ChassisEC1_GPIO, &GPIO_InitStructure);
		
    //定时器配置	
	TIM_TimeBaseInitTypeDef TIM1_TimeBaseInitStructure;
	TIM1_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM1_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM1_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM1_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(ChassisEC1_TIM, &TIM1_TimeBaseInitStructure);
	
	//输入捕获
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC1_TIM, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC1_TIM, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(ChassisEC1_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	

	TIM_Cmd(ChassisEC1_TIM, ENABLE);
}


void Encoder2_Init(void)
{
	//RCC
    RCC_APB2PeriphClockCmd(ChassisEC2_TIMRCC, ENABLE);
    RCC_APB2PeriphClockCmd(ChassisEC2_GPIORCC1, ENABLE);
    RCC_APB2PeriphClockCmd(ChassisEC2_GPIORCC2, ENABLE);
    
	
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = ChassisEC2_IN1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(ChassisEC2_GPIO1, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = ChassisEC2_IN2;
    GPIO_Init(ChassisEC2_GPIO2, &GPIO_InitStructure);
		
    //定时器配置	
	TIM_TimeBaseInitTypeDef TIM2_TimeBaseInitStructure;
	TIM2_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM2_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM2_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM2_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(ChassisEC2_TIM, &TIM2_TimeBaseInitStructure);
	
	//输入捕获
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC2_TIM, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC2_TIM, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(ChassisEC2_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	

	TIM_Cmd(ChassisEC2_TIM, ENABLE);
}


void Encoder3_Init(void)
{
	//RCC
    RCC_APB2PeriphClockCmd(ChassisEC3_TIMRCC, ENABLE);
    RCC_APB2PeriphClockCmd(ChassisEC3_GPIORCC, ENABLE);
    
	
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = ChassisEC3_IN1 |ChassisEC3_IN2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(ChassisEC3_GPIO, &GPIO_InitStructure);
		
    //定时器配置	
	TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStructure;
	TIM3_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM3_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM3_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM3_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM3_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(ChassisEC3_TIM, &TIM3_TimeBaseInitStructure);
	
	//输入捕获
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC3_TIM, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC3_TIM, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(ChassisEC3_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	

	TIM_Cmd(ChassisEC3_TIM, ENABLE);
}


void Encoder4_Init(void)
{
	//RCC
    RCC_APB2PeriphClockCmd(ChassisEC4_TIMRCC, ENABLE);
    RCC_APB2PeriphClockCmd(ChassisEC4_GPIORCC, ENABLE);
    
	//GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = ChassisEC4_IN1 |ChassisEC4_IN2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(ChassisEC4_GPIO, &GPIO_InitStructure);
		
    //定时器配置	
	TIM_TimeBaseInitTypeDef TIM4_TimeBaseInitStructure;
	TIM4_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM4_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM4_TimeBaseInitStructure.TIM_Period = 65536 - 1;		//ARR
	TIM4_TimeBaseInitStructure.TIM_Prescaler = 1 - 1;		//PSC
	TIM4_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(ChassisEC4_TIM, &TIM4_TimeBaseInitStructure);
	
	//输入捕获
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC4_TIM, &TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit(ChassisEC4_TIM, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(ChassisEC4_TIM, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	

	TIM_Cmd(ChassisEC4_TIM, ENABLE);
}

void Encoder_Init(void){
	Encoder1_Init();
	Encoder2_Init();
	Encoder3_Init();
	Encoder4_Init();
}

int16_t Encoder_Get1(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(ChassisEC1_TIM);
	TIM_SetCounter(ChassisEC1_TIM, 0);
	return Temp;
}

int16_t Encoder_Get2(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(ChassisEC2_TIM);
	TIM_SetCounter(ChassisEC2_TIM, 0);
	return Temp;
}
int16_t Encoder_Get3(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(ChassisEC3_TIM);
	TIM_SetCounter(ChassisEC3_TIM, 0);
	return Temp;
}

int16_t Encoder_Get4(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(ChassisEC4_TIM);
	TIM_SetCounter(ChassisEC4_TIM, 0);
	return Temp;
}
