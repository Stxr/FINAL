#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H
/*
	
	id		电机初始值   量程
	
	1                                  374  3ml     
	
	2				150				 400             351  8ml
	
	3				100				 350             365最低速度    420完全压死
	
	4				100				 350             315             380
*/
#include "sys.h"
#include "delay.h"
#include "GUI.h"
#include "24cxx.h"
#include "includes.h"
#define STEPMOTOR_OUT 1
#define STEPMOTOR_IN 0
#define STEPMOTOR_MAX  500
#define STEPMOTOR_MIN  280
#define stepMotor_dir1 PFout(13)
#define stepMotor_step1 PFout(11)
#define stepMotor_enable1 PFout(14)

#define stepMotor_dir2 PDout(11)
#define stepMotor_step2 PDout(12)
#define stepMotor_enable2 PDout(13)

#define stepMotor_dir3 PGout(2)
#define stepMotor_step3 PGout(3)
#define stepMotor_enable3 PGout(4)

#define stepMotor_dir4 PGout(5)
#define stepMotor_step4 PGout(6)
#define stepMotor_enable4 PDout(7)
void stepMotor_Init(void);
void stepMotor_Run(u8 id,u8 dir,int speed);//序号，转动方向，速度 速度越小越快，5ms为一个单位  一次前进0.03m
void stepMotor_Distance(u8 id,int speed,int distance);//distance (0.01mm) 精度+-0.05mm
void stepMotor_Reset(u8 id); //电机复位
int stepMotor_Read(u8 id);
#endif
