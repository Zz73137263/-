
#include "stm32f10x.h"                  // Device header


#ifndef __CONTROL_H
#define __CONTROL_H


/*       ½á ¹¹ Ìå ¶¨ Òå      */

// µç»úÄ¿±êÖµ£¨ËÙ¶È µçÁ÷£©
typedef struct {
    int16_t speed_set;      //Ä¿±ê×ªËÙ£¨RPM£©r/min
    uint16_t current_set;   // Ä¿±êµçÁ÷(PWMÕ¼¿Õ±È)
	float pid_speed;
} MOTOR_SET;

// µçÁ÷·´À¡Öµ£
typedef struct {
    int16_t speed_fdb;      // Êµ¼Ê×ªËÙ(RPM)r/min
    int16_t coder_fdb;      // ±àÂëÆ÷Âö³åÊı
    uint16_t current_fdb;   // Êµ¼ÊµçÁ÷
} MOTOR_FDB;

// µç»úGPIOÅäÖÃ(¿ØÖÆ×ªÏò)
typedef struct {
    GPIO_TypeDef *gpio;     // GPIO¶Ë¿Ú(ÈçGPIOA)
    uint16_t in1;           //·½ÏòÒı½Å1(ÈçGPIO_Pin_0)
    uint16_t in2;           //·½ÏòÒı½Å2(ÈçGPIO_Pin_1)
} MOTOR_GPIO;

// µç»ú×éÅäÖÃ(4¸öµç»ú)
typedef struct {
    MOTOR_SET   motor_set[4];   // 4¸öµç»úµÄÄ¿±êÖµ
    MOTOR_FDB   motor_fdb[4];   // 4¸öµç»úµÄ·´À¡Öµ
    MOTOR_GPIO  motor_gpio[4];  // 4¸öµç»úGPIOÅäÖÃ
} MOTOR_T;

// µ×ÅÌÈ«¾Ö²ÎÊı
typedef struct {
    MOTOR_T motor;               // µç»ú×éÅäÖÃ
    float chassisVx;             // µ×ÅÌxÖáÏßËÙ¶È(mm/min)
    float chassisVy;             // µ×ÅÌyÖáÏßËÙ¶È(mm/min)
    float chassisOmega;          // µ×ÅÌĞı×ª½ÇËÙ¶È(rad/s)
    float maxOmega;              // ×î´óĞı×ª½ÇËÙ¶È
    float maxRpm_Left[4];
    float maxRpm_Right[4];
    float maxVx;                 // µ×ÅÌxÖá×î´óÏßËÙ¶È
    float maxVy;                 // µ×ÅÌYÖá×î´óÏßËÙ¶È
    float pidMode;               // PIDÄ£Ê½(ÔöÁ¿Ê½/Î»ÖÃÊ½)
    int8_t gear;                 // µµÎ»(1/2/3)
    float speedtap[3];           // µµÎ»ËÙ¶È±ÈÀı(0.5, 0.75, 1)
    float chassisOmega_fdb;      // ÍÓÂİÒÇ·´À¡µÄ½ÇËÙ¶È£¨ÓÃÓÚ¾ÀÆ«£©
} ChassisMotor_t;

extern ChassisMotor_t ChassisMotor;

/*          ºê ¶¨ Òå         */

#define timeHz    100          //10ms, ²ÉÑùÆµÂÊ
#define NULL    0
#define Wheel_R 30.0f       //ÂÖ×Ó°ë¾¶
#define PI      3.1415926f  //PI
#define Motor_i 30.0f       //¼õËÙ±È
#define NPN     13.0f       //¼õËÙºóÊä³öÖáµÄÏßËÙ
#define T   100             //±àÂëÆ÷arr
#define r   188.14  		//°ë¾¶  
#define MotorMAXspeed   56520 //ÏßËÙ¶È
#define MAXOmega        200.0f		
#define MAXVx           79000.4  //mm/min
#define MAXVy           79000.4
#define K              1 / (2 * PI * Wheel_R)          //µ×ÅÌ½âËã×ªËÙÏµÊı 188.4

#define redclose    GPIO_Pin_0		//³£Ì¬¸ß£¬ºìµÆĞ¡ÓÚ80mm¸øµÍ£¬ÂÌµÆ»Ø¸ß
#define QR_Code1	GPIO_Pin_1
#define QR_Code2    GPIO_Pin_2



void ALL_Init(void);       
void Chassis_Move(float x,float y,float t);
void ChassisCalculate(float Vx, float Vy,  ChassisMotor_t *speedcalc);
void Motor_Control(int8_t current_1,int8_t current_2,int8_t current_3,int8_t current_4);

#endif
