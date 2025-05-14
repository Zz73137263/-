/**
 * @platform	keil5ƽ̨STM32F103C8T6�ͺŵ�Ƭ��
 * @mainpage	������ѧԺʮ�ڻ�����������R1��������Ƭ��(�ͺ�F103RCT6)
 * @author		ɣ��
 * @date		2025��4��11��
 */


// ����Ӳ��USART���д���ͨѶ
// ʹ��DMA��������ת�ˣ���Լ������Դ
// ֻд����̬�Ǻ������ǡ����ٶȼƵ����ݶ�ȡ
// ��ϸ��������ο������ļ�Ŀ¼�ı���ͼƬ�ļ�����ͼƬ


#include <stdint.h>
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "ATK_IMU901_API.h"


#define ATK_IMU901_bound		921600


// ���������ǣ���λ����/s���ͼ��ٶȼƣ���λ��G��������
#define AccelerationRange		2
#define GyroscopeRange 			1000


// USRTͨѶ���һ���Խ����ֽ���
#define USART_REC_LEN		80			// USART_REC_LEN ��ȫ�ƿ����� USART Receive Length
										// ���ݳ��ȣ�֡��ʽ�������λ+֡��ʽ�������λ����
										// 1. ��̬�� 			6+5���ֽ�
										// 2. ��Ԫ�� 			8+5���ֽ�
										// 3. �����Ǻͼ��ٶȼ� 	12+5���ֽ�
										// 4. ������			8+5���ֽ�			�ϱ�Ƶ�ʹ̶�20Hz
										// 5. ��ѹ��			10+5���ֽ�			�ϱ�Ƶ�ʹ̶�20Hz
										// 6. �˿�״̬			8+5���ֽ�


/* ������������������������������������������������������������������������*/
// GPIO�ڳ�ʼ��
#define GPIO_Speed_x		GPIO_Speed_50MHz

#define RCC_TX				RCC_APB2Periph_GPIOC		// TX
#define GPIOx_TX			GPIOC
#define GPIO_Pinx_TX		GPIO_Pin_10

#define RCC_RX				RCC_APB2Periph_GPIOC		// RX
#define GPIOx_RX			GPIOC
#define GPIO_Pinx_RX		GPIO_Pin_11
/* ������������������������������������������������*/


/* ������������������������������������������������������������������������*/
// UART�ڳ�ʼ��
// UART��ѡ������Ϊ1���ر�Ϊ0���������һ����
// UART5û��DMAת�˹��ܣ����������ֹʹ��UART5��
#define USART_1				0			// ������ USARTx �궨������
#define USART_2				0			// ������ USARTx �궨������
#define USART_3				0			// ������ USARTx �궨������
#define UART_4				1			// ������ UARTx �궨������
//#define UART_5				0			// ������ UARTx �궨������

// UART���շ�ģʽѡ��ѡ�������е�һ����Tx��ֻ��ģʽ��Rx��ֻ��ģʽ��TxAndRx���շ�ģʽ���������һ����
#define	UART_Mode_Tx				0	// ������ USART_Mode_Tx �궨������
#define	UART_Mode_Rx				1	// ������ USART_Mode_Rx �궨������
#define	UART_Mode_TxAndRx			0
/* ������������������������������������������������*/


static ATK_IMU901_DataTypeDef ATK_IMU901_Data;


/* ������������������������������������������������������������������������*/
// UART���ж�
#if USART_1
//#define IRQn_USARTx 			USART1_IRQn
#define RCC_UART 				RCC_APB2Periph_USART1
#define USART_x 				USART1
//#define USARTx_IRQHandler 		USART1_IRQHandler
#elif USART_2
//#define IRQn_USARTx 			USART2_IRQn
#define RCC_UART 				RCC_APB1Periph_USART2
#define USART_x 				USART2
//#define USARTx_IRQHandler 		USART2_IRQHandler
#elif USART_3
//#define IRQn_USARTx 			USART3_IRQn
#define RCC_UART 				RCC_APB1Periph_USART3
#define USART_x 				USART3
//#define USARTx_IRQHandler 		USART3_IRQHandler
#elif UART_4
//#define IRQn_USARTx 			UART4_IRQn
#define RCC_UART 				RCC_APB1Periph_UART4
#define USART_x 				UART4
//#define USARTx_IRQHandler 		UART4_IRQHandler
//#elif UART_5
////#define IRQn_USARTx 			UART5_IRQn
//#define RCC_UART 				RCC_APB1Periph_UART5
//#define USART_x 				UART5
////#define USARTx_IRQHandler 		UART5_IRQHandler
#endif

// UARTģʽ�ж�
#if			UART_Mode_Tx
#define		UART_Mode_x		USART_Mode_Tx
#elif		UART_Mode_Rx
#define		UART_Mode_x		USART_Mode_Rx
#elif		UART_Mode_TxAndRx
#define		UART_Mode_x		(USART_Mode_Rx | USART_Mode_Tx)
#endif

// DMAͨ���ж�
	// RX
#if UART_Mode_Rx || UART_Mode_TxAndRx
#if USART_1
#define RX_DMAx_Channely	DMA1_Channel5
#elif USART_2
#define RX_DMAx_Channely	DMA1_Channel6
#elif USART_3
#define RX_DMAx_Channely	DMA1_Channel3
#elif UART_4
#define RX_DMAx_Channely	DMA2_Channel3
#endif
#endif
	// TX
#if UART_Mode_Tx || UART_Mode_TxAndRx
#if USART_1
#define TX_DMAx_Channely	DMA1_Channel4
#elif USART_2
#define TX_DMAx_Channely	DMA1_Channel7
#elif USART_3
#define TX_DMAx_Channely	DMA1_Channel2
#elif UART_4
#define TX_DMAx_Channely	DMA2_Channel5
#endif
#endif


static vu8 ReceiveDataString[USART_REC_LEN];


void ATK_IMU901_Init()
{
	// GPIO������
	// ����GPIOʱ��
#if UART_Mode_Tx || UART_Mode_TxAndRx
	RCC_APB2PeriphClockCmd(RCC_TX, ENABLE);
#endif
#if UART_Mode_Rx || UART_Mode_TxAndRx
	RCC_APB2PeriphClockCmd(RCC_RX, ENABLE);
#endif

	// GPIO��ʼ��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_x;

#if UART_Mode_Tx || UART_Mode_TxAndRx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_TX;				// TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// ���ø����������ģʽ
	GPIO_Init(GPIOx_TX, &GPIO_InitStructure);
#endif

#if UART_Mode_Rx || UART_Mode_TxAndRx
	GPIO_InitStructure.GPIO_Pin = GPIO_Pinx_RX;				// RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	// ���ø�������ģʽ
	GPIO_Init(GPIOx_RX, &GPIO_InitStructure);
#endif

	// ����GPIO��ʼ״̬
//#if UART_Mode_Tx || UART_Mode_TxAndRx
//	TX_H;
//#endif

	// USART������
		// ����USARTʱ��
#if USART_1
	RCC_APB2PeriphClockCmd(RCC_UART, ENABLE);
#elif USART_2 || USART_3 || UART_4 || UART_5
	RCC_APB1PeriphClockCmd(RCC_UART, ENABLE);
#endif

	// USART��ʼ��
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = ATK_IMU901_bound;							// ���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;						// �ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;							// һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;								// ����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	// ��Ӳ������������
	USART_InitStructure.USART_Mode = UART_Mode_x;									// �ա������շ�ģʽѡ��
	USART_Init(USART_x, &USART_InitStructure);

	// ʹ��
	USART_Cmd(USART_x, ENABLE);								// ʹ�ܴ���

	// DMA����
		// ����DMAʱ��
#if UART_4
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);		// ����DMA2��ʱ��
#elif USART_1 || USART_2 || USART_3
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		// ����DMA1��ʱ��
#endif

	// DMA��ʼ��
	DMA_InitTypeDef DMA_InitStructure;											// ����ṹ�����
	// TX
#if UART_Mode_Tx || UART_Mode_TxAndRx
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART_x->DR;			// �������ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		// �������ݿ�ȣ�ѡ���ֽ�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// �����ַ������ѡ��ʧ�ܣ�ʼ����USART��DR�Ĵ���ΪĿ�ĵ�
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)UART_TXData;				// �洢������ַ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;				// �洢�����ݿ�ȣ�ѡ���ֽڣ����������ݿ�ȶ�Ӧ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// �洢����ַ������ѡ��ʹ�ܣ�ÿ��ת�˺������Ƶ���һ��λ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;							// ���ݴ��䷽��ѡ���ɴ洢�������裬����ת���������ݼĴ���
	DMA_InitStructure.DMA_BufferSize = 0;										// ת�˵����ݴ�С��ת�˴�����
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;								// ģʽ��ѡ�񵥴�ģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// �洢�����洢����ѡ��ʧ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;						// ���ȼ���ѡ���е�
	DMA_Init(TX_DMAx_Channely, &DMA_InitStructure);
#endif

	// RX
#if UART_Mode_Rx || UART_Mode_TxAndRx
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART_x->DR;			// �������ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;		// �������ݿ�ȣ�ѡ���ֽ�
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			// �����ַ������ѡ��ʧ�ܣ�ʼ����USART��DR�Ĵ���ΪĿ�ĵ�
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ReceiveDataString;			// �洢������ַ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;				// �洢�����ݿ�ȣ�ѡ���ֽڣ����������ݿ�ȶ�Ӧ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;						// �洢����ַ������ѡ��ʹ�ܣ�ÿ��ת�˺������Ƶ���һ��λ��
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;							// ���ݴ��䷽��ѡ�������赽�洢�����������ݼĴ���ת������
	DMA_InitStructure.DMA_BufferSize = USART_REC_LEN;							// ת�˵����ݴ�С��ת�˴�����
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;								// ģʽ��ѡ��ѭ��ģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;								// �洢�����洢����ѡ��ʧ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;							// ���ȼ���ѡ���
	DMA_Init(RX_DMAx_Channely, &DMA_InitStructure);
#endif

	// DMAʹ��
		// TX
#if UART_Mode_Tx || UART_Mode_TxAndRx
	USART_DMACmd(USART_x, USART_DMAReq_Tx, ENABLE);			// ʹ��USART��TX��DMAת��
#endif

	// RX
#if UART_Mode_Rx || UART_Mode_TxAndRx
	DMA_Cmd(RX_DMAx_Channely, ENABLE);						// DMAʹ��
	USART_DMACmd(USART_x, USART_DMAReq_Rx, ENABLE);			// ʹ��USART��RX��DMAת��
#endif
}

//void USARTx_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART_x, USART_IT_RXNE) == SET)		// �ж��ж�
//	{
//		
//	}
//
//	USART_ClearFlag(USART_x, USART_IT_RXNE);					// ����жϱ�־λ
//}

ATK_IMU901_DataTypeDef* ATK_IMU901_GetPoint_Data(void)
{
	return &ATK_IMU901_Data;
}

/**
  * @brief  ��ȡATK_IMU901����
  * @param  ��
  * @retval ��
  */
void ATK_IMU901_ReadData(void)
{
	uint8_t SUM;

	//DMA_Cmd(RX_DMAx_Channely, DISABLE);						// DMA2��ͨ��3ʧ��
	//USART_DMACmd(USART2, USART_DMAReq_Rx, DISABLE);		// ʧ��USART��DMAת��

	for (uint8_t i1 = 0; i1 < (USART_REC_LEN - 20);)
	{
		SUM = 0;

		if (ReceiveDataString[i1++] == 0x55)							// �ж�ATK-IMU901��֡��ʽ�ĵ�1���ֽ�
		{
			if (ReceiveDataString[i1++] == 0x55);					// �ж�ATK-IMU901��֡��ʽ�ĵ�2���ֽ�
			{
				switch (ReceiveDataString[i1++])						// �ж�ATK-IMU901��֡��ʽ�ĵ�3���ֽ�
				{
				case 0x01:
					if (ReceiveDataString[i1++] == 6)				// �ж�ATK-IMU901��֡��ʽ�ĵ�4���ֽ�
					{
						SUM += 0x55 + 0x55 + 0x01 + 6;
						for (uint8_t j = 0; j < 6; j++)
							SUM += ReceiveDataString[i1 + j];

						if (SUM == ReceiveDataString[i1 + 6])		// �ж�ATK-IMU901��֡��ʽ��SUM�ֽ�
						{
							// ��ʼ����ATK-IMU901��֡��ʽ��DATA������
							uint8_t DataH, DataL;						// �������ݸ�8λ�͵�8λ�ı���

							// ��Roll
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.Roll = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * 180;

							// ��Pitch
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.Pitch = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * 180;

							// ��Yaw
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.Yaw = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * 180;

							// ����SUM�ֽڣ���Ϊ��ǰ�Ѿ������
							i1++;
						}
					}
					else
						i1 += 7;
					break;
				case 0x03:
					if (ReceiveDataString[i1++] == 12)				// �ж�ATK-IMU901��֡��ʽ�ĵ�4���ֽ�
					{
						SUM += 0x55 + 0x55 + 0x03 + 12;
						for (uint8_t j = 0; j < 12; j++)
							SUM += ReceiveDataString[i1 + j];

						if (SUM == ReceiveDataString[i1 + 12])		// �ж�ATK-IMU901��֡��ʽ��SUM�ֽ�
						{
							// ��ʼ����ATK-IMU901��֡��ʽ��DATA������
							uint8_t DataH, DataL;						// �������ݸ�8λ�͵�8λ�ı���

							// �����ٶȼ�X��
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.AccX = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * AccelerationRange;

							// �����ٶȼ�Y��
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.AccY = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * AccelerationRange;

							// �����ٶȼ�Z��
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.AccZ = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * AccelerationRange;

							// ��������X��
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.GyroX = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * GyroscopeRange;

							// ��������Y��
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.GyroY = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * GyroscopeRange;

							// ��������Z��
							DataL = ReceiveDataString[i1++];
							DataH = ReceiveDataString[i1++];
							ATK_IMU901_Data.GyroZ = (float)((int16_t)((DataH << 8) | DataL)) / 32768 * GyroscopeRange;

							// ����SUM�ֽڣ���Ϊ��ǰ�Ѿ������
							i1++;
						}
					}
					else
						i1 += 13;
					break;
				}
			}
		}
	}

	//DMA_Cmd(RX_DMAx_Channely, ENABLE);							// DMA2��ͨ��3ʹ��
	//USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);			// ʹ��USART��DMAת��
}

