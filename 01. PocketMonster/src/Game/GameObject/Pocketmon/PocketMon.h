#pragma once
#include "Game/GameObject/Object.h"
#include "Common/SystemManagers.h"
class PocketMon
	: public Object
{
public:
	PocketMon();
	PocketMon(const PocketMon& _pocket);
	~PocketMon();

public:
	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

	void skillEffect(int _skillNum);
	bool getState() { return m_state; }

public:
	bool m_state; //1.플레이어, 2.npc, 3.야생
	Image* m_pocketmonFrontImg;
	Image* m_pocketmonBackImg;
	std::string m_name;
	std::string m_customName;
	PockemonAttibute m_Attribute;
	bool gender;
	int m_level;
	int m_maxHp;
	int m_currentHp;
	int m_atk;
	int m_def;
	int m_specialAtk;
	int m_specialDef;
	int m_speed;
	int m_maxExp;
	int m_currentExp;
	int m_wildExp;
	std::vector<PocketSkill> skillList;	//MaxSize4
};
