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
	Image*			m_img;				//�̹���
	UTIL::IRECT		m_iRect;			//����(��ǥ��)
	std::string		m_name;				//�̸�
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
