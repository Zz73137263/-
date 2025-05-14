#include "MPU6050_test.h"
#include "Serial.h"
#include "MPU6050.h"

void MPU6050_test()
{
	Serial_Init();
	MPU6050_Init();
	
	while(1)
	{
		MPU6050_UpDate();
		float ax = MPU6050_GetAx;
		float ay = MPU6050_GetAy;
		float az = MPU6050_GetAz;
		
		float gx = MPU6050_GetGx;
		float gy = MPU6050_GetGy;
		float gz = MPU6050_GetGz;
	}


}
