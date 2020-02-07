#pragma once
#include "Scene.h"
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

	void moveButton();
	void select();

	void moveSkillSelectButton();
	void playerStayMotion();

	//void test();
private:

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
	//플레이어 포켓몬
	UTIL::IRECT m_playerPocketmon;
	//플레이어 상태창
	UTIL::IRECT m_playerStatus;


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

	//적 상태창

	//플레이어 대기상태 모션
	bool motionUp;

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

