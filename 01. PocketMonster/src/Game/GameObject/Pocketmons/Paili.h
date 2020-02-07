#pragma once
#include "../PocketMon.h"
class Paili
	:public PocketMon
{
public:
	bool init() override;
	void update(float _deltaTime) override;

public:
	void render(HDC hdc) override;
	void afterRender(HDC hdc) override;
	void debugRender(HDC hdc) override;
	void skillEffect(int _skillNum) override;

	std::string getName() { return m_name; }
	bool getSkillMotionOn() { return skillMotionOn; }

private:
	bool skillMotionOn;
};

