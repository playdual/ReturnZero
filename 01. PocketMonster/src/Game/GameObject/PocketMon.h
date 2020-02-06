#pragma once
#include "Object.h"
#include "Common/SystemManagers.h"

//struct 
//{
//
//};
class PocketMon
	: public Object
{
public:
	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

private:
	std::shared_ptr<Image> m_pocketmonFrontImg;
	std::shared_ptr<Image> m_pocketmonBackImg;
	std::string m_name;
	std::string m_customName;
	POCKETMON_ATTRIBUTE m_Attribute;
	bool gender;
	int m_level;
	int m_maxHp;
	int m_currentHp;
	int m_atk;
	int m_def;
	int m_specialAtk;
	int m_specialDef;
	int m_dex;
	int m_maxExp;
	int m_currentExp;
};