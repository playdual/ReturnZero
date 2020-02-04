#pragma once
#include "Object.h"

class Item
	: public Object
{
protected:
	std::string m_name;
	ITEM_TYPE m_type;
};