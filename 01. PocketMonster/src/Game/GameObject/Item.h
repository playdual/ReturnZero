#pragma once
#include "Object.h"
#include "Common/SystemManagers.h"


class Item 
	: public Object
{
public:
	Item(ItemType _type /*, Image* _img*/,  UTIL::IRECT _rect, std::string _name,
		int _count, int _price, std::string _description);
	~Item();

protected:

   ItemType			m_type;				//
   Image*			m_img;			    // now not init Image
   UTIL::IRECT		m_iRect;			//
   std::string		m_ItemName;			// item Count
   int				m_count;			// 
   int				m_price;			//
   std::string		m_description;		//
	

public:
	virtual bool init() = 0;
	virtual void update(float _deltaTime) = 0;

	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;

	UTIL::IRECT getRect()	  { return m_iRect; }
	Image*		getImage()	  { return m_img; }
	int			getCount()	  { return m_count; }
	std::string getItemName() { return m_ItemName; }
	std::string getDescript() { return m_description; }

	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;
	 
private:
	

};

// 2020.02.04 item 
// 2020.02.04 item 
