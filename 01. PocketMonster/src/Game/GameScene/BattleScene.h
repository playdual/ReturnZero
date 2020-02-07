#pragma once
#include "Scene.h"
#include "Game/GameObject/PocketMon.h"
#include "Game/GameObject/Pocketmons/Paili.h"

//각 이미지별 정위치 좌표
//플레이어 UI 정위치
#define PLAYERBOTTOMX	0
#define PLAYERIMGX		200
#define PLAYERPOCKETMONX 200
#define PLAYERSTATUSX 535

// 적 UI 정위치
#define ENEMYBOTTOMX	477
#define ENEMYPOCKETMONX 664
#define ENEMYSTATUSX 55

class BattleScene
	:public Scene
{
public:
	BattleScene();
	virtual ~BattleScene();

public:
	bool init() override;
	void release() override;

public:
	void update(float _deltaTime) override;
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

	
	void wildBattleFunctions();
	void npcBattleFunctions();

	void wildBattleIntroAni();

	void wildBattleRender(HDC hdc);
	void npcBattleRender(HDC hdc);

	//행동선택관련
	void moveButton();
	void moveSkillSelectButton();

	void playerStayMotion();

	void skillMotion();
	void selectEnemyskill();

	//void test();
private:
	std::shared_ptr<Paili> m_player;
	std::shared_ptr<Paili> m_enemy;
	//bool moveOn;

	
	int m_count;
	
	//행동선택 커서
	UTIL::IRECT m_selectRect;
	//상황설명창
	UTIL::IRECT m_explainRect;
	//기술 커서
	UTIL::IRECT m_skillSelectRect;
	//기술 리스트
	UTIL::IRECT m_skillListRect;
	//기술 설명창
	UTIL::IRECT m_skillExplainRect;
	//적 상태창
	UTIL::IRECT m_enemyStatus;
	//적 포켓몬
	UTIL::IRECT m_enemyPocketmon;
	//적 바닥
	UTIL::IRECT m_enemyBottom;
	//플레이어바닥
	UTIL::IRECT m_playerBottom;
	//플레이어 이미지
	UTIL::IRECT m_playerImg;
	//플레이어 포켓몬
	UTIL::IRECT m_playerPocketmon;
	//플레이어 상태창
	UTIL::IRECT m_playerStatus;
	//스킬 이펙트
	UTIL::IRECT m_playerAtkSkillEffect;
	//스킬 이펙트
	UTIL::IRECT m_enemyAtkSkillEffect;


	//전투유형 변수 (npc 대결, 야생 전투)
	bool wildBattle;
	bool npcBattle;

	//=====================
	// 애니메이션 변수모음 //
	//=====================
	//전투 시작 인트로 화면
	bool wildBattleIntroAniOn;
	bool uiObjectRegularPosition;
	bool playerImgSlideOut;
	bool explainEnemyName;
	int m_playerBottomX;
	int m_playerimgX;
	int m_playerPocketmonX;
	int m_playerStatusX;
	int m_enemyBottomX;
	int m_enemyPocketmonX;
	int m_enemyStatusX;


	//선택창 커서 움직임 변수
	bool fight;
	bool bag;
	bool pocketmon;
	bool run;

	//선택행동 활성화 적용 변수
	bool playerAtkOn;

	//스킬선택 커서 움직임 변수
	bool skill_1;
	bool skill_2;
	bool skill_3;
	bool skill_4;

	//공격 턴 변수
	bool playerTurn;
	bool enemyTurn;

	//적 상태창

	//플레이어 대기상태 모션
	bool motionUp;

	//스킬사용 변수
	bool playerAtkSkillOn;
	bool skillMotionOn; 

	bool enemyAtkSkillOn;
	int m_skillCount;

	




	//init안에 들어갈 내용들
	/*
	1. 배경 이미지 저장 (메인에서 로딩으로 진행하게 될 수 있음)
	2. m_selectRect 위치 초기화
	
	*/

	/* 

	*/
	//update안에 들어갈 내용들
	/*
	1. 배경 이
	*/
};

