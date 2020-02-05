#pragma once
#include "Object.h"
#include "Common/SystemManagers.h"




class Item
	: public Object
{
protected:
	std::string m_name;
	ITEM_TYPE m_type;

public:
	virtual bool init() = 0;
	virtual void update(float _deltaTime) =0;

	virtual void render(HDC hdc) = 0;
	virtual void afterRender(HDC hdc) = 0;
	virtual void debugRender(HDC hdc) = 0;
	 
private:
	Image*			m_img;				//�̹���
	UTIL::IRECT		m_iRect;			//����(��ǥ��)
	std::string		m_itemName;				//�̸�
	int				m_count;			//����
	int				m_price;			//����
	int				m_healHp;			//Hpȸ����
	int				m_hitDamage;		//��������
	int				m_addAtk;			//���ݷ� 
	int				m_catchPercentage;	//���ϸ� ��� Ȯ��
	std::string		m_description;		//����
};

// 2020.02.04 item Ŭ���� ������ִ� Ŭ������ �����ϱ�
// 2020.02.04 item Ŭ���� ������ִ� Ŭ������ �����ϱ�
