#ifndef __PS2_typ_z_h
#define __PS2_typ_z_h

#include "stm32f10x.h"                  // Device header

/**
  * @brief  存储读取的手柄数据的结构体
  */
typedef struct
{
	u8 PS2_ID;			// 按下为0，其他为1
	u8 PS2_SELECT;		// 按下为0，其他为1
	u8 PS2_L3;			// 按下为0，其他为1
	u8 PS2_R3;			// 按下为0，其他为1
	u8 PS2_START;		// 按下为0，其他为1
	u8 PS2_UP;			// 按下为0，其他为1
	u8 PS2_RIGHT;		// 按下为0，其他为1
	u8 PS2_DOWN;		// 按下为0，其他为1
	u8 PS2_LEFT;		// 按下为0，其他为1
	u8 PS2_L2;			// 按下为0，其他为1
	u8 PS2_R2;			// 按下为0，其他为1
	u8 PS2_L1;			// 按下为0，其他为1
	u8 PS2_R1;			// 按下为0，其他为1
	u8 PS2_Triangle;	// 按下为0，其他为1
	u8 PS2_Circle;		// 按下为0，其他为1
	u8 PS2_Fork;		// 按下为0，其他为1
	u8 PS2_Rectangle;	// 按下为0，其他为1
	u8 PS2_PS2_RX;		// 0x00 = left , 0xFF = right
	u8 PS2_PS2_RY;		// 0x00 = up   , 0xFF = down
	u8 PS2_PS2_LX;		// 0x00 = left , 0xFF = right
	u8 PS2_PS2_LY;		// 0x00 = up   , 0xFF = down
	u8 PS2_Mode;		// 摇杆模拟量模式时是1，摇杆数字量模式时是0
}PS2_DataTypeDef;

#endif
