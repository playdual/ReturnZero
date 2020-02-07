#pragma once
#include "Scene.h"
#include "Game/GameObject/PocketMon.h"
#include "Game/GameObject/Pocketmons/Paili.h"

//�� �̹����� ����ġ ��ǥ
//�÷��̾� UI ����ġ
#define PLAYERBOTTOMX	0
#define PLAYERIMGX		200
#define PLAYERPOCKETMONX 200
#define PLAYERSTATUSX 535

// �� UI ����ġ
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

	//�ൿ���ð���
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
	
	//�ൿ���� Ŀ��
	UTIL::IRECT m_selectRect;
	//��Ȳ����â
	UTIL::IRECT m_explainRect;
	//��� Ŀ��
	UTIL::IRECT m_skillSelectRect;
	//��� ����Ʈ
	UTIL::IRECT m_skillListRect;
	//��� ����â
	UTIL::IRECT m_skillExplainRect;
	//�� ����â
	UTIL::IRECT m_enemyStatus;
	//�� ���ϸ�
	UTIL::IRECT m_enemyPocketmon;
	//�� �ٴ�
	UTIL::IRECT m_enemyBottom;
	//�÷��̾�ٴ�
	UTIL::IRECT m_playerBottom;
	//�÷��̾� �̹���
	UTIL::IRECT m_playerImg;
	//�÷��̾� ���ϸ�
	UTIL::IRECT m_playerPocketmon;
	//�÷��̾� ����â
	UTIL::IRECT m_playerStatus;
	//��ų ����Ʈ
	UTIL::IRECT m_playerAtkSkillEffect;
	//��ų ����Ʈ
	UTIL::IRECT m_enemyAtkSkillEffect;


	//�������� ���� (npc ���, �߻� ����)
	bool wildBattle;
	bool npcBattle;

	//=====================
	// �ִϸ��̼� �������� //
	//=====================
	//���� ���� ��Ʈ�� ȭ��
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


	//����â Ŀ�� ������ ����
	bool fight;
	bool bag;
	bool pocketmon;
	bool run;

	//�����ൿ Ȱ��ȭ ���� ����
	bool playerAtkOn;

	//��ų���� Ŀ�� ������ ����
	bool skill_1;
	bool skill_2;
	bool skill_3;
	bool skill_4;

	//���� �� ����
	bool playerTurn;
	bool enemyTurn;

	//�� ����â

	//�÷��̾� ������ ���
	bool motionUp;

	//��ų��� ����
	bool playerAtkSkillOn;
	bool skillMotionOn; 

	bool enemyAtkSkillOn;
	int m_skillCount;

	




	//init�ȿ� �� �����
	/*
	1. ��� �̹��� ���� (���ο��� �ε����� �����ϰ� �� �� ����)
	2. m_selectRect ��ġ �ʱ�ȭ
	
	*/

	/* 

	*/
	//update�ȿ� �� �����
	/*
	1. ��� ��
	*/
};

