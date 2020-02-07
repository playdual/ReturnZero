#include "stdafx.h"
#include "PocketmonManager.h"

DEFINITION_SINGLE(PocketmonManager)

PocketmonManager::PocketmonManager()
{
}

PocketmonManager::~PocketmonManager()
{
}


HRESULT PocketmonManager::init()
{

	//std::shared_ptr<PocketMon> pocket = std::make_shared<PocketMon>();

	//pocket->m_state = true;
	////pocket->//m_pocketmonFrontImg;
	////pocket->//m_pocketmonBackImg;
	//pocket->m_name = "파이리";
	//pocket->m_customName = "영환리";
	////pocket->//m_Attribute;
	//pocket->gender = false;
	//pocket->m_level = 10;
	//pocket->m_maxHp = 29;
	//pocket->m_currentHp = 29;
	//pocket->m_atk = 15;
	//pocket->m_def = 13;
	//pocket->m_specialAtk = 17;
	//pocket->m_specialDef = 17;
	//pocket->m_dex = 19;
	//pocket->m_maxExp = 742;
	//pocket->m_currentExp = 0;
	//pocket->skill_1 = "불꽃세례";

	//playerPocketmonVector.push_back(pocket);

	//std::shared_ptr<PocketMon> pocket2 = std::make_shared<PocketMon>();

	//pocket2->m_state = true;
	////pocket->//m_pocketmonFrontImg;
	////pocket->//m_pocketmonBackImg;
	//pocket2->m_name = "파이리";
	//pocket2->m_customName = "적 영환리";
	////pocket->//m_Attribute;
	//pocket2->gender = false;
	//pocket2->m_level = 10;
	//pocket2->m_maxHp = 29;
	//pocket2->m_currentHp = 29;
	//pocket2->m_atk = 15;
	//pocket2->m_def = 13;
	//pocket2->m_specialAtk = 17;
	//pocket2->m_specialDef = 17;
	//pocket2->m_dex = 19;
	//pocket2->m_maxExp = 742;
	//pocket2->m_currentExp = 0;
	//pocket2->skill_1 = "불꽃세례";

	//wildPocketmonVector.push_back(pocket2);

	for (int i = 0; i < 2; i++)
	{
		std::shared_ptr<PocketMon> pocket = std::make_shared<PocketMon>();

		pocket->m_state = true;
		//pocket->//m_pocketmonFrontImg;
		//pocket->//m_pocketmonBackImg;
		pocket->m_name = "파이리";
		pocket->m_customName = "영환리";
		//pocket->//m_Attribute;
		pocket->gender = false;
		pocket->m_level = 10+i*10;
		pocket->m_maxHp = 29;
		pocket->m_currentHp = 29;
		pocket->m_atk = 15;
		pocket->m_def = 13;
		pocket->m_specialAtk = 17;
		pocket->m_specialDef = 17;
		pocket->m_dex = 19;
		pocket->m_maxExp = 742;
		pocket->m_currentExp = 0;
		pocket->skill_1 = "불꽃세례";

		if (i == 0) playerPocketmonVector.push_back(pocket);
		else if (i == 1) wildPocketmonVector.push_back(pocket);

	}

	return S_OK;
}

void PocketmonManager::release()
{
}

void PocketmonManager::update(float deltaTime)
{
}

void PocketmonManager::render(HDC hdc)
{
}

void PocketmonManager::afterRender(HDC hdc)
{
}

void PocketmonManager::debugRender(HDC hdc)
{
}

std::shared_ptr<PocketMon> PocketmonManager::getPlayerPocketmon()
{
	std::vector<std::shared_ptr<PocketMon>>::iterator it = playerPocketmonVector.begin();
	
	for (it = playerPocketmonVector.begin(); it != playerPocketmonVector.end(); ++it)
	{
		if ((*it)->getState())
		{
			return (*it);
		}
	}
	return std::shared_ptr<PocketMon>();
}

std::shared_ptr<PocketMon> PocketmonManager::getNpcPocketmon()
{
	return std::shared_ptr<PocketMon>();
}

std::shared_ptr<PocketMon> PocketmonManager::getWildPocketmon()
{
	std::vector<std::shared_ptr<PocketMon>>::iterator it = wildPocketmonVector.begin();

	for (it = wildPocketmonVector.begin(); it != wildPocketmonVector.end(); ++it)
	{
		if ((*it)->getState())
		{
			return (*it);
		}
	}
	return std::shared_ptr<PocketMon>();
}
