// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
#pragma once
#pragma warning(disable : 4996)
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDKDDKVer.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <assert.h>


//STL
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <algorithm>
#include <bitset>
#include <stack>
#include <iostream>
#include <fstream>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include "Common/UTILS.h"


//======================================
//##			디파인문			  ##
//======================================
#define WINNAME		(LPTSTR)(TEXT("경일 프로그래밍 18기"))
#define WINSTARTX   100
#define WINSTARTY   100
#define WINSIZEX	1024
#define	WINSIZEY	768
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//player key setting
#define P1_UP			0
#define P1_DOWN			1
#define P1_LEFT			2
#define P1_RIGHT		3
#define P1_EVENT		4
#define P1_USEITEM		5
#define P1_Z            6
#define P1_X            7
#define P1_A            8
#define P1_Q			9
#define P1_P			10
#define P1_T			11
#define P1_B			12
#define P1_N			13

#define GAME_MENUPROTO	45
#define GAME_CHANGEMAP  46
#define GAME_MENU		47
#define GAME_LMOUSE		48
#define GAME_RMOUSE		49
#define GAME_SHOWFPS    50
#define GAME_DEBUGMODE	51
#define GAME_RECTMODE   52
#define GAME_RTT		53

//======================================
//## 메인게임 릴리즈에서 사용하는 녀석##
//======================================
#define SAFE_DELETE(p) {if(p) { delete(p); (p) = nullptr;} }

//================================================
//             Singleton Macro                  //
//================================================
#define DECLARE_SINGLE(TYPE) \
static TYPE* mInst; \
\
public: \
	static TYPE* GetInst() {\
		if (!mInst)\
			return mInst = new TYPE;\
		return mInst;\
	}\
	void Destroy() {\
		SAFE_DELETE(mInst);\
	} \
private:\
	TYPE();\
	~TYPE();

#define DEFINITION_SINGLE(TYPE) TYPE* TYPE::mInst = nullptr;
#define GET_SINGLE(TYPE) TYPE::GetInst()
#define RELEASE_SINGLE(TYPE) TYPE::GetInst()->Destroy()

//================================================
//전역변수(인스턴스, 윈도우 핸들, 마우스 좌표)  ##
//================================================
extern HINSTANCE m_hInstance;
extern HWND m_hWnd;
extern POINT m_ptMouse;
extern bool m_bLoop;
extern bool m_showFPS;
extern bool m_showRect;
extern bool m_debugMode;
