#pragma once
#include "Item.h"
#include "Game/GameObject/Pocketmon/PocketMon.h"

class Inventory 
{
public:
	Inventory();
	~Inventory();

	bool init();
	void update(float _deltaTime);

	void render(HDC hdc);
	void afterRender(HDC hdc);
	void debugRender(HDC hdc);
	void importRender(HDC hdc);
	void pokeBallRender(HDC hdc);

	std::vector<std::shared_ptr<Item>> m_potionItem;
	std::vector<std::shared_ptr<Item>> m_pockeBallItem;
	std::vector<std::shared_ptr<Item>> m_importItem;

public :
	bool getCloseInven() { return m_isCloseInven; }
	bool getSameNameInven() { return m_isSameNameClose; }
	bool getitemCount() { return m_itemCount; }

	void setCloseInven(bool _isClose) { m_isCloseInven = _isClose; }
	void setSameNameInven(bool _isSame) { m_isSameNameClose = _isSame; }
	void setItemCount(int _itemCount) { m_itemCount = _itemCount; }
	
	void setItemTag(bool _isItemTag) {m_isItemTag = _isItemTag;}
	void setImportTag(bool _isImportTag) { m_isImportTag = _isImportTag;}
	void setPokeBallTag(bool _isPokeBallTag) { m_isPokeBallTag = _isPokeBallTag;}




	void itemTagInit();
	void ImportTagInit();
	void pocketBallTagInit();

	int  m_itemCount;
	bool m_itemInit;
	bool	m_isPokeBallInit;
	// 다른 태그로 넘어갔는지 체크 
	bool m_isItemTag;
	bool m_isImportTag;
	bool m_isPokeBallTag;

private:
	int		count;
	int		itemNum;
	int		insertNum;
	bool	m_isItemTagCheck;

	int		m_importNum;
	int		m_importCount;
	int		m_importPlaceCount;
	bool	m_isImportInit;   // 아이템 위치 값 초기화 하기
	bool	m_isImportTagCheck;

	int		m_pokeBallNum;
	int		m_pokeBallCount;
	int		m_pokePlaceCount;
	
	bool m_isCloseInven;
	bool m_isSameNameClose;

	//인벤 화살표시 이미지//

	Image* m_currentArrow;


	

	//bool	nextText;
};

