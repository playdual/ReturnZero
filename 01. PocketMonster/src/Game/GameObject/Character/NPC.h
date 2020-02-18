#pragma once
#include "Game/GameObject/Object.h"

class NPC
	: public Object
{
public:
	NPC();
	NPC(int _bPosX, int _bPosY, std::string _name, NPCEventType _anotherEventType = NPCEventType::NPCNone, bool _ADHD = false);

public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;

public:
	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

public:
	void addSenario(std::string _scriptKey, Senario _senario);
	void activateNPC(Direction _dir);
	bool isOnActevated() { return isActivate; }

private:
	void updateSenario(float _deltaTime);
	void updatePocketCenterEvent(float _deltaTime);
	void updateShopEvent(float _deltaTime);
	void resetSenarioIndexData();

private:
	class Image* m_Img[4];
	UTIL::IRECT m_absRect;
	UTIL::IRECT m_outRect;

	std::map<std::string, Senario> m_Scripts;
	Senario m_curSenario;
	std::string m_Name;

	Direction m_PrintDirection;
	int m_blockPositionX;
	int m_blockPositionY;
	bool isADHD = false;
	bool isCanprint;
	bool isActivate = false;

	bool hasAnotherEvent = false;
	NPCEventType anoterEventType = NPCEventType::NPCNone;

	//문자 출력 변수
private:
	bool onSenarioPrint = false;

	float addCharacterDelay = 0.1f;
	float pastTime = 0.f;

	std::wstring firstOutStr;
	std::wstring secondOutStr;

	bool completedFirstOut = false;
	bool completedSecondOut = false;
	
	int firstStrIndex = 0;
	int secondStrIndex = 0;
	int senarioIndex = 0;

private:
	friend class MapManager;
};
