
#include "stm32f10x.h"                  // Device header


#ifndef __CONTROL_H
#define __CONTROL_H


/*       结 构 体 定 义      */

// 电机目标值（速度 电流）
typedef struct {
    int16_t speed_set;      //目标转速（RPM）r/min
    uint16_t current_set;   // 目标电流(PWM占空比)
	float pid_speed;
} MOTOR_SET;

// 电流反馈值�
typedef struct {
    int16_t speed_fdb;      // 实际转速(RPM)r/min
    int16_t coder_fdb;      // 编码器脉冲数
    uint16_t current_fdb;   // 实际电流
} MOTOR_FDB;

// 电机GPIO配置(控制转向)
typedef struct {
    GPIO_TypeDef *gpio;     // GPIO端口(如GPIOA)
    uint16_t in1;           //方向引脚1(如GPIO_Pin_0)
    uint16_t in2;           //方向引脚2(如GPIO_Pin_1)
} MOTOR_GPIO;

// 电机组配置(4个电机)
typedef struct {
    MOTOR_SET   motor_set[4];   // 4个电机的目标值
    MOTOR_FDB   motor_fdb[4];   // 4个电机的反馈值
    MOTOR_GPIO  motor_gpio[4];  // 4个电机GPIO配置
} MOTOR_T;

// 底盘全局参数
typedef struct {
    MOTOR_T motor;               // 电机组配置
    float chassisVx;             // 底盘x轴线速度(mm/min)
    float chassisVy;             // 底盘y轴线速度(mm/min)
    float chassisOmega;          // 底盘旋转角速度(rad/s)
    float maxOmega;              // 最大旋转角速度
    float maxRpm_Left[4];
    float maxRpm_Right[4];
    float maxVx;                 // 底盘x轴最大线速度
    float maxVy;                 // 底盘Y轴最大线速度
    float pidMode;               // PID模式(增量式/位置式)
    int8_t gear;                 // 档位(1/2/3)
    float speedtap[3];           // 档位速度比例(0.5, 0.75, 1)
    float chassisOmega_fdb;      // 陀螺仪反馈的角速度（用于纠偏）
} ChassisMotor_t;

extern ChassisMotor_t ChassisMotor;

/*          宏 定 义         */

#define timeHz    100          //10ms, 采样频率
#define NULL    0
#define Wheel_R 30.0f       //轮子半径
#define PI      3.1415926f  //PI
#define Motor_i 30.0f       //减速比
#define NPN     13.0f       //减速后输出轴的线速
#define T   100             //编码器arr
#define r   188.14  		//半径  
#define MotorMAXspeed   56520 //线速度
#define MAXOmega        200.0f		
#define MAXVx           79000.4  //mm/min
#define MAXVy           79000.4
#define K              1 / (2 * PI * Wheel_R)          //底盘解算转速系数 188.4

#define redclose    GPIO_Pin_2		//常态高，红灯小于80mm给低，绿灯回高
#define QR_Code1	GPIO_Pin_3
#define QR_Code2    GPIO_Pin_4
#define QR_Code3	GPIO_Pin_5
#define QR_Code4    GPIO_Pin_6


void ALL_Init(void);       
void Chassis_Move(float x,float y,float t);
void ChassisCalculate(float Vx, float Vy,  ChassisMotor_t *speedcalc);
void Motor_Control(int8_t current_1,int8_t current_2,int8_t current_3,int8_t current_4);
void Chassis_test(void);
void Chassis_Task(void);

#endif
