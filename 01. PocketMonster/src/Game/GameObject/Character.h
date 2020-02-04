#pragma once
#include "Object.h"

class Character
	: public Object
{
protected:
	std::string m_name;
	std::string m_customName;
	ITEM_TYPE m_type;
};