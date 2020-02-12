#include "stdafx.h"
#include "PocketmonBagScene.h"
#include "Common/SystemManagers.h"

PocketmoninfoScene::PocketmoninfoScene(std::vector<std::shared_ptr<PocketMon>>& _Pocketmons)
	: Pocketmons(_Pocketmons)
{
}

PocketmoninfoScene::~PocketmoninfoScene()
{
}

bool PocketmoninfoScene::init()
{
	m_Base = IMAGEMANAGER->addImage("Base","images/poketmonbagBase.bmp",WINSIZEX,WINSIZEY,true,RGB(255,0,255));
	m_mainRect = UTIL::IRectMake(5, 78, 318, 220);
	m_mainOn = IMAGEMANAGER->addImage("mainOn", "images/pocketmonBagMainOn.bmp", m_mainRect.left, m_mainRect.top, 368, 287, true, RGB(255, 0, 255));
	m_mainOff = IMAGEMANAGER->addImage("mainOff", "images/pocketmonBagMainOff.bmp", m_mainRect.left, m_mainRect.top, 367, 286, true, RGB(255, 0, 255));
	
	m_subRect0 = UTIL::IRectMake(365, 37, 500, 100);
	m_sub0On = IMAGEMANAGER->addImage("sun0On", "images/pocketmonBagSubOn.bmp", m_subRect0.left, m_subRect0.top, 651, 119, true, RGB(255, 0, 255));
	m_sub0Off = IMAGEMANAGER->addImage("sun0Off", "images/pocketmonBagSubOff.bmp", m_subRect0.left, m_subRect0.top, 651, 119, true, RGB(255, 0, 255));

	m_subRect1= UTIL::IRectMake(365, 153, 500, 100);
	m_sub1On = IMAGEMANAGER->addImage("sun1On", "images/pocketmonBagSubOn.bmp", m_subRect1.left, m_subRect1.top, 651, 119, true, RGB(255, 0, 255));
	m_sub1Off = IMAGEMANAGER->addImage("sun1Off", "images/pocketmonBagSubOff.bmp", m_subRect1.left, m_subRect1.top, 651, 119, true, RGB(255, 0, 255));

	m_subRect2 = UTIL::IRectMake(365, 269, 500, 100);
	m_sub2On = IMAGEMANAGER->addImage("sun2On", "images/pocketmonBagSubOn.bmp", m_subRect2.left, m_subRect2.top, 651, 119, true, RGB(255, 0, 255));
	m_sub2Off = IMAGEMANAGER->addImage("sun2Off", "images/pocketmonBagSubOff.bmp", m_subRect2.left, m_subRect2.top, 651, 119, true, RGB(255, 0, 255));

	m_subRect3 = UTIL::IRectMake(365, 385, 500, 100);
	m_sub3On = IMAGEMANAGER->addImage("sun3On", "images/pocketmonBagSubOn.bmp", m_subRect3.left, m_subRect3.top, 651, 119, true, RGB(255, 0, 255));
	m_sub3Off = IMAGEMANAGER->addImage("sun3Off", "images/pocketmonBagSubOff.bmp", m_subRect3.left, m_subRect3.top, 651, 119, true, RGB(255, 0, 255));

	m_subRect4 = UTIL::IRectMake(365, 501, 500, 100);
	m_sub4On = IMAGEMANAGER->addImage("sun4On", "images/pocketmonBagSubOn.bmp", m_subRect4.left, m_subRect4.top, 651, 119, true, RGB(255, 0, 255));
	m_sub4Off = IMAGEMANAGER->addImage("sun4Off", "images/pocketmonBagSubOff.bmp", m_subRect4.left, m_subRect4.top, 651, 119, true, RGB(255, 0, 255));


	m_indexCursor = 0;

	return true;
}

void PocketmoninfoScene::update(float _deltaTime)
{
	//temp
	if (KEYMANAGER->isOnceKeyDown(P1_USEITEM)) {
		Pocketmons.pop_back();
	}

	//마지막 인덱스는 취소키
	m_indexCursorMax = Pocketmons.size();

	if (KEYMANAGER->isOnceKeyDown(P1_X)) 
	{
		SCENEMANAGER->scenePop();
	}

	if (KEYMANAGER->isOnceKeyDown(P1_UP))
	{
		m_indexCursor--;
	}
	else if (KEYMANAGER->isOnceKeyDown(P1_DOWN))
	{
		m_indexCursor++;
	}

	//인덱스 커서 0아래면 최대로 또는 그 반대
	if (m_indexCursor < 0)
	{
		m_indexCursor = m_indexCursorMax;
	}
	else if (m_indexCursor > m_indexCursorMax)
	{
		m_indexCursor = 0;
	}
	//취소일때 확인누르면 끄기
	if (m_indexCursor == m_indexCursorMax && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		Pocketmons.pop_back();
	}
}

void PocketmoninfoScene::release()
{
}

void PocketmoninfoScene::render(HDC hdc)
{
	m_Base->render(hdc);

	/*int cnt = 0;
	for (auto e : Pocketmons) {
		UTIL::PrintText(hdc, e->m_name.c_str(), "소야바른9", 100, 100 + cnt * 70, 30);
		cnt++;
	}
	*/

	if (m_indexCursor == 0)
	{
		m_mainOn->render(hdc,m_mainRect.left-3,m_mainRect.top+3);
	}
	else
	{
		m_mainOff->render(hdc, m_mainRect.left, m_mainRect.top+3);
	}

	if (Pocketmons.size() >= 2)
	{
		if (m_indexCursor == 1)
		{
			m_sub0On->render(hdc, m_subRect0.left, m_subRect0.top);
		}
		else
		{
			m_sub0Off->render(hdc, m_subRect0.left, m_subRect0.top);
		}

	}
	if(Pocketmons.size() >= 3)
	{
		if (m_indexCursor == 2)
		{
			m_sub1On->render(hdc, m_subRect1.left, m_subRect1.top);
		}
		else
		{
			m_sub1Off->render(hdc, m_subRect1.left, m_subRect1.top);
		}
	}
	if (Pocketmons.size() >= 4)
	{
		if (m_indexCursor == 3)
		{
			m_sub2On->render(hdc, m_subRect2.left, m_subRect2.top);
		}
		else
		{
			m_sub2Off->render(hdc, m_subRect2.left, m_subRect2.top);
		}
	}
	if (Pocketmons.size() >= 5)
	{
		if (m_indexCursor == 4)
		{
			m_sub3On->render(hdc, m_subRect3.left, m_subRect3.top);
		}
		else
		{
			m_sub3Off->render(hdc, m_subRect3.left, m_subRect3.top);
		}
	}
	if (Pocketmons.size() >= 6)
	{
		if (m_indexCursor == 5)
		{
			m_sub4On->render(hdc, m_subRect4.left, m_subRect4.top);
		}
		else
		{
			m_sub4Off->render(hdc, m_subRect4.left, m_subRect4.top);
		}
	}
}

void PocketmoninfoScene::afterRender(HDC hdc)
{
}

void PocketmoninfoScene::debugRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, m_mainRect, false,false);
	UTIL::DrawColorRect(hdc, m_subRect0, false,false);
	UTIL::DrawColorRect(hdc, m_subRect1, false,false);

	
}
