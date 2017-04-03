#include "step_motor.h"
void stepMotor_Init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_11|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_11|GPIO_Pin_14);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_12|GPIO_Pin_7);

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOG,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);
	printf("stepInit:0X%0X\r\n",AT24CXX_ReadOneByte(0));//��ӡ��ʼ����Ϣ
	printf("stepmotor%d distance:%d\r\n",1,stepMotor_Read(1));
	printf("stepmotor%d distance:%d\r\n",2,stepMotor_Read(2));
	printf("stepmotor%d distance:%d\r\n",3,stepMotor_Read(3));
	printf("stepmotor%d distance:%d\r\n",4,stepMotor_Read(4));
	printf("stepMotor_Init OK!\r\n");
}
int stepMotor_Run(u8 id,u8 dir,int speed){
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
void stepMotor_Distance(u8 id,int speed,int distance){
	int i=0;
	u8 dir=0;
	i=stepMotor_Read(id);
	if(distance<0){ //�������������ԭ�������ϼ�
		dir=STEPMOTOR_IN;
		if(i+distance<STEPMOTOR_MIN){//���ʣ�µ�ֵ�ȼ�С��ֵ��
			distance=-i;//���ź���Ҫ
		}
	}else{//�����
		dir=STEPMOTOR_OUT;
		if(i+distance>STEPMOTOR_MAX){ //���������Χ��
			distance =STEPMOTOR_MAX-i;
		}
	}
	AT24CXX_WriteLenByte(id*2,i+distance,2); //16λ
	printf("stepInit:0X%0X\r\n",AT24CXX_ReadOneByte(0));//��ӡ��ʼ����Ϣ
	printf("stepmotor%d distance:%d\r\n",id,stepMotor_Read(id));
	for(i=0;i<abs(distance)/3;i++){
		stepMotor_Run(id,dir,speed);
	}
	
}
u8 stepMotor_Reset(u8 id){
	int i=0;
	i=AT24CXX_ReadOneByte(0);
	if((i&(0xf0|1<<(id-1)))==(0xf0|1<<(id-1))){ //���֮ǰ�Ѿ���ʼ���� ����λΪ1
		printf("�Ѿ���ʼ����\r\n");
		stepMotor_Distance(id,5,-STEPMOTOR_MAX); //
	}else{//��һ�γ�ʼ��
		printf("��һ�γ�ʼ��\r\n");
		AT24CXX_WriteOneByte(0,(i|0xf0)|1<<(id-1));//��ʼ�� ������λ��һλ��ʼ���Ͱ���һλ��һ
		for(i=0;i<333;i++){ //��λΪ0
			stepMotor_Run(id,STEPMOTOR_IN,5); 
		}
	for(i=0;i<abs(STEPMOTOR_MIN)/3;i++){ //��λ����Сֵ
		stepMotor_Run(id,STEPMOTOR_OUT,5);
	}
		AT24CXX_WriteLenByte(id*2,STEPMOTOR_MIN,2);//��ʼΪ0
	}
	printf("stepInit%d:0X%0X \r\n",id,AT24CXX_ReadOneByte(0));//��ӡ��ʼ����Ϣ
	printf("stepMotor_Reset OK!\r\n");
	return 0;
}
int stepMotor_Read(u8 id){
	return AT24CXX_ReadLenByte(id*2,2);
}
