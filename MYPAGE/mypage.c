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
	//  Function                 Text      Id					 Px   Py   Dx   Dy
	//
	{ WINDOW_CreateIndirect,    0,        0,				      0,	 217, 240,  78 },
	{ BUTTON_CreateIndirect,   "7",      GUI_ID_USER + 7,		 0,  0,  60,  26 },
	{ BUTTON_CreateIndirect,   "8",      GUI_ID_USER + 8,		60,  0,  60,  26},
	{ BUTTON_CreateIndirect,   "9",      GUI_ID_USER + 9,	   120,  0,  60,  26},
	{ BUTTON_CreateIndirect,   "4",      GUI_ID_USER + 4,		 0,	 26,  60,  26},
	{ BUTTON_CreateIndirect,   "5",      GUI_ID_USER + 5,		60,	 26,  60,  26},
	{ BUTTON_CreateIndirect,   "6",      GUI_ID_USER + 6,	   120,  26,  60,  26},
	{ BUTTON_CreateIndirect,   "1",      GUI_ID_USER + 1,		 0,	 52,  60,  26},
	{ BUTTON_CreateIndirect,   "2",      GUI_ID_USER + 2,		60,	 52,  60,  26},
	{ BUTTON_CreateIndirect,   "3",      GUI_ID_USER + 3,		120, 52,  60,  26},
	{ BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11,		180, 0,  60,  26},
	{ BUTTON_CreateIndirect,   "0",      GUI_ID_USER + 0,		180, 26,  60,  26},
	{ BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10,		180, 52,  60,  26},
};
GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = {
	{ WINDOW_CreateIndirect,    "Dialog 4",               0,            0,   0, 240, 212, FRAMEWIN_CF_MOVEABLE },
	{ EDIT_CreateIndirect,		"bottle1",     GUI_ID_EDIT0,           90,  17,  30,  20, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "speed1",       GUI_ID_EDIT1,           50,  50,  30,  15, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "speed2",       GUI_ID_EDIT2,           170,  50,  30,  15, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "time1",       GUI_ID_EDIT3,           50,  85,  30,  15, EDIT_CF_HCENTER },
	{ EDIT_CreateIndirect,      "time2",       GUI_ID_EDIT4,           170,  85,  30,  15, EDIT_CF_HCENTER }
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
		printf("use:%d\n",my_mem_perused(SRAMIN));
		printf("id_bottle:%d\n",id_bottle);
		printf("id_bottle:%d\n",id_bottle);
	}
}
void W_pageDisplay(void) {
	id_bottle = 0; //������
	//memset(buffer1, 0, sizeof(char));
	buffer1[0] = '\0'; //���������
	buffer3[0] = '\0'; //���������
	WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageDisplay, 0);
}
void W_pageHome(void) {
	WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageHome, 0);
	GUI_Exec();
}
void W_pageSetting(void) {
	WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageSetting, 0);
	GUI_Exec();
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);

}
void W_pageShuyeSetting(int page) {
	WM_HWIN hWnd, hNumPad;
	hWnd = WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageShuyeSetting, 0);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	BUTTON_SetSkinFlexProps(&MY_BUTTON_SKIN_ENABLE, 2);
	BUTTON_SetSkinFlexProps(&MY_BUTTON_SKIN_PRESSED, 0);
	hNumPad = GUI_CreateDialogBox(_aDialogNumPad, GUI_COUNTOF(_aDialogNumPad), _cbDialogNumPad, hWnd, 0, 0); /* Create the numpad dialog */
	WM_SetStayOnTop(hNumPad, 1);
	createMultipage(&hWnd,&page);

}
void W_pageShuyeDisplay(void) {
	id_bottle = 0; //������
	WM_CreateWindow(0, 0, 240, 320, WM_CF_SHOW, pageShuyeDisplay, 0);
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
	id_bottle = 0;//�ӵ�һ����ʼ����
	switch (pMsg->MsgId)
	{
	case WM_TIMER:
		if (shuyeData[id_bottle][0] == 0 || (shuyeData[id_bottle][3] == 0 && shuyeData[id_bottle][4] == 0)) {
			id_bottle++;
			if (id_bottle >= 4) id_bottle = 0;
		}
		if (shuyeData[id_bottle][3] > 0 || shuyeData[id_bottle][4] > 0) { //ʣ����Һʱ���Ƿ�Ϊ0
			Time_Used++;
			if (shuyeData[id_bottle][3] != 0) {
 				Time_Left = --shuyeData[id_bottle][3];
				speed = shuyeData[id_bottle][1];
			}
			else {
				change_data.color = GUI_BLUE;
				change_data.id = id_bottle+1;
				WM_SetUserData(hchild[id_bottle], &change_data, sizeof(mydata));
				Time_Left = --shuyeData[id_bottle][4];
				speed = shuyeData[id_bottle][2];
			}
			if (shuyeData[id_bottle][4] == 0 && shuyeData[id_bottle][3]==0) {
				change_data.color = GUI_BLACK;
				change_data.id = id_bottle+1;
				WM_SetUserData(hchild[id_bottle], &change_data, sizeof(mydata));
			}
		}
		sprintf(buffer3, "%d", speed);
		sprintf(buffer1, "%02d:%02d:%02d", Time_Left / 3600, Time_Left / 60, Time_Left%60);
		sprintf(buffer2, "%02d:%02d:%02d", Time_Used / 3600, Time_Used / 60, Time_Used % 60);
		//Time_Left--;
		if (Time_Used % 2) {
			WM_HideWindow(hchild[id_bottle]);
		}
		else {
			WM_ShowWindow(hchild[id_bottle]);
		}
		//���ڵ�Ƭ�����ٶ����⣬ֻ���²��ִ��ڣ��Դﵽ�Ӿ��Ż�
		InvalidateRect.x0 = 170;
		InvalidateRect.y0 = 206;
		InvalidateRect.x1 = 222;
		InvalidateRect.y1 = 225;
		WM_InvalidateRect(pMsg->hWin, &InvalidateRect);
		InvalidateRect.y0 = 262;
		InvalidateRect.y1 = 284;
		WM_InvalidateRect(pMsg->hWin, &InvalidateRect);
		if (isChange != speed) {
			isChange = speed;
			InvalidateRect.x0 = 127;
			InvalidateRect.y0 = 55;
			InvalidateRect.x1 = 161;
			InvalidateRect.y1 = 105;
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
		GUI_ClearRect(0, 296, 240, 320);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//д��
		GUI_SetFont(&GUI_FontHZ24);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT1);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_DispStringAt("��Һ����", 5, 56);
		GUI_DispStringAt("��Һƿ��", 5, 126);
		GUI_DispStringAt("��Һʱ��", 5, 224);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT2);
		GUI_DispStringAt("����", 150, 182);
		GUI_DispStringAt("ʣ��", 150, 236);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT3);
		GUI_DispStringHCenterAt(buffer2, 175, 206);
		GUI_DispStringHCenterAt(buffer1, 175, 262);
		GUI_SetFont(&GUI_FontD36x48);
		GUI_DispStringAt(buffer3, 126, 56);//��Ҫ��һ�������
										//��ť����
		GUI_SetFont(&GUI_FontHZ16);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_DispStringHCenterAt("����", 60, 300);
		GUI_DispStringHCenterAt(buttonString, 180, 300);

		break;
	case WM_CREATE:
		hTimer = WM_CreateTimer(pMsg->hWin, 0, 1000, 0);
		for (int i = 0; i < 4; i++) {
			if (shuyeData[i][0] == 0)continue;//�������Ϊ0���򲻴���
			hchild[i] = WM_CreateWindowAsChild(129 + i * 26, 126, 18, 18, pMsg->hWin, WM_CF_SHOW, _cbchild1, sizeof(mydata));
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
			if (pState->y >= 296) {
				if (pState->x < 120) {
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
		GUI_ClearRect(0, 60, 240, 296);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296, 240, 320);
		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(60, 0, 240);
		GUI_DrawHLine(119, 0, 240);
		GUI_DrawHLine(177, 0, 240);
		GUI_DrawHLine(236, 0, 240);
		GUI_DrawHLine(295, 0, 240);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//д��
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_DispStringAt("����Ԥ��", 72, 23);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt("һ", 12, 60.8+20.4);
		GUI_DispStringAt("��", 12, 119.2+20.4);
		GUI_DispStringAt("��", 12, 177.6+20.4);
		GUI_DispStringAt("��", 12, 236+20.4);

		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("����", 60, 300);
		GUI_DispStringHCenterAt("ȷ��", 180, 300);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_FontHZ12);

		sprintf(buffer1, "����:%.1f ml", shuyeData[0][0]);
		GUI_DispStringAt(buffer1, 110, 60.8 + 4.8);
		sprintf(buffer1, "����:%.1f ml", shuyeData[1][0]);
		GUI_DispStringAt(buffer1, 110, 119.2 + 4.8);
		sprintf(buffer1, "����:%.1f ml", shuyeData[2][0]);
		GUI_DispStringAt(buffer1, 110, 177.6 + 4.8);
		sprintf(buffer1, "����:%.1f ml", shuyeData[3][0]);
		GUI_DispStringAt(buffer1, 110, 236 + 4.8);

		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[0][1]);
		GUI_DispStringAt(buffer1,    60, 60.8 + 22);
		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[1][1]);
		GUI_DispStringAt(buffer1, 60, 119.2+ 22);
		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[2][1]);
		GUI_DispStringAt(buffer1, 60, 177.6+ 22);
		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[3][1]);
		GUI_DispStringAt(buffer1,60, 236+ 22);

		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[0][3]);
		GUI_DispStringAt(buffer1, 60, 60.8 + 40.8);
		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[1][3]);
		GUI_DispStringAt(buffer1, 60, 119.2 + 40.8);
		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[2][3]);
		GUI_DispStringAt(buffer1, 60, 177.6 + 40.8);
		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[3][3]);
		GUI_DispStringAt(buffer1, 60, 236 + 40.8);

		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[0][2]);
		GUI_DispStringAt(buffer1, 155, 60.8 + 22);
		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[1][2]);
		GUI_DispStringAt(buffer1, 155, 119.2 + 22);
		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[2][2]);
		GUI_DispStringAt(buffer1, 155, 177.6 + 22);
		sprintf(buffer1, "�ٶ�:%.1f ml/min", shuyeData[3][2]);
		GUI_DispStringAt(buffer1, 155, 236 + 22);

		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[0][4]);
		GUI_DispStringAt(buffer1, 155, 60.8 + 40.8);
		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[1][4]);
		GUI_DispStringAt(buffer1, 155, 119.2 + 40.8);
		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[2][4]);
		GUI_DispStringAt(buffer1, 155, 177.6 + 40.8);
		sprintf(buffer1, "ʱ��:%.1f min", shuyeData[3][4]);
		GUI_DispStringAt(buffer1, 155, 236 + 40.8);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
				WM_DeleteWindow(pMsg->hWin);
			if (pState->y > 60.8 && pState->y < 119.2) {
				W_pageShuyeSetting(0);
			}
			else if (pState->y > 119.2 && pState->y < 177.6) {
				W_pageShuyeSetting(1);
			}
			else if (pState->y > 177.6 && pState->y < 236) {
				W_pageShuyeSetting(2);
			}
			else if (pState->y > 236 && pState->y < 296) {
				W_pageShuyeSetting(3);
			}
			else if (pState->y >= 296) {
				if (pState->x < 120) {
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
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 85, 240, 296);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296, 240, 320);
		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(85, 0, 240);
		GUI_DrawHLine(136, 0, 240);
		GUI_DrawHLine(187, 0, 240);
		GUI_DrawHLine(238, 0, 240);
		GUI_DrawHLine(295, 0, 240);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120, 296, 320);
		//д��
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_DispStringHCenterAt("Ԥ����", 120, 40);


		GUI_SetFont(&GUI_FontHZ16);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("����", 60, 300);
		GUI_DispStringHCenterAt("ȷ��", 180, 300);

		// GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		// GUI_SetBkColor(GUI_WHITE);
		// GUI_SetFont(&GUI_FontHZ16);
		// GUI_DispStringAt("����:        ml", 85, 90);
		// GUI_DispStringAt("ʱ��:            ", 85, 110);
		// GUI_DispStringAt("����:        ml", 85, 140);
		// GUI_DispStringAt("ʱ��:            ", 85, 160);
		// GUI_DispStringAt("����:        ml", 85, 193);
		// GUI_DispStringAt("ʱ��:            ", 85, 213);
		// GUI_DispStringAt("����:        ml", 85, 243);
		// GUI_DispStringAt("ʱ��:            ", 85, 263);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 296) {
				if (pState->x < 120) {
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
		GUI_ClearRect(0, 197, 240, 259);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_ClearRect(0, 259, 240, 320);

		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(197, 0, 240);
		GUI_DrawHLine(259, 0, 240);

		//д��
		GUI_SetColor(MYCOLOR_PAGEHOME_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ24);
		GUI_DispStringHCenterAt("MULTI-ȫ�Զ�", 120, 70);
		GUI_DispStringHCenterAt("������Һ��", 120, 100);

		GUI_SetColor(MYCOLOR_PAGEHOME_SETTING_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringHCenterAt("��Һ����", 120, 222);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_DispStringHCenterAt("ϵͳ����", 120, 280);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 259 && pState->y>197) {//��Һ����
				WM_DeleteWindow(pMsg->hWin);
				W_pageShuyeSetting(0);
			}
			else if (pState->y > 259 && pState->y < 320) {//ϵͳ����
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
		GUI_ClearRect(0, 109, 240, 320);
		//����
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(109, 0, 240);
		GUI_DrawHLine(150, 0, 240);
		GUI_DrawHLine(193, 0, 240);
		GUI_DrawLine(0, 235, 240, 235);
		GUI_DrawHLine(278, 0, 240);
		//д��
		GUI_SetColor(MYCOLOR_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ32);
		GUI_DispStringHCenterAt("ϵͳ����", 120, 51.6);

		GUI_SetColor(MYCOLOR_CONTENT_TEXT);
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringHCenterAt("��������", 120, 108 + 10);
		GUI_DispStringHCenterAt("ϵͳ����", 120, 150.4 + 10);
		GUI_DispStringHCenterAt("ϵͳ״̬", 120, 192.8 + 10);
		GUI_DispStringHCenterAt("��������", 120, 235.2 + 10);
		GUI_DispStringHCenterAt("����", 120, 277.6 + 10);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 17.9&&pState->x>191) {
				GUI_DispStringAt("0", 0, 0);
			}
			else if (pState->y > 108 && pState->y < 150) {
				GUI_DispStringAt("1", 0, 0);
			}
			else if (pState->y >= 150 && pState->y<193) {
				GUI_DispStringAt("2", 0, 0);
			}
			else if (pState->y >= 193 && pState->y <= 235) {
				GUI_DispStringAt("3", 0, 0);
			}
			else if (pState->y >= 235 && pState->y <= 278) {
				GUI_DispStringAt("4", 0, 0);
			}
			else if (pState->y >= 278) {
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

	aMultipage = MULTIPAGE_CreateEx(0, 84, 240, 212, *hWnd, WM_CF_SHOW, 0, 0);
	MULTIPAGE_SetFont(aMultipage, &GUI_Font16B_1);
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     1      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     2      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     3      ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "     4      ");
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
		GUI_DispStringAt("����:", 16, 16);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt("ML", 130, 24);
		GUI_SetFont(&GUI_FontHZ16);
		GUI_DispStringAt("����1:", 5, 50);
		GUI_DispStringAt("ʱ��1:", 5, 85);
		GUI_DispStringAt("����2:", 125, 50);
		GUI_DispStringAt("ʱ��2:", 125, 85);
		GUI_SetFont(&GUI_Font10_1);
		GUI_DispStringAt("ml/min", 80, 50+3);
		GUI_DispStringAt("min", 80, 85+3);
		GUI_DispStringAt("ml/min", 200, 50+3);
		GUI_DispStringAt("min", 200, 85+3);
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
					shuyeData[id_bottle][2] = 5;//Ĭ����5ml/min
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
