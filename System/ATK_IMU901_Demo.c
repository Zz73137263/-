///**
// * @platform	keil5ƽ̨STM32F103C8T6�ͺŵ�Ƭ��
// * @mainpage	������ѧԺʮ�ڻ�����������R1��������Ƭ��(�ͺ�F103RCT6)
// * @author		ɣ��
// * @date		2025��4��11��
// */


//#include <stdint.h>
//#include "ATK_IMU901_API.h"
//#include "OLED_API.h"
//#include "Delay_API_z.h"


//void ATK_IMU901_Demo(void)
//{
//	OLED_Init();
//	ATK_IMU901_Init();

//	ATK_IMU901_DataTypeDef* ATK_IMU901_Data;
//	ATK_IMU901_Data = ATK_IMU901_GetPoint_Data();

//	while (1)
//	{
//		ATK_IMU901_ReadData();

//		OLED_ShowString(1, 1, "123");

//		OLED_Show_s32(2, 1, (int32_t)(ATK_IMU901_Data->Roll * 100), 6);
//		OLED_Show_s32(2, 10, (int32_t)(ATK_IMU901_Data->Pitch * 100), 6);
//		OLED_Show_s32(3, 1, (int32_t)(ATK_IMU901_Data->Yaw * 100), 6);
//		OLED_Show_s32(3, 10, (int32_t)(ATK_IMU901_Data->AccX * 100), 6);
//		OLED_Show_s32(4, 1, (int32_t)(ATK_IMU901_Data->AccY * 100), 6);
//		OLED_Show_s32(4, 10, (int32_t)(ATK_IMU901_Data->AccZ * 100), 6);

//		Delay_ms(10);
//	}
//}
