#pragma once
#include "Game/GameObject/Item.h"

class Postion
	: public Item
{
public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;


private:
     int	m_healHp;			//Hpȸ����
     int	m_hitDamage;		//��������

};

