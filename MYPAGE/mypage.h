#ifndef _MYPAGE_H_
#define _MYPAGE_H_
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "ILI93xx.h"
#include "usart.h"
#include "24cxx.h"
#include "flash.h"
#include "malloc.h"
#include "GUI.h"
#include "includes.h"
#include  "beep.h"
#include "step_motor.h"
//#include "bitmapdisplay.h"
#include "bmpdisplay.h"
#include "EmWinHZFont.h"
#include "WM.h"
#include "DIALOG.h"
//#include "image2lcd.h"
#define MYCOLOR_TITLE_BACKGROUND 0Xf1edec
#define MYCOLOR_TEXT_BACKGROUND 0Xffffff
#define MYCOLOR_TITLE_TEXT 0X3e4040
#define MYCOLOR_LINE  0Xf0f0f0
#define MYCOLOR_CONTENT_TEXT 0X4a4a4a
#define MYCOLOR_PAGEHOME_TITLE_BACKGROUND 0xf1edec
#define MYCOLOR_PAGEHOME_SHUYE_BACKGROUND 0x98593b
#define MYCOLOR_PAGEHOME_SYSTEM_BACKGROUND 0x47b6c7
#define MYCOLOR_PAGEHOME_TITLE_TEXT 0x484848
#define MYCOLOR_PAGEHOME_SETTING_TEXT 0xe5e5e
#define MYCOLOR_PAGESHUYESETTING_TITLE_BACKGROUND MYCOLOR_PAGEHOME_TITLE_BACKGROUND
#define MYCOLOR_PAGESHUYESETTING_CONTENT GUI_WHITE
#define MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND 0xf5b712
#define MYCOLOR_PAGESHUYESETTING_TITLE_TEXT MYCOLOR_PAGEHOME_TITLE_TEXT
#define MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT1 0x333333
#define MYCOLOR_PAGESHUYESETTING_CONTENT_TEXT2 0x98593b
#define MYCOLOR_PAGEDISPLAY_BACKGROUND GUI_WHITE
#define MYCOLOR_PAGEDISPLAY_BUTTON MYCOLOR_PAGESHUYESETTING_BOTTON_BACKGROUND
#define MYCOLOR_PAGEDISPLAY_TEXT1 0x484848
#define MYCOLOR_PAGEDISPLAY_TEXT2 0x93837f
#define MYCOLOR_PAGEDISPLAY_TEXT3 0x47b6c7

#define MULTIPAGE_PI_ENABLED MULTIPAGE_SKINFLEX_PI_ENABLED

#define SCREEN_X 1
#define SCREEN_Y 1


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
void W_aboutUs(void);
void _cbaboutus(WM_MESSAGE *pMsg);
void MainTask(void);
static void _cbdialogAlert(WM_MESSAGE * pMsg);
#endif
