#ifndef __PWM_H
#define __PWM_H
//PWM输出TIM
#define PWM_TIM                 TIM8
#define PWM_GPIO                GPIOC
#define PWM_RCCGPIO             RCC_APB2Periph_GPIOC
#define PWM_RCCTIM              RCC_APB2Periph_TIM8

//底盘电机1GPIO口		      
#define MotorA_PWM       	  GPIO_Pin_6  //PC6   T8C1
					          
#define MotorA_GPIO      	  GPIOC
#define MotorA_RCC       	  RCC_APB2Periph_GPIOC
#define AIN1  				  GPIO_Pin_2  //PC2
#define AIN2  				  GPIO_Pin_3  //PC3
		                      
//底盘电机2GPIO口		      
#define MotorB_PWM       	  GPIO_Pin_7  //PC7   T8C2
		                      
#define MotorB_GPIO      	  GPIOC
#define MotorB_RCC       	  RCC_APB2Periph_GPIOC
#define BIN1  				  GPIO_Pin_4  //PC4
#define BIN2  				  GPIO_Pin_5   //PC5
		                      
//底盘电机3GPIO口		      
#define MotorC_PWM       	  GPIO_Pin_8  //PC8   T8C3  
					          
#define MotorC_GPIO      	  GPIOC
#define MotorC_RCC       	  RCC_APB2Periph_GPIOC
#define CIN1  				  GPIO_Pin_0  //PC0
#define CIN2  				  GPIO_Pin_1  //PC1
		                      
//底盘电机4GPIO口		      
#define MotorD_PWM       	  GPIO_Pin_9 	//PC9   T8C4
		                      
#define MotorD_GPIO      	  GPIOA
#define MotorD_RCC       	  RCC_APB2Periph_GPIOA
#define DIN1  				  GPIO_Pin_10 //PA10
#define DIN2  				  GPIO_Pin_12 //PA12



void PWM_Init(void);
void PWM_SetCompareA(uint16_t Compare);
void PWM_SetCompareB(uint16_t Compare);
void PWM_SetCompareC(uint16_t Compare);
void PWM_SetCompareD(uint16_t Compare);


#endif
