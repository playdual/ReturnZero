#include "stdafx.h"
#include "BattleScene.h"
#include "Common/SystemManagers.h"
#include "Common/GameManagers.h"

//BattleScene::BattleScene(){}

BattleScene::BattleScene(){}

BattleScene::~BattleScene(){}

bool BattleScene::init()
{
	return true;
}

bool BattleScene::init(std::shared_ptr<player> _player, std::shared_ptr<player> _npc)
{
	pocketmonEffectInit();

	//테스트용 포켓몬 정보 복사하기
	//m_playerPocketmon = POCKETMONMANAGER->getPocketmonInform(0);
	//m_wildPocketmon = POCKETMONMANAGER->getPocketmonInform(1);
	return true;
}

bool BattleScene::init(std::shared_ptr<player> _player, PocketMon& _pocketmon)
{
	pocketmonEffectInit();

	//플레이어의 포켓몬 벡터를 가리키는 주소를 받아서 첫 번째 컨테이너의 값을 가리키는 주소를 가져온다
	trainer = _player;
	m_playerPocketmons = trainer->getPocketmons();
	for (auto it = m_playerPocketmons.begin(); it != m_playerPocketmons.end(); ++it)
	{
		selectPocketmon = (*it);
		break;
	}

	//changePocketmon();
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
	m_wildPocketmonHpBarWigth = 204;
	m_playerPocketmonHpBarWigth = checkHpBarWigth();
	/*selectPocketmon->m_currentExp = selectPocketmon->m_maxExp - 10;
	selectPocketmon->skillList[1].currentpp = 0;*/
	m_playerPocketmonExpBarWigth = checkExpBarWigth();

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
	trainerAni = false;
	//플레이어 포켓몬
	m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
	//플레이어 상태창
	m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
	//플레이어 최대 체력
	m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, 230, 30);
	//플레이어 현재 체력
	m_playerCurrentHp = UTIL::IRectMake(playerCurrentHpLeft(), playerCurrentHpTop(), m_playerPocketmonHpBarWigth, 30);
	//플레이어 현재 Exp
	m_playerCurrentExp = UTIL::IRectMake(playerCurrentExpLeft(), playerCurrentExpTop(), m_playerPocketmonExpBarWigth, 30);
	//플레이어 렙업시 증가 능력창 보여주는 창
	m_playerPocketmonLevelUpRect = UTIL::IRectMake(626, 266, 380, 400);

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


	//=====================
	// 포켓몬변경조절변수 //
	//=====================
	playerPocketmonChangeOn = false;

	//===================
	// 전투유형조절변수 //
	//===================
	wildBattle = true;
	npcBattle = false;

	//===========================
	// 전투 애니메이션 관련 변수 //
	//===========================
	wildBattleIntroAniOn = true;
	uiObjectRegularPosition = false;
	playerImgSlideOut = false;
	playerImgSlideOutOn = false;
	m_trainerThrowBall = IMAGEMANAGER->findImage("trainerThrowBall");
	m_trainerThrowBallAni = ANIMANAGER->findAnimation("trainerThrowBallAni");
	m_throwBall = IMAGEMANAGER->findImage("throwBall");
	m_throwBallAni = ANIMANAGER->findAnimation("throwBallAni");
	m_ballOpen = IMAGEMANAGER->findImage("ballOpen");
	m_ballOpenAni = ANIMANAGER->findAnimation("ballOpenAni");
	m_shakeBall = IMAGEMANAGER->findImage("shakeBall");
	m_shakeBallAni = ANIMANAGER->findAnimation("shakeBallAni");
	m_pocketmonCatchEffect = IMAGEMANAGER->findImage("pocketmonCatchEffect");
	m_pocketmonCatchEffectAni = ANIMANAGER->findAnimation("pocketmonCatchEffectAni");

	ANIMANAGER->stop("trainerThrowBallAni");
	ANIMANAGER->stop("throwBallAni");
	ANIMANAGER->stop("ballOpenAni");
	ANIMANAGER->stop("shakeBallAni");
	ANIMANAGER->stop("pocketmonCatchEffectAni");


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
	battleEnd = false;
	attributeOn = false;
	plusAttribute = false;
	comeBackEnemey = false;

	m_skillCount = 0;
	m_enemyEffectCount = 0;
	m_enemyMinusHp = 0;
	m_enemyCurrentMinusHp = 0;
	m_enemyAlpha = 255;
	m_playerAlpha = 255;
	m_playerCurrentPlusExp = 0;
	m_playerSelectSkillNumber = 0;

	//적
	enemySkillEffect = false;
	enemySkillEffectDone = false;
	enemyHitEffect = false;
	playerHpChange = false;
	enemyExplainEffect = false;
	enemySkillSelect = false;
	comeBackPlayer = false;
	m_playerAlpha = 255;
	m_playerTwinkleCount = 0;
	m_playerMinusHp = 0;
	m_playerCurrentMinusHp = 0;
	m_enemySelectSkillNumber = 0;
	m_playerPocketmonY = 329;

	//=================
	// 전투 승패 관련 //
	//=================

	pocketmonLose = false;
	playerLose = false;
	enemyLose = false;
	emptyBattlePocketmon = false;
	playerPocketmonLevelUpOn = false;
	playerPocketmonStatusPulsOn = false;
	getSkillDone = false;
	checkSkillGet = false;
	pushBackSkill = false;
	playerPocketmonLevelCheck = false;
	m_levelUpCount = 0;
	m_loseAniCount = 0;
	m_levelUpCount = 0;
	m_levelCheckCount = 0;

	//레벨업 시 능력치 업그레드
	int tempHp = 0;
	int tempAtk = 0;
	int tempDef = 0;
	int tempSpecialAtk = 0;
	int tempSpecialDef = 0;
	int tempSpeed = 0;

	//==========================
	// 포켓몬 잡기 관련 변수들 //
	//==========================
	catchAniOn = false;
	ballDownOn = false;
	ballOpen = false;
	ballDown = false;
	shakitBallOn = false;
	catchSuccess = false;
	catchSuccessEffect = false;
	catchSuccessEffectDone = false;
	catchExplainOn = false;
	catchOn = false;
	catchStartExplainOn = false;
	ballThrowOn = false;
	m_catchStartCount = 0;
	m_ballIndex = 0;
	m_catchCount = 0;
	m_ballOpenCount = 0;
	m_ballDownIndex = 0;
	m_ballSuccessAlpha = 0;
	m_successCount = 0;
	m_catchExplainCount = 0;
	whiteBgAlpha = 255;

	//================
	// 포켓몬 체인지 //
	//================
	pocketmonChangeOn = false;
	blackBgOn = false;
	throwBallOn = false;
	ballThrowStart = false;
	ballThrowAniOn = false;
	statusMoveOn = false;
	setPlayerStatus = false;
	moveEnemyStatus = false;
	whiteBgAlpahReversOn = false;
	setNewPocketmon = false;
	comeBackPocketmon = false;
	bufferTimeOn = false;
	pocketmonCatchEffectAniOn = false;

	blackBgAlpha = 255;
	whiteBgAlpah = 0;
	bufferTimeCount = 0;
	return true;	
}

void BattleScene::release()
{
}
void BattleScene::update(float _deltaTime)
{
	void* lastSceneInfo = SCENEMANAGER->getLastSceneReturnInfo();
	if (lastSceneInfo != nullptr)
	{
		int infoType = *(int*)lastSceneInfo;
		switch (infoType)
		{
		case INFO_ITEM:
			itempInfo = *(ItemInfo*)lastSceneInfo;
			if (itempInfo.name == "몬스터볼") catchAniOn = true;
			break;
		case INFO_CHANGEPOKE:
			cpInfo = *(ChangePocketInfo*)lastSceneInfo;
			pocketmonChangeOn = cpInfo.isChanged;
			break;
		case INFO_USEDITEM:
			uiInfo = *(UsedItemInfo*)lastSceneInfo;
			break;
		}
		SCENEMANAGER->eraseLastInfo();
	}

	if (wildBattle) wildBattleFunctions();

	//if (npcBattle) npcBattleFunctions();

	if (KEYMANAGER->isStayKeyDown(P1_N))
	{
		pocketmonChangeOn = true;
	}
}
void BattleScene::render(HDC hdc)
{
	char str[200];
	if (wildBattle) wildBattleRender(hdc);

	wsprintf(str, "Exp: %d, m_skillCount: %d", selectPocketmon->m_currentExp, m_skillCount);
	TextOut(hdc, 10, 25, str, strlen(str));

	wsprintf(str, "%d, %d", m_wildPocketmon.m_currentHp, m_wildPocketmonHpBarWigth);
	TextOut(hdc, 10, 40, str, strlen(str));

	EFFECTMANAGER->render(hdc);
}
void BattleScene::afterRender(HDC hdc)
{
}
void BattleScene::debugRender(HDC hdc)
{
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

}

void BattleScene::wildBattleFunctions()
{
	if (wildBattleIntroAniOn) wildBattleIntroAni();
	else 
	{
		if (playerTurn)
		{
			if (playerPocketmonChangeOn) playerPocketmonChange();
			if (!playerAtkOn) moveButton();
			if (playerAtkOn) moveSkillSelectButton();
			if (playerAtkOn && KEYMANAGER->isOnceKeyDown(P1_X)) playerAtkOn = false;
			playerStayMotion();
			m_playerPocketmonHpBarWigth = checkHpBarWigth();
			m_playerPocketmonExpBarWigth = checkExpBarWigth();
		}
		if (enemyTurn) { }
	}
	
}
void BattleScene::npcBattleIntroAni()
{
}

//========================
// UI RENDER 함수들 모음 //
//========================

void BattleScene::explainRect(HDC hdc)
{
	char str[100];

	IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);
	if (wildBattleIntroAniOn)
	{
		if (uiObjectRegularPosition && !playerImgSlideOut)
		{
			wsprintf(str, "앗!! 야생의");
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

			wsprintf(str, "%s가 튀어나왔다!!", m_wildPocketmon.m_name.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

		}
		if (playerImgSlideOut)
		{
			wsprintf(str, "가랏 %s!!!!", selectPocketmon->m_customName.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));
			playerImgSlideOutOn = true;
		}
	}
	
	if (playerTurn && !wildBattleIntroAniOn && !playerAtkOn && !catchAniOn && !pocketmonChangeOn)
	{
		wsprintf(str, "%s는(은)", selectPocketmon->m_name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "무엇을 할까?");
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

		wsprintf(str, "싸운다");
		TextOut(hdc, 649, 590, str, strlen(str));

		wsprintf(str, "가방");
		TextOut(hdc, 854, 590, str, strlen(str));

		wsprintf(str, "포켓몬");
		TextOut(hdc, 649, 666, str, strlen(str));

		wsprintf(str, "도망간다");
		TextOut(hdc, 854, 666, str, strlen(str));
	}

}
void BattleScene::selectRect(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_selectRect);
	IMAGEMANAGER->render("arrow", hdc, m_selectRect.left, m_selectRect.top);
}
void BattleScene::skillSelectRect(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_skillSelectRect);
	IMAGEMANAGER->render("arrow", hdc, m_skillSelectRect.left, m_skillSelectRect.top);
}
void BattleScene::playerPocketmonChange()
{
	for (auto it = m_playerPocketmons.begin(); it != m_playerPocketmons.end(); ++it)
	{
		selectPocketmon = (*it);
		break;
	}
}
void BattleScene::enemyUiStatus(HDC hdc)
{
	char str[100];
	//UTIL::DrawRect(hdc, m_enemyStatus);
	IMAGEMANAGER->render("enemyStatus", hdc, m_enemyStatus.left, m_enemyStatus.top);
	//이름
	wsprintf(str, "%s", m_wildPocketmon.m_name.c_str());
	TextOut(hdc, m_enemyStatus.left+30, m_enemyStatus.top + 25, str, strlen(str));

	//레벨
	wsprintf(str, "Lv %d", m_wildPocketmon.m_level);
	TextOut(hdc, m_enemyStatus.left + 280, m_enemyStatus.top + 25, str, strlen(str));
	enemyUiCurrentHp(hdc);
}
void BattleScene::enemyUiBottom(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_enemyBottom);
	IMAGEMANAGER->render("enemyBottom", hdc, m_enemyBottom.left, m_enemyBottom.top);
}
void BattleScene::enemyUiPocketmon(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_enemyPocketmon);
	m_wildPocketmon.m_pocketmonFrontImg->alphaRender(hdc, m_enemyPocketmon.left, m_enemyPocketmon.top, m_enemyAlpha);
}
void BattleScene::enemyUiMaxHp(HDC hdc)
{
	m_enemyMaxHp = UTIL::IRectMake(m_enemyStatus.left + 165, 160, 230, 30);
	//UTIL::DrawColorRect(hdc, m_enemyMaxHp, RGB(120, 120, 120));
}
void BattleScene::enemyUiCurrentHp(HDC hdc)
{
	m_enemyCurrentHp = UTIL::IRectMake(m_enemyStatus.left + 165, 161, m_wildPocketmonHpBarWigth, 30);
	//UTIL::DrawColorRect(hdc, m_enemyCurrentHp, RGB(10, 70, 70));
	IMAGEMANAGER->render("greenHpBar", hdc, m_enemyCurrentHp.left, m_enemyCurrentHp.top, 0, 0, m_wildPocketmonHpBarWigth, 3 * 5);
	//IMAGEMANAGER->render("greenHpBar", hdc, m_enemyCurrentHp.left, m_enemyCurrentHp.top);
	// 9*3+246, 3*4+1
}

void BattleScene::playerUiBottom(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_playerBottom);
	IMAGEMANAGER->render("playerBottom", hdc, m_playerBottom.left, m_playerBottom.top);
}
void BattleScene::playerUiPoketmon(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_playerPocketmonImg);
	if (trainerAni && !ANIMANAGER->isPlay("throwBallAni"))
	{
		selectPocketmon->m_pocketmonBackImg->alphaRender(hdc, m_playerPocketmonImg.left, m_playerPocketmonImg.top+20, m_playerAlpha);
	}
}
void BattleScene::playerUiImg(HDC hdc)
{
	if (playerImgSlideOutOn)
	{
		if (!trainerAni)
		{
			ANIMANAGER->start("trainerThrowBallAni");
			ANIMANAGER->start("throwBallAni");
			trainerAni = true;
		}
	}
	
	m_trainerThrowBall->aniRender(hdc, m_playerImg.left, m_playerImg.top, m_trainerThrowBallAni);
	if (trainerAni)
	{
		m_throwBall->aniRender(hdc, m_playerPocketmonImg.left, m_playerPocketmonImg.top, m_throwBallAni);
	}
	

}
void BattleScene::playerUiStatus(HDC hdc)
{
	char str[100];
	//UTIL::DrawRect(hdc, m_playerStatus);
	IMAGEMANAGER->render("playerStatus", hdc, m_playerStatus.left, m_playerStatus.top);

	wsprintf(str, "%s", selectPocketmon->m_name.c_str());
	TextOut(hdc, m_playerStatus.left + 70, m_playerStatus.top + 25, str, strlen(str));

	wsprintf(str, "Lv %d", selectPocketmon->m_level);
	TextOut(hdc, m_playerStatus.left + 330, m_playerStatus.top + 25, str, strlen(str));

	wsprintf(str, "%d/  %d", selectPocketmon->m_currentHp, selectPocketmon->m_maxHp);
	TextOut(hdc, m_playerStatus.left + 260, m_playerStatus.top + 110, str, strlen(str));

	playerUiCurrentHp(hdc, 0);
	plyaerUiCurrentExp(hdc, 0);
}
void BattleScene::playerUiSkillList(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_skillListRect);
	IMAGEMANAGER->render("skillSelect", hdc, m_skillListRect.left, m_skillListRect.top);
	char skillName[4][100];	
	for (int i = 0; i < selectPocketmon->skillList.size(); i++)
	{
		if (i == 0)
		{
			wsprintf(skillName[i], "%s", selectPocketmon->skillList[i].name.c_str());
			TextOut(hdc, 67, 595, skillName[i], strlen(skillName[i]));
		}
		else if (i == 1)
		{
			wsprintf(skillName[i], "%s", selectPocketmon->skillList[i].name.c_str());
			TextOut(hdc, 345, 595, skillName[i], strlen(skillName[i]));
		}
		else if (i == 2)
		{
			wsprintf(skillName[i], "%s", selectPocketmon->skillList[i].name.c_str());
			TextOut(hdc, 67, 676, skillName[i], strlen(skillName[i]));
		}
		else if (i == 3)
		{
			wsprintf(skillName[i], "%s", selectPocketmon->skillList[i].name.c_str());
			TextOut(hdc, 345, 676, skillName[i], strlen(skillName[i]));
		}
	}
	if (selectPocketmon->skillList.size() == 1)
	{
		wsprintf(skillName[1], "---");
		TextOut(hdc, 345, 595, skillName[1], strlen(skillName[1]));
		wsprintf(skillName[2], "---");
		TextOut(hdc, 67, 676, skillName[2], strlen(skillName[2]));
		wsprintf(skillName[3], "---");
		TextOut(hdc, 345, 676, skillName[3], strlen(skillName[3]));
	}
	else if (selectPocketmon->skillList.size() == 2) 
	{
		wsprintf(skillName[2], "---");
		TextOut(hdc, 67, 676, skillName[2], strlen(skillName[2]));
		wsprintf(skillName[3], "---");
		TextOut(hdc, 345, 676, skillName[3], strlen(skillName[3]));
	}
	else if (selectPocketmon->skillList.size() == 3) 
	{
		wsprintf(skillName[3], "---");
		TextOut(hdc, 345, 676, skillName[3], strlen(skillName[3]));
	}

}
void BattleScene::playerUiSkillExplain(HDC hdc)
{
	//UTIL::DrawRect(hdc, m_skillExplainRect);
	char str[100];

	if (skill_1)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[0].currentpp, selectPocketmon->skillList[0].maxpp);
		TextOut(hdc, 882, 597, str, strlen(str));

		wsprintf(str, "%s", playerUiSkillType(selectPocketmon->skillList[0].skilltype).c_str());
		TextOut(hdc, 872, 685, str, strlen(str));
	}
	if (skill_2)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[1].currentpp, selectPocketmon->skillList[1].maxpp);
		TextOut(hdc, 882, 597, str, strlen(str));

		wsprintf(str, "%s", playerUiSkillType(selectPocketmon->skillList[1].skilltype).c_str());
		TextOut(hdc, 872, 685, str, strlen(str));
	}
	if (skill_3)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[2].currentpp, selectPocketmon->skillList[2].maxpp);
		TextOut(hdc, 882, 597, str, strlen(str));

		wsprintf(str, "%s", playerUiSkillType(selectPocketmon->skillList[2].skilltype).c_str());
		TextOut(hdc, 872, 685, str, strlen(str));
	}
	if (skill_4)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[3].currentpp, selectPocketmon->skillList[3].maxpp);
		TextOut(hdc, 882, 597, str, strlen(str));

		wsprintf(str, "%s", playerUiSkillType(selectPocketmon->skillList[3].skilltype).c_str());
		TextOut(hdc, 872, 685, str, strlen(str));
	}
}
std::string BattleScene::playerUiSkillType(SkillType _skillType)
{
	switch (_skillType)
	{
	case SkillType::SkillAttibuteFire:
		return "불꽃";
	case SkillType::SkillAttibuteStone:
		return "바위";
	case SkillType::SkillAttibuteWater:
		return "물";
	case SkillType::SkillAttibuteGrass:
		return "풀";
	case SkillType::SkillAttibuteFly:
		return "비행";
	case SkillType::SkillAttibuteElectric:
		return "전기";
	case SkillType::SkillAttibuteNormal:
		return "노말";
	}
}
void BattleScene::playerUiMaxHp(HDC hdc, int _y)
{
	m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 205, 438 + _y, 230, 30);
	//UTIL::DrawColorRect(hdc, m_playerMaxHp, RGB(120, 120, 120));
	//IMAGEMANAGER->render("greenHpBar", hdc, m_playerMaxHp.left, m_playerMaxHp.top, 0, 0,  m_playerPocketmonHpBarWigth, 3 * 5);

}
void BattleScene::playerUiCurrentHp(HDC hdc, int _y)
{
	m_playerCurrentHp = UTIL::IRectMake(playerCurrentHpLeft(), playerCurrentHpTop() + _y, m_playerPocketmonHpBarWigth, 30);
	//UTIL::DrawColorRect(hdc, m_playerCurrentHp, RGB(10, 70, 70));
	IMAGEMANAGER->render("greenHpBar", hdc, m_playerCurrentHp.left, m_playerCurrentHp.top, 0, 0,  m_playerPocketmonHpBarWigth, 3 * 5);
}
void BattleScene::playerUiMaxExp(HDC hdc, int _y)
{
	//플레이어 최대경험치
	m_playerMaxExp = UTIL::IRectMake(m_playerStatus.left + 151, 500 + _y, 230, 30);
	//UTIL::DrawColorRect(hdc, m_playerMaxExp, RGB(120, 120, 120));
}
void BattleScene::plyaerUiCurrentExp(HDC hdc, int _y)
{
	//플레이어 현재경험치
	m_playerCurrentExp = UTIL::IRectMake(playerCurrentExpLeft(), playerCurrentExpTop() + _y, m_playerPocketmonExpBarWigth, 30);
	//UTIL::DrawColorRect(hdc, m_playerCurrentExp, RGB(10, 70, 70));
	IMAGEMANAGER->render("currentExp", hdc, m_playerCurrentExp.left, m_playerCurrentExp.top, 0, 0, m_playerPocketmonExpBarWigth, 9);
}
int BattleScene::checkHpBarWigth()
{
	return 206 * selectPocketmon->m_currentHp / selectPocketmon->m_maxHp;;
}
int BattleScene::checkExpBarWigth()
{
	return 274 * selectPocketmon->m_currentExp / selectPocketmon->m_maxExp;
}
bool BattleScene::checkPossiblePocketmon()
{
	for (auto it = m_playerPocketmons.begin(); it != m_playerPocketmons.end(); ++it)
	{
		if ((*it)->m_currentHp != 0) return true;
	}
	return false;
}
void BattleScene::playerStayMotion()
{
	if (!catchAniOn && !pocketmonChangeOn)
	{
		m_count++;
		if (m_count % 20 == 0 && motionUp)
		{
			motionUp = false;
			//플레이어 포켓몬
			m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 324, 210, 209);
			//플레이어 상태창
			m_playerStatus = UTIL::IRectMake(m_playerStatusX, 346, 446, 180);
		}
		else if (m_count % 20 == 0 && !motionUp)
		{
			motionUp = true;
			//플레이어 포켓몬
			m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 210, 209);
			//플레이어 상태창
			m_playerStatus = UTIL::IRectMake(m_playerStatusX, 351, 446, 180);
		}

		if (m_count > 10000) m_count = 0;
	}

}
void BattleScene::changePocketmon()
{
	m_playerPocketmons = trainer->getPocketmons();
	for (auto it = m_playerPocketmons.begin(); it != m_playerPocketmons.end(); ++it)
	{
		selectPocketmon = (*it);
		break;
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
		SCENEMANAGER->scenePush("inven", nullptr ,true);
	}
	if (pocketmon && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//포켓몬으로 씬체인지
		auto info = new ChangeSceneFromBattle;
		SCENEMANAGER->scenePush("PocketmonBagScene", info, true);
	}
	if (run && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//추가할꺼 - 플레이어에 setisBattle 함수를 써서 isbattle false로 바꿔주기
		battleSceneEnd();
	}

}
void BattleScene::moveSkillSelectButton()
{
	//스킬 선택창
	//skill_1: 39, 595, 20, 40
	//skill_2: 318, 595, 20, 40
	//skill_3: 39, 674, 20, 40
	//skill_4: 318, 674, 20, 40
	switch (selectPocketmon->skillList.size())
	{
	case 1:
		break;
	case 2:
		if (skill_1 && !skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_RIGHT))
		{
			skill_1 = false;
			skill_2 = true;
			m_skillSelectRect = UTIL::IRectMake(318, 595, 20, 40);
		}
		if (!skill_1 && skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_LEFT))
		{
			skill_2 = false;
			skill_1 = true;
			m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
		}
		break;
	case 3:
		if (skill_1 && !skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_RIGHT))
		{
			skill_1 = false;
			skill_2 = true;
			m_skillSelectRect = UTIL::IRectMake(318, 595, 20, 40);
		}
		if (!skill_1 && skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_LEFT))
		{
			skill_2 = false;
			skill_1 = true;
			m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
		}
		if (skill_1 && !skill_2 && !skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_DOWN))
		{
			skill_1 = false;
			skill_3 = true;
			m_skillSelectRect = UTIL::IRectMake(39, 674, 20, 40);
		}
		if (!skill_1 && !skill_2 && skill_3 && !skill_4 && KEYMANAGER->isOnceKeyDown(P1_UP))
		{
			skill_3 = false;
			skill_1 = true;
			m_skillSelectRect = UTIL::IRectMake(39, 595, 20, 40);
		}
		break;
	case 4:
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
		break;
	}

	if (KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		playerTurn = false;
		playerSkillMotionOn = true;
	}

	if (playerSkillMotionOn)
	{
		if (skill_1)
		{
			m_selectSkill = selectPocketmon->skillList[0].name;
			m_playerSelectSkillNumber = 0;
			if (selectPocketmon->skillList[0].currentpp != 0)
			{
				selectPocketmon->skillList[0].currentpp--;
			}
			else
			{
				playerTurn = true;
				playerSkillMotionOn = false;
			}
		}
		else if (skill_2)
		{
			m_selectSkill = selectPocketmon->skillList[1].name;
			m_playerSelectSkillNumber = 1;
			if (selectPocketmon->skillList[1].currentpp != 0)
			{
				selectPocketmon->skillList[1].currentpp--;
			}
			else
			{
				playerTurn = true;
				playerSkillMotionOn = false;
			}
		}
		else if (skill_3)
		{
			m_selectSkill = selectPocketmon->skillList[2].name;
			m_playerSelectSkillNumber = 2;
			if (selectPocketmon->skillList[2].currentpp != 0)
			{
				selectPocketmon->skillList[2].currentpp--;
			}
			else
			{
				playerTurn = true;
				playerSkillMotionOn = false;
			}
		}
		else if (skill_4)
		{
			m_selectSkill = selectPocketmon->skillList[3].name;
			m_playerSelectSkillNumber = 3;
			if (selectPocketmon->skillList[3].currentpp != 0)
			{
				selectPocketmon->skillList[3].currentpp--;
			}
			else
			{
				playerTurn = true;
				playerSkillMotionOn = false;
			}
		}
	}
}

//=================
// 공격&방어 함수 //
//=================
std::string BattleScene::selectEnemyskill()
{
	if (m_wildPocketmon.skillList.size() == 1)
	{
		m_enemySelectSkillNumber = 0;
		return m_wildPocketmon.skillList[m_enemySelectSkillNumber].name;
	}
	else
	{
		m_enemySelectSkillNumber = UTIL::GetRndIntFromTo(0, m_wildPocketmon.skillList.size() - 1);
		return m_wildPocketmon.skillList[m_enemySelectSkillNumber].name;
	}
}
int BattleScene::basicDamage()
{
	int temp = UTIL::GetRndIntFromTo(0, 9);
	if (temp < 3)
	{
		return selectPocketmon->skillList[m_playerSelectSkillNumber].power * selectPocketmon->m_atk * (selectPocketmon->m_level * 2 * 2 / 5 + 2) / m_wildPocketmon.m_def / 50 + 2;
	}
	else
	{
		return selectPocketmon->skillList[m_playerSelectSkillNumber].power * selectPocketmon->m_atk * (selectPocketmon->m_level * 1 * 2 / 5 + 2) / m_wildPocketmon.m_def / 50 + 2;
	}
}
int BattleScene::spacialBasicDamage()
{
	int temp = UTIL::GetRndIntFromTo(0, 9);
	if (temp < 3)
	{
		return selectPocketmon->skillList[m_playerSelectSkillNumber].power * selectPocketmon->m_specialAtk * (selectPocketmon->m_level * 2 * 2 / 5 + 2) / m_wildPocketmon.m_specialDef / 50 + 2;
	}
	else
	{
		return selectPocketmon->skillList[m_playerSelectSkillNumber].power * selectPocketmon->m_specialAtk * (selectPocketmon->m_level * 1 * 2 / 5 + 2) / m_wildPocketmon.m_specialDef / 50 + 2;
	}
}
int BattleScene::enemyBasicDamage()
{
	int temp = UTIL::GetRndIntFromTo(0, 9);
	if (temp < 3)
	{
		return m_wildPocketmon.skillList[m_enemySelectSkillNumber].power * m_wildPocketmon.m_atk * (m_wildPocketmon.m_level * 2 * 2 / 5 + 2) / selectPocketmon->m_def / 50 + 2;
	}
	else
	{
		return m_wildPocketmon.skillList[m_enemySelectSkillNumber].power * m_wildPocketmon.m_atk * (m_wildPocketmon.m_level * 1 * 2 / 5 + 2) / selectPocketmon->m_def / 50 + 2;
	}
}
int BattleScene::enemySpacialBasicDamage()
{
	int temp = UTIL::GetRndIntFromTo(0, 9);
	if (temp < 3)
	{
		return m_wildPocketmon.skillList[m_enemySelectSkillNumber].power * m_wildPocketmon.m_specialAtk * (m_wildPocketmon.m_level * 2 * 2 / 5 + 2) / selectPocketmon->m_specialDef / 50 + 2;
	}
	else
	{
		return m_wildPocketmon.skillList[m_enemySelectSkillNumber].power * m_wildPocketmon.m_specialAtk * (m_wildPocketmon.m_level * 1 * 2 / 5 + 2) / selectPocketmon->m_specialDef / 50 + 2;
	}
}

//=================
// main 렌더 함수 //
//=================
void BattleScene::wildBattleRender(HDC hdc)
{
	HFONT myFont = CreateFont(35, 15, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "소야바른9");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetBkMode(hdc, TRANSPARENT);

	char str[411];
	//배경
	//IMAGEMANAGER->findImage("battleTemp")->render(hdc);
	IMAGEMANAGER->findImage("backGroundImg")->render(hdc);

	//인트로 애니메이션 
	if (wildBattleIntroAniOn)
	{	
		//적
		enemyUiStatus(hdc);
		enemyUiBottom(hdc);
		enemyUiPocketmon(hdc);
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
		if (catchAniOn)
		{
			enemyUiBottom(hdc);
			playerUiBottom(hdc);
			explainRect(hdc);
			catchPocketmon(hdc);	//기준
			enemyUiStatus(hdc);
			enemyUiCurrentHp(hdc);
			playerUiPoketmon(hdc);
			playerUiStatus(hdc);
		}
		else if (pocketmonChangeOn)
		{
			enemyUiBottom(hdc);
			playerUiBottom(hdc);
			enemyUiStatus(hdc);
			playerUiStatus(hdc);
			enemyUiPocketmon(hdc);
			pocketmonChange(hdc);//기준
			sceneChageEffect(hdc);

		}
		else if (!catchAniOn && !pocketmonChangeOn)
		{
			//적
			enemyUiStatus(hdc);
			enemyUiBottom(hdc);
			enemyUiPocketmon(hdc);
			enemyUiCurrentHp(hdc);
			//플레이어
			playerUiBottom(hdc);
			playerUiPoketmon(hdc);
			playerUiStatus(hdc);

			if (playerTurn)
			{
				//플레이어 행동 선택
				if (!playerAtkOn)
				{
					explainRect(hdc);
					//선택 커서
					selectRect(hdc);
				}
				//플레이어 공격스킬 선택
				if (playerAtkOn)
				{
					playerUiSkillList(hdc);
					playerUiSkillExplain(hdc);
					skillSelectRect(hdc);
				}
			}
		}
		if (playerSkillMotionOn)
		{
			explainRect(hdc);
			playerPockatmonAttack(hdc);
		}
		//적 움직이고
		if (enemyLose) wildBattleOutAni(hdc);
		if (enemyTurn)
		{
			if (!enemySkillSelect)
			{
				m_enemySelectSkillName = selectEnemyskill();
				enemySkillSelect = true;
			}
			explainRect(hdc);
			enemySkillEffectAssemble(m_enemySelectSkillName, hdc);
			if (playerLose) playerPocketmonLoseAni(hdc);
		}
	}//end of atk/def

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
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "%s 공격!", selectPocketmon->skillList[m_playerSelectSkillNumber].name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
	}
	else if (m_skillCount >= 100 && !playerSkillExplainDone)
	{
		m_skillCount = 0;
		playerSkillExplainDone = true;
	}

	if (playerSkillExplainDone)
	{
		playerSkillEffectAssemble(m_selectSkill, hdc);
	}
}

//=====================
// npc 배틀 함수 모음 //
//=====================
void BattleScene::npcBattleFunctions()
{
}
void BattleScene::npcBattleRender(HDC hdc)
{
}

//==========================
// 플레이어 공격 스킬 모음 //
//==========================
void BattleScene::tackleProto(std::string _skillName, HDC hdc)
{
	//1단계: 포켓몬 스킬 이팩트
	if (!playerSkillEffect && !playerSkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 707, 195);
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
		m_enemyEffectCount++;
		m_enemyAlpha = 0;
		if (m_enemyEffectCount > 60)
		{
			m_enemyAlpha = 255;
			m_enemyEffectCount = 0;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}
	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::skillEmberProto(std::string _skillName, HDC hdc)
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
		m_enemyEffectCount++;
		m_enemyAlpha = 0;
		if (m_enemyEffectCount > 40)
		{
			m_enemyAlpha = 255;
			m_enemyEffectCount = 0;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::flameThrowerProto(std::string _skillName, HDC hdc)
{
	//1단계: 포켓몬 스킬 이팩트
	if (!playerSkillEffect && !playerSkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 707, 195);
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
		m_enemyEffectCount++;
		m_enemyAlpha = 0;
		if (m_enemyEffectCount > 60)
		{
			m_enemyAlpha = 255;
			m_enemyEffectCount = 0;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::fireBlastProto(std::string _skillName, HDC hdc)
{
	//1단계: 포켓몬 스킬 이팩트
	if (!playerSkillEffect && !playerSkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 750, 210);//중심
		//ㅣ
		EFFECTMANAGER->play(_skillName, 750, 170);
		EFFECTMANAGER->play(_skillName, 750, 130);
		//ㅡ
		EFFECTMANAGER->play(_skillName, 630, 210);
		EFFECTMANAGER->play(_skillName, 690, 210);
		EFFECTMANAGER->play(_skillName, 810, 210);
		EFFECTMANAGER->play(_skillName, 870, 210);
		// /
		EFFECTMANAGER->play(_skillName, 690, 250);
		EFFECTMANAGER->play(_skillName, 630, 290);
		// 마지막 획
		EFFECTMANAGER->play(_skillName, 810, 250);
		EFFECTMANAGER->play(_skillName, 870, 290);

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
		m_enemyEffectCount++;
		m_enemyAlpha = 0;
		if (m_enemyEffectCount > 60)
		{
			m_enemyAlpha = 255;
			m_enemyEffectCount = 0;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::scratchProto(std::string _skillName, HDC hdc)
{
	//1단계: 포켓몬 스킬 이팩트
	if (!playerSkillEffect && !playerSkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 810, 250);
		playerSkillEffect = EFFECTMANAGER->getIsPlay();
		playerHitEffect = true;

	}
	else if (playerSkillEffect && !EFFECTMANAGER->getIsPlay())
	{
		playerSkillEffect = false;
		playerSkillEffectDone = true;
	}

	//2단계: 적 포켓몬 왼쪽으로 이동했다 돌아오기깜빡 깜빡
	if (playerHitEffect)
	{
		m_enemyEffectCount++;
		m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX + m_enemyEffectCount, 165, 165, 181);
		if (m_enemyEffectCount > 30)	comeBackEnemey = true;
		if(comeBackEnemey) m_enemyEffectCount -= 3;
		
		if (m_enemyEffectCount < 0)
		{
			m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
			m_enemyEffectCount = 0;
			comeBackEnemey = false;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::playerThunderWaveProto(std::string _skillName, HDC hdc)
{
	//1단계: 포켓몬 스킬 이팩트
	if (!playerSkillEffect && !playerSkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 780, 250);
		playerSkillEffect = EFFECTMANAGER->getIsPlay();
		playerHitEffect = true;

	}
	else if (playerSkillEffect && !EFFECTMANAGER->getIsPlay())
	{
		playerSkillEffect = false;
		playerSkillEffectDone = true;
	}

	//2단계: 적 포켓몬 좌우로 흔들흔들
	if (playerHitEffect)
	{
		m_enemyEffectCount++;
		if (m_enemyEffectCount % 10 < 5)
		{
			m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX+5, 165, 165, 181);
		}
		else if (m_enemyEffectCount % 10 >= 5)
		{
			m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX - 5, 165, 165, 181);
		}
		if (m_enemyEffectCount > 100)
		{
			m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, 165, 165, 181);
			m_enemyEffectCount = 0;
			playerHitEffect = false;
			enemyHpChange = true;
			m_enemyMinusHp = checkDamage();
		}
	}

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}


//====================
// 적 공격 스킬 모음 //
//====================
void BattleScene::quickAttackProto(std::string _skillName, HDC hdc)
{
	char str[100];
	if (!enemyExplainEffect)
	{
		wsprintf(str, "상대 %s의", m_wildPocketmon.m_name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "%s 공격!", _skillName.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
	}
	
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
			if (m_playerMinusHp >= selectPocketmon->m_currentHp) m_playerMinusHp = selectPocketmon->m_currentHp;
		}
	}

	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}
void BattleScene::enemyScratchProto(std::string _skillName, HDC hdc)
{
	if (!enemySkillEffect && !enemySkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 357, 440);
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
		m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX - m_playerTwinkleCount, 329, 165, 181);
		if (m_playerTwinkleCount > 30) comeBackPlayer = true;
		if (comeBackPlayer) m_playerTwinkleCount -= 3;

		if (m_playerTwinkleCount < 0)
		{
			m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 165, 181);
			m_playerTwinkleCount = 0;
			enemyHitEffect = false;
			playerHpChange = true;
			m_playerMinusHp = checkDamage();
		}
	}
	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}
void BattleScene::enemyThunderWaveProto(std::string _skillName, HDC hdc)
{
	if (!enemySkillEffect && !enemySkillEffectDone)
	{
		EFFECTMANAGER->play(_skillName, 310, 430);
		enemySkillEffect = true;
	}
	else if (enemySkillEffect && !EFFECTMANAGER->getIsPlay())
	{
		enemyHitEffect = true;
		enemySkillEffect = false;
		enemySkillEffectDone = true;
	}
	//2단계: 플레이어 좌우로 흔들흔들
	if (enemyHitEffect)
	{
		m_playerTwinkleCount++;
		if (m_playerTwinkleCount % 10 < 5)
		{
			m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX + 5, 329, 165, 181);
		}
		else if (m_playerTwinkleCount % 10 >= 5)
		{
			m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX - 5, 329, 165, 181);
		}
		
		if (m_playerTwinkleCount > 100)
		{
			m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, 329, 165, 181);
			m_playerTwinkleCount = 0;
			enemyHitEffect = false;
			playerHpChange = true;
			m_playerMinusHp = checkDamage();
		}
	}

	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}
void BattleScene::thunderboltProto(std::string _skillName, HDC hdc)
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
	//플레이어 깜빡깜빡
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

	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}
void BattleScene::thunderProto(std::string _skillName, HDC hdc)
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
	//플레이어 깜빡깜빡
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

	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}

void BattleScene::enemySkillEmberProto(std::string _skillName, HDC hdc)
{
	if (!enemySkillEffect && !enemySkillEffectDone)
	{
		int tempX, tempY;
		tempX = 400;
		tempY = 200;
		EFFECTMANAGER->play(_skillName, 707-tempX, 195+tempY);
		EFFECTMANAGER->play(_skillName, 774-tempX, 222+tempY);
		EFFECTMANAGER->play(_skillName, 696-tempX, 287+tempY);
		EFFECTMANAGER->play(_skillName, 778-tempX, 304+tempY);
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
	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}

//======================
// 공방 공통 함수 모음 //
//======================
//플레이어
void BattleScene::enemyHpChangFromPlayerAtk()
{
	if (enemyHpChange)
	{
		m_enemyCurrentMinusHp++;
		m_wildPocketmon.m_currentHp--;
		if (m_wildPocketmon.m_currentHp <= 0)
		{
			m_wildPocketmon.m_currentHp = 0;
			m_enemyMinusHp = 0;
			enemyLose = true;
		}
		m_wildPocketmonHpBarWigth = (206 * m_wildPocketmon.m_currentHp) / m_wildPocketmon.m_maxHp;
		if (m_enemyCurrentMinusHp == m_enemyMinusHp)
		{
			m_enemyCurrentMinusHp = 0;
			m_enemyMinusHp = 0;
			enemyHpChange = false;
			explainEffect = true;
		}
	}
}
void BattleScene::playerAtkResultOutput(HDC hdc)
{
	if (attributeOn)
	{
		explainEffect = false;
		explainRect(hdc);
		if (plusAttribute)
		{
			m_skillCount++;
			char str[100];
			wsprintf(str, "효과는 굉장했다!!");
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));
			if (m_skillCount > 60)
			{
				UTIL::DrawRect(hdc, m_explainRect);
				m_skillCount = 0;
				playerSkillEffect = false;
				playerSkillEffectDone = false;
				explainEffect = false;
				playerSkillMotionOn = false;
				playerSkillExplainDone = false;
				attributeOn = false;
				enemyTurn = true;
				if (enemyLose) enemyTurn = false;
			} 
		}
		else
		{
			m_skillCount++;
			char str[100];
			wsprintf(str, "효과가 별로인 것 같다..");
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));
			if (m_skillCount > 60)
			{
				UTIL::DrawRect(hdc, m_explainRect);
				m_skillCount = 0;
				playerSkillEffect = false;
				playerSkillEffectDone = false;
				explainEffect = false;
				playerSkillMotionOn = false;
				playerSkillExplainDone = false;
				attributeOn = false;
				enemyTurn = true;
				if (enemyLose) enemyTurn = false;
			}
		}
	}

	if (explainEffect)
	{
		explainRect(hdc);
		m_skillCount++;
		if (m_skillCount > 60)
		{
			m_skillCount = 0;
			playerSkillEffect = false;
			playerSkillEffectDone = false;
			explainEffect = false;
			playerSkillMotionOn = false;
			playerSkillExplainDone = false;
			enemyTurn = true;
			if (enemyLose) enemyTurn = false;
		}
	}
}
//적
void BattleScene::playerHpChangFromEnemyAtk()
{
	if (playerHpChange)
	{
		enemyExplainEffect = false;
		m_playerCurrentMinusHp++;
		selectPocketmon->m_currentHp--;
		if (selectPocketmon->m_currentHp <= 0)
		{
			selectPocketmon->m_currentHp = 0;
			playerLose = true;
		}
		if (m_playerCurrentMinusHp == m_playerMinusHp)
		{
			m_playerCurrentMinusHp = 0;
			m_playerMinusHp = 0;
			playerHpChange = false;
			enemyExplainEffect = true;
		}
		m_playerPocketmonHpBarWigth = checkHpBarWigth();
	}
}
void BattleScene::enemyAtkResultOutput(HDC hdc)
{
	if (attributeOn)
	{
		enemyExplainEffect = false;
		explainRect(hdc);
		if (plusAttribute)
		{
			m_skillCount++;
			char str[100];
			wsprintf(str, "효과는 굉장했다!!");
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));
			if (m_skillCount > 60)
			{
				m_skillCount = 0;
				enemySkillEffectDone = false;
				enemyExplainEffect = false;
				enemyTurn = false;
				playerAtkOn = false;
				playerTurn = true;
				enemySkillSelect = false;
				attributeOn = false;
				plusAttribute = false;
			}
		}
		else
		{
			m_skillCount++;
			char str[100];
			wsprintf(str, "효과가 별로인 것 같다..");
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));
			if (m_skillCount > 60)
			{
				m_skillCount = 0;
				enemySkillEffectDone = false;
				enemyExplainEffect = false;
				enemyTurn = false;
				playerAtkOn = false;
				playerTurn = true;
				enemySkillSelect = false;
				attributeOn = false;
				plusAttribute = false;
			}
		}
	}

	if (enemyExplainEffect)
	{
		m_skillCount++;
		if (m_skillCount > 60)
		{
			m_skillCount = 0;
			enemySkillEffectDone = false;
			enemyExplainEffect = false;
			enemyTurn = false;
			playerAtkOn = false;
			playerTurn = true;
			enemySkillSelect = false;

		}
	}
}

//==============
// 상황별 Ani //
//==============
void BattleScene::wildBattleIntroAni()
{
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
		m_playerimgX -= 5;
		m_playerStatusX -= 10;
		//플레이어 이미지
		m_playerImg = UTIL::IRectMake(m_playerimgX, 329, 210, 209);
		//플레이어 상태창
		m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
		m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431, 230, 30);
		m_playerCurrentHp = UTIL::IRectMake(playerCurrentHpLeft(), playerCurrentHpTop(), m_playerPocketmonHpBarWigth, 30);
		if (m_playerStatusX <= PLAYERSTATUSX)
		{
			playerImgSlideOut = false;
			wildBattleIntroAniOn = false;
		}

	}
}

//플레이어 승리시
void BattleScene::wildBattleOutAni(HDC hdc)
{
	char str[100];
	//적 포켓몬
	m_enemyPocketmonY += 10;
	m_enemyPocketmon = UTIL::IRectMake(m_enemyPocketmonX, m_enemyPocketmonY, 165, 181);
	if (m_enemyPocketmonY > WINSIZEY)
	{
		m_enemyPocketmon = UTIL::IRectMake(1000, 1000, 165, 181);
		m_skillCount++;
		explainRect(hdc);
		wsprintf(str, "야생의 %s는(은)", m_wildPocketmon.m_name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "쓰러졌다!", m_wildPocketmon.m_name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

		if (m_skillCount > 40)
		{
			explainRect(hdc);
			wsprintf(str, "%s는(은)", selectPocketmon->m_name.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

			wsprintf(str, "%d 경험치를 얻었다!", m_wildPocketmon.m_wildExp);
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

			m_playerCurrentPlusExp++;
			selectPocketmon->m_currentExp++;
			if (selectPocketmon->m_currentExp >= selectPocketmon->m_maxExp)
			{
				m_playerCurrentPlusExp--;
				
				if (m_skillCount > 80)
				{
					explainRect(hdc);
					IMAGEMANAGER->findImage("levelUpRect")->render(hdc, m_playerPocketmonLevelUpRect.left, m_playerPocketmonLevelUpRect.top);
					if (!playerPocketmonLevelUpOn)
					{
						playerPocketmonLevelUpOn = true;
						selectPocketmon->m_level++;
					}
					wsprintf(str, "%s는(은)", selectPocketmon->m_name.c_str());
					TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

					wsprintf(str, "레벨%d(으)로 올랐다!", selectPocketmon->m_level);
					TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

					//능력치 변경 표시
					playerPocketmonLevelUp(hdc);
				}
				
			}
			//레벨에 일정이상 올라가면 스킬을 추가로 배우는 부분
			if (checkSkillGet)
			{
				//m_playerCurrentPlusExp--;
				playerPocketmonGetNewSkill(hdc);
			}
			m_playerPocketmonExpBarWigth = checkExpBarWigth();
			if (m_playerCurrentPlusExp == m_wildPocketmon.m_wildExp)
			{
				m_playerCurrentPlusExp = 0;
				battleEnd = true;
			}
			/*if (getSkillDone)
			{
			}*/
			
			if (battleEnd)
			{
				battleSceneEnd();
			}
		}
	}
}
void BattleScene::playerPocketmonLevelUp(HDC hdc)
{
	HFONT myFont = CreateFont(55, 24, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "소야바른9");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
	SetBkMode(hdc, TRANSPARENT);

	char str[100];

	m_levelUpCount++;
	//이미지 렌더


	wsprintf(str, "최대 HP");
	TextOut(hdc, m_playerPocketmonLevelUpRect.left + 30, m_playerPocketmonLevelUpRect.top + 20, str, strlen(str));

	wsprintf(str, "공격");
	TextOut(hdc, m_playerPocketmonLevelUpRect.left + 30, m_playerPocketmonLevelUpRect.top + 100, str, strlen(str));

	wsprintf(str, "방어");
	TextOut(hdc, m_playerPocketmonLevelUpRect.left + 30, m_playerPocketmonLevelUpRect.top + 180, str, strlen(str));

	wsprintf(str, "특수공격");
	TextOut(hdc, m_playerPocketmonLevelUpRect.left + 30, m_playerPocketmonLevelUpRect.top + 260, str, strlen(str));

	wsprintf(str, "특수방어");
	TextOut(hdc, m_playerPocketmonLevelUpRect.left + 30, m_playerPocketmonLevelUpRect.top + 340, str, strlen(str));

	wsprintf(str, "스피드");
	TextOut(hdc, m_playerPocketmonLevelUpRect.left + 30, m_playerPocketmonLevelUpRect.top + 420, str, strlen(str));

	if (!playerPocketmonStatusPulsOn)
	{
		PocketMon tempPocket = POCKETMONMANAGER->genPocketMon(selectPocketmon->m_EnglishName, selectPocketmon->m_level + 1);


		tempHp = tempPocket.m_maxHp - selectPocketmon->m_maxHp;
		tempAtk = tempPocket.m_atk - selectPocketmon->m_atk;
		tempDef = tempPocket.m_def - selectPocketmon->m_def;
		tempSpecialAtk = tempPocket.m_specialAtk - selectPocketmon->m_specialAtk;
		tempSpecialDef = tempPocket.m_specialDef - selectPocketmon->m_specialDef;
		tempSpeed = tempPocket.m_speed - selectPocketmon->m_speed;

		selectPocketmon->m_maxHp += tempHp;
		selectPocketmon->m_atk += tempAtk;
		selectPocketmon->m_def += tempDef;
		selectPocketmon->m_specialAtk += tempSpecialAtk;
		selectPocketmon->m_specialDef += tempSpecialDef;
		selectPocketmon->m_speed += tempSpeed;

		playerPocketmonStatusPulsOn = true;
	}

	if (m_levelUpCount < 100)
	{
		wsprintf(str, "+ %d", tempHp);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 20, str, strlen(str));

		wsprintf(str, "+ %d", tempAtk);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 100, str, strlen(str));

		wsprintf(str, "+ %d", tempDef);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 180, str, strlen(str));

		wsprintf(str, "+ %d", tempSpecialAtk);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 260, str, strlen(str));

		wsprintf(str, "+ %d", tempSpecialDef);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 340, str, strlen(str));

		wsprintf(str, "+ %d", tempSpeed);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 420, str, strlen(str));
	}
	else if (100 <= m_levelUpCount && m_levelUpCount <= 160)
	{
		//변한 능력치
		wsprintf(str, " %d", selectPocketmon->m_maxHp);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 20, str, strlen(str));

		wsprintf(str, " %d", selectPocketmon->m_atk);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 100, str, strlen(str));

		wsprintf(str, " %d", selectPocketmon->m_def);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 180, str, strlen(str));

		wsprintf(str, " %d", selectPocketmon->m_specialAtk);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 260, str, strlen(str));

		wsprintf(str, " %d", selectPocketmon->m_specialDef);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 340, str, strlen(str));

		wsprintf(str, " %d", selectPocketmon->m_speed);
		TextOut(hdc, m_playerPocketmonLevelUpRect.left + 260, m_playerPocketmonLevelUpRect.top + 420, str, strlen(str));
	}
	else if (160 < m_levelUpCount)
	{
		m_wildPocketmon.m_wildExp = m_wildPocketmon.m_wildExp - m_playerCurrentPlusExp;
		selectPocketmon->m_currentExp = 0;
		m_playerCurrentPlusExp = 0;

		checkSkillGet = true;
		m_levelUpCount = 0;
	}

	SelectObject(hdc, oldFont);
	DeleteObject(myFont);
}
void BattleScene::playerPocketmonGetNewSkill(HDC hdc)
{
	m_levelCheckCount++;
	char str[100];
	PocketMon tempPocket;
	if(!pushBackSkill) tempPocket = POCKETMONMANAGER->genPocketMon(selectPocketmon->m_EnglishName, selectPocketmon->m_level);

	if (m_levelCheckCount < 40)
	{
		explainRect(hdc);
		switch (selectPocketmon->m_level)
		{
		case 8:
			if (!pushBackSkill)
			{
				selectPocketmon->skillList.push_back(tempPocket.skillList[1]);
				pushBackSkill = true;
			}
			wsprintf(str, "%s는(은) 새로", selectPocketmon->m_customName.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

			wsprintf(str, "%s를(을) 배웠다!", selectPocketmon->skillList[1].name.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
			break;
		case 14:
			if (!pushBackSkill)
			{
				selectPocketmon->skillList.push_back(tempPocket.skillList[2]);
				pushBackSkill = true;
			}
			wsprintf(str, "%s는(은) 새로", selectPocketmon->m_customName.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

			wsprintf(str, "%s를(을) 배웠다!", selectPocketmon->skillList[2].name.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
			break;
		case 31:
			if (!pushBackSkill)
			{
				selectPocketmon->skillList.push_back(tempPocket.skillList[3]);
				pushBackSkill = true;
			}
			wsprintf(str, "%s는(은) 새로", selectPocketmon->m_customName.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

			wsprintf(str, "%s를(을) 배웠다!", selectPocketmon->skillList[3].name.c_str());
			TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
			break;
		}
	}
	else if (m_levelCheckCount >= 40)
	{
		//getSkillDone = true;
		checkSkillGet = false;
		m_levelCheckCount = 0;
	}

}
void BattleScene::sceneChageEffect(HDC hdc)
{
	//포켓몬 체인지
	if (pocketmonChangeOn)
	{
		if (!blackBgOn)
		{
			playerUiPoketmon(hdc);
			IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);
			IMAGEMANAGER->findImage("alpha")->alphaRender(hdc, blackBgAlpha);
			blackBgAlpha -= 5;
			if (blackBgAlpha < 0)
			{
				blackBgOn = true;
				comeBackPocketmon = true;
				blackBgAlpha = 0;
			}
		}
	}
}
void BattleScene::playerPocketmonLoseAni(HDC hdc)
{
	char str[100];
	m_playerPocketmonY += 10;
	m_playerPocketmonImg = UTIL::IRectMake(m_playerPocketmonX, m_playerPocketmonY, 210, 209);
	if (m_playerPocketmonY > WINSIZEY)
	{
		m_playerPocketmonImg = UTIL::IRectMake(1000, 1000, 210, 209);
		m_loseAniCount++;
		UTIL::DrawRect(hdc, m_explainRect);
		wsprintf(str, "%s는(은)", selectPocketmon->m_name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "쓰러졌다!");
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

		//포켓몬을 바꾸거나 완전히 지거나
		if (m_loseAniCount > 50)
		{
			//포켓몬 바꾸기
			if (checkPossiblePocketmon())
			{
				playerPocketmonChangeOn = true;
				SCENEMANAGER->scenePush("PocketmonBagScene");

			}
			else emptyBattlePocketmon = true;

			if (emptyBattlePocketmon)
			{
				UTIL::DrawRect(hdc, m_explainRect);
				wsprintf(str, "플레이어의 곁에는");
				TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

				wsprintf(str, "싸울 수 있는 포켓몬이 없다!");
				TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

				if (m_loseAniCount > 100)
				{
					UTIL::DrawRect(hdc, m_explainRect);
					int temp = UTIL::GetRndIntFromTo(60, 100);
					wsprintf(str, "플레이어는(은) 당황해서");
					TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

					wsprintf(str, "%d를 잃어버렸다!", temp);
					TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
					//trainer
					if (m_loseAniCount > 130)
					{
						UTIL::DrawRect(hdc, m_explainRect);
						wsprintf(str, "... ... ...");
						TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));
						if (m_loseAniCount > 150)
						{
							UTIL::DrawRect(hdc, m_explainRect);
							wsprintf(str, "플레이어는(은)");
							TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

							wsprintf(str, "눈앞이 깜깜해졌다!");
							TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

							if (m_loseAniCount > 170)
							{
								battleSceneEnd();						
							}
						}
					}
				}
			}
		}
	}
}
void BattleScene::catchPocketmon(HDC hdc)
{
	if (whiteBgAlpha != 215) enemyUiPocketmon(hdc);

	if (!catchStartExplainOn)
	{
		m_catchStartCount++;
		char str[100];
		wsprintf(str, "플레이어는(은)");
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "몬스터볼를(을) 사용했다!");
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));
	}
	if (m_catchStartCount == 40 && !ballThrowOn)
	{
		ballThrowOn = true;
	}
	if (ballThrowOn)
	{
		m_catchCount++;
		if (m_catchCount % 4 == 0) m_ballIndex++;
		switch (m_ballIndex)
		{
		case 0:
			m_ballOpen->aniRender(hdc, 170, 302, m_ballOpenAni);
			break;
		case 1:
			m_ballOpen->aniRender(hdc, 192, 270, m_ballOpenAni);
			break;
		case 2:
			m_ballOpen->aniRender(hdc, 216, 219, m_ballOpenAni);
			break;
		case 3:
			m_ballOpen->aniRender(hdc, 293, 130, m_ballOpenAni);
			break;
		case 4:
			m_ballOpen->aniRender(hdc, 405, 47, m_ballOpenAni);
			break;
		case 5:
			m_ballOpen->aniRender(hdc, 471, 16, m_ballOpenAni);
			break;
		case 6:
			m_ballOpen->aniRender(hdc, 513, 13, m_ballOpenAni);
			break;
		case 7:
			m_ballOpen->aniRender(hdc, 558, 14, m_ballOpenAni);
			break;
		case 8:
			m_ballOpen->aniRender(hdc, 596, 22, m_ballOpenAni);
			break;
		case 9:
			m_ballOpen->aniRender(hdc, 630, 44, m_ballOpenAni);
			break;
		case 10:
			m_ballOpen->aniRender(hdc, 735, 118, m_ballOpenAni);
			ANIMANAGER->start("ballOpenAni");
			ANIMANAGER->start("pocketmonCatchEffectAni");
			//m_ballIndex = 0;
			ballThrowOn = false;
			ballOpen = true;
			break;
		}
	}
	if (ballOpen)
	{
		m_ballOpenCount++;
		IMAGEMANAGER->findImage("backGroundImg")->alphaRender(hdc, 0, 0, 0, 0, WINSIZEX, WINSIZEY - (m_explainRect.bottom - m_explainRect.top), whiteBgAlpha);
		m_ballOpen->aniRender(hdc, 735, 118, m_ballOpenAni);
		m_pocketmonCatchEffect->aniRender(hdc, 380, -30, m_pocketmonCatchEffectAni);
		if (20 < m_ballOpenCount && m_ballOpenCount <= 70)
		{
			ANIMANAGER->pause("ballOpenAni");

		}
		else if (m_ballOpenCount == 71)
		{
			ANIMANAGER->resume("ballOpenAni");
			whiteBgAlpha -= 40;
			if (whiteBgAlpha <= 0) whiteBgAlpha = 0;
		}
		else if (m_ballOpenCount > 80)
		{
			m_ballOpenCount = 0;
			ballOpen = false;
			ballDown = true;
		}
	}
	if (ballDown)
	{
		m_ballOpenCount++;
		if (m_ballOpenCount % 5 == 0) m_ballDownIndex++;
		switch (m_ballDownIndex)
		{
		case 0:
			m_ballOpen->aniRender(hdc, 735, 118, m_ballOpenAni);
			break;
		case 1:
			m_ballOpen->aniRender(hdc, 735, 138, m_ballOpenAni);
			break;
		case 2:
			m_ballOpen->aniRender(hdc, 735, 163, m_ballOpenAni);
			break;
		case 3:
			m_ballOpen->aniRender(hdc, 735, 211, m_ballOpenAni);
			break;
		case 4:
			//바닥
			m_ballOpen->aniRender(hdc, 735, 260, m_ballOpenAni); //160
			break;
		case 5:
			m_ballOpen->aniRender(hdc, 735, 200, m_ballOpenAni);
			break;
		case 6:
			m_ballOpen->aniRender(hdc, 735, 180, m_ballOpenAni);
			break;
		case 7:
			//두번째 top
			m_ballOpen->aniRender(hdc, 735, 160, m_ballOpenAni);
			break;
		case 8:
			m_ballOpen->aniRender(hdc, 735, 180, m_ballOpenAni);
			break;
		case 9:
			m_ballOpen->aniRender(hdc, 735, 200, m_ballOpenAni);
			break;
		case 10:
			//바닥
			m_ballOpen->aniRender(hdc, 735, 260, m_ballOpenAni); //200
			break;
		case 11:
			m_ballOpen->aniRender(hdc, 735, 240, m_ballOpenAni);
			break;
		case 12:
			m_ballOpen->aniRender(hdc, 735, 200, m_ballOpenAni);
			break;
		case 13:
			m_ballOpen->aniRender(hdc, 735, 240, m_ballOpenAni);
			break;
		case 14:
			//바닥
			m_ballOpen->aniRender(hdc, 735, 260, m_ballOpenAni);
			break;
		case 15:
			m_ballOpen->aniRender(hdc, 735, 250, m_ballOpenAni);
			break;
		case 16:
			//세번째 TOP
			m_ballOpen->aniRender(hdc, 735, 245, m_ballOpenAni);
			break;
		case 17:
			m_ballOpen->aniRender(hdc, 735, 250, m_ballOpenAni);
			break;
		case 18:
			//바닥
			m_ballOpen->aniRender(hdc, 735, 260, m_ballOpenAni);
			break;
		case 19:
			m_ballOpen->aniRender(hdc, 735, 255, m_ballOpenAni);
			break;
		case 20:
			m_ballOpen->aniRender(hdc, 735, 260, m_ballOpenAni);
			ballDown = false;
			shakitBallOn = true;
			ANIMANAGER->start("shakeBallAni");
			break;
		}
	}
	if (shakitBallOn)
	{
		m_shakeBall->aniRender(hdc, 727, 260, m_shakeBallAni);
		if (!ANIMANAGER->isPlay("shakeBallAni"))
		{
			catchStartExplainOn = true;
			shakitBallOn = false;
			catchSuccess = true;
		}
	}
	if (catchSuccess)
	{
		m_successCount++;
		m_ballOpen->aniRender(hdc, 735, 257, m_ballOpenAni);
		IMAGEMANAGER->findImage("catchSuccess")->alphaRender(hdc, 727, 260, m_ballSuccessAlpha);
		if (m_successCount > 20)
		{
			m_ballSuccessAlpha = 120;
			if (m_successCount > 30)
			{
				if (!catchSuccessEffect)
				{
					EFFECTMANAGER->play("catchSuccessEffect", 759, 270);
					EFFECTMANAGER->play("catchSuccessEffect", 759, 290);
					catchSuccessEffect = true;
				}
				if (m_successCount > 50)
				{
					m_ballSuccessAlpha = 0;
					catchSuccess = false;
					catchExplainOn = true;
				}
			}
		}
	}
	if (catchExplainOn)
	{
		m_catchExplainCount++;
		char str[100];
		wsprintf(str, "신난다!");
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "%s를(을) 잡았다!!", m_wildPocketmon.m_name.c_str());
		TextOut(hdc, m_explainRect.left + 40, m_explainRect.top + 70, str, strlen(str));

		if (!catchOn)
		{
			trainer->pushBackPocketmon(POCKETMONMANAGER->genPocketMon(m_wildPocketmon.m_EnglishName, m_wildPocketmon.m_level));
			catchOn = true;
		}

		if (m_catchExplainCount > 40)
		{
			battleSceneEnd();			
		}
	}
}
//포켓몬 변경
void BattleScene::pocketmonChange(HDC hdc)
{
	if (comeBackPocketmon)
	{
		if (!pocketmonCatchEffectAniOn)
		{
			ANIMANAGER->start("pocketmonCatchEffectAni");
			pocketmonCatchEffectAniOn = true;
		}
		if (!whiteBgAlpahReversOn)	playerUiPoketmon(hdc);
		IMAGEMANAGER->findImage("backGroundImg")->alphaRender(hdc, whiteBgAlpah);
		m_pocketmonCatchEffect->aniRender(hdc, -75, 330, m_pocketmonCatchEffectAni);
		IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);

		whiteBgAlpah += 10;
		if (whiteBgAlpah > 255)
		{
			//플레이어 상태창 위치 초기화
			m_playerStatusX = 1324;
			m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
			whiteBgAlpahReversOn = true;
		}
		
		
		if (whiteBgAlpahReversOn)
		{
			whiteBgAlpah -= 20;
			if (whiteBgAlpah < 0)
			{
				whiteBgAlpah = 0;
				comeBackPocketmon = false;
				whiteBgAlpahReversOn = false;
				throwBallOn = true;
				pocketmonCatchEffectAniOn = false;
			}
		}
	}
	if (throwBallOn)
	{
		if (!ballThrowStart)
		{
			ANIMANAGER->start("throwBallAni");
			ballThrowStart = true;
			ballThrowAniOn = true;
		}
		if (ballThrowAniOn)
		{
			m_throwBall->aniRender(hdc, m_playerPocketmonImg.left, m_playerPocketmonImg.top, m_throwBallAni);
		}
		if (!ANIMANAGER->isPlay("throwBallAni"))
		{
			throwBallOn = false;
			ballThrowAniOn = false;
			statusMoveOn = true;
			changePocketmon();
		}
		IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);
	}
	if (statusMoveOn)
	{
		if (!setPlayerStatus)
		{
			if (!pocketmonCatchEffectAniOn)
			{
				ANIMANAGER->start("pocketmonCatchEffectAni");
				pocketmonCatchEffectAniOn = true;
			}

			whiteBgAlpah += 10;
			if (whiteBgAlpah > 255) whiteBgAlpahReversOn = true;
			if (whiteBgAlpahReversOn)
			{
				playerUiPoketmon(hdc);
				whiteBgAlpah -= 20;
				if (whiteBgAlpah < 0)
				{
					whiteBgAlpah = 0;
				}
			}
			IMAGEMANAGER->findImage("backGroundImg")->alphaRender(hdc, whiteBgAlpah);
			m_pocketmonCatchEffect->aniRender(hdc, -75, 330, m_pocketmonCatchEffectAni);
			IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);


			//플레이어 상태창
			m_playerStatusX -= 10;
			m_playerStatus = UTIL::IRectMake(m_playerStatusX, 356, 446, 180);
			if (m_playerStatusX <= PLAYERSTATUSX)
			{
				statusMoveOn = false;
				pocketmonCatchEffectAniOn = false;
				whiteBgAlpahReversOn = false;
				setPlayerStatus = true;
				bufferTimeOn = true;
			}
		}
	}
	if (bufferTimeOn)
	{
		playerUiPoketmon(hdc);
		IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);

		bufferTimeCount++;
		if (bufferTimeCount > 100)
		{
			//관련변수 모두 초기화
			pocketmonChangeOn = false;
			blackBgOn = false;
			throwBallOn = false;
			ballThrowStart = false;
			ballThrowAniOn = false;
			statusMoveOn = false;
			setPlayerStatus = false;
			moveEnemyStatus = false;
			whiteBgAlpahReversOn = false;
			setNewPocketmon = false;
			comeBackPocketmon = false;
			bufferTimeOn = false;
			pocketmonCatchEffectAniOn = false;

			blackBgAlpha = 255;
			whiteBgAlpah = 0;
			bufferTimeCount = 0;

			playerTurn = false;
			enemyTurn = true;
		}
	}
}

void BattleScene::battleSceneEnd()
{
	SOUNDMANAGER->stopChannel(Channel::eChannelBattleBgm);
	SOUNDMANAGER->playSound("Route", Channel::eChannelBgm);
	SCENEMANAGER->scenePop();
}

//포켓몬 스킬 이펙트들 모음
void BattleScene::pocketmonEffectInit()
{
	//완료
	//공용 이팩트
	EFFECTMANAGER->addEffect("불꽃세례", "Images/attackEffect/pailiSkill_1.bmp", 35 * 3, 150 * 3, 35 * 3, 30 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("할퀴기", "Images/attackEffect/Scratch.bmp", 32 * 7, 96 * 7, 32 * 7, 36 * 7, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("전기자석파", "images/attackEffect/ThunderWave.bmp", 32 * 4, 96 * 4, 32 * 4, 32 * 4, 1, 0.1f, 100);

	//플레이어
	
		
	//적
	//피카츄
	EFFECTMANAGER->addEffect("번개", "images/attackEffect/100v.bmp", 159 * 4, 550 * 4, 159 * 4, 110 * 4, 1, 0.1f, 100);
	//파이리,식스테일 공격
	EFFECTMANAGER->addEffect("불대문자", "Images/attackEffect/fireBlast.bmp", 32 * 3, 128 * 3, 32 * 3, 32 * 3, 1, 0.1f, 100);
	//캐터피, 꼬렛
	EFFECTMANAGER->addEffect("전광석화", "Images/attackEffect/QuickAttack.bmp", 32 * 3, 32 * 3, 32 * 3, 32 * 3, 10, 0.1f, 100);
	EFFECTMANAGER->addEffect("날개치기", "Images/attackEffect/wingAttack.bmp", 16 * 3, 48 * 3, 16 * 3, 16 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("날개치기(적)", "Images/attackEffect/wingAttack_Enemy.bmp", 16 * 3, 48 * 3, 16 * 3, 16 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("덩쿨채찍", "Images/attackEffect/VineWhip.bmp", 32 * 3, 160 * 3, 32 * 3, 32 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("덩쿨채찍(적)", "Images/attackEffect/VineWhip_Enemy.bmp", 32 * 3, 160 * 3, 32 * 3, 32 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("잎날가르기", "Images/attackEffect/razorLeaf.bmp", 16 * 3, 144 * 3, 16 * 3, 48 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("잎날가르기(적)", "Images/attackEffect/razorLeaf_Enemy.bmp", 16 * 3, 144 * 3, 16 * 3, 16 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("소금물", "Images/attackEffect/brine.bmp", 32 * 3, 160 * 3, 32 * 3, 32 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("소금물(적)", "Images/attackEffect/brine_Enemy.bmp", 32 * 3, 160 * 3, 32 * 3, 32 * 3, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("하이드로펌프", "Images/attackEffect/HydroPump.bmp", 16 * 3, 128 * 3, 16 * 3, 32 * 3, 1, 0.1f, 100);
	//피카츄 공격
	EFFECTMANAGER->addEffect("번개", "images/attackEffect/100v.bmp", 159 * 4, 550 * 4, 159 * 4, 110 * 4, 1, 0.1f, 100);
	EFFECTMANAGER->addEffect("10만볼트", "images/attackEffect/Thunder.bmp", 32 * 4, 160 * 4, 32 * 4, 32 * 4, 1, 0.1f, 100);

}
bool BattleScene::playerSkillEffectAssemble(std::string _skillName, HDC hdc)
{
	//파이리 스킬
	if (_skillName == "몸통박치기") tackleProto(_skillName, hdc);
	else if (_skillName == "화염방사") flameThrowerProto(_skillName, hdc);
	else if (_skillName == "불대문자") fireBlastProto(_skillName, hdc);
	//공통모음
	else if (_skillName == "불꽃세례") skillEmberProto(_skillName, hdc);
	else if (_skillName == "할퀴기") scratchProto(_skillName, hdc);
	else if (_skillName == "전기자석파") playerThunderWaveProto(_skillName, hdc);
	
	return true;
}
void BattleScene::enemySkillEffectAssemble(std::string _skillName, HDC hdc)
{
	_skillName = "불꽃세례";
	if (_skillName == "전광석화") quickAttackProto(_skillName, hdc);
	else if (_skillName == "십만볼트") thunderboltProto(_skillName, hdc);
	else if (_skillName == "번개") thunderProto(_skillName, hdc);
	//공통모음
	else if (_skillName == "불꽃세례") enemySkillEmberProto(_skillName, hdc);
	else if (_skillName == "할퀴기") enemyScratchProto(_skillName, hdc);
	else if (_skillName == "전기자석파") enemyThunderWaveProto(_skillName, hdc);
}

int BattleScene::checkDamage()
{
	if (!enemyTurn)
	{
		//포켓몬 타입별 상성
		switch (selectPocketmon->m_Attribute)
		{
		case PockemonAttibute::PockemonAttibuteFire:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					//불 vs 불    0.5
					//불 vs 바위  0.5
					//불 vs 물    0.5
					//불 vs 풀    2
					//불 vs 비행  
					//불 vs 전기  
					//불 vs 노멀  
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					//바위 vs 불   2
					//바위 vs 바위 0.5
					//바위 vs 물
					//바위 vs 풀 
					//바위 vs 비행 2  
					//바위 vs 전기 
					//바위 vs 노멀
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					//물 vs 불    2
					//물 vs 바위  2
					//물 vs 물    0.5
					//물 vs 풀    0.5
					//물 vs 비행
					//물 vs 전기
					//물 vs 노멀
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					//풀 vs 불   0.5
					//풀 vs 바위 2
					//풀 vs 물   2
					//풀 vs 풀   0.5
					//풀 vs 비행 0.5
					//풀 vs 전기
					//풀 vs 노멀
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					//비행 vs 불   
					//비행 vs 바위 0.5
					//비행 vs 물   
					//비행 vs 풀   2
					//비행 vs 비행 
					//비행 vs 전기 0.5
					//비행 vs 노멀
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					//전기 vs 불   
					//전기 vs 바위
					//전기 vs 물    2
					//전기 vs 풀    0.5
					//전기 vs 비행  2
					//전기 vs 전기  0.5
					//전기 vs 노멀
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					//노멀 vs 불 
					//노멀 vs 바위  0.5
					//노멀 vs 물
					//노멀 vs 풀
					//노멀 vs 비행
					//노멀 vs 전기
					//노멀 vs 노멀
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteStone:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteWater:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteGrass:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteFly:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteElectric:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteNormal:
			switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skillclassify)
			{

				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return basicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return basicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return basicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (selectPocketmon->skillList[m_playerSelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return spacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return spacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return spacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		}
	}
	else if (enemyTurn)
	{
		switch (m_wildPocketmon.m_Attribute)
		{
		case PockemonAttibute::PockemonAttibuteFire:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					//불 vs 불    0.5
					//불 vs 바위  0.5
					//불 vs 물    0.5
					//불 vs 풀    2
					//불 vs 비행  
					//불 vs 전기  
					//불 vs 노멀  
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					//바위 vs 불   2
					//바위 vs 바위 0.5
					//바위 vs 물
					//바위 vs 풀 
					//바위 vs 비행 2  
					//바위 vs 전기 
					//바위 vs 노멀
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					//물 vs 불    2
					//물 vs 바위  2
					//물 vs 물    0.5
					//물 vs 풀    0.5
					//물 vs 비행
					//물 vs 전기
					//물 vs 노멀
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					//풀 vs 불   0.5
					//풀 vs 바위 2
					//풀 vs 물   2
					//풀 vs 풀   0.5
					//풀 vs 비행 0.5
					//풀 vs 전기
					//풀 vs 노멀
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					//비행 vs 불   
					//비행 vs 바위 0.5
					//비행 vs 물   
					//비행 vs 풀   2
					//비행 vs 비행 
					//비행 vs 전기 0.5
					//비행 vs 노멀
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					//전기 vs 불   
					//전기 vs 바위
					//전기 vs 물    2
					//전기 vs 풀    0.5
					//전기 vs 비행  2
					//전기 vs 전기  0.5
					//전기 vs 노멀
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					//노멀 vs 불 
					//노멀 vs 바위  0.5
					//노멀 vs 물
					//노멀 vs 풀
					//노멀 vs 비행
					//노멀 vs 전기
					//노멀 vs 노멀
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteStone:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteWater:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteGrass:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteFly:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteElectric:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1.5 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		case PockemonAttibute::PockemonAttibuteNormal:
			switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skillclassify)
			{
				//// 노공 ////
			case SkillClassify::SkillTypeNormal:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemyBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (selectPocketmon->m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemyBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemyBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
				//// 특공 ////
			case SkillClassify::SkillTypeSpecial:
				switch (m_wildPocketmon.skillList[m_enemySelectSkillNumber].skilltype)
				{
				case SkillType::SkillAttibuteFire:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteStone:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteWater:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteGrass:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteFly:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteElectric:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						attributeOn = true;
						plusAttribute = true;
						return enemySpacialBasicDamage() * 1 * 2 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				case SkillType::SkillAttibuteNormal:
					switch (m_wildPocketmon.m_Attribute)
					{
					case PockemonAttibute::PockemonAttibuteFire:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteStone:
						attributeOn = true;
						plusAttribute = false;
						return enemySpacialBasicDamage() * 1.5 * 0.5 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteWater:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteGrass:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteFly:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteElectric:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					case PockemonAttibute::PockemonAttibuteNormal:
						return enemySpacialBasicDamage() * 1.5 * 1 * UTIL::GetRndIntFromTo(217, 255) / 255;
					}
				}
			}
		}
	}
}
