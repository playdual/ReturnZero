#pragma once
#include "Game/GameObject/Item.h"

class SkillMachine
	: public Item
{
public:
	SkillMachine(ItemType _type , PockemonAttibute _kind/*, Image* _img*/, UTIL::IRECT _rect, std::string _name,
		int _count, int _price, std::string _description , int _damage);
	~SkillMachine();

	virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;


private:
	int m_damage;						// pokenMon skill damage
	PockemonAttibute pockemonKind;		// pokenMon Atiibute (Fire , Water, Grass)
};

