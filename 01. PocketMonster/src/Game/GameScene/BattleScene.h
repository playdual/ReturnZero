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

	//�ൿ���ð���
	void moveButton();
	void moveSkillSelectButton();

	void playerStayMotion();

	void skillMotion();
	void selectEnemyskill();

	//void test();
private:

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
	//�÷��̾� ���ϸ�
	UTIL::IRECT m_playerPocketmon;
	//�÷��̾� ����â
	UTIL::IRECT m_playerStatus;
	//��ų ����Ʈ
	UTIL::IRECT m_playerAtkSkillEffect;
	//��ų ����Ʈ
	UTIL::IRECT m_enemyAtkSkillEffect;

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

	//��ų��� ����(�÷��̾�, �� ����)
	bool playerAtkSkillOn;
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

