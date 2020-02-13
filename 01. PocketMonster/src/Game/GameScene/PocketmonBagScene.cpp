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
	m_Base = IMAGEMANAGER->findImage("Base");

	m_mainRect = UTIL::IRectMake(5, 78, 318, 220);
	m_mainIconRect = UTIL::IRectMake(56, 175, 90, 90);
	m_mainOn = IMAGEMANAGER->findImage("mainOn");
	m_mainOff = IMAGEMANAGER->findImage("mainOff");

	m_subRect0 = UTIL::IRectMake(365, 37, 500, 100);
	m_subIconRect0 = UTIL::IRectMake(409, 55, 90, 90);
	m_sub0On = IMAGEMANAGER->findImage("sun0On");
	m_sub0Off = IMAGEMANAGER->findImage("sun0Off");

	m_subRect1 = UTIL::IRectMake(365, 153, 500, 100);
	m_subIconRect1 = UTIL::IRectMake(409, 171, 90, 90);
	m_sub1On =  IMAGEMANAGER->findImage("sun1On");
	m_sub1Off = IMAGEMANAGER->findImage("sun1Off");

	m_subRect2 = UTIL::IRectMake(365, 269, 500, 100);
	m_subIconRect2 = UTIL::IRectMake(409, 277, 90, 90);
	m_sub2On = IMAGEMANAGER->findImage("sun2On");
	m_sub2Off = IMAGEMANAGER->findImage("sun2Off");

	m_subRect3 = UTIL::IRectMake(365, 385, 500, 100);
	m_subIconRect3 = UTIL::IRectMake(409, 393, 90, 90);
	m_sub3On = IMAGEMANAGER->findImage("sun3On");
	m_sub3Off = IMAGEMANAGER->findImage("sun3Off");

	m_subRect4 = UTIL::IRectMake(365, 501, 500, 100);
	m_subIconRect4 = UTIL::IRectMake(409, 505, 90, 90);
	m_sub4On = IMAGEMANAGER->findImage("sun4On");
	m_sub4Off = IMAGEMANAGER->findImage("sun4Off");

	m_cancle = UTIL::IRectMake(770, 625, 100, 50);
	m_cancleOn = IMAGEMANAGER->findImage("cancleOn");
	m_cancleOff = IMAGEMANAGER->findImage("cancleOff");

	m_sexMan = IMAGEMANAGER->findImage("ManSex");
	m_sexWoman = IMAGEMANAGER->findImage("WomanSex");

	m_mainHpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub0HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub1HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub2HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub3HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_sub4HpBarGreen = IMAGEMANAGER->findImage("BagHpBarGreen");
	m_mainHpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub0HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub1HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub2HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub3HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_sub4HpBarYellow = IMAGEMANAGER->findImage("BagHpBarYellow");
	m_mainHpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub0HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub1HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub2HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub3HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");
	m_sub4HpBarRed = IMAGEMANAGER->findImage("BagHpBarRed");

	m_indexCursor = 0;



	return true;
}

void PocketmoninfoScene::update(float _deltaTime)
{
	//temp
	if (KEYMANAGER->isStayKeyDown(P1_Z))
	{
		Pocketmons[0]->m_currentHp -= 1;
		Pocketmons[1]->m_currentHp -= 1;
		Pocketmons[2]->m_currentHp -= 1;
		Pocketmons[3]->m_currentHp -= 1;
		Pocketmons[4]->m_currentHp -= 1;
		Pocketmons[5]->m_currentHp -= 1;
	}
	else if (KEYMANAGER->isStayKeyDown(P1_A))
	{
		Pocketmons[0]->m_currentHp += 1;
		Pocketmons[1]->m_currentHp += 1;
		Pocketmons[2]->m_currentHp += 1;
		Pocketmons[3]->m_currentHp += 1;
		Pocketmons[4]->m_currentHp += 1;
		Pocketmons[5]->m_currentHp += 1;
	}
	//endtemp

	pastTime += _deltaTime;
	if (pastTime > frameDelay) {
		if (m_pocketMonFrameIdx == 0) {
			m_pocketMonFrameIdx = 1;
		}
		else {
			m_pocketMonFrameIdx = 0;
		}
		pastTime = 0;
	}

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
	if (m_indexCursor == Pocketmons.size() && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		SCENEMANAGER->scenePop();
	}
}

void PocketmoninfoScene::release()
{
}

void PocketmoninfoScene::render(HDC hdc)
{
	m_Base->render(hdc);

	int cnt = 0;
	for (auto e : Pocketmons)
	{
		//UTIL::PrintText(hdc, e->m_name.c_str(), "소야바른9", 100, 100 + cnt * 70, 30);
		if (m_indexCursor == 0)
		{
			m_mainOn->render(hdc, m_mainRect.left - 5, m_mainRect.top+2);
		}
		else
		{
			m_mainOff->render(hdc, m_mainRect.left, m_mainRect.top + 3);
		}

		Pocketmons[0]->m_pocketmonIconImg->frameRender(hdc, m_mainIconRect.left, m_mainIconRect.top, m_pocketMonFrameIdx, 0);
		UTIL::PrintText(hdc, Pocketmons[0]->m_name.c_str(), "소야바른9", 175, 170, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, Pocketmons[0]->m_name.c_str(), "소야바른9", 170, 170, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_mainlevel = std::to_string(Pocketmons[0]->m_level);
		UTIL::PrintText(hdc, m_mainlevel.c_str(), "소야바른9", 210, 215, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_mainlevel.c_str(), "소야바른9", 205, 215, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

		std::string m_mainCurrentHp = std::to_string(Pocketmons[0]->m_currentHp);
		UTIL::PrintText(hdc, m_mainCurrentHp.c_str(), "소야바른9", 165, 300, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_mainCurrentHp.c_str(), "소야바른9", 160, 300, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
		std::string m_mainMaxHp = std::to_string(Pocketmons[0]->m_maxHp);
		UTIL::PrintText(hdc, m_mainMaxHp.c_str(), "소야바른9", 280, 300, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
		UTIL::PrintText(hdc, m_mainMaxHp.c_str(), "소야바른9", 275, 300, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

		if((float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp > 0.5)
		m_mainHpBarGreen->render(hdc,130, 283, 0,0, 208 * (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp,15);
		else if ((float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp <= 0.5 && (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp > 0.1)
		m_mainHpBarYellow->render(hdc, 130, 283, 0, 0, 208 * (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp, 15);
		else if ((float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp <= 0.1)
		m_mainHpBarRed->render(hdc, 130, 283, 0, 0, 208 * (float)Pocketmons[0]->m_currentHp / (float)Pocketmons[0]->m_maxHp, 15);

		if (Pocketmons[0]->m_currentHp <= 0)Pocketmons[0]->m_currentHp = 0;
		if (Pocketmons[0]->m_currentHp >= Pocketmons[0]->m_maxHp)Pocketmons[0]->m_currentHp = Pocketmons[0]->m_maxHp;


		if (Pocketmons[0]->gender)m_sexWoman->render(hdc, 300, 220);
		else m_sexMan->render(hdc, 300, 225);

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

			Pocketmons[1]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect0.left, m_subIconRect0.top, m_pocketMonFrameIdx, 0);
			UTIL::PrintText(hdc, Pocketmons[1]->m_name.c_str(), "소야바른9", 550, 50, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, Pocketmons[1]->m_name.c_str(), "소야바른9", 545, 50, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub0level = std::to_string(Pocketmons[1]->m_level);
			UTIL::PrintText(hdc, m_sub0level.c_str(), "소야바른9", 585, 95, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub0level.c_str(), "소야바른9", 580, 95, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub0CurrentHp = std::to_string(Pocketmons[1]->m_currentHp);
			UTIL::PrintText(hdc, m_sub0CurrentHp.c_str(), "소야바른9", 825, 95, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub0CurrentHp.c_str(), "소야바른9", 820, 95, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
			std::string m_sub0MaxHp = std::to_string(Pocketmons[1]->m_maxHp);
			UTIL::PrintText(hdc, m_sub0MaxHp.c_str(), "소야바른9", 935, 95, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub0MaxHp.c_str(), "소야바른9", 930, 95, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			if ((float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp > 0.5)
				m_sub0HpBarGreen->render(hdc, 782, 81, 0, 0, 208 * (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp, 15);
			else if ((float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp <= 0.5 && (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp > 0.1)
				m_sub0HpBarYellow->render(hdc, 782, 81, 0, 0, 208 * (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp, 15);
			else if ((float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp <= 0.1)
				m_sub0HpBarRed->render(hdc, 782, 81, 0, 0, 208 * (float)Pocketmons[1]->m_currentHp / (float)Pocketmons[1]->m_maxHp, 15);

			if (Pocketmons[1]->m_currentHp <= 0)Pocketmons[1]->m_currentHp = 0;
			if (Pocketmons[1]->m_currentHp >= Pocketmons[1]->m_maxHp)Pocketmons[1]->m_currentHp = Pocketmons[1]->m_maxHp;

			if (Pocketmons[1]->gender)m_sexWoman->render(hdc, 675, 105);
			else m_sexMan->render(hdc, 675, 105);
		}
		if (Pocketmons.size() >= 3)
		{

			if (m_indexCursor == 2)
			{
				m_sub1On->render(hdc, m_subRect1.left, m_subRect1.top);
			}
			else
			{
				m_sub1Off->render(hdc, m_subRect1.left, m_subRect1.top);
			}
			Pocketmons[2]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect1.left, m_subIconRect1.top, m_pocketMonFrameIdx, 0);
			UTIL::PrintText(hdc, Pocketmons[2]->m_name.c_str(), "소야바른9", 550, 166, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, Pocketmons[2]->m_name.c_str(), "소야바른9", 545, 166, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub1level = std::to_string(Pocketmons[2]->m_level);
			UTIL::PrintText(hdc, m_sub1level.c_str(), "소야바른9", 585, 211, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub1level.c_str(), "소야바른9", 580, 211, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub1CurrentHp = std::to_string(Pocketmons[2]->m_currentHp);
			UTIL::PrintText(hdc, m_sub1CurrentHp.c_str(), "소야바른9", 825, 211, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub1CurrentHp.c_str(), "소야바른9", 820, 211, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
			std::string m_sub1MaxHp = std::to_string(Pocketmons[2]->m_maxHp);
			UTIL::PrintText(hdc, m_sub1MaxHp.c_str(), "소야바른9", 935, 211, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub1MaxHp.c_str(), "소야바른9", 930, 211, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			if ((float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp > 0.5)
				m_sub1HpBarGreen->render(hdc, 782, 197, 0, 0, 208 * (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp, 15);
			else if ((float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp <= 0.5 && (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp > 0.1)
				m_sub1HpBarYellow->render(hdc, 782, 197, 0, 0, 208 * (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp, 15);
			else if ((float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp <= 0.1)
				m_sub1HpBarRed->render(hdc, 782, 197, 0, 0, 208 * (float)Pocketmons[2]->m_currentHp / (float)Pocketmons[2]->m_maxHp, 15);

			if (Pocketmons[2]->m_currentHp <= 0)Pocketmons[2]->m_currentHp = 0;
			if (Pocketmons[2]->m_currentHp >= Pocketmons[2]->m_maxHp)Pocketmons[2]->m_currentHp = Pocketmons[2]->m_maxHp;

			if (Pocketmons[2]->gender)m_sexWoman->render(hdc, 675, 221);
			else m_sexMan->render(hdc, 675, 221);
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
			Pocketmons[3]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect2.left, m_subIconRect2.top, m_pocketMonFrameIdx, 0);
			UTIL::PrintText(hdc, Pocketmons[3]->m_name.c_str(), "소야바른9", 550, 282, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, Pocketmons[3]->m_name.c_str(), "소야바른9", 545, 282, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub2level = std::to_string(Pocketmons[3]->m_level);
			UTIL::PrintText(hdc, m_sub2level.c_str(), "소야바른9", 585, 327, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub2level.c_str(), "소야바른9", 580, 327, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub2CurrentHp = std::to_string(Pocketmons[3]->m_currentHp);
			UTIL::PrintText(hdc, m_sub2CurrentHp.c_str(), "소야바른9", 825, 327, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub2CurrentHp.c_str(), "소야바른9", 820, 327, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
			std::string m_sub2MaxHp = std::to_string(Pocketmons[3]->m_maxHp);
			UTIL::PrintText(hdc, m_sub2MaxHp.c_str(), "소야바른9", 935, 327, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub2MaxHp.c_str(), "소야바른9", 930, 327, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			if ((float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp > 0.5)
				m_sub2HpBarGreen->render(hdc, 782, 313, 0, 0, 208 * (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp, 15);
			else if ((float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp <= 0.5 && (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp > 0.1)
				m_sub2HpBarYellow->render(hdc, 782, 313, 0, 0, 208 * (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp, 15);
			else if ((float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp <= 0.1)
				m_sub2HpBarRed->render(hdc, 782, 313, 0, 0, 208 * (float)Pocketmons[3]->m_currentHp / (float)Pocketmons[3]->m_maxHp, 15);

			if (Pocketmons[3]->m_currentHp <= 0)Pocketmons[3]->m_currentHp = 0;
			if (Pocketmons[3]->m_currentHp >= Pocketmons[3]->m_maxHp)Pocketmons[3]->m_currentHp = Pocketmons[3]->m_maxHp;


			if (Pocketmons[3]->gender)m_sexWoman->render(hdc, 675, 337);
			else m_sexMan->render(hdc, 675, 337);
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
			Pocketmons[4]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect3.left, m_subIconRect3.top, m_pocketMonFrameIdx, 0);
			UTIL::PrintText(hdc, Pocketmons[4]->m_name.c_str(), "소야바른9", 550, 398, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, Pocketmons[4]->m_name.c_str(), "소야바른9", 545, 398, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub3level = std::to_string(Pocketmons[4]->m_level);
			UTIL::PrintText(hdc, m_sub3level.c_str(), "소야바른9", 585, 443, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub3level.c_str(), "소야바른9", 580, 443, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub3CurrentHp = std::to_string(Pocketmons[4]->m_currentHp);
			UTIL::PrintText(hdc, m_sub3CurrentHp.c_str(), "소야바른9", 825, 443, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub3CurrentHp.c_str(), "소야바른9", 820, 443, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
			std::string m_sub3MaxHp = std::to_string(Pocketmons[4]->m_maxHp);
			UTIL::PrintText(hdc, m_sub3MaxHp.c_str(), "소야바른9", 935, 443, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub3MaxHp.c_str(), "소야바른9", 930, 443, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			if ((float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp > 0.5)
				m_sub3HpBarGreen->render(hdc, 782, 429, 0, 0, 208 * (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp, 15);
			else if ((float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp <= 0.5 && (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp > 0.1)
				m_sub3HpBarYellow->render(hdc, 782, 429, 0, 0, 208 * (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp, 15);
			else if ((float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp <= 0.1)
				m_sub3HpBarRed->render(hdc, 782, 429, 0, 0, 208 * (float)Pocketmons[4]->m_currentHp / (float)Pocketmons[4]->m_maxHp, 15);

			if (Pocketmons[4]->m_currentHp <= 0)Pocketmons[4]->m_currentHp = 0;
			if (Pocketmons[4]->m_currentHp >= Pocketmons[4]->m_maxHp)Pocketmons[4]->m_currentHp = Pocketmons[4]->m_maxHp;


			if (Pocketmons[4]->gender)m_sexWoman->render(hdc, 675, 453);
			else m_sexMan->render(hdc, 675, 453);
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
			Pocketmons[5]->m_pocketmonIconImg->frameRender(hdc, m_subIconRect4.left, m_subIconRect4.top, m_pocketMonFrameIdx, 0);
			UTIL::PrintText(hdc, Pocketmons[5]->m_name.c_str(), "소야바른9", 550, 514, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, Pocketmons[5]->m_name.c_str(), "소야바른9", 545, 514, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub4level = std::to_string(Pocketmons[5]->m_level);
			UTIL::PrintText(hdc, m_sub4level.c_str(), "소야바른9", 585, 559, 70, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub4level.c_str(), "소야바른9", 580, 559, 70, RGB(255, 255, 255), true, RGB(160, 112, 240));

			std::string m_sub4CurrentHp = std::to_string(Pocketmons[5]->m_currentHp);
			UTIL::PrintText(hdc, m_sub4CurrentHp.c_str(), "소야바른9", 825, 559, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub4CurrentHp.c_str(), "소야바른9", 820, 559, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));
			std::string m_sub4MaxHp = std::to_string(Pocketmons[5]->m_maxHp);
			UTIL::PrintText(hdc, m_sub4MaxHp.c_str(), "소야바른9", 935, 559, 60, RGB(112, 112, 112), true, RGB(160, 112, 240));
			UTIL::PrintText(hdc, m_sub4MaxHp.c_str(), "소야바른9", 930, 559, 60, RGB(255, 255, 255), true, RGB(160, 112, 240));

			if ((float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp > 0.5)
				m_sub4HpBarGreen->render(hdc, 782, 545, 0, 0, 208 * (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp, 15);
			else if ((float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp <= 0.5 && (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp > 0.1)
				m_sub4HpBarYellow->render(hdc, 782, 545, 0, 0, 208 * (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp, 15);
			else if ((float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp <= 0.1)
				m_sub4HpBarRed->render(hdc, 782, 545, 0, 0, 208 * (float)Pocketmons[5]->m_currentHp / (float)Pocketmons[5]->m_maxHp, 15);

			if (Pocketmons[5]->m_currentHp <= 0)Pocketmons[5]->m_currentHp = 0;
			if (Pocketmons[5]->m_currentHp >= Pocketmons[5]->m_maxHp)Pocketmons[5]->m_currentHp = Pocketmons[5]->m_maxHp;

			if (Pocketmons[5]->gender)m_sexWoman->render(hdc, 675, 569);
			else m_sexMan->render(hdc, 675, 569);


		}

		if (m_indexCursor == Pocketmons.size())
		{
			m_cancleOn->render(hdc, m_cancle.left, m_cancle.top);
		}
		else
		{
			m_cancleOff->render(hdc, m_cancle.left, m_cancle.top);
		}
	}


	UTIL::PrintText(hdc, "취소", "소야바른9", 900, 655, 75, RGB(112, 112, 112), true, RGB(160, 112, 240));
	UTIL::PrintText(hdc, "취소", "소야바른9", 895, 655, 75, RGB(255, 255, 255), true, RGB(160, 112, 240));
}



void PocketmoninfoScene::afterRender(HDC hdc)
{
}

void PocketmoninfoScene::debugRender(HDC hdc)
{
	UTIL::DrawColorRect(hdc, m_mainRect, false, false);
	UTIL::DrawColorRect(hdc, m_subRect0, false, false);
	UTIL::DrawColorRect(hdc, m_subRect1, false, false);
	UTIL::DrawColorRect(hdc, m_subRect2, false, false);
	UTIL::DrawColorRect(hdc, m_subRect3, false, false);
	UTIL::DrawColorRect(hdc, m_subRect4, false, false);

	UTIL::DrawColorRect(hdc, m_mainIconRect, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect0, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect1, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect2, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect3, false, false);
	UTIL::DrawColorRect(hdc, m_subIconRect4, false, false);
	UTIL::DrawColorRect(hdc, m_cancle, false, false);


}
