#ifndef __PS2_typ_z_h
#define __PS2_typ_z_h

#include "stm32f10x.h"                  // Device header

/**
  * @brief  �洢��ȡ���ֱ����ݵĽṹ��
  */
typedef struct
{
	u8 PS2_ID;			// ����Ϊ0������Ϊ1
	u8 PS2_SELECT;		// ����Ϊ0������Ϊ1
	u8 PS2_L3;			// ����Ϊ0������Ϊ1
	u8 PS2_R3;			// ����Ϊ0������Ϊ1
	u8 PS2_START;		// ����Ϊ0������Ϊ1
	u8 PS2_UP;			// ����Ϊ0������Ϊ1
	u8 PS2_RIGHT;		// ����Ϊ0������Ϊ1
	u8 PS2_DOWN;		// ����Ϊ0������Ϊ1
	u8 PS2_LEFT;		// ����Ϊ0������Ϊ1
	u8 PS2_L2;			// ����Ϊ0������Ϊ1
	u8 PS2_R2;			// ����Ϊ0������Ϊ1
	u8 PS2_L1;			// ����Ϊ0������Ϊ1
	u8 PS2_R1;			// ����Ϊ0������Ϊ1
	u8 PS2_Triangle;	// ����Ϊ0������Ϊ1
	u8 PS2_Circle;		// ����Ϊ0������Ϊ1
	u8 PS2_Fork;		// ����Ϊ0������Ϊ1
	u8 PS2_Rectangle;	// ����Ϊ0������Ϊ1
	u8 PS2_PS2_RX;		// 0x00 = left , 0xFF = right
	u8 PS2_PS2_RY;		// 0x00 = up   , 0xFF = down
	u8 PS2_PS2_LX;		// 0x00 = left , 0xFF = right
	u8 PS2_PS2_LY;		// 0x00 = up   , 0xFF = down
	u8 PS2_Mode;		// ҡ��ģ����ģʽʱ��1��ҡ��������ģʽʱ��0
}PS2_DataTypeDef;

#endif
