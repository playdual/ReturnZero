#pragma once
#define PI		3.141592653
#define PI2		PI*2

namespace UTIL
{
	//?ㅼ닔????
	typedef struct _tagFpoint {
		float x, y;
	}FPOINT, *PFPOINT;

	//??
	typedef struct _tagCircle {
		FPOINT p;
		int radius;
	}Circle, *PCircle;

	//?ㅼ닔???ш컖??
	typedef struct _tagFrect {
		float left, top, right, bottom;
	}FRECT, *PFRECT;

	//?뺤닔???ш컖??
	typedef struct _tagIrect {
		int left, top, right, bottom;
		_tagIrect()
			:left(0), top(0), right(0), bottom(0)
		{}
		_tagIrect(int _left, int _top, int _right, int _bottom)
			: left(_left), top(_top), right(_right), bottom(_bottom)
		{}

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
		}
	}IRECT, *PIRECT;

	//?쒕뜡媛?媛?몄삤湲?
	int getInt(int num);
	int getFromIntTo(int fromNum, int toNum);

	//嫄곕━
	float getDistance(float startX, float startY, float endX, float endY);
	//???먯쑝濡?媛곷룄 援ы븯湲?
	float getAngle(float x1, float y1, float x2, float y2);

	//?먯땐??
	bool isCircleCircleCollision(Circle& c1, Circle& c2);

	//?ш컖?뺢낵 ?ш컖?뺤땐??
	bool isRectRectCollision(const RECT & rect1, const RECT& rect2);
	bool isRectRectCollision(const RECT & rect1, const FRECT & rect2);
	bool isRectRectCollision(const FRECT & rect1, const FRECT & rect2);
	bool isRectRectCollision(const IRECT& rect1, const IRECT & rect2);
	bool isRectRectCollision(const IRECT& rect1, const RECT & rect2);

	//?먭낵 ?ш컖??異⑸룎
	bool isPointRectCollision(const POINT & point, const RECT& rect);
	bool isPointRectCollision(const POINT & point, const FRECT& rect);
	bool isPointRectCollision(const FPOINT & point, const RECT& rect);
	bool isPointRectCollision(const FPOINT & point, const FRECT& rect);
	bool isPointRectCollision(const POINT & point, const IRECT & rect);


	bool isPixelColorSame(HDC _targetImgDC, const int _x, const int _y, COLORREF _targetColor = RGB(255, 0, 255));
	bool isPixelColorSame(HDC _targetImgDC, const POINT& _destPos, COLORREF _targetColor = RGB(255, 0, 255));

	bool isRectColorSame(HDC _targetImgDC, const RECT& rect, int _divisionX = 1, int _divisionY = 1, COLORREF _targetColor = RGB(255, 0, 255));
	bool isRectColorSame(HDC _targetImgDC, const IRECT& rect, int _division = 1, int _divisionY = 1, COLORREF _targetColor = RGB(255, 0, 255));


	//??留뚮뱾湲?
	POINT PointMake(int x, int y);

	//RECT留뚮뱾湲?醫뚯긽??湲곗?)
	RECT RectMake(int x, int y, int width, int height);
	RECT RectMakeCenter(int x, int y, int width, int height);
	FRECT FRectMake(float x, float y, float width, float height);
	FRECT FRectMakeCenter(float x, float y, float width, float height);
	
	//?좉렇由ш린
	void LineMake(HDC hdc, int x1, int y1, int x2, int y2);

	//?ш컖??洹몃━湲?
	void RectangleMake(HDC hdc, int x, int y, int width, int height);
	void drawRect(HDC hdc, const RECT& rect);
	
	//?ш컖??洹몃━湲?以묒떖??
	void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height);
	void DrawRect(HDC hdc, const RECT& rect);
	
	//?먭렇由ш린
	void EllipseMake(HDC hdc, int x, int y, int width, int height);
	void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height);

	//IRECT
	bool operator==(const IRECT& rect1, const IRECT& rect2);
	void DrawColorRect(HDC hdc, const IRECT& rect, bool _cleanEdge = false, COLORREF color = RGB(0, 0, 0));
	void DrawColorRect(HDC hdc, const RECT& rect, bool _cleanEdge = false, COLORREF color = RGB(0, 0, 0));
	void drawRect(HDC hdc, const UTIL::IRECT& rect);
	IRECT IRectMake(int x, int y, int width, int height);
	IRECT IRectMakeCenter(int x, int y, int width, int height);

	void BeginSolidColor(HDC hdc, HBRUSH* brush, COLORREF color);

}