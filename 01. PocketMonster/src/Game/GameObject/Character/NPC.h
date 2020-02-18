#pragma once
#include "Game/GameObject/Object.h"

class NPC
	: public Object
{
public:
	NPC();
	NPC(int _bPosX, int _bPosY, std::string _name);

public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;

public:
	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

public:
	void addScript(std::string _scriptKey, std::string _firstLine, std::string _secondLine);
	void activateNPC(Direction _dir);

private:
	class Image* m_Img[4];
	UTIL::IRECT m_absRect;
	UTIL::IRECT m_outRect;

	std::map<std::string, std::pair<std::string, std::string>> m_Scripts;
	std::string m_Name;

	Direction m_PrintDirection;
	int m_blockPositionX;
	int m_blockPositionY;
	bool isCanprint;
	bool isActivate = false;

	friend class MapManager;
};
