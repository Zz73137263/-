#ifndef __PS2_def_z_h
#define __PS2_def_z_h

#include "stm32f10x.h"                  // Device header
#include "Delay.h"


// GPIO口初始化
#define GPIO_Speed_x			GPIO_Speed_50MHz

#define RCC_MISO				RCC_APB2Periph_GPIOB			// MISO
#define GPIOx_MISO				GPIOB
#define GPIO_Pinx_MISO			GPIO_Pin_14

#define RCC_MOSI				RCC_APB2Periph_GPIOB			// MOSI
#define GPIOx_MOSI				GPIOB
#define GPIO_Pinx_MOSI			GPIO_Pin_15

#define RCC_CS					RCC_APB2Periph_GPIOB			// CS
#define GPIOx_CS				GPIOB
#define GPIO_Pinx_CS			GPIO_Pin_12

#define RCC_SCK					RCC_APB2Periph_GPIOB			// SCK，即CLK
#define GPIOx_SCK				GPIOB
#define GPIO_Pinx_SCK			GPIO_Pin_13

// GPIO口电平设置
#define DI				(GPIO_ReadInputDataBit(GPIOx_MISO, GPIO_Pinx_MISO))				// MISO

#define DO_H			(GPIO_WriteBit(GPIOx_MOSI, GPIO_Pinx_MOSI, (BitAction)1))		// MOSI
#define DO_L			(GPIO_WriteBit(GPIOx_MOSI, GPIO_Pinx_MOSI, (BitAction)0))

#define CS_H			(GPIO_WriteBit(GPIOx_CS, GPIO_Pinx_CS, (BitAction)1))		// CS
#define CS_L			(GPIO_WriteBit(GPIOx_CS, GPIO_Pinx_CS, (BitAction)0))

#define CLK_H			(GPIO_WriteBit(GPIOx_SCK, GPIO_Pinx_SCK, (BitAction)1))		// SCK，即CLK
#define CLK_L			(GPIO_WriteBit(GPIOx_SCK, GPIO_Pinx_SCK, (BitAction)0))

// SPI通信速度降低
#define SPI_SpeedDelay		Delay_us(10)		// 我也不知道为什么是50us，20KHz，抄的里面就是这么写的


#endif
