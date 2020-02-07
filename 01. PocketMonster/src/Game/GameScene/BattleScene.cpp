#include "stdafx.h"
#include "BattleScene.h"
#include "Common/SystemManagers.h"
#include "Common/GameManagers.h"

BattleScene::BattleScene(){}

BattleScene::~BattleScene(){}

bool BattleScene::init()
{
	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	
	pocketmonEffectInit();
	

	m_player = POCKETMONMANAGER->getPlayerPocketmon();
	m_wildEnemy = POCKETMONMANAGER->getWildPocketmon();
	/*m_wildEnemy = std::make_shared<Paili>();
	m_wildEnemy->init();*/

	//===============
	// RECT 초기화 //
	//===============
	//UI 오브젝트 위치 초기화
	m_playerBottomX = WINSIZEX;
	m_playerimgX = 1224;
	m_playerPocketmonX= 1224;
	m_playerStatusX = 1524;
	m_enemyBottomX = -547;
	m_enemyPocketmonX = -360;
	m_enemyStatusX = -425;

	//배경화면
	//적 상태창 
	m_enemyStatus = UTIL::IRectMake(m_enemyStatusX, 80, 425, 130);
	//적 바닥
	 m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
	//적 포켓몬
	m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
	//플레이어바닥
	m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 547, 159);
	//플레이어 이미지
	m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
	//플레이어 포켓몬
	m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	//플레이어 상태창
	m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	//스킬 이팩트
	m_playerAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
	m_enemyAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
	
	//===========
	// 대기상태 //
	//===========
	//행동 선택창
	m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	m_explainRect = UTIL::IRectMake(0, 538, WINSIZEX, WINSIZEY - 538);

	//스킬 선택창
	m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	m_skillListRect = UTIL::IRectMake(0, 538, 605, WINSIZEY - 538);
	m_skillExplainRect = UTIL::IRectMake(610, 538, WINSIZEX - 610, WINSIZEY - 538);

	//===================
	// 전투유형조절변수 //
	//===================
	wildBattle = true;
	npcBattle = false;
	
	//===========================
	// 전투 애니케이션 관련 변수 //
	//===========================
	wildBattleIntroAniOn = true;
	uiObjectRegularPosition = false;
	playerImgSlideOut = false;

	//===================
	// 선택창 조절 변수 //
	//===================
	fight = true;
	bag = false;
	pocketmon = false;
	run = false;

	playerAtkOn = false;

	//===================
	// 스킬창 조절 변수 //
	//===================
	skill_1 = true;
	skill_2 = false;
	skill_3 = false;
	skill_4 = false;

	//===============
	// 공격 턴 변수 //
	//===============
	playerTurn = true;
	enemyTurn = false;
	motionUp = true;
	m_count = 0;

	//================
	// 공격관련 변수 //
	//================
	playerAtkSkillOn = false;
	skillMotionOn = false;
	enemyAtkSkillOn = false;
	m_skillCount = 0;

	
	//moveOn = true;
	return true;

}

//bool BattleScene::init(std::shared_ptr<player> _player)
//{
//	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
//
//	pocketmonEffectInit();
//
//
//	m_player = POCKETMONMANAGER->getPlayerPocketmon();
//	m_wildEnemy = POCKETMONMANAGER->getWildPocketmon();
//	/*m_wildEnemy = std::make_shared<Paili>();
//	m_wildEnemy->init();*/
//
//	//===============
//	// RECT 초기화 //
//	//===============
//	//UI 오브젝트 위치 초기화
//	m_playerBottomX = WINSIZEX;
//	m_playerimgX = 1224;
//	m_playerPocketmonX = 1224;
//	m_playerStatusX = 1524;
//	m_enemyBottomX = -547;
//	m_enemyPocketmonX = -360;
//	m_enemyStatusX = -425;
//
//	//배경화면
//	//적 상태창 
//	m_enemyStatus = UTIL::IRectMake(m_enemyStatusX, 80, 425, 130);
//	//적 바닥
//	m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
//	//적 포켓몬
//	m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
//	//플레이어바닥
//	m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 547, 159);
//	//플레이어 이미지
//	m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
//	//플레이어 포켓몬
//	m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
//	//플레이어 상태창
//	m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
//	//스킬 이팩트
//	m_playerAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
//	m_enemyAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
//
//	//===========
//	// 대기상태 //
//	//===========
//	//행동 선택창
//	m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
//	m_explainRect = UTIL::IRectMake(0, 538, WINSIZEX, WINSIZEY - 538);
//
//	//스킬 선택창
//	m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
//	m_skillListRect = UTIL::IRectMake(0, 538, 605, WINSIZEY - 538);
//	m_skillExplainRect = UTIL::IRectMake(610, 538, WINSIZEX - 610, WINSIZEY - 538);
//
//	//===================
//	// 전투유형조절변수 //
//	//===================
//	wildBattle = true;
//	npcBattle = false;
//
//	//===========================
//	// 전투 애니케이션 관련 변수 //
//	//===========================
//	wildBattleIntroAniOn = true;
//	uiObjectRegularPosition = false;
//	playerImgSlideOut = false;
//
//	//===================
//	// 선택창 조절 변수 //
//	//===================
//	fight = true;
//	bag = false;
//	pocketmon = false;
//	run = false;
//
//	playerAtkOn = false;
//
//	//===================
//	// 스킬창 조절 변수 //
//	//===================
//	skill_1 = true;
//	skill_2 = false;
//	skill_3 = false;
//	skill_4 = false;
//
//	//===============
//	// 공격 턴 변수 //
//	//===============
//	playerTurn = true;
//	enemyTurn = false;
//	motionUp = true;
//	m_count = 0;
//
//	//================
//	// 공격관련 변수 //
//	//================
//	playerAtkSkillOn = false;
//	skillMotionOn = false;
//	enemyAtkSkillOn = false;
//	m_skillCount = 0;
//
//	return true;
//}

void BattleScene::release()
{
}

void BattleScene::update(float _deltaTime)
{
	if (wildBattle) wildBattleFunctions();
	//if (npcBattle) npcBattleFunctions();
}

void BattleScene::render(HDC hdc)
{
	//IMAGEMANAGER->findImage("battleTemp")->render(hdc);
	//UTIL::DrawRect(hdc, m_selectRect);
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
	//if (npcBattle) npcBattleRender(hdc);
	
	//========================
	// 디버깅 출력 내용 모음 //
	//========================
		/*
	//if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE))
	//{
	//	//EFFECTMANAGER->play("파이리스킬1", m_ptMouse.x, m_ptMouse.y);
	//	//test = EFFECTMANAGER->getIsPlay();
	//	//m_player->skillEffect(1);
	//}
	
	//if(test) test = EFFECTMANAGER->getIsPlay();

	//wsprintf(str, "%d", test);
	//TextOut(hdc, 100, 100, str, strlen(str));

	/*wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(hdc, m_ptMouse.x, m_ptMouse.y - 20, str, strlen(str));



	wsprintf(str, "fight: %d, bag: %d, pocketmon: %d, run: %d", fight, bag, pocketmon, run);
	TextOut(hdc, 10, 10, str, strlen(str));

	wsprintf(str, "s_1: %d, s_2: %d, s_3: %d, s_4: %d", skill_1, skill_2, skill_3, skill_4);
	TextOut(hdc, 10, 25, str, strlen(str));

	wsprintf(str, "m_count: %d", m_count);
	TextOut(hdc, 10, 40, str, strlen(str));
	*/

	EFFECTMANAGER->render(hdc);
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

		/*if (playerAtkSkillOn) playerskillMotion();

		if (enemyTurn)
		{
			selectEnemyskill();
			playerskillMotion();
		}

		if (enemyAtkSkillOn) playerskillMotion();*/
	}
}

void BattleScene::wildBattleIntroAni()
{
	////적 상태창 
		//m_enemyStatus = UTIL::IRectMake(55, 80, 425, 130);
		////적 포켓몬
		//m_enemyPocketmon = UTIL::IRectMake(664, 165, 165, 181);
		////적 바닥
		//m_enemyBottom = UTIL::IRectMake(477, 228, 547, 159);
		////플레이어바닥
		//m_playerBottom = UTIL::IRectMake(0, 467, 534, 82);
		////플레이어 이미지
		//m_playerImg = UTIL::IRectMake(200, 329, 210, 209);
		////플레이어 포켓몬
		//m_playerPocketmon = UTIL::IRectMake(200, 329, 210, 209);
		//플레이어 상태창
		//m_playerStatus = UTIL::IRectMake(535, 356, 446, 180);
	if (!uiObjectRegularPosition)
	{
		m_enemyBottomX += 10;
		m_enemyPocketmonX += 10;
		m_playerBottomX -= 10;
		m_playerimgX -= 10;
		m_playerPocketmonX -= 10;
		//적 바닥
		m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
		//적 포켓몬
		m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
		//플레이어바닥
		m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 534, 159);
		//플레이어 이미지
		m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
		//플레이어 포켓몬
		m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	}

	if (m_enemyBottomX >= ENEMYBOTTOMX) uiObjectRegularPosition = true;

	if (uiObjectRegularPosition && !playerImgSlideOut)
	{
		m_enemyStatusX += 5;
		//적 상태창 
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
		//플레이어 이미지
		m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
		//플레이어 상태창
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
		if (m_playerStatusX <= PLAYERSTATUSX) wildBattleIntroAniOn = false;
	}
}

void BattleScene::npcBattleIntroAni()
{
}

void BattleScene::pocketmonEffectInit()
{
	//파이리 공격
	//스킬_3
	EFFECTMANAGER->addEffect("불꽃세례", "images/pailiSkill_1.bmp", 35, 150, 35, 30, 1, 0.1f, 100);
}

//========================
// UI RENDER 함수들 모음 //
//========================
void BattleScene::enemyUiStatus(HDC hdc)
{
	char str[100];
	UTIL::DrawRect(hdc, m_enemyStatus);

	
	//이름
	wsprintf(str, "%s", m_wildEnemy->m_name.c_str());
	TextOut(hdc, m_enemyStatus.left+10, m_enemyStatus.top+10, str, strlen(str));

	//레벨
	wsprintf(str, "Lv %d", m_wildEnemy->m_level);
	TextOut(hdc, m_enemyStatus.left + 310, m_enemyStatus.top + 20, str, strlen(str));

}
void BattleScene::enemyUiBottom(HDC hdc)
{
	UTIL::DrawRect(hdc, m_enemyBottom);
}
void BattleScene::enemyUiPocketmon(HDC hdc)
{

	UTIL::DrawRect(hdc, m_enemyPocketmon);
}
void BattleScene::playerUiBottom(HDC hdc)
{
	UTIL::DrawRect(hdc, m_playerBottom);
}
void BattleScene::playerUiPoketmon(HDC hdc)
{
	UTIL::DrawRect(hdc, m_playerPocketmon);
}
void BattleScene::playerUiImg(HDC hdc)
{
	UTIL::DrawRect(hdc, m_playerImg);
}
void BattleScene::playerUiStatus(HDC hdc)
{
	char str[100];
	UTIL::DrawRect(hdc, m_playerStatus);
	wsprintf(str, "%d", m_player->m_level);
	TextOut(hdc, m_playerStatus.left + 10, m_playerStatus.top + 10, str, strlen(str));

}
void BattleScene::playerUiSkillList(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillListRect);
}
void BattleScene::playerUiSkillExplain(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillExplainRect);
}
void BattleScene::playerStayMotion()
{
	m_count++;
	if (m_count % 20 == 0 && motionUp)
	{
		motionUp = false;
		//플레이어 포켓몬
		m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 319, 210, 209);
		//플레이어 상태창
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 346, 446, 180);
	}
	else if (m_count % 20 == 0 && !motionUp)
	{
		motionUp = true;
		//플레이어 포켓몬
		m_playerPocketmon = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
		//플레이어 상태창
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	}

	if (m_count > 10000) m_count = 0;

}
void BattleScene::moveButton()
{
	//싸운다: 618, 595, 20, 40
	//가방: 824, 595, 20, 40
	//포켓몬: 618, 668, 20, 40
	//도망: 824, 668, 20, 40
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
		//가방으로 씬체인지
		//SCENEMANAGER->scenePush("bag");
	}
	if (pocketmon && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//포켓몬으로 씬체인지
		//SCENEMANAGER->scenePush("pocketmon");
	}
	if (run && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//추가할꺼 - 플레이어에 setisBattle 함수를 써서 isbattle false로 바꿔주기
		SCENEMANAGER->scenePop();
	}

}
void BattleScene::moveSkillSelectButton()
{
	//스킬 선택창
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
void BattleScene::playerskillMotion()
{
	//공격모션
	//적 깜빡깜빡
	//피달기
	m_skillCount++;
	if (playerAtkSkillOn)
	{
		//플레이어 클래스의 스킬 이름을 가져온다.
		if (skill_1 && !skillMotionOn)
		{
			skillEffectAssemble(m_player->skill_1);
			//skillMotionOn = m_player->getSkillMotionOn();
		}
		if (skill_2) {}
		if (skill_3) {}
		if (skill_4) {}
	}


	else if (enemyAtkSkillOn)
	{

	}

	//if (skillMotionOn/* && !m_player->getSkillMotionOn()*/);
	//{
	//	skillMotionOn = false;
	//	playerAtkSkillOn = false;
	//	enemyTurn = true;
	//}
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

bool BattleScene::skillEffectAssemble(HDC _hdc, std::string * _skillName)
{
	return false;
}



void BattleScene::explainRect(HDC hdc)
{
	char str[100];

	UTIL::DrawRect(hdc, m_explainRect);
	if (uiObjectRegularPosition && !playerImgSlideOut)
	{
		wsprintf(str, "앗!! 야생의");
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

		wsprintf(str, "영환이가 튀어나왔다!!");
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 30, str, strlen(str));

	}
	if (playerImgSlideOut)
	{
		wsprintf(str, "가랏 포켓영환!!!!");
		TextOut(hdc, 83, 584, str, strlen(str));
	}
}

void BattleScene::wildBattleRender(HDC hdc)
{
	HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "소야바른9");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetBkMode(hdc, TRANSPARENT);

	char str[411];
	//배경
	IMAGEMANAGER->findImage("battleTemp")->render(hdc);

	//인트로 애니메이션 
	if (wildBattleIntroAniOn)
	{
		//적
		enemyUiStatus(hdc);
		enemyUiBottom(hdc);
		enemyUiPocketmon(hdc);

		//플레이어
		playerUiBottom(hdc);
		playerUiPoketmon(hdc);
		playerUiImg(hdc);
		playerUiStatus(hdc);
		
		//설명창
		explainRect(hdc);
	}
	//공격 애니메이션
	else
	{
		//적
		enemyUiStatus(hdc);
		enemyUiBottom(hdc);
		enemyUiPocketmon(hdc);
		//플레이어
		playerUiBottom(hdc);
		playerUiPoketmon(hdc);
		playerUiStatus(hdc);

		if (playerTurn)
		{
			//설명 + 선택창
			if (!playerAtkOn)
			{
				explainRect(hdc);
				//선택 커서
				UTIL::DrawRect(hdc, m_selectRect);
			}
			
			if (playerAtkOn)
			{
				playerUiSkillList(hdc);
				playerUiSkillExplain(hdc);
				UTIL::DrawRect(hdc, m_skillSelectRect);
			}
		}
		if (playerAtkSkillOn)
		{
			UTIL::DrawRect(hdc, m_playerAtkSkillEffect);
			wsprintf(str, "포켓몬 스킬 공격 !!! 영환이가 울부짖었다!! 크아아아아앙!!");
			TextOut(hdc, 500, 300, str, strlen(str));
		}
		if (enemyAtkSkillOn)
		{
			UTIL::DrawRect(hdc, m_enemyAtkSkillEffect);
			wsprintf(str, "준수가 얼굴로 반격한다!!! 크아아아아아아아아악!!!!");
			TextOut(hdc, 500, 300, str, strlen(str));
		}
	}

	wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(hdc, m_ptMouse.x, m_ptMouse.y-20, str, strlen(str));
	
	EFFECTMANAGER->render(hdc);
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}


//npc 배틀 함수 모음
void BattleScene::npcBattleFunctions()
{
}

void BattleScene::npcBattleRender(HDC hdc)
{
}

bool BattleScene::skillEffectAssemble(std::string _skillName)
{
	
	EFFECTMANAGER->play(_skillName, 300, 300);

	return false;
}
