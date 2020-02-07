#pragma once
#define PI		3.141592653
#define PI2		PI*2

namespace UTIL
{
	//실수형 점
	typedef struct _tagFpoint {
		_tagFpoint()
			: x(0), y(0)
		{}
		_tagFpoint(float _x, float _y)
			: x(_x), y(_y)
		{}
		_tagFpoint(const _tagFpoint& _point)
			: x(_point.x), y(_point.y)
		{}
		float x, y;
	}FPOINT, *PFPOINT;
	//원
	typedef struct _tagCircle {
		_tagCircle()
			: radius(0)
		{
			p.x = 0;
			p.y = 0;
		}
		_tagCircle(float _x, float _y, float _radius)
			: radius(_radius)
		{
			p.x = _x;
			p.y = _y;
		}
		_tagCircle(const POINT& _p, float _radius)
			: radius(_radius)
		{
			p.x = _p.x;
			p.y = _p.y;
		}
		_tagCircle(const _tagCircle& _circle)
			: radius(_circle.radius)
		{
			p.x = _circle.p.x;
			p.y = _circle.p.y;
		}
		POINT p;
		float radius;
	}Circle, *PCircle;
	//실수형 사각형(기능 미구현)
	typedef struct _tagFrect {
		float left, top, right, bottom;
	}FRECT, *PFRECT;
	//정수형 기능 사각형
	typedef struct _tagIrect {
		int left, top, right, bottom;
		int centerX, centerY;
		_tagIrect()
			:left(0), top(0), right(0), bottom(0), centerX(0), centerY(0)
		{}
		_tagIrect(int _left, int _top, int _right, int _bottom)
			: left(_left), top(_top), right(_right), bottom(_bottom)
		{
			alignment();
			setCenter();
		}
		_tagIrect(const _tagIrect& rect)
			: left(rect.left), top(rect.top), right(rect.right), bottom(rect.bottom)
		{
			alignment();
			setCenter();
		}
		_tagIrect(const RECT& rect)
			: left(rect.left), top(rect.top), right(rect.right), bottom(rect.bottom)
		{
			alignment();
			setCenter();
		}
		_tagIrect(const POINT& _pt1, const POINT& _pt2)
			: left(_pt1.x), top(_pt1.y), right(_pt2.x), bottom(_pt2.y)
		{
			alignment();
			setCenter();
		}
		void moveUp(int dist);
		void moveDown(int dist);
		void moveLeft(int dist);
		void moveRight(int dist);
		void move(int _dx, int _dy);
		void reset();
		void alignment();
		int getWidth();
		int getHeight();
		inline void operator=(const _tagIrect& rect) {
			left = rect.left;
			right = rect.right;
			top = rect.top;
			bottom = rect.bottom;
			alignment();
			centerX = rect.centerX;
			centerY = rect.centerY;
		}
		inline void operator=(const RECT& rect) {
			left = rect.left;
			right = rect.right;
			top = rect.top;
			bottom = rect.bottom;
			alignment();
			setCenter();
		}		
	private:
		void setCenter();
	}IRECT, *PIRECT;
	//IRECT operator override
	bool operator==(const IRECT& rect1, const IRECT& rect2);


//================= MATH FUNCTION =======================
	
	//랜덤값 가져오기
	int GetRndInt(int _zeroToNum);
	int GetRndIntFromTo(int _fromNum, int _toNum);
	float GetRndFloat(float _zeroToNum);
	float GetRndFloatFromTo(float _fromNum, float _toNum);

	//두점의 거리 구하기
	float GetDistance(int _startX, int _startY, int _endX, int _endY);
	float GetDistance(const POINT& _start, const POINT& _end);
	float GetDistance(const POINT& _start, int _endX, int _endY);
	float GetDistance(float _startX, float _startY, float _endX, float _endY);
	float GetDistance(const FPOINT& _start, const FPOINT& _end);
	float GetDistance(const FPOINT& _start, float _endX, float _endY);

	//두점의 각도 구하기
	float GetAngle(int _srcX, int _srcY, int _targetX, int _targetY);
	float GetAngle(POINT _src, POINT _target);
	float GetAngle(float _srcX, float _srcY, float _targetX, float _targetY);
	float GetAngle(FPOINT _src, FPOINT _target);


//================== MAKE FUNCTION ==========================
	//점 만들기
	POINT PointMake(int _x, int _y);
	FPOINT FPointMake(float _x, float _y);

	//원 만들기
	Circle MakeCircle(float _x, float _y, int _radius);

	//RECT만들기(좌상단 기준)
	RECT RectMake(int x, int y, int width, int height);
	RECT RectMakeCenter(int x, int y, int width, int height);
	FRECT FRectMake(float x, float y, float width, float height);
	FRECT FRectMakeCenter(float x, float y, float width, float height);
	IRECT IRectMake(int x, int y, int width, int height);
	IRECT IRectMakeCenter(int x, int y, int width, int height);

//================= Draw Function ==============================
	//선그리기
	void DrawLine(HDC _hdc, int _startX, int _startY, int _endX, int _endY);
	void DrawLine(HDC _hdc, const POINT& _start, const POINT& _end);
	void DrawLine(HDC _hdc, float _startX, float _startY, float _endX, float _endY);
	void DrawLine(HDC _hdc, const FPOINT& _start, const FPOINT& _end);

	//사각형 그리기
	void DrawRect(HDC _hdc, const RECT& _rect, bool _isTransParent = false);
	void DrawRect(HDC _hdc, const IRECT& _rect, bool _isTransParent = false);
	void DrawColorRect(HDC _hdc, const RECT& _rect, COLORREF _color = RGB(255, 255, 255), bool _cleanEdge = false);
	void DrawColorRect(HDC _hdc, const IRECT& _rect, COLORREF _color = RGB(255, 255, 255), bool _cleanEdge = false);

	//타원 그리기
	void DrawEllipse(HDC _hdc, int _x, int _y, int _width, int _height, bool _isTransParent = false);
	void DrawEllipse(HDC _hdc, const RECT& _rect, bool _isTransParent = false);
	void DrawEllipse(HDC _hdc, const IRECT& _rect, bool _isTransParent = false);
	void DrawColorEllipse(HDC _hdc, int _x, int _y, int _width, int _height, COLORREF _color = RGB(255, 255, 255), bool _cleanEdge = false);
	void DrawColorEllipse(HDC _hdc, const RECT& _rect, COLORREF _color = RGB(255, 255, 255), bool _cleanEdge = false);
	void DrawColorEllipse(HDC _hdc, const IRECT& _rect, COLORREF _color = RGB(255, 255, 255), bool _cleanEdge = false);

	//원 그리기
	void DrawCircle(HDC _hdc, const Circle& _circle, bool _isTransParent = false);
	void DrawColorCircle(HDC _hdc, const Circle& _circle, COLORREF _color = RGB(255, 255, 255), bool _cleanEdge = false);

	//Text 출력
	void PrintText(HDC _hdc, const char* _str, const char* _font, int _destX, int _destY, 
		int _fontSize = 20, COLORREF _fontColor = RGB(0, 0, 0), bool _isBgTransParent = false, COLORREF _bgColor = RGB(255, 255, 255));

//================== Collision Function ===========================
	//원과 원 충돌
	bool isCircleCircleCollision(const Circle& _circle1, const Circle& _circle2);

	//원과 사각형 충돌
	bool isCircleRectCollision(const Circle & _circle, RECT _rect);
	bool isCircleRectCollision(const Circle & _circle, FRECT _rect);
	bool isCircleRectCollision(const Circle & _circle, IRECT _rect);

	//원과 점 충돌
	bool isCirclePointCollision(const Circle & _circle, int _pointX, int _pointY);
	bool isCirclePointCollision(const Circle & _circle, const POINT& _point);

	//사각형과 사각형충돌
	bool isRectRectCollision(const RECT& _rect1, const RECT& _rect2);
	bool isRectRectCollision(const FRECT& _rect1, const FRECT& _rect2);
	bool isRectRectCollision(const IRECT& _rect1, const IRECT& _rect2);
	bool isRectRectCollision(const IRECT& _rect1, const RECT& _rect2);

	//점과 사각형 충돌
	bool isPointRectCollision(const POINT & point, const RECT& rect);
	bool isPointRectCollision(const POINT & point, const FRECT& rect);
	bool isPointRectCollision(const FPOINT & point, const RECT& rect);
	bool isPointRectCollision(const FPOINT & point, const FRECT& rect);
	bool isPointRectCollision(const POINT & point, const IRECT & rect);

	//픽셀충돌
	bool isPixelColorSame(HDC _targetImgDC, const int _x, const int _y, COLORREF _targetColor = RGB(255, 0, 255));
	bool isPixelColorSame(HDC _targetImgDC, const POINT& _destPos, COLORREF _targetColor = RGB(255, 0, 255));
	bool isRectColorSame(HDC _targetImgDC, const RECT& _rect, int _divisionX = 1, int _divisionY = 1, COLORREF _targetColor = RGB(255, 0, 255));
	bool isRectColorSame(HDC _targetImgDC, const IRECT& _rect, int _division = 1, int _divisionY = 1, COLORREF _targetColor = RGB(255, 0, 255));
}
