#include "mypage.h"
#define __Y 2.5
#define __X 2
float shuyeData[4][5];
int my_index = 0;
float data[5];
int testdata = 0, testdata1 = 0;
MULTIPAGE_Handle aMultipage;
typedef struct {
	U32 color;
	int id;
}mydata;
char buffer_left[20], buffer_used[20], buffer_speed[4];
mydata data_send[4] = { { GUI_GREEN ,1 },{ GUI_GREEN ,2 },{ GUI_GREEN ,3 },{ GUI_GREEN ,4 } };
mydata change_data;
WM_HTIMER hTimer;

int id_bottle = 0;
WM_HWIN hchild[4];
int speed = 0;

static WM_CALLBACK * _pEditCallback;
void pageSetting(WM_MESSAGE *pMsg);
void pageHome(WM_MESSAGE *pMsg);
void pageShuyeSetting(WM_MESSAGE *pMsg);
void pageDisplay(WM_MESSAGE *pMsg);
void pageShuyeDisplay(WM_MESSAGE *pMsg);
void _cbBottle4(WM_MESSAGE *pMsg);
void _cbDialogNumPad(WM_MESSAGE *pMsg);
void _cbEdit(WM_MESSAGE * pMsg);
void _cbEditAddKey(EDIT_Handle hObj, int Key);
void _cbchild1(WM_MESSAGE *pMsg);
void W_pageHome(void);
void W_pageShuyeSetting(int page);
void W_pageSetting(void);
void W_pageDisplay(void);
void W_pageShuyeDisplay(void);
void createMultipage(WM_HWIN *hWnd, int *page);
void _MultipageSkin(WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void _mCreatSpinBox(int x0, int y0, int xSize, int ySize, GUI_HWIN hParent, int WinFlags, int Id, int Min, int Max);
//void my_creatBlock(int x0, int y0, int xSize, int ySize, int id, int color);


static const GUI_WIDGET_CREATE_INFO _aDialogNumPad[] = {
	//
	//  Function                 Text      Id					 Px         Py         Dx           Dy
	//
	{ WINDOW_CreateIndirect,    0,        0,				     0,	        217 * __Y, 240 * __X, 78 * __Y },
	{ BUTTON_CreateIndirect,   "7",      GUI_ID_USER + 7,		 0,			0,		   60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "8",      GUI_ID_USER + 8,		 60 * __X,  0,		   60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "9",      GUI_ID_USER + 9,	     120 * __X, 0,		   60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "4",      GUI_ID_USER + 4,		 0,	        26 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "5",      GUI_ID_USER + 5,		 60 * __X,	26 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "6",      GUI_ID_USER + 6,	     120 * __X, 26 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "1",      GUI_ID_USER + 1,		 0,	        52 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "2",      GUI_ID_USER + 2,		 60 * __X,	52 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "3",      GUI_ID_USER + 3,		 120 * __X, 52 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "Del",    GUI_ID_USER + 11,		 180 * __X, 0,         60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   "0",      GUI_ID_USER + 0,		 180 * __X, 26 * __Y,  60 * __X,  26 * __Y },
	{ BUTTON_CreateIndirect,   ".",      GUI_ID_USER + 10,		 180 * __X, 52 * __Y,  60 * __X,  26 * __Y },
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
	GUI_Init();
	WM_EnableMemdev(WM_HBKWIN); //启用储存设备
	W_pageHome();

	//GUI_PID_STATE test_point;
	while (1) {
		//GUI_PID_GetState(&test_point);
		//GUI_DispStringAt("TEST", 240, 0);
		//GUI_DispDecAt(test_point.x, 240, 20, 3);
		//GUI_DispDecAt(test_point.y, 240, 40, 3);
		GUI_Delay(500);
	}
}
void W_pageDisplay(void) {
	my_index = 0; //很神奇
	WM_CreateWindow(0, 0, 240 * __X, 320 * __Y, WM_CF_SHOW, pageDisplay, 0);
}
void W_pageHome(void) {
	WM_CreateWindow(0, 0, 240 * __X, 320 * __Y, WM_CF_SHOW, pageHome, 0);
	GUI_Exec();
}
void W_pageSetting(void) {
	WM_CreateWindow(0, 0, 240 * __X, 320 * __Y, WM_CF_SHOW, pageSetting, 0);
	GUI_Exec();
	GUI_SetColor(MYCOLOR_TITLE_TEXT);
	GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
	//while (1)
	//{
	//	GUI_Delay(20);
	//}

}
void W_pageShuyeSetting(int page) {
	WM_HWIN hWnd, hNumPad;
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
	hWnd = WM_CreateWindow(0, 0, 240 * __X, 320 * __Y, WM_CF_SHOW, pageShuyeSetting, 0);
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
	BUTTON_SetSkinFlexProps(&MY_BUTTON_SKIN_ENABLE, 2);
	BUTTON_SetSkinFlexProps(&MY_BUTTON_SKIN_PRESSED, 0);
	hNumPad = GUI_CreateDialogBox(_aDialogNumPad, GUI_COUNTOF(_aDialogNumPad), _cbDialogNumPad, hWnd, 0, 0); /* Create the numpad dialog */
	WM_SetStayOnTop(hNumPad, 1);
	createMultipage(&hWnd, &page);

}
void W_pageShuyeDisplay(void) {
	my_index = 0; //很神奇
	WM_CreateWindow(0, 0, 240 * __X, 320 * __Y, WM_CF_SHOW, pageShuyeDisplay, 0);
}
void _cbchild1(WM_MESSAGE *pMsg) {
	mydata data_receive;
	char id[2];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		WM_GetUserData(pMsg->hWin, &data_receive, sizeof(mydata));
		GUI_SetBkColor(data_receive.color);
		GUI_Clear();
		GUI_SetColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font20_1);
		sprintf(id, "%d", data_receive.id);
		GUI_DispStringHCenterAt(id, 9 * __X, 1 * __Y);
		break;
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
void pageDisplay(WM_MESSAGE *pMsg) {
	WM_PID_STATE_CHANGED_INFO  *pState;
	switch (pMsg->MsgId)
	{
	case WM_TIMER:
		if (shuyeData[id_bottle][0] == 0 || (shuyeData[id_bottle][3] == 0 && shuyeData[id_bottle][4] == 0)) {
			id_bottle++;
			if (id_bottle >= 4) id_bottle = 0;
		}
		if (shuyeData[id_bottle][3] > 0 || shuyeData[id_bottle][4] > 0) { //剩余输液时间是否为0
			testdata1++;
			if (shuyeData[id_bottle][3] != 0) {
				testdata = --shuyeData[id_bottle][3];
				speed = shuyeData[id_bottle][1];
			}
			else {
				change_data.color = GUI_BLUE;
				change_data.id = id_bottle + 1;
				WM_SetUserData(hchild[id_bottle], &change_data, sizeof(mydata));
				testdata = --shuyeData[id_bottle][4];
				speed = shuyeData[id_bottle][2];
			}
			if (shuyeData[id_bottle][4] == 0 && shuyeData[id_bottle][3] == 0) {
				change_data.color = GUI_BLACK;
				change_data.id = id_bottle + 1;
				WM_SetUserData(hchild[id_bottle], &change_data, sizeof(mydata));
			}
		}
		sprintf(buffer_speed, "%d", speed);
		sprintf(buffer_left, "%02d:%02d:%02d", testdata / 3600, testdata / 60, testdata % 60);
		sprintf(buffer_used, "%02d:%02d:%02d", testdata1 / 3600, testdata1 / 60, testdata1 % 60);
		//testdata--;
		if (testdata1 % 2) {
			WM_HideWindow(hchild[id_bottle]);
		}
		else {
			WM_ShowWindow(hchild[id_bottle]);
		}
		WM_InvalidateWindow(pMsg->hWin); //使窗口无效，从而进行更新
		WM_RestartTimer(hTimer, 1000);
		break;

	case WM_PAINT:
		//画背景
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_Clear();
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_ClearRect(0, 296 * __Y, 240 * __X, 320 * __Y);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120 * __X, 296 * __Y, 320 * __Y);
		//写字
		GUI_SetFont(&GUI_Font24_1);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT1);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BACKGROUND);
		GUI_DispStringAt("shuyesulv", 5 * __X, 56 * __Y);
		GUI_DispStringAt("shuyeshul", 5 * __X, 126 * __Y);
		GUI_DispStringAt("shuyeTime", 5 * __X, 224 * __Y);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT2);
		GUI_DispStringAt("Used", 150 * __X, 182 * __Y);
		GUI_DispStringAt("Left", 150 * __X, 236 * __Y);
		GUI_SetColor(MYCOLOR_PAGEDISPLAY_TEXT3);
		GUI_DispStringHCenterAt(buffer_used, 175 * __X, 206 * __Y);
		GUI_DispStringHCenterAt(buffer_left, 175 * __X, 262 * __Y);
		GUI_SetFont(&GUI_FontD36x48);
		GUI_DispStringAt(buffer_speed, 126 * __X, 56 * __Y);//需要大一点的字体
												//按钮字体
		GUI_SetFont(&GUI_Font16_1);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGEDISPLAY_BUTTON);
		GUI_DispStringHCenterAt("BACK", 60 * __X, 300 * __Y);
		GUI_DispStringHCenterAt("PAUSE", 180 * __X, 300 * __Y);

		break;
	case WM_CREATE:
		hTimer = WM_CreateTimer(pMsg->hWin, 0, 1000, 0);
		for (int i = 0; i < 4; i++) {
			if (shuyeData[i][0] == 0)continue;//如果容量为0，则不创建
			hchild[i] = WM_CreateWindowAsChild((129 + i * 26)* __X, 126 * __Y, 18 * __X, 18 * __Y, pMsg->hWin, WM_CF_SHOW, _cbchild1, sizeof(mydata));
			WM_SetUserData(hchild[i], &data_send[i], sizeof(mydata));
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
			if (pState->y >= 296 * __Y) {
				if (pState->x < 120 * __X) {
					for (int i = 0; i < 4; i++) {
						shuyeData[i][3] /= 60;
						shuyeData[i][4] /= 60;
					}
					WM_DeleteWindow(pMsg->hWin);
					W_pageShuyeSetting(0);
				}
				else //pause
				{

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
	char tempt[20];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//画框
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 60.8* __Y, 240 * __X, 296 * __Y);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296 * __Y, 240 * __X, 320 * __Y);
		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(60.8* __Y, 0, 240 * __X);
		GUI_DrawHLine(119.2* __Y, 0, 240 * __X);
		GUI_DrawHLine(177.6* __Y, 0, 240 * __X);
		GUI_DrawHLine(236 * __Y, 0, 240 * __X);
		GUI_DrawHLine(295 * __Y, 0, 240 * __X);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120 * __X, 296 * __Y, 320 * __Y);
		//写字
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font24_1);
		GUI_DispStringAt("PRE-SETTING", 72 * __X, 23.4* __Y);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("ONE", 12.4* __X, 81.2 * __Y);
		GUI_DispStringAt("TWO", 12.4* __X, 139.6 * __Y);
		GUI_DispStringAt("THREE", 12.4* __X, 198 * __Y);
		GUI_DispStringAt("FOUR", 12.4* __X, 256.4 * __Y);

		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("BACK", 60 * __X, 300 * __Y);
		GUI_DispStringHCenterAt("CONFIRM", 180 * __X, 300 * __Y);

		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		GUI_SetBkColor(GUI_WHITE);
		GUI_SetFont(&GUI_Font13_1);

		sprintf(tempt, "valume: %.1f ml", shuyeData[0][0]);
		GUI_DispStringAt(tempt, 110 * __X, 65.6 * __Y);
		sprintf(tempt, "valume: %.1f ml", shuyeData[1][0]);
		GUI_DispStringAt(tempt, 110 * __X, 124 * __Y);
		sprintf(tempt, "valume: %.1f ml", shuyeData[2][0]);
		GUI_DispStringAt(tempt, 110 * __X, 184.2 * __Y);
		sprintf(tempt, "valume: %.1f ml", shuyeData[3][0]);
		GUI_DispStringAt(tempt, 110 * __X, 240.8 * __Y);

		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[0][1]);
		GUI_DispStringAt(tempt, 90.4 * __X, 82.8 * __Y);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[1][1]);
		GUI_DispStringAt(tempt, 90.4 * __X, 141.2 * __Y);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[2][1]);
		GUI_DispStringAt(tempt, 90.4 * __X, 199.6 * __Y);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[3][1]);
		GUI_DispStringAt(tempt, 90.4 * __X, 258 * __Y);

		sprintf(tempt, "time: %.1f min", shuyeData[0][3]);
		GUI_DispStringAt(tempt, 90.4 * __X, 101.6 * __Y);
		sprintf(tempt, "time: %.1f min", shuyeData[1][3]);
		GUI_DispStringAt(tempt, 90.4 * __X, 160 * __Y);
		sprintf(tempt, "time: %.1f min", shuyeData[2][3]);
		GUI_DispStringAt(tempt, 90.4 * __X, 218.4 * __Y);
		sprintf(tempt, "time: %.1f min", shuyeData[3][3]);
		GUI_DispStringAt(tempt, 90.4 * __X, 276.8 * __Y);

		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[0][2]);
		GUI_DispStringAt(tempt, 172.8 * __X, 82.8 * __Y);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[1][2]);
		GUI_DispStringAt(tempt, 172.8 * __X, 141.2 * __Y);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[2][2]);
		GUI_DispStringAt(tempt, 172.8 * __X, 199.6 * __Y);
		sprintf(tempt, "sudu: %.1f ml/min", shuyeData[3][2]);
		GUI_DispStringAt(tempt, 172.8 * __X, 258 * __Y);

		sprintf(tempt, "time: %.1f min", shuyeData[0][4]);
		GUI_DispStringAt(tempt, 172.8 * __X, 101.6 * __Y);
		sprintf(tempt, "time: %.1f min", shuyeData[1][4]);
		GUI_DispStringAt(tempt, 172.8 * __X, 160 * __Y);
		sprintf(tempt, "time: %.1f min", shuyeData[2][4]);
		GUI_DispStringAt(tempt, 172.8 * __X, 218.4 * __Y);
		sprintf(tempt, "time: %.1f min", shuyeData[3][4]);
		GUI_DispStringAt(tempt, 172.8 * __X, 276.8 * __Y);

	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			WM_DeleteWindow(pMsg->hWin);
			if (pState->y > 60.8 * __Y && pState->y < 119.2* __Y) {
				W_pageShuyeSetting(0);
			}
			else if (pState->y > 119.2* __Y && pState->y < 177.6* __Y) {
				W_pageShuyeSetting(1);
			}
			else if (pState->y > 177.6* __Y && pState->y < 236 * __Y) {
				W_pageShuyeSetting(2);
			}
			else if (pState->y > 236 * __Y && pState->y < 296 * __Y) {
				W_pageShuyeSetting(3);
			}
			else if (pState->y >= 296 * __Y) {
				if (pState->x < 120 * __X) {
					W_pageShuyeSetting(0);
				}
				else {
					W_pageDisplay();
					for (int i = 0; i < 4; i++) {
						shuyeData[i][3] *= 60;
						shuyeData[i][4] *= 60;
					}
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
	GUI_HWIN hItem;
	char s[5];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_Clear();

		//画框
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_CONTENT);
		GUI_ClearRect(0, 85 * __Y, 240 * __X, 296 * __Y);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_ClearRect(0, 296 * __Y, 240 * __X, 320 * __Y);
		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(85 * __Y, 0, 240 * __X);
		GUI_DrawHLine(136 * __Y, 0, 240 * __X);
		GUI_DrawHLine(187* __Y * __Y, 0, 240 * __X);
		GUI_DrawHLine(238 * __Y, 0, 240 * __X);
		GUI_DrawHLine(295 * __Y, 0, 240 * __X);
		GUI_SetColor(GUI_WHITE);
		GUI_DrawVLine(120 * __X, 296 * __Y, 320 * __Y);
		//写字
		GUI_SetColor(MYCOLOR_PAGESHUYESETTING_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font24_1);
		GUI_DispStringHCenterAt("PRE-SETTING", 120 * __X, 40 * __Y);


		GUI_SetFont(&GUI_Font16_1);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND);
		GUI_DispStringHCenterAt("BACK", 60 * __X, 300 * __Y);
		GUI_DispStringHCenterAt("CONFIRM", 180 * __X, 300 * __Y);

		//GUI_SetColor(MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2);
		//GUI_SetBkColor(GUI_WHITE);
		//GUI_SetFont(&GUI_Font16_1);
		//GUI_DispStringAt("valume:        ml", 85 * __Y, 90 * __Y);
		//GUI_DispStringAt("time:            ", 85 * __Y, 110 * __Y);
		//GUI_DispStringAt("valume:        ml", 85 * __Y, 140 * __Y);
		//GUI_DispStringAt("time:            ", 85 * __Y, 160 * __Y);
		//GUI_DispStringAt("valume:        ml", 85 * __Y, 193 * __Y);
		//GUI_DispStringAt("time:            ", 85 * __Y, 213 * __Y);
		//GUI_DispStringAt("valume:        ml", 85 * __Y, 243 * __Y);
		//GUI_DispStringAt("time:            ", 85 * __Y, 263 * __Y);



	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y >= 296 * __Y) {
				if (pState->x < 120 * __X) {
					WM_DeleteWindow(pMsg->hWin);
					W_pageHome();
				}
				else {
					//save the data
					for (int i = 0; i < 4; i++) {
						for (int j = 0; j < 5; j++) {
							hItem = WM_GetDialogItem(MULTIPAGE_GetWindow(aMultipage, i), GUI_ID_EDIT0 + j);
							EDIT_GetText(hItem, s, 4);
							sscanf(s, "%f", &shuyeData[i][j]);
							//if (j == 3 || j == 4) {
							//	shuyeData[i][j] *= 60;
							//}
						}
					}
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

		//画框
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_ClearRect(0, 197 * __Y, 240 * __X, 259 * __Y);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_ClearRect(0, 259 * __Y, 240 * __X, 320 * __Y);

		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(197 * __Y, 0, 240 * __X);
		GUI_DrawHLine(259 * __Y, 0, 240 * __X);

		//写字
		GUI_SetColor(MYCOLOR_PAGEHOME_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font24_1);
		GUI_DispStringHCenterAt("MULTI-quanzid", 120 * __X, 70 * __Y);
		GUI_DispStringHCenterAt("zhinegnshuyebao", 120 * __X, 100 * __Y);

		GUI_SetColor(MYCOLOR_PAGEHOME_SETTING_TEXT);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SHUYE_BACKGROUND);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringHCenterAt("shuyeshezhi", 120 * __X, 218 * __Y);
		GUI_SetBkColor(MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND);
		GUI_DispStringHCenterAt("zhinegnshuyebao", 120 * __X, 280 * __Y);
		break;
	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 259 * __Y && pState->y>197 * __Y) {//输液设置
				WM_DeleteWindow(pMsg->hWin);
				W_pageShuyeSetting(0);
			}
			else if (pState->y > 259 * __Y && pState->y < 320 * __Y) {//系统设置
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
		//画背景
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_ClearRect(0, 109 * __Y, 240 * __X, 320 * __Y);
		//画线
		GUI_SetPenSize(1);
		GUI_SetColor(MYCOLOR_LINE);
		GUI_DrawHLine(109 * __Y, 0, 240 * __X);
		GUI_DrawHLine(150 * __Y, 0, 240 * __X);
		GUI_DrawHLine(193 * __Y, 0, 240 * __X);
		GUI_DrawLine(0, 235 * __Y, 240 * __X, 235 * __Y);
		GUI_DrawHLine(278 * __Y, 0, 240 * __X);
		//写字
		GUI_SetColor(MYCOLOR_TITLE_TEXT);
		GUI_SetBkColor(MYCOLOR_TITLE_BACKGROUND);
		GUI_SetFont(&GUI_Font20_1);
		GUI_DispStringHCenterAt("System Setting", 120 * __X, 51.6*2.5);

		GUI_SetColor(MYCOLOR_CONTENT_TEXT);
		GUI_SetBkColor(MYCOLOR_TEXT_BACKGROUND);
		GUI_SetFont(&GUI_Font16B_1);
		GUI_DispStringHCenterAt("Personal Setting", 120 * __X, 118 * __Y);
		GUI_DispStringHCenterAt("System Update", 120 * __X, 160.4* __Y);
		GUI_DispStringHCenterAt("System Statistics", 120 * __X, 202.8* __Y);
		GUI_DispStringHCenterAt("About", 120 * __X, 245.2* __Y);
		GUI_DispStringHCenterAt("Back", 120 * __X, 287.6* __Y);

	case WM_PID_STATE_CHANGED:
		pState = (WM_PID_STATE_CHANGED_INFO *)pMsg->Data.p;
		if ((pState->StatePrev == 0) && (pState->State == 1)) {
			if (pState->y < 17.9*2.5&&pState->x>191 * __Y) {
				GUI_DispStringAt("0", 0, 0);
			}
			else if (pState->y > 108 * __Y && pState->y < 150 * __Y) {
				GUI_DispStringAt("1", 0, 0);
			}
			else if (pState->y >= 150 * __Y && pState->y<193 * __Y) {
				GUI_DispStringAt("2", 0, 0);
			}
			else if (pState->y >= 193 * __Y && pState->y <= 235 * __Y) {
				GUI_DispStringAt("3", 0, 0);
			}
			else if (pState->y >= 235 * __Y && pState->y <= 278 * __Y) {
				GUI_DispStringAt("4", 0, 0);
			}
			else if (pState->y >= 278 * __Y) {
				WM_DeleteWindow(pMsg->hWin);
				W_pageHome();
			}
		}
		break;
	default:
		break;
	}

}	  
void createMultipage(WM_HWIN *hWnd, int *page) {
	WM_HWIN pageBottle;
	MULTIPAGE_SKINFLEX_PROPS multipage_skin_SELECTED = {
		GUI_WHITE,{ GUI_WHITE,GUI_WHITE },{ GUI_WHITE ,GUI_WHITE },0Xe3d7d4,GUI_BLACK
	};
	MULTIPAGE_SKINFLEX_PROPS multipage_skin_ENABLE = {
		GUI_YELLOW,{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
		{ MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND ,MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND },
		MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND,GUI_BLACK
	};
	GUI_WIDGET_CREATE_INFO _aDialogCreate4[] = {
		{ WINDOW_CreateIndirect,    "Dialog 4",               0,            0,   0, 240 * __Y, 212 * __X, FRAMEWIN_CF_MOVEABLE },
		{ EDIT_CreateIndirect,		"bottle1",     GUI_ID_EDIT0,           90 * __X,  17 * __Y,  30 * __X,  20 * __Y, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "speed1",       GUI_ID_EDIT1,           50 * __X,  50 * __Y,  30 * __X,  15 * __Y, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "speed2",       GUI_ID_EDIT2,           170 * __X,  50 * __Y,  30 * __X,  15 * __Y, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "time1",       GUI_ID_EDIT3,           50 * __X,  85 * __Y,  30 * __X,  15 * __Y, EDIT_CF_HCENTER },
		{ EDIT_CreateIndirect,      "time2",       GUI_ID_EDIT4,           170 * __X,  85 * __Y,  30 * __X,  15 * __Y, EDIT_CF_HCENTER }
	};

	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);

	MULTIPAGE_SetSkinFlexProps(&multipage_skin_SELECTED, MULTIPAGE_SKINFLEX_PI_SELECTED);
	MULTIPAGE_SetSkinFlexProps(&multipage_skin_ENABLE, MULTIPAGE_SKINFLEX_PI_ENABLED);

	aMultipage = MULTIPAGE_CreateEx(0, 84 * __Y, 240 * __X, 212 * __Y, *hWnd, WM_CF_SHOW, 0, 0);
	MULTIPAGE_SetFont(aMultipage, &GUI_Font16B_1);
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	//WM_SetUserData(pageBottle, "botttle1",sizeof("botttle1"));
	MULTIPAGE_AddPage(aMultipage, pageBottle, "              1            ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	//WM_SetUserData(pageBottle, "botttle2",9);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "              2            ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	//WM_SetUserData(pageBottle, "botttle3",9);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "              3             ");
	pageBottle = GUI_CreateDialogBox(_aDialogCreate4, GUI_COUNTOF(_aDialogCreate4), _cbBottle4, WM_UNATTACHED, 0, 0);
	//WM_SetUserData(pageBottle, "botttle4",9);
	MULTIPAGE_AddPage(aMultipage, pageBottle, "              4             ");
	MULTIPAGE_SelectPage(aMultipage, *page);

}
void _cbBottle4(WM_MESSAGE *pMsg) {
	WM_HWIN hEdit, hEdit1;
	unsigned Id;
	int NCode;
	char buff[5], getmessage[4];
	switch (pMsg->MsgId)
	{
	case WM_PAINT:

		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		GUI_SetFont(&GUI_Font20_1);
		GUI_SetColor(GUI_BLACK);
		GUI_DispStringAt("bottle1:", 16 * __X, 16 * __Y);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("ML", 130 * __X, 24 * __Y);
		GUI_SetFont(&GUI_Font16_1);
		GUI_DispStringAt("speed1:", 5 * __X, 50 * __Y);
		GUI_DispStringAt("time1:", 5 * __X, 85 * __Y);
		GUI_DispStringAt("speed2:", 125 * __X, 50 * __Y);
		GUI_DispStringAt("time2:", 125 * __X, 85 * __Y);
		GUI_SetFont(&GUI_Font10_1);
		GUI_DispStringAt("ml/min", 80 * __X, 53 * __Y);
		GUI_DispStringAt("min", 80 * __X, 88 * __Y);
		GUI_DispStringAt("ml/min", 200 * __X, 53 * __Y);
		GUI_DispStringAt("min", 200 * __X, 88 * __Y);
		break;
	case WM_INIT_DIALOG:
		my_index++;
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

			//初始化数据
			if (shuyeData[my_index - 1][i] != 0) {
				sprintf(buff, "%.1f", shuyeData[my_index - 1][i]);
				EDIT_SetText(hEdit, buff);
			}
			else {
				EDIT_SetText(hEdit, "\0");
			}
		}
		MULTIPAGE_GetSelection(aMultipage);
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      /* Id of widget */
		NCode = pMsg->Data.v;                 /* Notification code */
		switch (NCode)
		{
		case WM_NOTIFICATION_VALUE_CHANGED:
			//hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0);
			//EDIT_GetText(hEdit1, c_valume, 4);
			//sscanf(c_valume, "%f", &data[0]);
			for (int i = 0; i < 5; i++) {   // save the data to data[5]
				hEdit = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0 + i);
				EDIT_GetText(hEdit, buff, 5);
				sscanf(buff, "%f", &data[i]);
			}
			switch (Id)
			{
			case GUI_ID_EDIT0:
				data[1] = data[2] = data[3] = data[4] = 0;
				for (int i = 1; i <= 4; i++) {
					hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT0 + i);
					EDIT_SetText(hEdit1, "\0");
					data[i] = 0;
				}
				break;
			case GUI_ID_EDIT1:
				hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
				if (data[1] != 0) {
					data[3] = data[0] / data[1];
					sprintf(buff, "%.1f", data[3]);
				}
				else {
					sprintf(buff, "%s", "err");
				}
				EDIT_SetText(hEdit1, buff);
				//break;
			case GUI_ID_EDIT3:
				if (data[3] * data[1] > data[0]) {//超出范围了
					data[3] = data[0] / data[1];
					hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT3);
					sprintf(buff, "%.1f", data[3]);
					EDIT_SetText(hEdit1, buff);

				}
				else if (data[1] * data[3] == data[0]) {//因为上面改变了data[3]，所以会自动相等
					data[4] = 0;
					data[2] = 0;
					//data[1] = data[0] / data[3];
				}
				else {//改小值了
					data[2] = 5;//默认是5ml/min
					data[4] = (data[0] - data[1] * data[3]) / data[2];
				}
				hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT2);
				sprintf(buff, "%.1f", data[2]);
				EDIT_SetText(hEdit1, buff);
			case GUI_ID_EDIT2:
				if (data[2] != 0) {
					data[4] = (data[0] - data[1] * data[3]) / data[2];
				}
				hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT4);
				sprintf(buff, "%.1f", data[4]);
				EDIT_SetText(hEdit1, buff);
				//hEdit1 = WM_GetDialogItem(pMsg->hWin, GUI_ID_EDIT1);
				//sprintf(buff, "%.1f", data[1]);
				//EDIT_SetText(hEdit1, buff);				
			case GUI_ID_EDIT4:

				break;


			default:

				break;
			}
			//EDIT_GetText(hEdit, s, 5);
			//my_index = MULTIPAGE_GetSelection(aMultipage);

			//sprintf(sDest,"%d",my_index);
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

