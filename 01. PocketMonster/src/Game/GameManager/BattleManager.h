#pragma once
class BattleManager
{

public:
	HRESULT init();
	void release();

	void update(float deltaTime);
	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);

private:
	UTIL::IRECT testRect;

private:
	DECLARE_SINGLE(BattleManager)
};

#define BATTLEMANAGER BattleManager::GetInst()
