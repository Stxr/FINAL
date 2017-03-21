#include "mypage.h"
typedef struct {
	U32 color;
	u8 id;
}mydata;
mydata change_data;

int Time_Left = 0,Time_Used=0,speed=0;
int isChange=-1;
float shuyeData[4][5]={0};
u8 id_bottle=0;
char buffer1[20], buffer2[20], buffer3[5];//���������ڴ�ռ�

WM_HTIMER hTimer;
WM_HWIN hchild[4];
MULTIPAGE_Handle aMultipage;

GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {
	//
	//  Function                 Text      Id					       Px   Py   Dx   Dy
	//
	{ WINDOW_CreateIndirect,    0,        0,				         0,	 162, 320,  60},
	{ BUTTON_CreateIndirect,   "7",      GUI_ID_USER + 7,		 0,    0,  80,  20},
	{ BUTTON_CreateIndirect,   "8",      GUI_ID_USER + 8,		80,    0,  80,  20},
	{ BUTTON_CreateIndirect,   "9",      GUI_ID_USER + 9,	 160,    0,  80,  20},
	{ BUTTON_CreateIndirect,   "4",      GUI_ID_USER + 4,		 0,	 	20,  80,  20},
	{ BUTTON_CreateIndirect,   "5",      GUI_ID_USER + 5,		80,	 	20,  80,  20},
	{ BUTTON_CreateIndirect,   "6",      GUI_ID_USER + 6,	 160,  	20,  80,  20},
	{ BUTTON_CreateIndirect,   "1",      GUI_ID_USER + 1,		 0,	 	38,  80,  20},
	{ BUTTON_CreateIndirect,   "2",      GUI_ID_USER + 2,		80,	 	38,  80,  20},
	{ BUTTON_CreateIndirect,   "3",      GUI_ID_USER + 3,	 160,		38,  80,  20},
	{ BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11, 240, 	 0,  80,  20},
	{ BUTTON_CreateIndirect,   "0",      GUI_ID_USER + 0,	 240, 	20,  80,  20},
	{ BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10, 240, 	38,  80,  20},
};
GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = {
	{ WINDOW_CreateIndirect,    "Dialog 4",               0,         0,   0, 320, 159, FRAMEWIN_CF_MOVEABLE },
	{ EDIT_CreateIndirect,		  "bottle1",     GUI_ID_EDIT0,         150,  9,  50,  20, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "speed1",       GUI_ID_EDIT1,        66,  37,  30,  15, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "speed2",       GUI_ID_EDIT2,        226,  37,  30,  15, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "time1",       GUI_ID_EDIT3,         66,  64,  30,  15, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "time2",       GUI_ID_EDIT4,         226,  64,  30,  15, EDIT_CF_HCENTER }
};
BUTTON_SKINFLEX_PROPS MY_BUTTON_SKIN_ENABLE = {
	{ MYCOLOR_LINE,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
	{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
	{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },0
};
BUTTON_SKINFLEX_PROPS MY_BUTTON_SKIN_PRESSED = {
	{ MYCOLOR_LINE,GUI_WHITE,GUI_WHITE },
	{ GUI_WHITE,GUI_WHITE },
	{ GUI_WHITE,GUI_WHITE },0
};
MULTIPAGE_SKINFLEX_PROPS multipage_skin_SELECTED = {
	GUI_WHITE,{ GUI_WHITE,GUI_WHITE },{ GUI_WHITE ,GUI_WHITE },0Xe3d7d4,GUI_BLACK
};
MULTIPAGE_SKINFLEX_PROPS multipage_skin_ENABLE = {
	GUI_YELLOW,{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
	{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND ,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
	MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,GUI_BLACK
};
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
	// GUI_Init();
//	WM_EnableMemdev(WM_HBKWIN); //���ô����豸
	W_pageShuyeSetting(0);
	while (1) {
		GUI_Delay(1000);
//		printf("use:%d\n",my_mem_perused(SRAMIN));
//		printf("id_bottle:%d\n",id_bottle);
	}
}
void W_pageDisplay(void) {
	id_bottle = 0; //������
	//memset(buffer1, 0, sizeof(char));
	buffer1[0] = '\0'; //���������
	buffer3[0] = '\0'; //���������
//	stepMotor_Reset(1);
//	stepMotor_Reset(2);
//	stepMotor_Reset(3);
//	stepMotor_Reset(4);
	WM_CreateWindow(0, 0, 320, 240, WM_CF_SHOW, pageDisplay, 0);
}
void W_pageHome(void) {
	WM_CreateWindow(0, 0, 320, 240, WM_CF_SHOW, pageHome, 0);
	GUI_Exec();
}
void W_pageSetting(void) {
	WM_CreateWindow(0, 0, 320, 240, WM_CF_SHOW, pageSetting, 0);
	GUI_Exec();
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);

}
void W_pageShuyeSetting(int page) {
	WM_HWIN hWnd, hNumPad;
	hWnd = WM_CreateWindow(0, 0, 320, 240, WM_CF_SHOW, pageShuyeSetting, 0);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	BUTTON_SetSkinFlexProps(&MY_BUTTON_SKIN_ENABLE, 2);
	BUTTON_SetSkinFlexProps(&MY_BUTTON_SKIN_PRESSED, 0);
	hNumPad = GUI_CreateDialogBox(_aDialogNumPad, GUI_COUNTOF(_aDialogNumPad), _cbDialogNumPad, hWnd, 0, 0); /* Create the numpad dialog */
	WM_SetStayOnTop(hNumPad, 1);
	createMultipage(&hWnd,&page);

}
void W_pageShuyeDisplay(void) {
	id_bottle = 0; //������
	WM_CreateWindow(0, 0, 320, 240, WM_CF_SHOW, pageShuyeDisplay, 0);
}
void _cbchild1(WM_MESSAGE *pMsg) {
	// mydata data_receive;
	char id[2];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		WM_GetUserData(pMsg->hWin, &change_data, sizeof(mydata));
		GUI_SetBkColor(change_data.color);
		GUI_Clear();
		GUI_SetColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font20_1);
		sprintf(id, "%d", change_data.id);
		GUI_DispStringHCenterAt(id, 9, 0);
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
void pageDisplay(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	GUI_RECT InvalidateRect = { 175,206,222,225 };
	static char buttonString[6]="��ͣ";
	switch (pMsg->MsgId)
	{
	case WM_TIMER:
		if (shuyeData[id_bottle][0] == 0 || (shuyeData[id_bottle][3] <= 0 && shuyeData[id_bottle][4] <= 0)) { //shuyeData[][3]��shuyeData[][4]�п���С��0
			id_bottle++;
			if (id_bottle >= 4) id_bottle = 0;
		}
		if (shuyeData[id_bottle][3] > 0 || shuyeData[id_bottle][4] > 0) { //ʣ����Һʱ���Ƿ�Ϊ0
			Time_Used++;
			if (Time_Used % 2) {
				WM_HideWindow(hchild[id_bottle]);
			}
			else {
				WM_ShowWindow(hchild[id_bottle]);
			}
			if (shuyeData[id_bottle][3] != 0) { //����1
 				Time_Left = --shuyeData[id_bottle][3];
				if(speed!=shuyeData[id_bottle][1]){
					speed = shuyeData[id_bottle][1];
//					stepMotor_Distance(id_bottle+1,5,speed*100); //speedԽ��distanceԽС
				}
			}
			else { //����2
				change_data.color = GUI_BLUE;
				change_data.id = id_bottle+1;
				WM_SetUserData(hchild[id_bottle], &change_data, sizeof(mydata));
				Time_Left = --shuyeData[id_bottle][4];
				if(speed != shuyeData[id_bottle][2]){
//					stepMotor_Distance(id_bottle+1,5,(shuyeData[id_bottle][1]-shuyeData[id_bottle][2])*100); //
					speed = shuyeData[id_bottle][2];
				}				
			}
			if (shuyeData[id_bottle][4] <= 0 && shuyeData[id_bottle][3] <= 0) { //��Һ���
				change_data.color = GUI_BLACK;
				change_data.id = id_bottle+1;//��Ŵ�0��ʼ����ʾ��1��ʼ
				WM_SetUserData(hchild[id_bottle], &change_data, sizeof(mydata));
				WM_ShowWindow(hchild[id_bottle]);
			}
		}
		sprintf(buffer3, "%d", speed);
		sprintf(buffer1, "%02d:%02d:%02d", Time_Left / 3600, Time_Left / 60, Time_Left%60);
		sprintf(buffer2, "%02d:%02d:%02d", Time_Used / 3600, Time_Used / 60, Time_Used % 60);
		//Time_Left--;

		//���ڵ�Ƭ�����ٶ����⣬ֻ���²��ִ��ڣ��Դﵽ�Ӿ��Ż�
		InvalidateRect.x0 = 226;
		InvalidateRect.y0 = 154;
		InvalidateRect.x1 = 296;
		InvalidateRect.y1 = 168;
		WM_InvalidateRect(pMsg->hWin, &InvalidateRect);
		InvalidateRect.y0 = 190;
		InvalidateRect.y1 = 224;
		WM_InvalidateRect(pMsg->hWin, &InvalidateRect);
		if (isChange != speed) {
			isChange = speed;
			InvalidateRect.x0 = 169;
			InvalidateRect.y0 = 41;
			InvalidateRect.x1 = 214;
			InvalidateRect.y1 = 78;
			WM_InvalidateRect(pMsg->hWin, &InvalidateRect);
		}
		//WM_InvalidateWindow(pMsg->hWin); //ʹ������Ч���Ӷ����и���
		WM_RestartTimer(hTimer, 1000);
		break;

	case WM_PAINT:
		//������
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_Clear();
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_ClearRect(0, 222, 320, 240);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(160, 222, 320);
		//д��
		GUI_SetFont(&GUI_FontHZ24);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT1);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_DispStringAt("��Һ����", 7, 42);
		GUI_DispStringAt("��Һƿ��", 7, 102);
		GUI_DispStringAt("��Һʱ��", 7, 168);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT2);
		GUI_DispStringAt("����", 130, 154);
		GUI_DispStringAt("ʣ��", 130, 190);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT3);
		GUI_DispStringHCenterAt(buffer2, 233, 154);
		GUI_DispStringHCenterAt(buffer1, 233, 190);
		GUI_SetFont(&GUI_FontD36x48);
		GUI_DispStringAt(buffer3, 168, 42);//��Ҫ��һ�������
		GUI_SetFont(&GUI_FontHZ12);
		GUI_GotoY(75);
		GUI_DispString(" ����/��");
										//��ť����
		GUI_SetFont(&GUI_FontHZ16);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_DispStringHCenterAt("����", 80, 225);
		GUI_DispStringHCenterAt(buttonString, 240, 225);

		break;
	case WM_CREATE:
		hTimer = WM_CreateTimer(pMsg->hWin, 0, 1000, 0);
		for (int i = 0; i < 4; i++) {
			if (shuyeData[i][0] == 0)continue;//�������Ϊ0���򲻴���
			hchild[i] = WM_CreateWindowAsChild(172 + i * 34, 105, 18, 18, pMsg->hWin, WM_CF_SHOW, _cbchild1, sizeof(mydata));
			change_data.id = i + 1;
			change_data.color = GUI_GREEN;
			WM_SetUserData(hchild[i], &change_data, sizeof(mydata));
		}

		//display
		//GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		//for (int i = 0; i < 4; i++) {
		//	for (int j = 0; j < 5; j++) {
		//		GUI_DispDecAt(shuyeData[i][j], 50*j, 50*i, 5);
		//	}
		//}
		break;

	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 222) {
				if (pState->x < 160) {
					hTimer = WM_CreateTimer(pMsg->hWin, 0, 1000, 0);//��ֹ����
					for (int i = 0; i < 4; i++) {
						shuyeData[i][3] /= 60;
						shuyeData[i][4] /= 60;
					}
					WM_DeleteWindow(pMsg->hWin);
					W_pageShuyeSetting(0);
				}
				else //pause
				{
					if (!strcmp("��ͣ", buttonString)) {
						BEEP=1;
						sprintf(buttonString, "%s","��ʼ");
						WM_InvalidateWindow(pMsg->hWin); //ʹ������Ч���Ӷ����и��� �¾�ios
						WM_DeleteTimer(hTimer);
					}
					else {
						BEEP=0;
						sprintf(buttonString, "%s", "��ͣ");
						WM_InvalidateWindow(pMsg->hWin); //ʹ������Ч���Ӷ����и���
						hTimer = WM_CreateTimer(pMsg->hWin, 0, 1000, 0);
					}
				}
			}
		}
		break;
	case WM_DELETE:
		WM_DeleteTimer(hTimer);
		id_bottle = 0;
	default:
		break;
	}
}
void pageShuyeDisplay(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	// char *buffer1=(char *)mymalloc(SRAMIN,sizeof(char)*20);
//	char buffer1[20];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//����
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 45, 320, 222);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 222, 320, 240);
		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(45, 0, 320);
		GUI_DrawHLine(89, 0, 320);
		GUI_DrawHLine(133, 0, 320);
		GUI_DrawHLine(177, 0, 320);
		GUI_DrawHLine(221, 0, 320);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(160, 222, 320);
		//д��
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_DispStringHCenterAt("����Ԥ��", 160, 17);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt("һ��ƿ", 16, 60);
		GUI_DispStringAt("����ƿ", 16, 105);
		GUI_DispStringAt("����ƿ", 16, 148);
		GUI_DispStringAt("�ĺ�ƿ", 16, 192);

		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("����", 80, 225);
		GUI_DispStringHCenterAt("ȷ��", 240, 225);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_FontHZ12);

		sprintf(buffer1, "����:%.1f ����", shuyeData[0][0]);
		GUI_DispStringAt(buffer1, 156, 49);
		sprintf(buffer1, "����:%.1f ����", shuyeData[1][0]);
		GUI_DispStringAt(buffer1, 156, 93);
		sprintf(buffer1, "����:%.1f ����", shuyeData[2][0]);
		GUI_DispStringAt(buffer1, 156, 137);
		sprintf(buffer1, "����:%.1f ����", shuyeData[3][0]);
		GUI_DispStringAt(buffer1, 156, 180);

		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[0][1]);
		GUI_DispStringAt(buffer1, 90, 62);
		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[1][1]);
		GUI_DispStringAt(buffer1, 90, 106);
		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[2][1]);
		GUI_DispStringAt(buffer1, 90, 150);
		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[3][1]);
		GUI_DispStringAt(buffer1,90, 193);

		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[0][3]);
		GUI_DispStringAt(buffer1, 90, 76);
		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[1][3]);
		GUI_DispStringAt(buffer1, 90, 120);
		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[2][3]);
		GUI_DispStringAt(buffer1, 90, 163);
		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[3][3]);
		GUI_DispStringAt(buffer1, 90, 207);

		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[0][2]);
		GUI_DispStringAt(buffer1, 207, 62);
		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[1][2]);
		GUI_DispStringAt(buffer1, 207, 106);
		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[2][2]);
		GUI_DispStringAt(buffer1, 207, 150);
		sprintf(buffer1, "�ٶ�:%.1f ����/��", shuyeData[3][2]);
		GUI_DispStringAt(buffer1, 207, 193);

		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[0][4]);
		GUI_DispStringAt(buffer1, 207, 76);
		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[1][4]);
		GUI_DispStringAt(buffer1, 207, 120);
		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[2][4]);
		GUI_DispStringAt(buffer1, 207, 163);
		sprintf(buffer1, "ʱ��:%.1f ��", shuyeData[3][4]);
		GUI_DispStringAt(buffer1, 207, 207);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
				WM_DeleteWindow(pMsg->hWin);
			if (pState->y > 45 && pState->y < 89) {
				W_pageShuyeSetting(0);
			}
			else if (pState->y > 89 && pState->y < 133) {
				W_pageShuyeSetting(1);
			}
			else if (pState->y > 133 && pState->y < 177) {
				W_pageShuyeSetting(2);
			}
			else if (pState->y > 177 && pState->y < 222) {
				W_pageShuyeSetting(3);
			}
			else if (pState->y >= 222) {
				if (pState->x < 160) {
					W_pageShuyeSetting(0);
				}
				else {
					for (int i = 0; i < 4; i++) {
						shuyeData[i][3] *= 60;//���ӻ���
						shuyeData[i][4] *= 60;
					}
					W_pageDisplay();
				}
			}
		}
		break;
	default:
		break;
	}
}

void pageShuyeSetting(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
//	GUI_HWIN hItem;
	// char *s=mymalloc(SRAMIN,sizeof(char)*5);
//	char s[5];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//����
//		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
//		GUI_ClearRect(0, 64, 320, 222);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 222, 320, 240);
		//����
//		GUI_SetPenSize(1);
//		GUI_SetColor(MYCOLOR_LINE);
//		GUI_DrawHLine(63, 0, 320);
//		GUI_DrawHLine(102, 0, 320);
//		GUI_DrawHLine(140, 0, 320);
//		GUI_DrawHLine(178, 0, 320);
//		GUI_DrawHLine(221, 0, 320);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(160, 222, 320);
		//д��
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_DispStringHCenterAt("Ԥ����", 160, 15);


		GUI_SetFont(&GUI_FontHZ16);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("����", 80, 225);
		GUI_DispStringHCenterAt("ȷ��", 240, 225); 

		// GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		// GUI_SetBkColor(GUI_WHITE);
		// GUI_SetFont(&GUI_FontHZ16);
		// GUI_DispStringAt("����:        ����", 85, 90);
		// GUI_DispStringAt("ʱ��:            ", 85, 110);
		// GUI_DispStringAt("����:        ����", 85, 140);
		// GUI_DispStringAt("ʱ��:            ", 85, 160);
		// GUI_DispStringAt("����:        ����", 85, 193);
		// GUI_DispStringAt("ʱ��:            ", 85, 213);
		// GUI_DispStringAt("����:        ����", 85, 243);
		// GUI_DispStringAt("ʱ��:            ", 85, 263);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 222) {
				if (pState->x < 160) {
					WM_DeleteWindow(pMsg->hWin);
					W_pageHome();
				}
				else {
					//save the data
					// for (int i = 0; i < 4; i++) {
					// 	for (int j = 0; j < 5; j++) {
					// 		hItem = WM_GetDialogItem(MULTIPAGE_GetWindow(aMultipage, i), GUI_ID_EDIT0+j);
					// 		EDIT_GetText(hItem, s, 4);
					// 		sscanf(s, "%f", &shuyeData[i][j]);
					// 		//if (j == 3 || j == 4) {
					// 		//	shuyeData[i][j] *= 60;
					// 		//}
					// 	}
					// }
					// myfree(SRAMIN,s);
					WM_DeleteWindow(pMsg->hWin);
					W_pageShuyeDisplay();
				}
			}
		}
		break;
	default:
		break;
	}
}
void pageHome(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_Clear();

		//����
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_ClearRect(0, 147, 320, 194);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_ClearRect(0, 194, 320, 240);

		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(147, 0, 320);
		GUI_DrawHLine(194, 0, 320);

		//д��
		GUI_SetColor(MYCOLOR_PAGEHOME_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_DispStringHCenterAt("MULTI-ȫ�Զ�", 160, 52);
		GUI_DispStringHCenterAt("������Һ��", 160, 75);

		GUI_SetColor(MYCOLOR_PAGEHOME_SETTING_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringHCenterAt("��Һ����", 160, 166);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_DispStringHCenterAt("ϵͳ����", 160, 210);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 194 && pState->y>147) {//��Һ����
				WM_DeleteWindow(pMsg->hWin);
				W_pageShuyeSetting(0);
			}
			else if (pState->y > 194 && pState->y < 240) {//ϵͳ����
														  //GUI_DispStringAt("1", 0, 0);
				WM_DeleteWindow(pMsg->hWin);
				W_pageSetting();
			}
		}
		break;
	default:
		break;
	}
}
void pageSetting(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
		GUI_Clear();
		GUI_SetFont(&GUI_Font32_ASCII);
		//GUI_DispString("hello,emwin");
		//������
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
 		GUI_ClearRect(0, 82, 320, 240);
		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(82, 0, 320);
		GUI_DrawHLine(112, 0, 320);
		GUI_DrawHLine(144, 0, 320);
		GUI_DrawLine(0, 176, 320, 176);
		GUI_DrawHLine(208, 0, 320);
		//д��
		GUI_SetColor(MYCOLOR_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ32);
		GUI_DispStringHCenterAt("ϵͳ����", 160, 39);

		GUI_SetColor(MYCOLOR_CONTENT_TEXT);
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringHCenterAt("��������", 160, 88);
		GUI_DispStringHCenterAt("ϵͳ����", 160, 120);
		GUI_DispStringHCenterAt("ϵͳ״̬", 160, 152);
		GUI_DispStringHCenterAt("��������", 160, 183);
		GUI_DispStringHCenterAt("����", 160, 216);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 13&&pState->x>254) {
				GUI_DispStringAt("0", 0, 0);
			}
			else if (pState->y > 81 && pState->y < 112) {
				GUI_DispStringAt("1", 0, 0);
			}
			else if (pState->y >= 112 && pState->y<144) {
				GUI_DispStringAt("2", 0, 0);
			}
			else if (pState->y >= 144 && pState->y <= 176) {
				GUI_DispStringAt("3", 0, 0);
			}
			else if (pState->y >= 176 && pState->y <= 208) {
				GUI_DispStringAt("4", 0, 0);
			}
			else if (pState->y >= 208) {
				WM_DeleteWindow(pMsg->hWin);
				W_pageHome();
			}
		}
		break;
	default:
		break;
	}

}
	void createMultipage(WM_HWIN *hWnd,int *page) {
	WM_HWIN pageBottle;

	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

	MULTIPAGE_SetSkinFlexProps(&multipage_skin_SELECTED, MULTIPAGE_SKINFLEX_PI_SELECTED);
	MULTIPAGE_SetSkinFlexProps(&multipage_skin_ENABLE, MULTIPAGE_SKINFLEX_PI_ENABLED);

	aMultipage = MULTIPAGE_CreateEx(0, 45, 320, 159, *hWnd, WM_CF_SHOW, 0, 0);
	MULTIPAGE_SetFont(aMultipage, &GUI_Font16B_1);
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "       1         ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "       2         ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "       3         ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "       4         ");
	MULTIPAGE_SelectPage(aMultipage, *page);

}
void _cbBottle4(WM_MESSAGE *pMsg) {
	WM_HWIN hEdit;
	unsigned Id;
	int NCode;
	// char buff[5];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		GUI_SetFont(&GUI_FontHZ24);
		GUI_SetColor(GUI_BLACK);
		GUI_DispStringAt("����:", 86, 7);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt("����", 210, 13);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt("����1:", 6, 35);
		GUI_DispStringAt("ʱ��1:", 6, 63);
		GUI_DispStringAt("����2:", 166, 35);
		GUI_DispStringAt("ʱ��2:", 166, 63);
		GUI_SetFont(&GUI_FontHZ12);
		GUI_DispStringAt("����/��", 106, 39);
		GUI_DispStringAt("��", 106, 65);
		GUI_DispStringAt("����/��", 266, 39);
		GUI_DispStringAt("��", 266, 65);
		break;
	case WM_INIT_DIALOG:
		id_bottle++;
		for (int i = 0; i < 5; i++) {
			hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0 + i);
			if (i == 0) {
				EDIT_SetFont(hEdit, &GUI_Font24B_1);
			}
			EDIT_SetMaxLen(hEdit, 4);
			WIDGET_SetEffect(hEdit, &WIDGET_Effect_None);

			//if (!_pEditCallback) {
			//	_pEditCallback = WM_SetCallback(hEdit, _cbEdit); // Overwrite callback function and remember original function
			//}
			//else {
			//	WM_SetCallback(hEdit, _cbEdit);                  // Overwrite callback function
			//}
			//EDIT_SetDecMode(hEdit,0,0,9999,1, GUI_EDIT_NORMAL);

			//��ʼ������
			if (shuyeData[id_bottle - 1][i] != 0) {
				if (shuyeData[id_bottle - 1][i] == (int)shuyeData[id_bottle - 1][i]) { //������
					sprintf(buffer3, "%d", (int)shuyeData[id_bottle - 1][i]);//��ʼ������
				}
				else{//С��
					sprintf(buffer3, "%.1f", shuyeData[id_bottle - 1][i]);//��ʼ������
				}
				EDIT_SetText(hEdit, buffer3);
			}
			else {
				EDIT_SetText(hEdit, "\0");
			}
		}
//		MULTIPAGE_GetSelection(aMultipage);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
		NCode = pMsg->Data.v;                 /* Notification code */
		switch (NCode)
		{
		case WM_NOTIFICATION_VALUE_CHANGED:
			//hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
			//EDIT_GetText(hEdit, c_valume, 4);
			//sscanf(c_valume, "%f", &data[0]);
			id_bottle = MULTIPAGE_GetSelection(aMultipage);
			for (int i = 0; i < 5; i++) {   // save the data to shuyeData
				hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0+i);
				EDIT_GetText(hEdit, buffer3, 5);
				sscanf(buffer3, "%f", &shuyeData[id_bottle][i]);//д������
			}
			switch (Id)
			{
			case GUI_ID_EDIT0:
				shuyeData[id_bottle][1] = shuyeData[id_bottle][2] = shuyeData[id_bottle][3] = shuyeData[id_bottle][4] = 0;
				for (int i = 1; i <= 4; i++) {
					hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0+i);
					EDIT_SetText(hEdit, "\0");
					shuyeData[id_bottle][i] = 0;
				}
				break;
			case GUI_ID_EDIT1:
				hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
				if (shuyeData[id_bottle][1] != 0) {
					shuyeData[id_bottle][3] = shuyeData[id_bottle][0] / shuyeData[id_bottle][1];
					sprintf(buffer3, "%.1f", shuyeData[id_bottle][3]);
				}
				else {
					sprintf(buffer3, "%s", "err");
				}
				EDIT_SetText(hEdit, buffer3);
				//break;
			case GUI_ID_EDIT3:
				if (shuyeData[id_bottle][3] * shuyeData[id_bottle][1] > shuyeData[id_bottle][0]) {//������Χ��
					shuyeData[id_bottle][3] = shuyeData[id_bottle][0] / shuyeData[id_bottle][1];
					hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
					sprintf(buffer3, "%.1f", shuyeData[id_bottle][3]);
					EDIT_SetText(hEdit, buffer3);

				}
				else if (shuyeData[id_bottle][1] * shuyeData[id_bottle][3] == shuyeData[id_bottle][0] ) {//��Ϊ����ı���shuyeData[id_bottle][3]�����Ի��Զ����
					shuyeData[id_bottle][4] = 0;
					shuyeData[id_bottle][2] = 0;
					//shuyeData[id_bottle][1] = shuyeData[id_bottle][0] / shuyeData[id_bottle][3];
				}
				else {//��Сֵ��
					shuyeData[id_bottle][2] = 5;//Ĭ����5ml/��
					shuyeData[id_bottle][4] = (shuyeData[id_bottle][0] - shuyeData[id_bottle][1] * shuyeData[id_bottle][3]) / shuyeData[id_bottle][2];
				}
				hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
				sprintf(buffer3, "%.1f", shuyeData[id_bottle][2]);
				EDIT_SetText(hEdit, buffer3);
			case GUI_ID_EDIT2:
				if (shuyeData[id_bottle][2] != 0) {
					shuyeData[id_bottle][4] = (shuyeData[id_bottle][0] - shuyeData[id_bottle][1] * shuyeData[id_bottle][3]) / shuyeData[id_bottle][2];
				}
				hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT4);
				sprintf(buffer3, "%.1f", shuyeData[id_bottle][4]);
				EDIT_SetText(hEdit, buffer3);
				//hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
				//sprintf(buffer3, "%.1f", shuyeData[id_bottle][1]);
				//EDIT_SetText(hEdit, buffer3);
			case GUI_ID_EDIT4:

				break;


			default:

				break;
			}
			//EDIT_GetText(hEdit, s, 5);
			//id_bottle = MULTIPAGE_GetSelection(aMultipage);

			//sprintf(sDest,"%d",id_bottle);
			//hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
			//EDIT_SetText(hEdit, sDest);

			break;
		default:
			break;
		}
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
void _cbDialogNumPad(WM_MESSAGE * pMsg) {
	unsigned i;
	int      NCode;
	unsigned Id;
	int      Pressed;
	WM_HWIN  hItem;
	//int _aKey[] = { GUI_KEY_BACKSPACE, GUI_KEY_TAB, GUI_KEY_LEFT, GUI_KEY_RIGHT };
	Pressed = 0;

	switch (pMsg->MsgId) {
		case WM_PAINT:
			break;
		case WM_INIT_DIALOG:
			for (i = 0; i < GUI_COUNTOF(_aDialogNumPad) - 1; i++) {
				hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_USER + i);
				BUTTON_SetFocussable(hItem, 0);		//Set all buttons non focussable
			}
			break;
		case WM_NOTIFY_PARENT:
			Id = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
			NCode = pMsg->Data.v;                 /* Notification code */
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				Pressed = 1;
			case WM_NOTIFICATION_RELEASED:
				if ((Id >= GUI_ID_USER) && (Id <= (GUI_ID_USER + GUI_COUNTOF(_aDialogNumPad) - 1))) {
					int Key;
					if (Id < GUI_ID_USER + 11) {
						char acBuffer[10];
						BUTTON_GetText(pMsg->hWinSrc, acBuffer, sizeof(acBuffer)); /* Get the text of the button */
						Key = acBuffer[0];
					}
					else {
						//Key = _aKey[Id - GUI_ID_USER - 11];
						Key = GUI_KEY_BACKSPACE;                        /* Get the text from the array */
					}
					GUI_SendKeyMsg(Key, Pressed);                                /* Send a key message to the focussed window */
				}
				break;
			}
		default:
			WM_DefaultProc(pMsg);
	}
}
void _cbEditAddKey(EDIT_Handle hObj, int Key) {
	char acBuffer[2] = { 0 };

	switch (Key) {
	case GUI_KEY_LEFT:
		EDIT_SetpfAddKeyEx(hObj, 0);                            // Clear user defined AddKey function
		EDIT_SetCursorAtChar(hObj, EDIT_GetNumChars(hObj) - 1); // Set cursor if GUI_KEY_LEFT has been pressed
		break;
	case GUI_KEY_RIGHT:
		EDIT_SetpfAddKeyEx(hObj, 0);                            // Clear user defined AddKey function
		EDIT_SetCursorAtChar(hObj, 1);                          // Set cursor if GUI_KEY_RIGHT has been pressed
		break;
	case GUI_KEY_UP:                                          // Do not react on GUI_KEY_UP and GUI_KEY_DOWN
	case GUI_KEY_DOWN:
		break;
	default:
		if (Key >= 0x20) {
			acBuffer[0] = (U8)Key;
			EDIT_SetpfAddKeyEx(hObj, 0);                          // Clear user defined AddKey function
			EDIT_SetText(hObj, acBuffer);                         // Overwrite contents of edit widget with pressed key
		}
	}
}

void _cbEdit(WM_MESSAGE * pMsg) {
	switch (pMsg->MsgId) {
	case WM_PID_STATE_CHANGED:
		if (((const WM_PID_STATE_CHANGED_INFO*)pMsg->Data.p)->State) {
			return;            // Do not call edit callback
		}
		break;
	case WM_TOUCH:
		if (pMsg->Data.p) {  // Something happened in our area (pressed or released)
			const GUI_PID_STATE* pState;
			pState = (const GUI_PID_STATE*)pMsg->Data.p;
			if (pState->Pressed) {
				if (WM_GetFocussedWindow() != pMsg->hWin) {
					WM_SetFocus(pMsg->hWin);
					return;        // Do not call edit callback
				}
			}
		}
		break;
	case WM_SET_FOCUS:
		if (pMsg->Data.v == 1) {
			EDIT_SetpfAddKeyEx(pMsg->hWin, _cbEditAddKey); // Set function pointer for a user defined AddKey function
			EDIT_SetSel(pMsg->hWin, 0, -1);                // Select the whole contents of the edit field
		}
	}
	if (_pEditCallback) {
		_pEditCallback(pMsg);
	}
}
