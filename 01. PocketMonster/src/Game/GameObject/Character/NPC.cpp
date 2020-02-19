#include "stdafx.h"
#include "NPC.h"
#include "Common/SystemManagers.h"
#include "Game/GameManager/MapManager.h"

NPC::NPC()
{
}

NPC::NPC(int _bPosX, int _bPosY, std::string _name, NPCEventType _anotherEventType, bool _ADHD)
{
	m_Img[DirectionUp] = IMAGEMANAGER->findImage(_name + "Back");
	m_Img[DirectionDown] = IMAGEMANAGER->findImage(_name + "Front");
	m_Img[DirectionLeft] = IMAGEMANAGER->findImage(_name + "Left");
	m_Img[DirectionRight] = IMAGEMANAGER->findImage(_name + "Right");
	m_Dialog = IMAGEMANAGER->findImage("상점NPC대화상자");
	m_DialCopleteArrow = IMAGEMANAGER->findImage("DialCopleteArrow");
	m_SelectBox = IMAGEMANAGER->findImage("yesOrNoBox");
	m_SelectPointer = IMAGEMANAGER->findImage("현재아이템표시");
	alphaEffect = IMAGEMANAGER->findImage("alpha");

	m_Name = _name;
	isADHD = _ADHD;
	m_blockPositionX = _bPosX;
	m_blockPositionY = _bPosY;
	m_DefaultDirection = DirectionDown;
	if (m_Name == "Mother")
		m_DefaultDirection = DirectionLeft;
	m_PrintDirection = m_DefaultDirection;

	m_absRect.left = _bPosX * TILE_WIDTH;
	m_absRect.right = _bPosX * TILE_WIDTH + TILE_WIDTH;
	m_absRect.top = _bPosY * TILE_HEIGHT;
	m_absRect.bottom = _bPosY * TILE_HEIGHT + TILE_HEIGHT;
	m_DialCompleteArrowRect = UTIL::IRectMakeCenter(WINSIZEX / 2, WINSIZEY - 55, 14, 9);

	anoterEventType = _anotherEventType;
	hasAnotherEvent = true;
	if (anoterEventType == NPCEventType::NPCNone)
		hasAnotherEvent = false;
	if (anoterEventType == NPCEventType::NPCShop)
		onSenarioPrint = false;

}

bool NPC::init()
{
	return true;
}

void NPC::updateSenario(float _deltaTime)
{
	pastTime += _deltaTime;
	if (completedFirstOut == false)
	{
		if (KEYMANAGER->isOnceKeyDown(P1_X)) {
			firstOutStr = m_curSenario[senarioIndex].first;
			completedFirstOut = true;
		}
		else if (pastTime > addCharacterDelay) {
			pastTime = 0.f;
			firstOutStr += m_curSenario[senarioIndex].first[firstStrIndex++];
			if (firstOutStr.size() >= m_curSenario[senarioIndex].first.size()) {
				completedFirstOut = true;
			}
		}
	}
	else if (!completedSecondOut) {
		if (KEYMANAGER->isOnceKeyDown(P1_X)) {
			secondOutStr = m_curSenario[senarioIndex].second;
			completedSecondOut = true;
		}
		else if (pastTime > addCharacterDelay) {
			pastTime = 0.f;
			secondOutStr += m_curSenario[senarioIndex].second[secondStrIndex++];
			if (secondOutStr.size() >= m_curSenario[senarioIndex].second.size()) {
				completedSecondOut = true;
			}
		}
	}
	if (completedSecondOut) {
		if (KEYMANAGER->isStayKeyDown(P1_Z) || KEYMANAGER->isOnceKeyDown(P1_X)) {
			SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
			senarioIndex++;
			if (senarioIndex == m_curSenario.size()) {
				//onSenarioPrint = false;
				if (!hasAnotherEvent) {
					m_PrintDirection = m_DefaultDirection;
					isActivate = false;
				}
				else {
					isOnSelectAction = true;
					//onSenarioPrint = false;
				}
			}
			if (!isOnSelectAction)
				resetSenarioIndexData();
		}
	}
}

void NPC::selectActionUpdate()
{
	if (KEYMANAGER->isOnceKeyDown(P1_UP)) {
		SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
		if (curArrowY == SelectArrowY1)
			curArrowY = SelectArrowY2;
		else
			curArrowY = SelectArrowY1;
	}
	if (KEYMANAGER->isOnceKeyDown(P1_DOWN)) {
		SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
		if (curArrowY == SelectArrowY1)
			curArrowY = SelectArrowY2;
		else
			curArrowY = SelectArrowY1;
	}
	if (KEYMANAGER->isOnceKeyDown(P1_Z)) {
		SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
		resetSenarioIndexData();
		if (curArrowY == SelectArrowY1) {
			isOnAlphaEffect = true;
			isOnSelectAction = false;
			onSenarioPrint = true;
			senarioIndex = 0;
			curePocket();
			SOUNDMANAGER->pauseChannel(Channel::eChannelBgm);
			SOUNDMANAGER->playSound("pocketmonRecovery", Channel::eChannelEffect);
		}
		else {
			isOnAlphaEffect = false;
			isOnSelectAction = false;
			onSenarioPrint = true;
			senarioIndex = 0;
			isActivate = false;
		}
	}


}

void NPC::selectActionRender(HDC _hdc)
{
	m_SelectBox->render(_hdc, 620, 300);
	m_SelectPointer->render(_hdc, 640, curArrowY);
	UTIL::PrintText(_hdc, cureStr.c_str(), "소야바른9", 730, 390, 65, RGB(0, 0, 0), true);
	UTIL::PrintText(_hdc, noncureStr.c_str(), "소야바른9", 730, 460, 65, RGB(0, 0, 0), true);
}

void NPC::curePocket()
{
	for (auto& pocketMon : playerPokemons) {
		pocketMon->m_currentHp = pocketMon->m_maxHp;
		for (auto& skill : pocketMon->skillList) {
			skill.currentpp = skill.maxpp;
		}
	}
}

void NPC::alphaUpdate()
{
	if (isOnAlphaEffect) {
		if (negative) curAlpha -= 3;
		else curAlpha += 3;

		if (curAlpha == 255) {
			negative = true;
		}
		if (curAlpha == 0) {
			negative = false;
			completeAlphaEffect = true;
			isOnAlphaEffect = false;
			isActivate = false;
			SOUNDMANAGER->resumeChannel(Channel::eChannelBgm);
		}
	}
}

void NPC::updateShopEvent(float _deltaTime)
{
	SCENEMANAGER->scenePush("friendlyShop");
	isActivate = false;
}

void NPC::resetSenarioIndexData()
{
	pastTime = 0.f;

	firstOutStr = L"";
	secondOutStr = L"";

	completedFirstOut = false;
	completedSecondOut = false;

	firstStrIndex = 0;
	secondStrIndex = 0;
}

void NPC::updateDialArrowPosition()
{
	movedArrowDist += arrowDirection;
	m_DialCompleteArrowRect.move(0, arrowDirection);
	if (std::abs(movedArrowDist) == dialArrowDistLimit) {
		movedArrowDist = 0;
		arrowDirection = -arrowDirection;
	}
}

void NPC::update(float _deltaTime)
{
	CAMERAMANAGER->rectInCamera(m_outRect, m_absRect, isCanprint);
	if (!isActivate && isADHD) {
		if (UTIL::GetRndInt(100) <= 2)
			m_PrintDirection = (Direction)UTIL::GetRndInt(4);
	}
	if (isActivate && anoterEventType == NPCEventType::NPCShop) {
		updateShopEvent(_deltaTime);
	}
	else if (isActivate) {
		if (isOnAlphaEffect) {
			alphaUpdate();
			return;
		}
		if (onSenarioPrint && !isOnSelectAction) {
			updateSenario(_deltaTime);
			if (completedSecondOut)
				updateDialArrowPosition();
		}
		if (hasAnotherEvent && isOnSelectAction) {
			if (anoterEventType == NPCEventType::NPCPocketCenter)
				selectActionUpdate();
		}
	}
}

void NPC::render(HDC hdc)
{
	if (isCanprint)
	{
		m_Img[m_PrintDirection]->render(hdc, (m_outRect.left - 10), (m_outRect.top - 20) + 40, 0, 40, 80, 40);
	}
}

void NPC::afterRender(HDC hdc)
{
	if (isCanprint)
	{
		m_Img[m_PrintDirection]->render(hdc, (m_outRect.left - 10), (m_outRect.top - 20), 0, 0, 80, 40);
	}
	if (isActivate) {
		if (!isOnAlphaEffect) {
			if (onSenarioPrint)
			{
				m_Dialog->render(hdc, 20, WINSIZEY - 185);
				UTIL::PrintText(hdc, firstOutStr.c_str(), "소야바른9", 100, WINSIZEY - 160, 65, RGB(0, 0, 0), true);
				UTIL::PrintText(hdc, secondOutStr.c_str(), "소야바른9", 100, WINSIZEY - 90, 65, RGB(0, 0, 0), true);
				if (completedSecondOut && !isOnSelectAction)
					m_DialCopleteArrow->render(hdc, m_DialCompleteArrowRect.left, m_DialCompleteArrowRect.top);
			}
			if (isOnSelectAction) {
				selectActionRender(hdc);
			}
		}
	}
	if (isOnAlphaEffect) {
		alphaEffect->alphaRender(hdc, curAlpha);
	}
}

void NPC::debugRender(HDC hdc)
{
	if (isCanprint)
	{
		UTIL::DrawColorRect(hdc, m_outRect, RGB(123, 41, 78), true);
	}
}

void NPC::addSenario(std::string _scriptKey, Senario _senario)
{
	m_Scripts.insert({ _scriptKey, _senario });
}

void NPC::activateNPC(Direction _dir)
{
	isActivate = true;
	SOUNDMANAGER->playSound("Ok", Channel::eChannelEffect);
	switch (_dir)
	{
	case DirectionDown:
		m_PrintDirection = DirectionUp;
		break;
	case DirectionUp:
		m_PrintDirection = DirectionDown;
		break;
	case DirectionLeft:
		m_PrintDirection = DirectionRight;
		break;
	case DirectionRight:
		m_PrintDirection = DirectionLeft;
		break;
	}
	m_curSenario = (m_Scripts.find("default"))->second;

	senarioIndex = 0;
	if (anoterEventType != NPCEventType::NPCShop) {
		onSenarioPrint = true;
		playerPokemons = MAPMANGER->getPlayer()->getPocketmons();
	}
}