#pragma once
#include "Game/GameObject/Object.h"

class Character
	: public Object
{
protected:
	std::string m_name;
	std::string m_customName;
	ItemType m_type;

public:
	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;

public:
	std::string getName() { return m_name; }
};
