#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H
#include "sys.h"
#include "delay.h"
#include "GUI.h"
#define STEPMOTOR_OUT 1
#define STEPMOTOR_IN 0
#define stepMotor_dir1 PBout(3)
#define stepMotor_step1 PBout(4)
#define stepMotor_enable1 PBout(5)

#define stepMotor_dir2 PBout(8)
#define stepMotor_step2 PBout(9)
#define stepMotor_enable2 PEout(0)

#define stepMotor_dir3 PGout(3)
#define stepMotor_step3 PGout(4)
#define stepMotor_enable3 PGout(5)

#define stepMotor_dir4 PGout(6)
#define stepMotor_step4 PGout(7)
#define stepMotor_enable4 PGout(8)
void stepMotor_Init(void);
int stepMotor_Run(int id,int dir,int speed);//序号，转动方向，速度 速度越小越快，5ms为一个单位  一次前进0.03m
void stepMotor_Distance(int id,int dir,int speed,int distance);//distance (0.01mm) 精度+-0.05mm
int stepMotor_Reset(int id); //电机复位
#endif 
