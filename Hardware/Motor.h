#ifndef __MOTOR_H
#define __MOTOR_H

void MotorA_Init(void);
void MotorB_Init(void);
void MotorC_Init(void);
void MotorD_Init(void);
void Motor_Init(void);
void MotorA_SetPWM(int8_t PWM);
void MotorB_SetPWM(int8_t PWM);
void MotorC_SetPWM(int8_t PWM);
void MotorD_SetPWM(int8_t PWM);

#endif
