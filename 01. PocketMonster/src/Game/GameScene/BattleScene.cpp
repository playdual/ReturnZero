#include "stdafx.h"
#include "BattleScene.h"
#include "Common/SystemManagers.h"
#include "Common/GameManagers.h"

//BattleScene::BattleScene(){}

BattleScene::BattleScene(){}

BattleScene::~BattleScene(){}

bool BattleScene::init()
{
	//IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//pocketmonEffectInit();
	//
	////테스트용 포켓몬 정보 복사하기
	//m_playerPocketmon = POCKETMONMANAGER->getPocketmonInform(0);
	//m_wildPocketmon = POCKETMONMANAGER->getPocketmonInform(1);


	//===============
	// RECT 초기화 //
	//===============
	//UI 오브젝트 위치 초기화
	//m_playerBottomX = WINSIZEX;
	//m_playerimgX = 1224;
	//m_playerPocketmonX= 1224;
	//m_playerStatusX = 1524;
	//m_enemyBottomX = -547;
	//m_enemyPocketmonX = -360;
	//m_enemyPocketmonY = 165;
	//m_enemyStatusX = -425;
	//m_wildPocketmonHpBarWigth = 230;
	//m_playerPocketmonHpBarWigth = 230;

	////배경화면
	////적 상태창 
	//m_enemyStatus = UTIL::IRectMake(m_enemyStatusX, 80, 425, 130);
	////적 바닥
	// m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
	////적 포켓몬
	//m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, m_enemyPocketmonY, 165, 181);
	//
	//
	////플레이어바닥
	//m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 547, 159);
	////플레이어 이미지
	//m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
	////플레이어 포켓몬
	//m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	////플레이어 상태창
	//m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	////플레이어 최대 체력
	//m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, 230, 30);
	////플레이어 현재 체력
	//m_playerCurrentHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, m_playerPocketmonHpBarWigth, 30);


	////스킬 이팩트
	//m_playerAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
	//m_enemyAtkSkillEffect = UTIL::IRectMake(410, 165, 563, 365);
	//
	////===========
	//// 대기상태 //
	////===========
	////행동 선택창
	//m_selectRect = UTIL::IRectMake(618, 595, 20, 40);
	//m_explainRect = UTIL::IRectMake(0, 538, WINSIZEX, WINSIZEY - 538);

	////스킬 선택창
	//m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
	//m_skillListRect = UTIL::IRectMake(0, 538, 605, WINSIZEY - 538);
	//m_skillExplainRect = UTIL::IRectMake(610, 538, WINSIZEX - 610, WINSIZEY - 538);

	////===================
	//// 전투유형조절변수 //
	////===================
	//wildBattle = true;
	//npcBattle = false;
	//
	////===========================
	//// 전투 애니케이션 관련 변수 //
	////===========================
	//wildBattleIntroAniOn = true;
	//uiObjectRegularPosition = false;
	//playerImgSlideOut = false;
	//playerHpExpBarStayMotionOn = false;

	////===================
	//// 선택창 조절 변수 //
	////===================
	//fight = true;
	//bag = false;
	//pocketmon = false;
	//run = false;

	//playerAtkOn = false;

	////===================
	//// 스킬창 조절 변수 //
	////===================
	//skill_1 = true;
	//skill_2 = false;
	//skill_3 = false;
	//skill_4 = false;

	////===============
	//// 공격 턴 변수 //
	////===============
	//playerTurn = true;
	//enemyTurn = false;
	//motionUp = true;
	//m_count = 0;

	////================
	//// 공격관련 변수 //
	////================
	////플레이어
	//playerAtkSkillOn = false;
	//playerSkillMotionOn = false;
	//playerSkillEffect = false;
	//playerHitEffect = false;
	//playerSkillExplainDone = false;
	//playerSkillEffectDone = false;
	//enemyHpChange = false;
	//explainEffect = false;
	//enemyAtkSkillOn = false;
	//
	//m_skillCount = 0;
	//m_enemyTwinkleCount = 0;
	//m_enemyMinusHp = 0;
	//m_enemyCurrentMinusHp = 0;
	//m_enemyAlpha = 255;
	//m_playerAlpha = 255;

	////적
	//enemySkillEffect = false;
	//enemySkillEffectDone = false;
	//enemyHitEffect = false;
	//playerHpChange = false;
	//enemyExplainEffect = false;
	//m_playerAlpha = 255;
	//m_playerTwinkleCount = 0;
	//m_playerMinusHp = 0;
	//m_playerCurrentMinusHp = 0;

	////=================
	//// 전투 승패 관련 //
	////=================
	//
	//pocketmonLose = false;
	//playerLose = false;
	//enemyLose = false;
	//getExp = false;

	return true;

}

bool BattleScene::init(std::shared_ptr<player> _player, std::shared_ptr<player> _npc)
{
	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	pocketmonEffectInit();

	//테스트용 포켓몬 정보 복사하기
	//m_playerPocketmon = POCKETMONMANAGER->getPocketmonInform(0);
	//m_wildPocketmon = POCKETMONMANAGER->getPocketmonInform(1);
	return true;
}

bool BattleScene::init(std::shared_ptr<player> _player, PocketMon& _pocketmon)
{
	IMAGEMANAGER->addImage("battleTemp", "images/battleTemp2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	pocketmonEffectInit();

	//플레이어의 포켓몬 벡터를 가리키는 주소를 받아서 첫 번째 컨테이너의 값을 가리키는 주소를 가져온다
	m_playerPocketmons = _player->getPocketmons();
	for (auto it = m_playerPocketmons.begin(); it != m_playerPocketmons.end(); ++it)
	{
		selectPocketmon = (*it);
		break;
	}

	m_wildPocketmon = _pocketmon;
	


	//===============
	// RECT 초기화 //
	//===============
	//UI 오브젝트 위치 초기화
	m_playerBottomX = WINSIZEX;
	m_playerimgX = 1224;
	m_playerPocketmonX = 1224;
	m_playerStatusX = 1524;
	m_enemyBottomX = -547;
	m_enemyPocketmonX = -360;
	m_enemyPocketmonY = 165;
	m_enemyStatusX = -425;
	m_wildPocketmonHpBarWigth = 230;
	m_playerPocketmonHpBarWigth = 230;

	//배경화면
	//적 상태창 
	m_enemyStatus = UTIL::IRectMake(m_enemyStatusX, 80, 425, 130);
	//적 바닥
	m_enemyBottom = UTIL::IRectMake(m_enemyBottomX, 228, 547, 159);
	//적 포켓몬
	m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, m_enemyPocketmonY, 165, 181);


	//플레이어바닥
	m_playerBottom = UTIL::IRectMake(m_playerBottomX, 467, 547, 159);
	//플레이어 이미지
	m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
	//플레이어 포켓몬
	m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	//플레이어 상태창
	m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	//플레이어 최대 체력
	m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, 230, 30);
	//플레이어 현재 체력
	m_playerCurrentHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, m_playerPocketmonHpBarWigth, 30);


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
	playerHpExpBarStayMotionOn = false;

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
	//플레이어
	playerAtkSkillOn = false;
	playerSkillMotionOn = false;
	playerSkillEffect = false;
	playerHitEffect = false;
	playerSkillExplainDone = false;
	playerSkillEffectDone = false;
	enemyHpChange = false;
	explainEffect = false;
	enemyAtkSkillOn = false;

	m_skillCount = 0;
	m_enemyTwinkleCount = 0;
	m_enemyMinusHp = 0;
	m_enemyCurrentMinusHp = 0;
	m_enemyAlpha = 255;
	m_playerAlpha = 255;

	//적
	enemySkillEffect = false;
	enemySkillEffectDone = false;
	enemyHitEffect = false;
	playerHpChange = false;
	enemyExplainEffect = false;
	m_playerAlpha = 255;
	m_playerTwinkleCount = 0;
	m_playerMinusHp = 0;
	m_playerCurrentMinusHp = 0;

	//=================
	// 전투 승패 관련 //
	//=================

	pocketmonLose = false;
	playerLose = false;
	enemyLose = false;
	getExp = false;

	return true;	
}

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
	if (KEYMANAGER->isOnceKeyDown(GAME_LMOUSE))
	{
		//EFFECTMANAGER->play("파이리스킬1", m_ptMouse.x, m_ptMouse.y);
		//test = EFFECTMANAGER->getIsPlay();
		//m_player->skillEffect(1);
	}
	
	if(test) test = EFFECTMANAGER->getIsPlay();

	wsprintf(str, "%d", test);
	TextOut(hdc, 100, 100, str, strlen(str));

	wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(hdc, m_ptMouse.x, m_ptMouse.y - 20, str, strlen(str));

	wsprintf(str, "fight: %d, bag: %d, pocketmon: %d, run: %d", fight, bag, pocketmon, run);
	TextOut(hdc, 10, 10, str, strlen(str));

	wsprintf(str, "s_1: %d, s_2: %d, s_3: %d, s_4: %d", skill_1, skill_2, skill_3, skill_4);
	TextOut(hdc, 10, 25, str, strlen(str));

	wsprintf(str, "포켓몬 hp: %d, m_enemyMinusHp: %d", m_wildPocketmon.m_currentHp, m_enemyMinusHp);
	TextOut(hdc, 500, 300, str, strlen(str));
	*/

	wsprintf(str, "Exp: %d, m_skillCount: %d", selectPocketmon->m_currentExp, m_skillCount);
	TextOut(hdc, 10, 25, str, strlen(str));
	
	wsprintf(str, "%d, %d", m_wildPocketmon.m_currentHp, m_wildPocketmonHpBarWigth);
	TextOut(hdc, 10, 40, str, strlen(str));


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
		if (enemyTurn)
		{
			//m_skillCount++;
			enemySkillName = selectEnemyskill();
		}
		/*	if (m_skillCount > 20)
			{
				m_skillCount = 0;
				enemyTurn = false;
				enemyAtkSkillOn = false;
				playerTurn = true;
			}
		}*/
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
		m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
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
		m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, 230, 30);
		m_playerCurrentHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, m_playerPocketmonHpBarWigth, 30);
		if (m_playerStatusX <= PLAYERSTATUSX) wildBattleIntroAniOn = false;
	}
}
void BattleScene::npcBattleIntroAni()
{
}

void BattleScene::pocketmonEffectInit()
{
	//플레이어
	//파이리 공격
	EFFECTMANAGER->addEffect("불꽃세례", "images/pailiSkill_1.bmp", 35*3, 150*3, 35*3, 30*3, 1, 0.1f, 100);

	//적
	//피카츄 공격
	EFFECTMANAGER->addEffect("피카츄백만볼트", "images/attackEffect/picachu100v.bmp", 159*4, 550*4, 159*4, 110*4, 1, 0.1f, 100);
}

//========================
// UI RENDER 함수들 모음 //
//========================

void BattleScene::explainRect(HDC hdc)
{
	char str[100];

	UTIL::DrawRect(hdc, m_explainRect);
	if (wildBattleIntroAniOn)
	{
		if (uiObjectRegularPosition && !playerImgSlideOut)
		{
			wsprintf(str, "앗!! 야생의");
			TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 10, str, strlen(str));

			wsprintf(str, "%s가 튀어나왔다!!", m_wildPocketmon.m_name.c_str());
			TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 40, str, strlen(str));

		}
		if (playerImgSlideOut)
		{
			wsprintf(str, "가랏 %s!!!!", selectPocketmon->m_customName.c_str());
			TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 10, str, strlen(str));
		}
	}
}
void BattleScene::selectRect(HDC hdc)
{
	UTIL::DrawRect(hdc, m_selectRect);
}
void BattleScene::skillSelectRect(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillSelectRect);
}
void BattleScene::enemyUiStatus(HDC hdc)
{
	char str[100];
	UTIL::DrawRect(hdc, m_enemyStatus);

	
	//이름
	wsprintf(str, "%s", m_wildPocketmon.m_name.c_str());
	TextOut(hdc, m_enemyStatus.left+10, m_enemyStatus.top+10, str, strlen(str));

	//레벨
	wsprintf(str, "Lv %d", m_wildPocketmon.m_level);
	TextOut(hdc, m_enemyStatus.left + 310, m_enemyStatus.top + 20, str, strlen(str));

}
void BattleScene::enemyUiBottom(HDC hdc)
{
	UTIL::DrawRect(hdc, m_enemyBottom);
}
void BattleScene::enemyUiPocketmon(HDC hdc)
{
	UTIL::DrawRect(hdc, m_enemyPocketmon);
	m_wildPocketmon.m_pocketmonFrontImg->alphaRender(hdc, m_enemyPocketmon.left, m_enemyPocketmon.top, m_enemyAlpha);
}
void BattleScene::enemyUiMaxHp(HDC hdc)
{
	m_enemyMaxHp = UTIL::IRectMake(m_enemyStatus.left+181, 155, 230, 30);
	//UTIL::DrawRect(hdc, m_enemyMaxHp);
	UTIL::DrawColorRect(hdc, m_enemyMaxHp, RGB(120, 120, 120));
}
void BattleScene::enemyUiCurrentHp(HDC hdc)
{
	m_enemyCurrentHp = UTIL::IRectMake(m_enemyStatus.left + 181, 155, m_wildPocketmonHpBarWigth, 30);
	UTIL::DrawColorRect(hdc, m_enemyCurrentHp, RGB(10, 70, 70));
}

void BattleScene::playerUiBottom(HDC hdc)
{
	UTIL::DrawRect(hdc, m_playerBottom);
}
void BattleScene::playerUiPoketmon(HDC hdc)
{
	UTIL::DrawRect(hdc, m_playerPocketmonImg);
	selectPocketmon->m_pocketmonBackImg->alphaRender(hdc, m_playerPocketmonImg.left, m_playerPocketmonImg.top, m_playerAlpha);
}
void BattleScene::playerUiImg(HDC hdc)
{
	UTIL::DrawRect(hdc, m_playerImg);
	IMAGEMANAGER->findImage("trainersMan")->alphaRender(hdc, m_playerImg.left, m_playerImg.top, m_playerAlpha);
}
void BattleScene::playerUiStatus(HDC hdc)
{
	char str[100];
	UTIL::DrawRect(hdc, m_playerStatus);
	wsprintf(str, "%s", selectPocketmon->m_customName.c_str());
	TextOut(hdc, m_playerStatus.left + 10, m_playerStatus.top + 10, str, strlen(str));

	wsprintf(str, "Lv %d", selectPocketmon->m_level);
	TextOut(hdc, m_playerStatus.left + 310, m_playerStatus.top + 20, str, strlen(str));

}
void BattleScene::playerUiSkillList(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillListRect);
}
void BattleScene::playerUiSkillExplain(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillExplainRect);
}
void BattleScene::playerUiMaxHp(HDC hdc, int _y)
{
	m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431 + _y, 230, 30);
	//UTIL::DrawRect(hdc, m_enemyMaxHp);
	UTIL::DrawColorRect(hdc, m_playerMaxHp, RGB(120, 120, 120));
}
void BattleScene::playerUiCurrentHp(HDC hdc, int _y)
{
	m_playerCurrentHp = UTIL::IRectMake(m_playerStatus.left + 181, 431 + _y, m_playerPocketmonHpBarWigth, 30);
	UTIL::DrawColorRect(hdc, m_playerCurrentHp, RGB(10, 70, 70));
}
void BattleScene::playerUiMaxExp(HDC hdc, int _y)
{
}
void BattleScene::plyaerUiCurrentExp(HDC hdc, int _y)
{
}
void BattleScene::playerStayMotion()
{
	m_count++;
	if (m_count % 20 == 0 && motionUp)
	{
		motionUp = false;
		//플레이어 포켓몬
		m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 319, 210, 209);
		//플레이어 상태창
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 346, 446, 180);
		playerHpExpBarStayMotionOn = true;
	}
	else if (m_count % 20 == 0 && !motionUp)
	{
		motionUp = true;
		//플레이어 포켓몬
		m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
		//플레이어 상태창
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
		playerHpExpBarStayMotionOn = false;
	}

	if (m_count > 10000) m_count = 0;

}
void BattleScene::playerHpExpBarStayMotion(HDC hdc)
{
	if (playerHpExpBarStayMotionOn)
	{
		playerUiMaxHp(hdc, -10);
		playerUiCurrentHp(hdc, -10);
		playerUiMaxExp(hdc, -10);
		plyaerUiCurrentExp(hdc, -10);
	}
	else if (!playerHpExpBarStayMotionOn)
	{
		playerUiMaxHp(hdc, 0);
		playerUiCurrentHp(hdc, 0);
		playerUiMaxExp(hdc, 0);
		plyaerUiCurrentExp(hdc, 0);
	}
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
		//playerAtkSkillOn = true;
		playerSkillMotionOn = true;
	}

}

//=================
// 공격&방어 함수 //
//=================

std::string BattleScene::selectEnemyskill()
{
	int temp = 0;/*UTIL::GetRndIntFromTo(0, 3);*/
	if (temp == 0)
		return "";
		//return m_wildPocketmon.m_skill_1;
	/*else if (temp == 1) return m_wildPocketmon.m_skill_2;
	else if (temp == 2) return m_wildPocketmon.m_skill_3;
	else if (temp == 3) return m_wildPocketmon.m_skill_4;*/

	//enemyAtkSkillOn = true;
}


//============
// 렌더 함수 //
//============
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
		enemyUiMaxHp(hdc);
		enemyUiCurrentHp(hdc);

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
		enemyUiMaxHp(hdc);
		enemyUiCurrentHp(hdc);
		//플레이어
		playerUiBottom(hdc);
		playerUiPoketmon(hdc);
		playerUiStatus(hdc);
		playerHpExpBarStayMotion(hdc);

		if (playerTurn)
		{
			//설명 + 선택창
			if (!playerAtkOn)
			{
				explainRect(hdc);
				//선택 커서
				selectRect(hdc);
			}
			
			if (playerAtkOn)
			{
				playerUiSkillList(hdc);
				playerUiSkillExplain(hdc);
				skillSelectRect(hdc);
			}
		}
		if (playerSkillMotionOn)
		{
			explainRect(hdc);
			playerPockatmonAttack(hdc);
		}
		if (enemyTurn)
		{
			explainRect(hdc);
			enemySkillEffectAssemble(selectEnemyskill(), hdc);
		}
	}

	wsprintf(str, "%d, %d", m_ptMouse.x, m_ptMouse.y);
	TextOut(hdc, m_ptMouse.x, m_ptMouse.y-20, str, strlen(str));
	
	EFFECTMANAGER->render(hdc);
	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}

void BattleScene::playerPockatmonAttack(HDC hdc)
{
	char str[100];

	if (m_skillCount < 100 && !playerSkillExplainDone)
	{
		m_skillCount++;
		wsprintf(str, "%s의", selectPocketmon->m_name.c_str());
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

		//wsprintf(str, "%s 공격!", m_playerPocketmon.m_skill_1.c_str());
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 30, str, strlen(str));
	}
	else if (m_skillCount >= 100 && !playerSkillExplainDone)
	{
		m_skillCount = 0;
		playerSkillExplainDone = true;
	}
	//{
	//	//playerSkillEffect = true;
	//}

	if (playerSkillExplainDone)
	{
		//playerSkillEffectAssemble(m_playerPocketmon.m_skill_1, hdc);
	}

	/*if (m_count > 200)
	{
		m_skillCount = 0;
		playerAtkSkillOn = false;
		enemyTurn = true;
	}*/

}
int BattleScene::checkDamage()
{
	if (!enemyTurn)
	{
		return 30;/*m_playerPocketmon.m_atk	- m_wildPocketmon.m_def;*/
	}
	else if (enemyTurn)
	{
		return 4;
	}
}

//npc 배틀 함수 모음
void BattleScene::npcBattleFunctions()
{
}
void BattleScene::npcBattleRender(HDC hdc)
{
}

//플레이어 공격 스킬 모음
void BattleScene::pailiFireShower(std::string _skillName, HDC hdc)
{
	//1단계: 포켓몬 스킬 이팩트
	if (!playerSkillEffect && !playerSkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 707, 195);
		EFFECTMANAGER->play(_skillName, 774, 222);
		EFFECTMANAGER->play(_skillName, 696, 287);
		EFFECTMANAGER->play(_skillName, 778, 304);
		playerSkillEffect = EFFECTMANAGER->getIsPlay();
	}
	else if (playerSkillEffect && !EFFECTMANAGER->getIsPlay())
	{
		playerSkillEffect = false;
		playerSkillEffectDone = true;
		playerHitEffect = true;
	}

	//2단계: 적 포켓몬 깜빡 깜빡
	if (playerHitEffect)
	{
		m_enemyTwinkleCount++;
		m_enemyAlpha = 0;
		if (m_enemyTwinkleCount > 60)
		{
			m_enemyAlpha = 255;
			m_enemyTwinkleCount = 0;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}

	if (enemyHpChange)
	{
		//m_skillCount++;
		m_enemyCurrentMinusHp++;
		m_wildPocketmon.m_currentHp--;
		if (m_wildPocketmon.m_currentHp <= 0)
		{
			m_wildPocketmon.m_currentHp = 0;
			m_enemyMinusHp = 0;
			enemyLose = true;
		}
		m_wildPocketmonHpBarWigth = (230 * m_wildPocketmon.m_currentHp) / m_wildPocketmon.m_maxHp;
		if (m_enemyCurrentMinusHp == m_enemyMinusHp)
		{
			m_enemyCurrentMinusHp = 0;
			//m_skillCount = 0;
			m_enemyMinusHp = 0;
			enemyHpChange = false;
			explainEffect = true;
		}
	}

	if (explainEffect)
	{
		m_skillCount++;
		char str[100];
		wsprintf(str, "효과는 굉장했다!!");
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
		if (m_skillCount > 40)
		{
			m_skillCount = 0;
			playerSkillEffect = false;
			playerSkillEffectDone = false;
			explainEffect = false;
			playerSkillMotionOn = false;
			playerSkillExplainDone = false;
			enemyTurn = true;
		}
	}

	//적 움직이고
	if (enemyLose) wildBattleOutroAni(hdc);
}

//적 공격 스킬 모음
void BattleScene::picachu100v(std::string _skillName, HDC hdc)
{
	if (!enemySkillEffect && !enemySkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 573, 317);
		enemySkillEffect = true;
	}
	else if (enemySkillEffect && !EFFECTMANAGER->getIsPlay())
	{
		enemyHitEffect = true;
		enemySkillEffect = false;
		enemySkillEffectDone = true;
	}

	if (enemyHitEffect)
	{
		m_playerTwinkleCount++;
		m_playerAlpha = 0;
		if (m_playerTwinkleCount > 20)
		{
			m_playerAlpha = 255;
			m_playerTwinkleCount = 0;
			enemyHitEffect = false;
			playerHpChange = true;
			m_playerMinusHp = checkDamage();
		}
	}

	if (playerHpChange)
	{
		m_playerCurrentMinusHp++;
		selectPocketmon->m_currentHp--;
		if (selectPocketmon->m_currentHp <= 0)
		{
			selectPocketmon->m_currentHp = 0;
			m_playerMinusHp = 0;
			playerLose = true;
		}
		m_playerPocketmonHpBarWigth = (230 * selectPocketmon->m_currentHp) / selectPocketmon->m_maxHp;
		if (m_playerCurrentMinusHp == m_playerMinusHp)
		{
			m_playerCurrentMinusHp = 0;
			m_playerMinusHp = 0;
			playerHpChange = false;
			enemyExplainEffect = true;
		}
	}
	if (enemyExplainEffect)
	{
		m_skillCount++;
		char str[100];
		wsprintf(str, "효과는 굉장했다!!");
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
		if (m_skillCount > 40)
		{
			m_skillCount = 0;
			enemySkillEffectDone = false;
			enemyExplainEffect = false;
			enemyTurn = false;
			playerAtkOn = false;
			playerTurn = true;
		}
	}
}



void BattleScene::wildBattleOutroAni(HDC hdc)
{
	char str[100];
	//적 포켓몬
	m_enemyPocketmonY += 10;
	m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, m_enemyPocketmonY, 165, 181);
	if (m_enemyPocketmonY > WINSIZEY)
	{
		m_skillCount++;
		wsprintf(str, "야생의 %s는(은)", m_wildPocketmon.m_name.c_str());
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

		wsprintf(str, "쓰러졌다!", m_wildPocketmon.m_name.c_str());
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 40, str, strlen(str));

		if (m_skillCount > 50)
		{
			explainRect(hdc);
			wsprintf(str, "%s는(은)", selectPocketmon->m_customName.c_str());
			TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

			wsprintf(str, "%d 경험치를 얻었다!", m_wildPocketmon.m_wildExp);
			TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 40, str, strlen(str));

			if (!getExp)
			{
				getExp = true;
				selectPocketmon->m_currentExp += m_wildPocketmon.m_wildExp;
			}
			if (m_skillCount > 150)
			{
				SCENEMANAGER->scenePop();
			}
		}
	}
}


//포켓몬 스킬 이펙트들 모음
bool BattleScene::playerSkillEffectAssemble(std::string _skillName, HDC hdc)
{
	//EFFECTMANAGER->play(_skillName, 300, 300);
	if (_skillName == "불꽃세례") pailiFireShower(_skillName, hdc);


	return true;
}

void BattleScene::enemySkillEffectAssemble(std::string _skillName, HDC hdc)
{
	if (_skillName == "피카츄백만볼트") picachu100v(_skillName, hdc);
}
