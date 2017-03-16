#include "step_motor.h"
void stepMotor_Init(void){
	 GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_7);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
}
int stepMotor_Run(int id,int dir,int speed){
	switch (id) {
		case 1:
			stepMotor_dir1=dir;
			stepMotor_step1=1;
			GUI_Delay(speed);
			stepMotor_step1=0;
			GUI_Delay(speed);
			break;
		case 2:
			stepMotor_dir2=dir;
			stepMotor_step2=1;
			GUI_Delay(speed);
			stepMotor_step2=0;
			GUI_Delay(speed);
			break;
		case 3:
			stepMotor_dir3=dir;
			stepMotor_step3=1;
			GUI_Delay(speed);
			stepMotor_step3=0;
			GUI_Delay(speed);
			break;
		case 4:
			stepMotor_dir4=dir;
			stepMotor_step4=1;
			GUI_Delay(speed);
			stepMotor_step4=0;
			GUI_Delay(speed);
			break;
		default:
			break;
	}
	return 0;
}
void stepMotor_Distance(int id,int dir,int speed,int distance){ 
	int i=0;
	for(i=0;i<distance/3;i++){
		stepMotor_Run(id,dir,speed);
	}
}
int stepMotor_Reset(int id){
	stepMotor_Distance(id,STEPMOTOR_IN,5,1090); //先复位为最短
	return 0;
}
