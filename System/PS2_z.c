// 采用软件翻转GPIO口电平实现SPI通讯
// 使用手柄的“红灯模式”

#include "stm32f10x.h"                  // Device header
#include "PS2_def_z.h"
#include "PS2_typ_z.h"
#include "PS2_func_z.h"

static u8 SPI_SwapByte(u8 ByteSend);

// 手柄接口初始化
void PS2_Init(void)
{
	// 使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_MISO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_MOSI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_SCK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_CS, ENABLE);

	// 初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_x;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_MISO;			// MISO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// 配置上拉输入模式
	GPIO_Init(GPIOx_MISO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_MOSI;			// MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// 配置推挽输出模式
	GPIO_Init(GPIOx_MOSI, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_SCK;			// SCK，即CLK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// 配置推挽输出模式
	GPIO_Init(GPIOx_SCK, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_CS;				// CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// 配置推挽输出模式
	GPIO_Init(GPIOx_CS, &GPIO_InitStructure);

	// 设置GPIO初始状态
	DO_L;
	CLK_H;
	CS_H;
}

/**
  * @brief  读取手柄数据
  * @param  无
  * @retval PS2_DataTypeDef 类型结构体的指针
  */
PS2_DataTypeDef* PS2_ReadData(void)
{
	static PS2_DataTypeDef PS2_Data;
	u8 tem = 0x00;

	// 手柄数据读取
	CS_L;		// 拉低CS，开始时序

	// 第1个字节
	SPI_SwapByte(0x01);		// 0x01 和 0x42 是手柄命令，详见手柄使用说明书
	
	// 第2个字节
	PS2_Data.PS2_ID = SPI_SwapByte(0x42);		// 0x01 和 0x42 是手柄命令，详见手柄使用说明书

	// 第3个字节
	SPI_SwapByte(0x00);		// 没测试过传入字节的功能

	// 第4个字节
	tem = SPI_SwapByte(0x00);		// 转入数据用于控制右侧的小震动电机，0x00关，其他值为开，没测试过，不包对

	PS2_Data.PS2_SELECT		=	tem & 0x01;
	PS2_Data.PS2_L3			=	(tem >> 1) & 0x01;
	PS2_Data.PS2_R3			=	(tem >> 2) & 0x01;
	PS2_Data.PS2_START		=	(tem >> 3) & 0x01;
	PS2_Data.PS2_UP			=	(tem >> 4) & 0x01;
	PS2_Data.PS2_RIGHT		=	(tem >> 5) & 0x01;
	PS2_Data.PS2_DOWN		=	(tem >> 6) & 0x01;
	PS2_Data.PS2_LEFT		=	(tem >> 7) & 0x01;

	// 第5个字节
	tem = SPI_SwapByte(0x00);		// 转入数据用于控制左侧的大震动电机，0x40~0xFF电机开，值越大，电机转动越快，震动越明显，没测试过，不包对

	PS2_Data.PS2_L2 = tem & 0x01;
	PS2_Data.PS2_R2 = (tem >> 1) & 0x01;
	PS2_Data.PS2_L1 = (tem >> 2) & 0x01;
	PS2_Data.PS2_R1 = (tem >> 3) & 0x01;
	PS2_Data.PS2_Triangle = (tem >> 4) & 0x01;
	PS2_Data.PS2_Circle = (tem >> 5) & 0x01;
	PS2_Data.PS2_Fork = (tem >> 6) & 0x01;
	PS2_Data.PS2_Rectangle = (tem >> 7) & 0x01;

	// 第6个字节
	PS2_Data.PS2_PS2_RX = SPI_SwapByte(0x00);		// 随意传入字节，用于交换数据

	// 第7个字节
	PS2_Data.PS2_PS2_RY = SPI_SwapByte(0x00);		// 随意传入字节，用于交换数据

	// 第8个字节
	PS2_Data.PS2_PS2_LX = SPI_SwapByte(0x00);		// 随意传入字节，用于交换数据

	// 第9个字节
	PS2_Data.PS2_PS2_LY = SPI_SwapByte(0x00);		// 随意传入字节，用于交换数据

	CS_H;		// 拉高CS，结束时序


	// 判断手柄模式
	if (PS2_Data.PS2_ID == 0x41)
		PS2_Data.PS2_Mode = 0;				// 摇杆数字量模式
	else
		PS2_Data.PS2_Mode = 1;				// 摇杆模拟量模式

	return &PS2_Data;
}

// SPI协议通信进行单字节交换
// 注意里面并未包含“开始时序”和“结束时序”信号
// 返回值：一个字节
static u8 SPI_SwapByte(u8 ByteSend)
{
	u8 ByteReceive = 0x00;

	for (u16 ref = 0x01; ref<0x100; ref <<= 1)
	{
		if (ref & ByteSend)			// 高读低写
			DO_H;
		else
			DO_L;

		CLK_L;
		SPI_SpeedDelay;				// PS2手柄不能以过高的频率通信，需要人为降低通信速度

		if (DI)
			ByteReceive |= ref;

		CLK_H;
		SPI_SpeedDelay;				// PS2手柄不能以过高的频率通信，需要人为降低通信速度
	}

	return ByteReceive;
}
