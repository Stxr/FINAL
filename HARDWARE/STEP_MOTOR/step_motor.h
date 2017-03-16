#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H
#include "sys.h"
#include "delay.h"
#include "GUI.h"
#define STEPMOTOR_OUT 1
#define STEPMOTOR_IN 0
#define stepMotor_dir1 PFout(3)
#define stepMotor_step1 PFout(4)
#define stepMotor_enable1 PFout(5)

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
int stepMotor_Run(int id,int dir,int speed);//��ţ�ת�������ٶ� �ٶ�ԽСԽ�죬5msΪһ����λ  һ��ǰ��0.03m
void stepMotor_Distance(int id,int dir,int speed,int distance);//distance (0.01mm) ����+-0.05mm
int stepMotor_Reset(int id); //�����λ
#endif 
