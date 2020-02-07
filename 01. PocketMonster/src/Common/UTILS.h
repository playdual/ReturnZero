#pragma once
#define PI		3.141592653
#define PI2		PI*2

namespace UTIL
{
	//�Ǽ��� ��
	typedef struct _tagFpoint {
		float x, y;
	}FPOINT, *PFPOINT;

	//��
	typedef struct _tagCircle {
		FPOINT p;
		int radius;
	}Circle, *PCircle;

	//�Ǽ��� �簢��
	typedef struct _tagFrect {
		float left, top, right, bottom;
	}FRECT, *PFRECT;

	//������ �簢��
	typedef struct _tagIrect {
		int left, top, right, bottom;
		int centerX, centerY;
		_tagIrect()
			:left(0), top(0), right(0), bottom(0)
		{}
		_tagIrect(int _left, int _top, int _right, int _bottom)
			: left(_left), top(_top), right(_right), bottom(_bottom)
		{
			centerX = left + (right - left) / 2;
			centerY = top + (bottom - top) / 2;
		}

		void moveUp(int dist);
		void moveDown(int dist);
		void moveLeft(int dist);
		void moveRight(int dist);
		void reset();
		void operator=(const _tagIrect& rect) {
			left = rect.left;
			right = rect.right;
			top = rect.top;
			bottom = rect.bottom;
			centerX = rect.centerX;
			centerY = rect.centerY;
		}
	}IRECT, *PIRECT;

	//������ ��������
	int getInt(int num);
	int getFromIntTo(int fromNum, int toNum);

	//�Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);
	//�� ������ ���� ���ϱ�
	float getAngle(float x1, float y1, float x2, float y2);

	//���浹
	bool isCircleCircleCollision(Circle& c1, Circle& c2);

	//�簢���� �簢���浹
	bool isRectRectCollision(const RECT & rect1, const RECT& rect2);
	bool isRectRectCollision(const RECT & rect1, const FRECT & rect2);
	bool isRectRectCollision(const FRECT & rect1, const FRECT & rect2);
	bool isRectRectCollision(const IRECT& rect1, const IRECT & rect2);
	bool isRectRectCollision(const IRECT& rect1, const RECT & rect2);

	//���� �簢�� �浹
	bool isPointRectCollision(const POINT & point, const RECT& rect);
	bool isPointRectCollision(const POINT & point, const FRECT& rect);
	bool isPointRectCollision(const FPOINT & point, const RECT& rect);
	bool isPointRectCollision(const FPOINT & point, const FRECT& rect);
	bool isPointRectCollision(const POINT & point, const IRECT & rect);


	bool isPixelColorSame(HDC _targetImgDC, const int _x, const int _y, COLORREF _targetColor = RGB(255, 0, 255));
	bool isPixelColorSame(HDC _targetImgDC, const POINT& _destPos, COLORREF _targetColor = RGB(255, 0, 255));

	bool isRectColorSame(HDC _targetImgDC, const RECT& rect, int _divisionX = 1, int _divisionY = 1, COLORREF _targetColor = RGB(255, 0, 255));
	bool isRectColorSame(HDC _targetImgDC, const IRECT& rect, int _division = 1, int _divisionY = 1, COLORREF _targetColor = RGB(255, 0, 255));


	//�� �����
	POINT PointMake(int x, int y);

	//RECT�����(�»�� ����)
	RECT RectMake(int x, int y, int width, int height);
	RECT RectMakeCenter(int x, int y, int width, int height);
	FRECT FRectMake(float x, float y, float width, float height);
	FRECT FRectMakeCenter(float x, float y, float width, float height);
	
	//���׸���
	void LineMake(HDC hdc, int x1, int y1, int x2, int y2);

	//�簢�� �׸���
	void RectangleMake(HDC hdc, int x, int y, int width, int height);
	void drawRect(HDC hdc, const RECT& rect);
	
	//�簢�� �׸���(�߽���)
	void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height);
	void DrawRect(HDC hdc, const RECT& rect);
	void drawRect(HDC hdc, const UTIL::IRECT & rect);

	//원그리기
	void EllipseMake(HDC hdc, int x, int y, int width, int height);
	void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height);

	//IRECT
	bool operator==(const IRECT& rect1, const IRECT& rect2);
	void DrawColorRect(HDC hdc, const IRECT& rect, bool _cleanEdge = false, COLORREF color = RGB(0, 0, 0));
	void DrawColorRect(HDC hdc, const RECT& rect, bool _cleanEdge = false, COLORREF color = RGB(0, 0, 0));
	void drawRect(HDC hdc, const UTIL::IRECT& rect);
	IRECT IRectMake(int x, int y, int width, int height);
	IRECT IRectMakeCenter(int x, int y, int width, int height);
}
