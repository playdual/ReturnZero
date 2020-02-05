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

	//�� ����â

	//�÷��̾� ������ ���
	bool motionUp;

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

