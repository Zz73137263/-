#ifndef __ENCODER_H
#define __ENCODER_H


//µ×ÅÌmotor1±àÂëÆ÷
#define ChassisEC1_TIM          TIM1
#define ChassisEC1_TIMRCC       RCC_APB2Periph_TIM1
#define ChassisEC1_GPIO         GPIOA
#define ChassisEC1_GPIORCC      RCC_APB2Periph_GPIOA
#define ChassisEC1_IN1          GPIO_Pin_8              //PA8   CH1
#define ChassisEC1_IN2          GPIO_Pin_9              //PA9   CH2

//µ×ÅÌmotor2±àÂëÆ÷
#define ChassisEC2_TIM          TIM2
#define ChassisEC2_TIMRCC       RCC_APB1Periph_TIM2
#define ChassisEC2_GPIO1        GPIOA
#define ChassisEC2_GPIO2        GPIOB
#define ChassisEC2_GPIORCC1      RCC_APB2Periph_GPIOA
#define ChassisEC2_GPIORCC2      RCC_APB2Periph_GPIOB
#define ChassisEC2_IN1          GPIO_Pin_15             //PA15  CH1
#define ChassisEC2_IN2          GPIO_Pin_3              //PB3   CH2

//µ×ÅÌmotor3±àÂëÆ÷
#define ChassisEC3_TIM          TIM3
#define ChassisEC3_TIMRCC       RCC_APB1Periph_TIM3
#define ChassisEC3_GPIO         GPIOA
#define ChassisEC3_GPIORCC      RCC_APB2Periph_GPIOB
#define ChassisEC3_IN1          GPIO_Pin_4              //PB4   CH1			
#define ChassisEC3_IN2          GPIO_Pin_5              //PB5   CH2

//µ×ÅÌmotor4±àÂëÆ÷
#define ChassisEC4_TIM          TIM4
#define ChassisEC4_TIMRCC       RCC_APB1Periph_TIM4
#define ChassisEC4_GPIO         GPIOB
#define ChassisEC4_GPIORCC      RCC_APB2Periph_GPIOB
#define ChassisEC4_IN1          GPIO_Pin_6              //PB6   CH1
#define ChassisEC4_IN2          GPIO_Pin_7              //PB7   CH2



void Encoder1_Init(void);
void Encoder2_Init(void);
void Encoder3Init(void);
void Encoder4_Init(void);
void Encoder_Init(void);
int16_t Encoder_Get1(void);
int16_t Encoder_Get2(void);
int16_t Encoder_Get3(void);
int16_t Encoder_Get4(void);

#endif
