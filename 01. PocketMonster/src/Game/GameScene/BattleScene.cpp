#include "stdafx.h"
#include "BattleScene.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

bool BattleScene::init()
{
	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	//===============
	// RECT �ʱ�ȭ //
	//===============

	//�ൿ ����â
	m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	m_explainRect = UTIL::IRectMake(0, 538, WINSIZEX, WINSIZEY - 538);
	
	//��ų ����â
	m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	m_skillListRect = UTIL::IRectMake(0, 538, 605, WINSIZEY - 538);
	m_skillExplainRect = UTIL::IRectMake(610, 538, WINSIZEX - 610, WINSIZEY - 538);
	
	//���ȭ��
	//�� ����â 
	m_enemyStatus = UTIL::IRectMake(55,80, 425,130);
	//�� ���ϸ�
	m_enemyPocketmon = UTIL::IRectMake(664, 165, 165, 181);
	//�� �ٴ�
	 m_enemyBottom = UTIL::IRectMake(477, 228, 547, 159);
	//�÷��̾�ٴ�
	m_playerBottom = UTIL::IRectMake(0, 467, 534, 82);
	//�÷��̾� ���ϸ�
	m_playerPocketmon = UTIL::IRectMake(200, 329, 210, 209);
	//�÷��̾� ����â
	m_playerStatus = UTIL::IRectMake(535, 356, 446, 180);
	

	//===================
	// ����â ���� ���� //
	//===================
	fight = true;
	bag = false;
	pocketmon = false;
	run = false;

	playerAtkOn = false;

	//===================
	// ��ųâ ���� ���� //
	//===================
	skill_1 = true;
	skill_2 = false;
	skill_3 = false;
	skill_4 = false;

	//===============
	// ���� �� ���� //
	//===============
	playerTurn = true;
	motionUp = true;
	m_count = 0;
	
	
	//moveOn = true;
	return true;

}

void BattleScene::release()
{
}

void BattleScene::update(float _deltaTime)
{
	if (playerTurn)
	{
		if (!playerAtkOn) moveButton();
		select();
		if (playerAtkOn) moveSkillSelectButton();
		if (KEYMANAGER->isStayKeyDown(P1_X) && playerAtkOn)
		{
			playerAtkOn = false;
		}
		playerStayMotion();
	}
}

void BattleScene::render(HDC hdc)
{
	//IMAGEMANAGER->findImage("battleTemp")->render(hdc);
	//UTIL::drawRect(hdc, m_selectRect);
	////UTIL::DrawColorRect(hdc, m_selectRect, false, RGB(100, 100, 100));
	//char str[111];
	//wsprintf(str, "%d", m_count);
	//TextOut(hdc, 200, 200, str, strlen(str));

	//wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	//TextOut(hdc, m_ptMouse.x, m_ptMouse.y-20, str, strlen(str));
}

void BattleScene::afterRender(HDC hdc)
{
}

void BattleScene::debugRender(HDC hdc)
{
	//���
	IMAGEMANAGER->findImage("battleTemp")->render(hdc);
	//��
	UTIL::drawRect(hdc, m_enemyStatus);
	UTIL::drawRect(hdc, m_enemyBottom);
	UTIL::drawRect(hdc, m_enemyPocketmon);
	//�÷��̾�
	UTIL::drawRect(hdc, m_playerBottom);
	UTIL::drawRect(hdc, m_playerPocketmon);
	UTIL::drawRect(hdc, m_playerStatus);

	if (playerTurn)
	{
		//���� + ����â
		if (!playerAtkOn)
		{
			UTIL::drawRect(hdc, m_explainRect);
			//���� Ŀ��
			UTIL::drawRect(hdc, m_selectRect);
		}

		if (playerAtkOn)
		{
			UTIL::drawRect(hdc, m_skillListRect);
			UTIL::drawRect(hdc, m_skillSelectRect);
			UTIL::drawRect(hdc, m_skillExplainRect);
		}
	}
	else if (!playerTurn)
	{
		UTIL::drawRect(hdc, m_explainRect);
	}
		
	//UTIL::DrawColorRect(hdc, m_selectRect, false, RGB(100, 100, 100));
	char str[111];
	wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(hdc, m_ptMouse.x, m_ptMouse.y - 20, str, strlen(str));

	wsprintf(str, "fight: %d, bag: %d, pocketmon: %d, run: %d", fight, bag, pocketmon, run);
	TextOut(hdc, 10, 10, str, strlen(str));

	wsprintf(str, "s_1: %d, s_2: %d, s_3: %d, s_4: %d", skill_1, skill_2, skill_3, skill_4);
	TextOut(hdc, 10, 25, str, strlen(str));

	wsprintf(str, "m_count: %d", m_count);
	TextOut(hdc, 10, 40, str, strlen(str));
}

void BattleScene::moveButton()
{
	//�ο��: 618, 595, 20, 40
	//����: 824, 595, 20, 40
	//���ϸ�: 618, 668, 20, 40
	//����: 824, 668, 20, 40
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && fight && !bag && !pocketmon && !run)
	{
		fight = false;
		bag = true;
		m_selectRect = UTIL::IRectMake(824, 595, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && !fight && !bag && pocketmon && !run)
	{
		pocketmon = false;
		run = true;
		m_selectRect = UTIL::IRectMake(824, 668, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !fight && bag && !pocketmon && !run)
	{
		bag = false;
		fight = true;
		m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !fight && !bag && !pocketmon && run)
	{
		run = false;
		pocketmon = true;
		m_selectRect = UTIL::IRectMake(618, 668, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN) && fight && !bag && !pocketmon && !run)
	{
		fight = false;
		pocketmon = true;
		m_selectRect = UTIL::IRectMake(618, 668, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !fight && bag && !pocketmon && !run)
	{
		bag = false;
		run = true;
		m_selectRect = UTIL::IRectMake(824, 668, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_UP) && !fight && !bag && pocketmon && !run)
	{
		pocketmon = false;
		fight = true;
		m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_UP) && !fight && !bag && !pocketmon && run)
	{
		run = false;
		bag = true;
		m_selectRect = UTIL::IRectMake(824, 595, 20, 40);
	}
}

void BattleScene::select()
{
	if (KEYMANAGER->isStayKeyDown(P1_Z) && fight)
	{
		playerAtkOn = true;
	}
	if (KEYMANAGER->isStayKeyDown(P1_Z) && bag)
	{
		//�������� ��ü����
		//SCENEMANAGER->scenePush("bag");
	}
	if (KEYMANAGER->isStayKeyDown(P1_Z) && pocketmon)
	{
		//���ϸ����� ��ü����
		//SCENEMANAGER->scenePush("pocketmon");
	}
	if (KEYMANAGER->isStayKeyDown(P1_Z) && run)
	{
		SCENEMANAGER->scenePop();
	}
	/////////////////////////////z
	



}

void BattleScene::moveSkillSelectButton()
{
	//��ų ����â
	//skill_1: 39, 595, 20, 40
	//skill_2: 318, 595, 20, 40
	//skill_3: 39, 674, 20, 40
	//skill_4: 318, 674, 20, 40
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && skill_1 && !skill_2 && !skill_3 && !skill_4)
	{
		skill_1 = false;
		skill_2 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 595, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && !skill_1 && !skill_2 && skill_3 && !skill_4)
	{
		skill_3 = false;
		skill_4 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 674, 20, 40);
	}
	///////
	if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !skill_1 && skill_2 && !skill_3 && !skill_4)
	{
		skill_2 = false;
		skill_1 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_LEFT) && !skill_1 && !skill_2 && !skill_3 && skill_4)
	{
		skill_4 = false;
		skill_3 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 674, 20, 40);
	}
	///////
	if (KEYMANAGER->isStayKeyDown(P1_UP) && !skill_1 && !skill_2 && skill_3 && !skill_4)
	{
		skill_3 = false;
		skill_1 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_UP) && !skill_1 && !skill_2 && !skill_3 && skill_4)
	{
		skill_4 = false;
		skill_2 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 595, 20, 40);
	}
	///////
	if (KEYMANAGER->isStayKeyDown(P1_DOWN) && skill_1 && !skill_2 && !skill_3 && !skill_4)
	{
		skill_1 = false;
		skill_3 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 674, 20, 40);
	}
	if (KEYMANAGER->isStayKeyDown(P1_DOWN) && !skill_1 && skill_2 && !skill_3 && !skill_4)
	{
		skill_2 = false;
		skill_4 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 674, 20, 40);
	}

}

void BattleScene::playerStayMotion()
{
	m_count++;
	if (m_count % 20 == 0 && motionUp)
	{
		motionUp = false;
		//�÷��̾� ���ϸ�
		m_playerPocketmon = UTIL::IRectMake(200, 319, 210, 209);
		//�÷��̾� ����â
		m_playerStatus = UTIL::IRectMake(535, 346, 446, 180);
	}
	else if (m_count % 20 == 0 && !motionUp)
	{
		motionUp = true;
		//�÷��̾� ���ϸ�
		m_playerPocketmon = UTIL::IRectMake(200, 329, 210, 209);
		//�÷��̾� ����â
		m_playerStatus = UTIL::IRectMake(535, 356, 446, 180);
	}
	
	if (m_count > 10000) m_count = 0;

}
//
//void BattleScene::test()
//{
//	if (KEYMANAGER->isStayKeyDown(P1_RIGHT) && moveOn)
//	{
//		moveOn = false;
//	}
//
//	if (!moveOn)
//	{
//		x += 5;
//		rect(x, y, w, h);
//		if (x > 100) moveOn = true;
//
//	}
//}
