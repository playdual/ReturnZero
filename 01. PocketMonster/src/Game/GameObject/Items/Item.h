#pragma once
#include "Game/GameObject/Object.h"

class Item 
	: public Object
{
public:
	Item(ItemType _type , class Image* _img,  UTIL::IRECT _rect, std::string _name,
		int _count, int _price, std::string _description);
	~Item();

public:

   ItemType			m_type;				//
   Image*			m_img = nullptr;	//
   UTIL::IRECT		m_iRect;			//
   std::string		m_ItemName;			// item Count
   int				m_count;			// 
   int				m_price;			//
   std::string		m_description;		//
   int				m_itemNum;

public:
	/*virtual bool init() override;
	virtual void update(float _deltaTime) override;

	virtual void render(HDC hdc) override;
	virtual void afterRender(HDC hdc) override;
	virtual void debugRender(HDC hdc) override;*/

	UTIL::IRECT getRect()	  { return m_iRect; }
	void		setRect(UTIL::IRECT _iRect) { m_iRect = _iRect; }
	Image*		getImage()	  { return m_img; }
  	int			getCount()	  { return m_count; }
	std::string getItemName() { return m_ItemName; }
	std::string getDescript() { return m_description; }
	int			getItemNum()  { return m_itemNum;  }

private:
	

};

// 2020.02.04 item 
// 2020.02.04 item 
