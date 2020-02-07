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
	virtual bool init()=0;
	virtual void update(float _deltaTime) = 0;

public:
	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;
	virtual void skillEffect(int _skillNum) = 0;

protected:
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