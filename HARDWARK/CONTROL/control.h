#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
#define PI 3.14159265
int TIM1_UP_IRQHandler(void);  
void Get_Angle(u8 way);
float Angle_PID(void);
float Speed_PID(float Set_Speed);
float Position_PID(float Set_Position);
void Set_Pwm(void);
#endif
