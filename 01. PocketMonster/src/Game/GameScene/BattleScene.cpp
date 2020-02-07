#include "stdafx.h"
#include "BattleScene.h"

BattleScene::BattleScene(){}

BattleScene::~BattleScene(){}

bool BattleScene::init()
{
	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	EFFECTMANAGER->addEffect("���̸���ų1", "images/pailiSkill_1.bmp", 35, 150, 35, 30, 1, 0.1f, 100);

	m_pocketmonpaili = std::make_shared<PocketMon>();

	//===============
	// RECT �ʱ�ȭ //
	//===============
	//UI ������Ʈ ��ġ �ʱ�ȭ
	m_playerBottomX = WINSIZEX;
	m_playerimgX = 1224;
	m_playerPocketmonX= 1224;
	m_playerStatusX = 1524;
	m_enemyBottomX = -547;
	m_enemyPocketmonX = -360;
	m_enemyStatusX = -425;

	//���ȭ��
	//�� ����â 
	m_enemyStatus = UTIL::IRectMake(m_enemyStatusX, 80, 425, 130);
	//�� �ٴ�
	 m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
	//�� ���ϸ�
	m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
	//�÷��̾�ٴ�
	m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 547, 159);
	//�÷��̾� �̹���
	m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
	//�÷��̾� ���ϸ�
	m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	//�÷��̾� ����â
	m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	//��ų ����Ʈ
	m_playerAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
	m_enemyAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
	
	//===========
	// ������ //
	//===========
	//�ൿ ����â
	m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	m_explainRect = UTIL::IRectMake(0, 538, WINSIZEX, WINSIZEY - 538);

	//��ų ����â
	m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	m_skillListRect = UTIL::IRectMake(0, 538, 605, WINSIZEY - 538);
	m_skillExplainRect = UTIL::IRectMake(610, 538, WINSIZEX - 610, WINSIZEY - 538);

	//===================
	// ���������������� //
	//===================
	wildBattle = true;
	npcBattle = false;
	
	//===========================
	// ���� �ִ����̼� ���� ���� //
	//===========================
	wildBattleIntroAniOn = true;
	uiObjectRegularPosition = false;
	playerImgSlideOut = false;

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
	enemyTurn = false;
	motionUp = true;
	m_count = 0;

	//================
	// ���ݰ��� ���� //
	//================
	playerAtkSkillOn = false;
	enemyAtkSkillOn = false;
	m_skillCount = 0;

	
	//moveOn = true;
	return true;

}

void BattleScene::release()
{
}

void BattleScene::update(float _deltaTime)
{
	if (wildBattle) wildBattleFunctions();
	if (npcBattle) npcBattleFunctions();
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
	char str[200];
	if (wildBattle) wildBattleRender(hdc);
	if (npcBattle) npcBattleRender(hdc);
	
	//����� ��� ���� ����

	if (KEYMANAGER->isStayKeyDown(GAME_LMOUSE))
	{
		EFFECTMANAGER->play("���̸���ų1", m_ptMouse.x, m_ptMouse.y);
	}
	wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(hdc, m_ptMouse.x, m_ptMouse.y - 20, str, strlen(str));

	EFFECTMANAGER->render(hdc);

	/*
	wsprintf(str, "fight: %d, bag: %d, pocketmon: %d, run: %d", fight, bag, pocketmon, run);
	TextOut(hdc, 10, 10, str, strlen(str));

	wsprintf(str, "s_1: %d, s_2: %d, s_3: %d, s_4: %d", skill_1, skill_2, skill_3, skill_4);
	TextOut(hdc, 10, 25, str, strlen(str));

	wsprintf(str, "m_count: %d", m_count);
	TextOut(hdc, 10, 40, str, strlen(str));
	*/
}

void BattleScene::wildBattleFunctions()
{
	if (wildBattleIntroAniOn) wildBattleIntroAni();
	else 
	{
		if (playerTurn)
		{
			if (!playerAtkOn) moveButton();
			if (playerAtkOn) moveSkillSelectButton();
			if (playerAtkOn && KEYMANAGER->isOnceKeyDown(P1_X)) playerAtkOn = false;
			playerStayMotion();
		}

		if (playerAtkSkillOn) skillMotion();

		if (enemyTurn)
		{
			selectEnemyskill();
			skillMotion();
		}

		if (enemyAtkSkillOn) skillMotion();
	}
}

void BattleScene::wildBattleIntroAni()
{
	////�� ����â 
		//m_enemyStatus = UTIL::IRectMake(55, 80, 425, 130);
		////�� ���ϸ�
		//m_enemyPocketmon = UTIL::IRectMake(664, 165, 165, 181);
		////�� �ٴ�
		//m_enemyBottom = UTIL::IRectMake(477, 228, 547, 159);
		////�÷��̾�ٴ�
		//m_playerBottom = UTIL::IRectMake(0, 467, 534, 82);
		////�÷��̾� �̹���
		//m_playerImg = UTIL::IRectMake(200, 329, 210, 209);
		////�÷��̾� ���ϸ�
		//m_playerPocketmon = UTIL::IRectMake(200, 329, 210, 209);
		//�÷��̾� ����â
		//m_playerStatus = UTIL::IRectMake(535, 356, 446, 180);
	if (!uiObjectRegularPosition)
	{
		m_enemyBottomX += 10;
		m_enemyPocketmonX += 10;
		m_playerBottomX -= 10;
		m_playerimgX -= 10;
		m_playerPocketmonX -= 10;
		//�� �ٴ�
		m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
		//�� ���ϸ�
		m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
		//�÷��̾�ٴ�
		m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 534, 159);
		//�÷��̾� �̹���
		m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
		//�÷��̾� ���ϸ�
		m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	}

	if (m_enemyBottomX >= ENEMYBOTTOMX) uiObjectRegularPosition = true;

	if (uiObjectRegularPosition && !playerImgSlideOut)
	{
		m_enemyStatusX += 5;
		//�� ����â 
		m_enemyStatus = UTIL::IRectMake(m_enemyStatusX, 80, 425, 130);
		if (m_enemyStatusX >= ENEMYSTATUSX)
		{
			//wildBattleIntroAni = false;
			playerImgSlideOut = true;
		}
	}
	if (playerImgSlideOut)
	{
		m_playerimgX -= 10;
		m_playerStatusX -= 10;
		//�÷��̾� �̹���
		m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
		//�÷��̾� ����â
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
		if (m_playerStatusX <= PLAYERSTATUSX) wildBattleIntroAniOn = false;
	}
}

void BattleScene::playerStayMotion()
{
	m_count++;
	if (m_count % 20 == 0 && motionUp)
	{
		motionUp = false;
		//�÷��̾� ���ϸ�
		m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 319, 210, 209);
		//�÷��̾� ����â
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 346, 446, 180);
	}
	else if (m_count % 20 == 0 && !motionUp)
	{
		motionUp = true;
		//�÷��̾� ���ϸ�
		m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
		//�÷��̾� ����â
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	}

	if (m_count > 10000) m_count = 0;

}

void BattleScene::moveButton()
{
	//�ο��: 618, 595, 20, 40
	//����: 824, 595, 20, 40
	//���ϸ�: 618, 668, 20, 40
	//����: 824, 668, 20, 40
	if (fight && !bag && !pocketmon && !run && KEYMANAGER->isOnceKeyDown(P1_RIGHT))
	{
		fight = false;
		bag = true;
		m_selectRect = UTIL::IRectMake(824, 595, 20, 40);
	}
	if (!fight && !bag && pocketmon && !run && KEYMANAGER->isOnceKeyDown(P1_RIGHT))
	{
		pocketmon = false;
		run = true;
		m_selectRect = UTIL::IRectMake(824, 668, 20, 40);
	}
	if (!fight && bag && !pocketmon && !run && KEYMANAGER->isOnceKeyDown(P1_LEFT))
	{
		bag = false;
		fight = true;
		m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	}
	if (!fight && !bag && !pocketmon && run && KEYMANAGER->isOnceKeyDown(P1_LEFT))
	{
		run = false;
		pocketmon = true;
		m_selectRect = UTIL::IRectMake(618, 668, 20, 40);
	}
	if (fight && !bag && !pocketmon && !run && KEYMANAGER->isOnceKeyDown(P1_DOWN))
	{
		fight = false;
		pocketmon = true;
		m_selectRect = UTIL::IRectMake(618, 668, 20, 40);
	}
	if (!fight && bag && !pocketmon && !run && KEYMANAGER->isOnceKeyDown(P1_DOWN))
	{
		bag = false;
		run = true;
		m_selectRect = UTIL::IRectMake(824, 668, 20, 40);
	}
	if (!fight && !bag && pocketmon && !run && KEYMANAGER->isOnceKeyDown(P1_UP))
	{
		pocketmon = false;
		fight = true;
		m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	}
	if (!fight && !bag && !pocketmon && run && KEYMANAGER->isOnceKeyDown(P1_UP))
	{
		run = false;
		bag = true;
		m_selectRect = UTIL::IRectMake(824, 595, 20, 40);
	}

	if (fight && KEYMANAGER->isOnceKeyDown(P1_Z) )
	{
		playerAtkOn = true;
	}
	if (bag && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//�������� ��ü����
		//SCENEMANAGER->scenePush("bag");
	}
	if (pocketmon && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//���ϸ����� ��ü����
		//SCENEMANAGER->scenePush("pocketmon");
	}
	if (run && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		SCENEMANAGER->scenePop();
	}

}

void BattleScene::moveSkillSelectButton()
{
	//��ų ����â
	//skill_1: 39, 595, 20, 40
	//skill_2: 318, 595, 20, 40
	//skill_3: 39, 674, 20, 40
	//skill_4: 318, 674, 20, 40
	if (skill_1 && !skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_RIGHT))
	{
		skill_1 = false;
		skill_2 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 595, 20, 40);
	}
	if (!skill_1 && !skill_2 && skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_RIGHT))
	{
		skill_3 = false;
		skill_4 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 674, 20, 40);
	}
	if (!skill_1 && skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_LEFT))
	{
		skill_2 = false;
		skill_1 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	}
	if (!skill_1 && !skill_2 && !skill_3 && skill_4 && KEYMANAGER->isOnceKeyDown(P1_LEFT))
	{
		skill_4 = false;
		skill_3 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 674, 20, 40);
	}
	if (!skill_1 && !skill_2 && skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_UP))
	{
		skill_3 = false;
		skill_1 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	}
	if (!skill_1 && !skill_2 && !skill_3 && skill_4 && KEYMANAGER->isOnceKeyDown(P1_UP))
	{
		skill_4 = false;
		skill_2 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 595, 20, 40);
	}
	if (skill_1 && !skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_DOWN))
	{
		skill_1 = false;
		skill_3 = true;
		m_skillSelectRect = UTIL::IRectMake(39, 674, 20, 40);
	}
	if (!skill_1 && skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_DOWN))
	{
		skill_2 = false;
		skill_4 = true;
		m_skillSelectRect = UTIL::IRectMake(318, 674, 20, 40);
	}

	if (KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		playerTurn = false;
		playerAtkSkillOn = true;
	}

}

void BattleScene::skillMotion()
{
	//���ݸ��
	//�� ��������
	//�Ǵޱ�
	m_skillCount++;
	if (playerAtkSkillOn)
	{
		//���ϸ� Ŭ������ ��ų ����� ���ۉ����� �˸��� bool������, ��ų ��ȣ�� ������.
		if (skill_1) {}
		if (skill_2) {}
		if (skill_3) {}
		if (skill_4) {}
	}
	else if (enemyAtkSkillOn)
	{

	}

	if (m_skillCount > 100 && playerAtkSkillOn)
	{
		m_skillCount = 0;
		playerAtkSkillOn = false;
		enemyTurn = true;
	}
	if (m_skillCount > 300 && enemyAtkSkillOn)
	{
		m_skillCount = 0;
		enemyAtkSkillOn = false;
		playerTurn = true;
		playerAtkOn = false;
		enemyTurn = false;
	}
}

void BattleScene::selectEnemyskill()
{
	enemyAtkSkillOn = true;
}

void BattleScene::wildBattleRender(HDC hdc)
{
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "�Ҿ߹ٸ�9");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetBkMode(hdc, TRANSPARENT);

	char str[111];
	//���
	IMAGEMANAGER->findImage("battleTemp")->render(hdc);
	//��Ʈ�� �ִϸ��̼� 
	if (wildBattleIntroAniOn)
	{
		//��
		UTIL::drawRect(hdc, m_enemyStatus);
		UTIL::drawRect(hdc, m_enemyBottom);
		UTIL::drawRect(hdc, m_enemyPocketmon);
		//�÷��̾�
		UTIL::drawRect(hdc, m_playerBottom);
		UTIL::drawRect(hdc, m_playerPocketmon);
		UTIL::drawRect(hdc, m_playerImg);
		UTIL::drawRect(hdc, m_playerStatus);
		//����â
		UTIL::drawRect(hdc, m_explainRect);
		if (uiObjectRegularPosition && !playerImgSlideOut)
		{
			wsprintf(str, "��!! �߻���");
			TextOut(hdc, 83, 584, str, strlen(str));

			wsprintf(str, "��ȯ�̰� Ƣ��Դ�!!");
			TextOut(hdc, 83, 584 + 40, str, strlen(str));

		}
		if (playerImgSlideOut)
		{
			wsprintf(str, "���� ���Ͽ�ȯ!!!!");
			TextOut(hdc, 83, 584, str, strlen(str));
		}
	}
	//���� �ִϸ��̼�
	else
	{
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
		if (playerAtkSkillOn)
		{
			UTIL::drawRect(hdc, m_playerAtkSkillEffect);
			wsprintf(str, "���ϸ� ��ų ���� !!! ��ȯ�̰� ���¢����!! ũ�ƾƾƾƾ�!!");
			TextOut(hdc, 500, 300, str, strlen(str));
		}
		if (enemyAtkSkillOn)
		{
			UTIL::drawRect(hdc, m_enemyAtkSkillEffect);
			wsprintf(str, "�ؼ��� �󱼷� �ݰ��Ѵ�!!! ũ�ƾƾƾƾƾƾƾƾ�!!!!");
			TextOut(hdc, 500, 300, str, strlen(str));
		}
	}
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}


//npc ��Ʋ �Լ� ����
void BattleScene::npcBattleFunctions()
{
}

void BattleScene::npcBattleRender(HDC hdc)
{
}
