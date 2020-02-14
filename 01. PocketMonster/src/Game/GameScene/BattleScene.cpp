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
	trainer = _player;
	m_playerPocketmons = trainer->getPocketmons();
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
	m_playerPocketmonHpBarWigth = checkHpBarWigth();
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
	battleEnd = false;
	attributeOn = false;
	plusAttribute = false;

	m_skillCount = 0;
	m_enemyTwinkleCount = 0;
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
	m_loseAniCount = 0;

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


//========================
// UI RENDER 함수들 모음 //
//========================

void BattleScene::explainRect(HDC hdc)
{
	char str[100];

	//UTIL::DrawRect(hdc, m_explainRect);
	IMAGEMANAGER->render("explainRect", hdc, m_explainRect.left, m_explainRect.top);
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
	
	if (!wildBattleIntroAniOn && !playerAtkOn)
	{
		wsprintf(str, "%s는(은)", selectPocketmon->m_name.c_str());
		TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 10, str, strlen(str));

		wsprintf(str, "무엇을 할까?");
		TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 40, str, strlen(str));

		wsprintf(str, "싸운다");
		TextOut(hdc, 649, 590, str, strlen(str));

		wsprintf(str, "가방");
		TextOut(hdc, 854, 590, str, strlen(str));

		wsprintf(str, "포켓몬");
		TextOut(hdc, 649, 666, str, strlen(str));

		wsprintf(str, "도망간다");
		TextOut(hdc, 854, 666, str, strlen(str));
	}

	if (enemyTurn)
	{
		if (!enemyExplainEffect)
		{
			wsprintf(str, "상대 %s의", m_wildPocketmon.m_name.c_str());
			TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 10, str, strlen(str));

			wsprintf(str, "%s 공격!", m_enemySelectSkillName.c_str());
			TextOut(hdc, m_explainRect.left + 20, m_explainRect.top + 40, str, strlen(str));
		}
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
	wsprintf(str, "%s", selectPocketmon->m_name.c_str());
	TextOut(hdc, m_playerStatus.left + 10, m_playerStatus.top + 10, str, strlen(str));

	wsprintf(str, "Lv %d", selectPocketmon->m_level);
	TextOut(hdc, m_playerStatus.left + 310, m_playerStatus.top + 20, str, strlen(str));

	wsprintf(str, "%d/  %d", selectPocketmon->m_currentHp, selectPocketmon->m_maxHp);
	TextOut(hdc, m_playerStatus.left + 290, m_playerStatus.top + 115, str, strlen(str));

}
void BattleScene::playerUiSkillList(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillListRect);

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
}
void BattleScene::playerUiSkillExplain(HDC hdc)
{
	UTIL::DrawRect(hdc, m_skillExplainRect);
	char str[100];
	wsprintf(str, "PP");
	TextOut(hdc, 649, 590, str, strlen(str));

	if (skill_1)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[0].currentpp, selectPocketmon->skillList[0].maxpp);
		TextOut(hdc, 863, 590, str, strlen(str));

		wsprintf(str, "기술타입  / %s", playerUiSkillType(selectPocketmon->skillList[0].skilltype).c_str());
		TextOut(hdc, 649, 670, str, strlen(str));
	}
	if (skill_2)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[1].currentpp, selectPocketmon->skillList[1].maxpp);
		TextOut(hdc, 863, 590, str, strlen(str));

		wsprintf(str, "기술타입  / %s", playerUiSkillType(selectPocketmon->skillList[1].skilltype).c_str());
		TextOut(hdc, 649, 670, str, strlen(str));
	}
	if (skill_3)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[2].currentpp, selectPocketmon->skillList[2].maxpp);
		TextOut(hdc, 863, 590, str, strlen(str));

		wsprintf(str, "기술타입  / %s", playerUiSkillType(selectPocketmon->skillList[2].skilltype).c_str());
		TextOut(hdc, 649, 670, str, strlen(str));
	}
	if (skill_4)
	{
		wsprintf(str, "%d / %d", selectPocketmon->skillList[3].currentpp, selectPocketmon->skillList[3].maxpp);
		TextOut(hdc, 863, 590, str, strlen(str));

		wsprintf(str, "기술타입  / %s", playerUiSkillType(selectPocketmon->skillList[3].skilltype).c_str());
		TextOut(hdc, 649, 670, str, strlen(str));
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
	m_playerMaxHp = UTIL::IRectMake(m_playerStatus.left + 181, 431 + _y, 230, 30);
	UTIL::DrawColorRect(hdc, m_playerMaxHp, RGB(120, 120, 120));
}
void BattleScene::playerUiCurrentHp(HDC hdc, int _y)
{
	m_playerCurrentHp = UTIL::IRectMake(m_playerStatus.left + 181, 431 + _y, m_playerPocketmonHpBarWigth, 30);
	UTIL::DrawColorRect(hdc, m_playerCurrentHp, RGB(10, 70, 70));
}
void BattleScene::playerUiMaxExp(HDC hdc, int _y)
{
	//플레이어 최대경험치
	m_playerMaxExp = UTIL::IRectMake(m_playerStatus.left + 151, 500 + _y, 230, 30);
	UTIL::DrawColorRect(hdc, m_playerMaxExp, RGB(120, 120, 120));
}
void BattleScene::plyaerUiCurrentExp(HDC hdc, int _y)
{
	//플레이어 현재경험치
	m_playerCurrentExp = UTIL::IRectMake(m_playerStatus.left + 151, 500 + _y, m_playerPocketmonExpBarWigth, 30);
	UTIL::DrawColorRect(hdc, m_playerCurrentExp, RGB(10, 70, 70));
}
int BattleScene::checkHpBarWigth()
{
	return 230 * selectPocketmon->m_currentHp / selectPocketmon->m_maxHp;;
}
int BattleScene::checkExpBarWigth()
{
	return 230 * selectPocketmon->m_currentExp / selectPocketmon->m_maxExp;
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
		SCENEMANAGER->scenePush("inven");
	}
	if (pocketmon && KEYMANAGER->isOnceKeyDown(P1_Z))
	{
		//포켓몬으로 씬체인지
		SCENEMANAGER->scenePush("PocketmonBagScene");
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
		playerSkillMotionOn = true;
	}

	if (playerSkillMotionOn)
	{
		if (skill_1)
		{
			m_selectSkill = selectPocketmon->skillList[0].name;
			m_playerSelectSkillNumber = 0;
		}
		else if (skill_2)
		{
			m_selectSkill = selectPocketmon->skillList[1].name;
			m_playerSelectSkillNumber = 1;
		}
		else if (skill_3)
		{
			m_selectSkill = selectPocketmon->skillList[2].name;
			m_playerSelectSkillNumber = 2;
		}
		else if (skill_4)
		{
			m_selectSkill = selectPocketmon->skillList[3].name;
			m_playerSelectSkillNumber = 3;
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
		playerUiMaxHp(hdc, 0);
		playerUiCurrentHp(hdc, 0);
		playerUiMaxExp(hdc, 0);
		plyaerUiCurrentExp(hdc, 0);


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

		int temp = 0;
		for (auto it = selectPocketmon->skillList.begin(); it != selectPocketmon->skillList.end(); ++it)
		{
			if (temp == 1)
			{
				wsprintf(str, "%s 공격!", it->name.c_str());
				TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 30, str, strlen(str));
				break;
			}
			temp++;
		}
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
	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::emberProto(std::string _skillName, HDC hdc)
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

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}
void BattleScene::fireBlastProto(std::string _skillName, HDC hdc)
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

	enemyHpChangFromPlayerAtk();
	playerAtkResultOutput(hdc);
}

//====================
// 적 공격 스킬 모음 //
//====================
void BattleScene::quickAttackProto(std::string _skillName, HDC hdc)
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
			if (m_playerMinusHp >= selectPocketmon->m_currentHp) m_playerMinusHp = selectPocketmon->m_currentHp;
		}
	}

	playerHpChangFromEnemyAtk();
	enemyAtkResultOutput(hdc);
}
void BattleScene::thunderWaveProto(std::string _skillName, HDC hdc)
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

//======================
// 공통 출력 문구 모음 //
//======================
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
		m_wildPocketmonHpBarWigth = (230 * m_wildPocketmon.m_currentHp) / m_wildPocketmon.m_maxHp;
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
		if (plusAttribute)
		{
			m_skillCount++;
			char str[100];
			wsprintf(str, "효과는 굉장했다!!");
			TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
			if (m_skillCount > 40)
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
			}
		}
		else
		{
			m_skillCount++;
			char str[100];
			wsprintf(str, "효과가 별로인 것 같다..");
			TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
			if (m_skillCount > 40)
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
			}
		}
	}

	if (explainEffect)
	{
		m_skillCount++;
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
}
void BattleScene::playerHpChangFromEnemyAtk()
{
	if (playerHpChange)
	{
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
		UTIL::DrawRect(hdc, m_explainRect);
		if (plusAttribute)
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
			TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
			if (m_skillCount > 40)
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
		if (m_skillCount > 100)
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

			m_playerCurrentPlusExp++;
			selectPocketmon->m_currentExp++;
			m_playerPocketmonExpBarWigth = checkExpBarWigth();
			if (m_playerCurrentPlusExp == m_wildPocketmon.m_wildExp)
			{
				m_playerCurrentPlusExp = 0;
				battleEnd = true;
			}
			
			if (battleEnd)
			{
				SCENEMANAGER->scenePop();
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
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

		wsprintf(str, "쓰러졌다!");
		TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 40, str, strlen(str));

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
			
			if(emptyBattlePocketmon)
			{
				UTIL::DrawRect(hdc, m_explainRect);
				wsprintf(str, "플레이어의 곁에는");
				TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
				
				wsprintf(str, "싸울 수 있는 포켓몬이 없다!");
				TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 40, str, strlen(str));

				if (m_loseAniCount > 100)
				{
					UTIL::DrawRect(hdc, m_explainRect);
					int temp = UTIL::GetRndIntFromTo(60, 100);
					wsprintf(str, "플레이어는(은) 당황해서");
					TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

					wsprintf(str, "%d를 잃어버렸다!", temp);
					TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 40, str, strlen(str));
					//trainer
					if (m_loseAniCount > 130)
					{
						UTIL::DrawRect(hdc, m_explainRect);
						wsprintf(str, "... ... ...");
						TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));
						if (m_loseAniCount > 150)
						{
							UTIL::DrawRect(hdc, m_explainRect);
							wsprintf(str, "플레이어는(은)");
							TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 10, str, strlen(str));

							wsprintf(str, "눈앞이 깜깜해졌다!");
							TextOut(hdc, m_explainRect.left + 10, m_explainRect.top + 40, str, strlen(str));
							
							if (m_loseAniCount > 170)
							{
								SCENEMANAGER->scenePop();
							}
						}
					}
				}
			}
		}
	}
}


//포켓몬 스킬 이펙트들 모음

void BattleScene::pocketmonEffectInit()
{
	//플레이어
	//파이리 공격
	EFFECTMANAGER->addEffect("불꽃세례", "images/pailiSkill_1.bmp", 35 * 3, 150 * 3, 35 * 3, 30 * 3, 1, 0.1f, 100);

	//적
	//피카츄 공격
	EFFECTMANAGER->addEffect("전광석화", "images/attackEffect/100v.bmp", 159 * 4, 550 * 4, 159 * 4, 110 * 4, 1, 0.1f, 100);
}

bool BattleScene::playerSkillEffectAssemble(std::string _skillName, HDC hdc)
{
	//파이리 스킬
	if (_skillName == "몸통박치기") tackleProto(_skillName, hdc);
	else if (_skillName == "불꽃세례") emberProto(_skillName, hdc);
	else if (_skillName == "화염방사") flameThrowerProto(_skillName, hdc);
	else if (_skillName == "불대문자") fireBlastProto(_skillName, hdc);

	return true;
}

void BattleScene::enemySkillEffectAssemble(std::string _skillName, HDC hdc)
{
	_skillName = "전광석화";
	if (_skillName == "전광석화") quickAttackProto(_skillName, hdc);
	else if (_skillName == "전기자석파") thunderWaveProto(_skillName, hdc);
	else if (_skillName == "십만볼트") thunderboltProto(_skillName, hdc);
	else if (_skillName == "번개") thunderProto(_skillName, hdc);
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