﻿#pragma once
#include "Scene.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"
#include "Game/GameObject/Character/player.h"

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

class player;
class PocketMon;
class BattleScene
	:public Scene
{
public:
	BattleScene();
	virtual ~BattleScene();

public:
	bool init() override;
	bool init(std::shared_ptr<player> _player, std::shared_ptr<player> _npc) override;
	bool init(std::shared_ptr<player> _player, PocketMon& _pocketmon) override;
	void update(float _deltaTime) override;
	void release() override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

	
	void wildBattleFunctions();
	void npcBattleFunctions();

	//상황별 Ani
	void wildBattleIntroAni();
	void npcBattleIntroAni();
	void wildBattleOutAni(HDC hdc);
	void playerPocketmonLoseAni(HDC hdc);
	void playerLoseAni(HDC hdc);

	//포켓몬 공격 및 피격 이팩트 관련
	void pocketmonEffectInit();
	bool playerSkillEffectAssemble(std::string _skillName, HDC hdc);
	void enemySkillEffectAssemble(std::string _skillName, HDC hdc);

	
	//===================
	// 오브젝트 UI 모음 //
	//===================
	//적
	void enemyUiStatus(HDC hdc);
	void enemyUiBottom(HDC hdc);
	void enemyUiPocketmon(HDC hdc);
	void enemyUiMaxHp(HDC hdc);
	void enemyUiCurrentHp(HDC hdc);
	//플레이어
	void playerUiBottom(HDC hdc);
	void playerUiPoketmon(HDC hdc);
	void playerUiImg(HDC hdc);
	void playerUiStatus(HDC hdc);
	void playerUiSkillList(HDC hdc);
	void playerUiSkillExplain(HDC hdc);
	std::string playerUiSkillType(SkillType _skillType);
	void playerUiMaxHp(HDC hdc, int _y);
	void playerUiCurrentHp(HDC hdc, int _y);
	void playerUiMaxExp(HDC hdc, int _y);
	void plyaerUiCurrentExp(HDC hdc, int _y);
	int checkHpBarWigth();
	int checkExpBarWigth();
	bool checkPossiblePocketmon();
	int playerCurrentHpLeft() { return m_playerStatus.left + 205; }
	int playerCurrentHpTop() { return m_playerStatus.top+81; }
	int playerCurrentExpLeft() { return m_playerStatus.left + 137; }
	int playerCurrentExpTop() { return m_playerStatus.top+159; }



	//시스템
	void explainRect(HDC hdc);
	void selectRect(HDC hdc);
	void skillSelectRect(HDC hdc);
	void playerPocketmonChange();

	//행동선택관련
	void moveButton();
	void moveSkillSelectButton();

	void playerStayMotion();

	std::string selectEnemyskill();

	//공격에 hp 변동 체크
	//공격하면 현재 피가 달면서 current의 wigth 값이 줄어든다.
	void playerPockatmonAttack(HDC hdc);
	
	int checkDamage();
	int basicDamage();
	int spacialBasicDamage();
	int enemyBasicDamage();
	int enemySpacialBasicDamage();
	
	//렌더링
	void wildBattleRender(HDC hdc);
	void npcBattleRender(HDC hdc);


	//스킬 이팩트 모듬
	//플레이어	
	void tackleProto(std::string _skillName, HDC hdc);
	void emberProto(std::string _skillName, HDC hdc);
	void flameThrowerProto(std::string _skillName, HDC hdc);
	void fireBlastProto(std::string _skillName, HDC hdc);

	//적
	void quickAttackProto(std::string _skillName, HDC hdc);
	void thunderWaveProto(std::string _skillName, HDC hdc);
	void thunderboltProto(std::string _skillName, HDC hdc);
	void thunderProto(std::string _skillName, HDC hdc);
	
	//공통 출력 문구
	void enemyHpChangFromPlayerAtk();
	void playerHpChangFromEnemyAtk();

	void playerAtkResultOutput(HDC hdc);
	void enemyAtkResultOutput(HDC hdc);
	
private:
	
	std::shared_ptr<player> trainer;
	std::vector<std::shared_ptr<PocketMon>> m_playerPocketmons;
	std::shared_ptr<PocketMon> selectPocketmon;
	PocketMon m_wildPocketmon;
	ChangePocketInfo cpInfo;
	UsedItemInfo uiInfo;


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
	//적 최대체력
	UTIL::IRECT m_enemyMaxHp;
	//적 현재체력
	UTIL::IRECT m_enemyCurrentHp;

	//플레이어바닥
	UTIL::IRECT m_playerBottom;
	//플레이어 이미지
	UTIL::IRECT m_playerImg;
	//플레이어 포켓몬
	UTIL::IRECT m_playerPocketmonImg;
	//플레이어 상태창
	UTIL::IRECT m_playerStatus;
	//플레이어 최대체력
	UTIL::IRECT m_playerMaxHp;
	//플레이어 현재체력
	UTIL::IRECT m_playerCurrentHp;
	//플레이어 최대경험치
	UTIL::IRECT m_playerMaxExp;
	//플레이어 현재경험치
	UTIL::IRECT m_playerCurrentExp;

	//스킬 이펙트
	UTIL::IRECT m_playerAtkSkillEffect;
	//스킬 이펙트
	UTIL::IRECT m_enemyAtkSkillEffect;

	//포켓몬 체인지 관련
	bool playerPocketmonChangeOn;

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
	//적	 UI
	int m_enemyBottomX;
	int m_enemyPocketmonX;
	int m_enemyPocketmonY;
	int m_enemyStatusX;
	int m_enemyHpX;
	int m_wildPocketmonHpBarWigth;
	//플레이어 UI
	int m_playerBottomX;
	int m_playerimgX;
	int m_playerPocketmonX;
	int m_playerStatusX;
	int m_playerHpX;
	int m_playerExp;
	int m_playerPocketmonHpBarWigth;
	int m_playerPocketmonExpBarWigth;


	//선택창 커서 움직임 변수
	bool fight;
	bool bag;
	bool pocketmon;
	bool run;

	//선택행동 활성화 적용 변수
	bool playerAtkOn;

	//스킬선택 변수
	bool skill_1;
	bool skill_2;
	bool skill_3;
	bool skill_4;
	std::string m_selectSkill;

	//===================
	// 전투 시스템 관련 //
	//===================
	//공격 턴 변수
	bool playerTurn;
	bool enemyTurn;

	//적 상태창

	//플레이어 대기상태 모션
	bool motionUp;

	//공격 이팩트 및 피격효과 구현
	//플레이어측
	bool playerAtkSkillOn;
	bool playerSkillMotionOn; 
	bool playerSkillEffect;
	bool playerHitEffect;
	bool playerSkillExplainDone;
	bool playerSkillEffectDone;
	bool enemyHpChange;
	bool explainEffect;
	bool enemyAtkSkillOn;
	bool battleEnd;
	bool attributeOn;
	bool plusAttribute;

	int m_skillCount;
	int m_enemyTwinkleCount;
	int m_enemyMinusHp;
	int m_enemyCurrentMinusHp;
	int m_enemyAlpha;
	int m_playerCurrentPlusExp;
	int m_playerSelectSkillNumber;
	


	//적
	std::string enemySkillName;
	bool enemySkillEffect;
	bool enemySkillEffectDone;
	bool enemyHitEffect;
	bool playerHpChange;
	bool enemyExplainEffect;
	bool enemySkillNameExplain;
	bool enemySkillResultExplain;
	bool enemySkillSelect;
	int m_playerAlpha;
	int m_playerTwinkleCount;
	int m_playerMinusHp;
	int m_playerCurrentMinusHp;
	int m_enemySelectSkillNumber;
	int m_playerPocketmonY;

	std::string m_enemySelectSkillName;



	//전투 승패 관련
	bool pocketmonLose;
	bool playerLose;
	bool enemyLose;
	bool emptyBattlePocketmon;
	int m_loseAniCount;
	int playerPocketmonsNumber;
	




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

