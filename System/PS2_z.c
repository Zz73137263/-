// ���������תGPIO�ڵ�ƽʵ��SPIͨѶ
// ʹ���ֱ��ġ����ģʽ��

#include "stm32f10x.h"                  // Device header
#include "PS2_def_z.h"
#include "PS2_typ_z.h"
#include "PS2_func_z.h"

static u8 SPI_SwapByte(u8 ByteSend);

// �ֱ��ӿڳ�ʼ��
void PS2_Init(void)
{
	// ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_MISO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_MOSI, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_SCK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_CS, ENABLE);

	// ��ʼ��GPIO��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_x;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_MISO;			// MISO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// ������������ģʽ
	GPIO_Init(GPIOx_MISO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_MOSI;			// MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �����������ģʽ
	GPIO_Init(GPIOx_MOSI, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_SCK;			// SCK����CLK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �����������ģʽ
	GPIO_Init(GPIOx_SCK, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_CS;				// CS
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �����������ģʽ
	GPIO_Init(GPIOx_CS, &GPIO_InitStructure);

	// ����GPIO��ʼ״̬
	DO_L;
	CLK_H;
	CS_H;
}

/**
  * @brief  ��ȡ�ֱ�����
  * @param  ��
  * @retval PS2_DataTypeDef ���ͽṹ���ָ��
  */
PS2_DataTypeDef* PS2_ReadData(void)
{
	static PS2_DataTypeDef PS2_Data;
	u8 tem = 0x00;

	// �ֱ����ݶ�ȡ
	CS_L;		// ����CS����ʼʱ��

	// ��1���ֽ�
	SPI_SwapByte(0x01);		// 0x01 �� 0x42 ���ֱ��������ֱ�ʹ��˵����
	
	// ��2���ֽ�
	PS2_Data.PS2_ID = SPI_SwapByte(0x42);		// 0x01 �� 0x42 ���ֱ��������ֱ�ʹ��˵����

	// ��3���ֽ�
	SPI_SwapByte(0x00);		// û���Թ������ֽڵĹ���

	// ��4���ֽ�
	tem = SPI_SwapByte(0x00);		// ת���������ڿ����Ҳ��С�𶯵����0x00�أ�����ֵΪ����û���Թ���������

	PS2_Data.PS2_SELECT		=	tem & 0x01;
	PS2_Data.PS2_L3			=	(tem >> 1) & 0x01;
	PS2_Data.PS2_R3			=	(tem >> 2) & 0x01;
	PS2_Data.PS2_START		=	(tem >> 3) & 0x01;
	PS2_Data.PS2_UP			=	(tem >> 4) & 0x01;
	PS2_Data.PS2_RIGHT		=	(tem >> 5) & 0x01;
	PS2_Data.PS2_DOWN		=	(tem >> 6) & 0x01;
	PS2_Data.PS2_LEFT		=	(tem >> 7) & 0x01;

	// ��5���ֽ�
	tem = SPI_SwapByte(0x00);		// ת���������ڿ������Ĵ��𶯵����0x40~0xFF�������ֵԽ�󣬵��ת��Խ�죬��Խ���ԣ�û���Թ���������

	PS2_Data.PS2_L2 = tem & 0x01;
	PS2_Data.PS2_R2 = (tem >> 1) & 0x01;
	PS2_Data.PS2_L1 = (tem >> 2) & 0x01;
	PS2_Data.PS2_R1 = (tem >> 3) & 0x01;
	PS2_Data.PS2_Triangle = (tem >> 4) & 0x01;
	PS2_Data.PS2_Circle = (tem >> 5) & 0x01;
	PS2_Data.PS2_Fork = (tem >> 6) & 0x01;
	PS2_Data.PS2_Rectangle = (tem >> 7) & 0x01;

	// ��6���ֽ�
	PS2_Data.PS2_PS2_RX = SPI_SwapByte(0x00);		// ���⴫���ֽڣ����ڽ�������

	// ��7���ֽ�
	PS2_Data.PS2_PS2_RY = SPI_SwapByte(0x00);		// ���⴫���ֽڣ����ڽ�������

	// ��8���ֽ�
	PS2_Data.PS2_PS2_LX = SPI_SwapByte(0x00);		// ���⴫���ֽڣ����ڽ�������

	// ��9���ֽ�
	PS2_Data.PS2_PS2_LY = SPI_SwapByte(0x00);		// ���⴫���ֽڣ����ڽ�������

	CS_H;		// ����CS������ʱ��


	// �ж��ֱ�ģʽ
	if (PS2_Data.PS2_ID == 0x41)
		PS2_Data.PS2_Mode = 0;				// ҡ��������ģʽ
	else
		PS2_Data.PS2_Mode = 1;				// ҡ��ģ����ģʽ

	return &PS2_Data;
}

// SPIЭ��ͨ�Ž��е��ֽڽ���
// ע�����沢δ��������ʼʱ�򡱺͡�����ʱ���ź�
// ����ֵ��һ���ֽ�
static u8 SPI_SwapByte(u8 ByteSend)
{
	u8 ByteReceive = 0x00;

	for (u16 ref = 0x01; ref<0x100; ref <<= 1)
	{
		if (ref & ByteSend)			// �߶���д
			DO_H;
		else
			DO_L;

		CLK_L;
		SPI_SpeedDelay;				// PS2�ֱ������Թ��ߵ�Ƶ��ͨ�ţ���Ҫ��Ϊ����ͨ���ٶ�

		if (DI)
			ByteReceive |= ref;

		CLK_H;
		SPI_SpeedDelay;				// PS2�ֱ������Թ��ߵ�Ƶ��ͨ�ţ���Ҫ��Ϊ����ͨ���ٶ�
	}

	return ByteReceive;
}
