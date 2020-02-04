#pragma once
#include "Object.h"



class Item
	: public Object
{
protected:
	std::string m_name;
	ITEM_TYPE m_type;

public:
	virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;

private:
	Image*			m_img;				//이미지
	UTIL::IRECT		m_iRect;			//상자(좌표값)
	std::string		m_name;				//이름
	int				m_count;			//개수
	int				m_price;			//가격
	int				m_healHp;			//Hp회복량
	int				m_hitDamage;		//데미지량
	int				m_addAtk;			//공격력 
	int				m_catchPercentage;	//포켓몬 잡는 확률
	std::string		m_description;		//설명
};

// 2020.02.04 item 클래스 상속해주는 클래스로 변경하기