#include "stdafx.h"
#include "UTILS.h"

namespace UTIL
{
	//IRECT Method
	bool operator==(const IRECT& rect1, const IRECT& rect2) {
		if (rect1.centerX == rect2.centerX && rect1.centerY == rect2.centerY)
			return true;
		return false;
	}
	void _tagIrect::moveUp(int dist) {
		top -= dist;
		bottom -= dist;
		centerY -= dist;
	}
	void _tagIrect::moveDown(int dist) {
		top += dist;
		bottom += dist;
		centerY += dist;
	}
	void _tagIrect::moveLeft(int dist) {
		left -= dist;
		right -= dist;
		centerX -= dist;
	}
	void _tagIrect::moveRight(int dist) {
		left += dist;
		right += dist;
		centerX += dist;
	}
	void _tagIrect::move(int _dx, int _dy)
	{
		left += _dx;
		top += _dy;
		right += _dx;
		bottom += _dy;
		centerX += _dx;
		centerY += _dy;
	}
	int _tagIrect::getWidth()
	{
		return right - left;
	}
	int _tagIrect::getHeight()
	{
		return bottom - top;
	}
	void _tagIrect::setCenter()
	{
		centerX = left + (right - left) / 2;
		centerY = top + (bottom - top) / 2;
	}
	void _tagIrect::reset() {
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
		centerX = 0;
		centerY = 0;
	}
	void _tagIrect::alignment()
	{
		if (left > right)
			std::swap(left, right);
		if (top > bottom)
			std::swap(top, bottom);
	}

	//?úÎç§Í∞?Í∞Ä?∏Ïò§Í∏?
	int GetRndInt(int _zeroToNum)
	{
		return rand() % _zeroToNum;
	}
	int GetRndIntFromTo(int _fromNum, int _toNum)
	{
		if (_fromNum > _toNum)
			std::swap(_toNum, _fromNum);
		return rand() % (_toNum - _fromNum + 1) + _fromNum;
	}
	float GetRndFloat(float _zeroToNum)
	{
		return rand() / (float)RAND_MAX * _zeroToNum;
	}

	float GetRndFloatFromTo(float _fromNum, float _toNum)
	{
		if (_fromNum > _toNum)
			std::swap(_toNum, _fromNum);
		return rand() / (float)RAND_MAX * (_toNum - _fromNum) + _fromNum;
	}

	//???êÏÇ¨?¥Ïùò Í±∞Î¶¨ Íµ¨ÌïòÍ∏?
	float GetDistance(int startX, int startY, int endX, int endY)
	{
		int x = endX - startX;
		int y = endY - startY;
		return sqrtf(x * x + y * y);
	}
	float GetDistance(const POINT & start, const POINT & end)
	{
		int x = end.x - start.x;
		int y = end.y - start.y;
		return sqrtf(x * x + y * y);
	}
	float GetDistance(const POINT & _start, int _endX, int _endY)
	{
		int x = _endX - _start.x;
		int y = _endY - _start.y;
		return sqrtf(x * x + y * y);
	}
	float GetDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;
		return sqrtf(x * x + y * y);
	}
	float GetDistance(const FPOINT & start, const FPOINT & end)
	{
		float x = end.x - start.x;
		float y = end.y - start.y;
		return sqrtf(x * x + y * y);
	}

	float GetDistance(const FPOINT & _start, float _endX, float _endY)
	{
		float x = _endX - _start.x;
		float y = _endY - _start.y;
		return sqrtf(x * x + y * y);
	}

	//???êÏÇ¨?¥Ïùò Í∞ÅÎèÑ Íµ¨ÌïòÍ∏?
	float GetAngle(int _srcX, int _srcY, int _targetX, int _targetY)
	{
		float dx = _srcX - _targetX;
		float dy = _srcY - _targetY;
		float angle = 0.f;
		float distance = sqrtf(dx * dx + dy * dy);

		if (dx < 0 && dy < 0)
			angle = PI2 - acosf(dx / distance);
		if (dx < 0 && dy > 0)
			angle = PI + acosf(dx / distance);
		if (dx > 0 && dy > 0)
			angle = acosf(dx / distance);
		if (dx > 0 && dy < 0)
			angle = PI - acosf(dx / distance);

		return angle;
	}
	float GetAngle(POINT _src, POINT _target)
	{
		float dx = _src.x - _target.x;
		float dy = _src.y - _target.y;
		float angle = 0.f;
		float distance = sqrtf(dx * dx + dy * dy);

		if (dx < 0 && dy < 0)
			angle = PI2 - acosf(dx / distance);
		if (dx < 0 && dy > 0)
			angle = PI + acosf(dx / distance);
		if (dx > 0 && dy > 0)
			angle = acosf(dx / distance);
		if (dx > 0 && dy < 0)
			angle = PI - acosf(dx / distance);

		return angle;
	}
	float GetAngle(float _srcX, float _srcY, float _targetX, float _targetY)
	{
		float dx = _srcX - _targetX;
		float dy = _srcY - _targetY;
		float angle = 0.f;
		float distance = sqrtf(dx * dx + dy * dy);

		if (dx < 0 && dy < 0)
			angle = PI2 - acosf(dx / distance);
		if (dx < 0 && dy > 0)
			angle = PI + acosf(dx / distance);
		if (dx > 0 && dy > 0)
			angle = acosf(dx / distance);
		if (dx > 0 && dy < 0)
			angle = PI - acosf(dx / distance);

		return angle;
	}
	float GetAngle(FPOINT _src, FPOINT _target)
	{
		float dx = _src.x - _target.x;
		float dy = _src.y - _target.y;
		float angle = 0.f;
		float distance = sqrtf(dx * dx + dy * dy);

		if (dx < 0 && dy < 0)
			angle = PI2 - acosf(dx / distance);
		if (dx < 0 && dy > 0)
			angle = PI + acosf(dx / distance);
		if (dx > 0 && dy > 0)
			angle = acosf(dx / distance);
		if (dx > 0 && dy < 0)
			angle = PI - acosf(dx / distance);

		return angle;
	}

	//?êÎßå?§Í∏∞
	POINT PointMake(int x, int y)
	{
		POINT pt = { x ,y };
		return pt;
	}
	FPOINT FPointMake(float _x, float _y)
	{
		return FPOINT(_x, _y);
	}

	//??ÎßåÎì§Í∏?
	Circle MakeCircle(float _x, float _y, int _radius)
	{
		return Circle(_x, _y, _radius);
	}

	//?¨Í∞Å??ÎßåÎì§Í∏?
	RECT RectMake(int x, int y, int width, int height)
	{
		RECT rc = { x,y, x + width, y + height };
		return rc;
	}
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}
	IRECT IRectMake(int x, int y, int width, int height)
	{
		IRECT rc( x,y, x + width, y + height );
		return rc;
	}
	IRECT IRectMakeCenter(int x, int y, int width, int height)
	{
		IRECT rc(x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		return rc;
	}
	FRECT FRectMake(float x, float y, float width, float height)
	{
		FRECT rc = { x,y, x + width, y + height };
		return rc;
	}
	FRECT FRectMakeCenter(float x, float y, float width, float height)
	{
		FRECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}

	//?†Í∑∏Î¶¨Í∏∞
	void DrawLine(HDC _hdc, int _startX, int _startY, int _endX, int _endY)
	{
		MoveToEx(_hdc, _startX, _startY, NULL);
		LineTo(_hdc, _endX, _endY);
	}
	void DrawLine(HDC _hdc, const POINT & _start, const POINT & _end)
	{
		MoveToEx(_hdc, _start.x, _start.y, NULL);
		LineTo(_hdc, _end.x, _end.y);
	}
	void DrawLine(HDC _hdc, float _startX, float _startY, float _endX, float _endY)
	{
		MoveToEx(_hdc, _startX, _startY, NULL);
		LineTo(_hdc, _endX, _endY);
	}
	void DrawLine(HDC _hdc, const FPOINT & _start, const FPOINT & _end)
	{
		MoveToEx(_hdc, _start.x, _start.y, NULL);
		LineTo(_hdc, _end.x, _end.y);
	}

	//?¨Í∞Å??Í∑∏Î¶¨Í∏?
	void DrawRect(HDC _hdc, const RECT & _rect, bool _isTransParent)
	{
		HBRUSH oldBrush;
		if (_isTransParent)
			oldBrush = (HBRUSH)SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		Rectangle(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		if (_isTransParent)
			SelectObject(_hdc, oldBrush);
	}
	void DrawRect(HDC _hdc, const IRECT & _rect, bool _isTransParent)
	{
		HBRUSH oldBrush;
		if (_isTransParent)
			oldBrush = (HBRUSH)SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		Rectangle(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		if (_isTransParent)
			SelectObject(_hdc, oldBrush);

	}
	void DrawColorRect(HDC _hdc, const RECT & _rect, COLORREF _color, bool _cleanEdge)
	{
		HBRUSH oldBrush, curBrush;
		HGDIOBJ oldPen;
		curBrush = CreateSolidBrush(_color);
		oldBrush = (HBRUSH)SelectObject(_hdc, curBrush);
		SelectObject(_hdc, curBrush);

		if (_cleanEdge)
			oldPen = SelectObject(_hdc, GetStockObject(NULL_PEN));

		Rectangle(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		SelectObject(_hdc, oldBrush);
		if (_cleanEdge)
			SelectObject(_hdc, oldPen);
		DeleteObject(curBrush);
	}
	void DrawColorRect(HDC _hdc, const IRECT & _rect, COLORREF _color, bool _cleanEdge)
	{
		HBRUSH oldBrush, curBrush;
		HGDIOBJ oldPen;
		curBrush = CreateSolidBrush(_color);
		oldBrush = (HBRUSH)SelectObject(_hdc, curBrush);
		SelectObject(_hdc, curBrush);

		if (_cleanEdge)
			oldPen = SelectObject(_hdc, GetStockObject(NULL_PEN));

		Rectangle(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		SelectObject(_hdc, oldBrush);
		if (_cleanEdge)
			SelectObject(_hdc, oldPen);
		DeleteObject(curBrush);
	}

	//?Ä??Í∑∏Î¶¨Í∏?
	void DrawEllipse(HDC _hdc, int _x, int _y, int _width, int _height, bool _isTransParent)
	{
		HBRUSH oldBrush;
		if (_isTransParent)
			oldBrush = (HBRUSH)SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		Ellipse(_hdc, _x, _y, _x + _width, _y + _height);

		if (_isTransParent)
			SelectObject(_hdc, oldBrush);
	}
	void DrawEllipse(HDC _hdc, const RECT & _rect, bool _isTransParent)
	{
		HBRUSH oldBrush;
		if (_isTransParent)
			oldBrush = (HBRUSH)SelectObject(_hdc, GetStockObject(NULL_BRUSH));


		Ellipse(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		if (_isTransParent)
			SelectObject(_hdc, oldBrush);
		
	}
	void DrawEllipse(HDC _hdc, const IRECT & _rect, bool _isTransParent)
	{
		HBRUSH oldBrush, curBrush;
		if (_isTransParent)
			oldBrush = (HBRUSH)SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		Ellipse(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		if (_isTransParent) 
			SelectObject(_hdc, oldBrush);
	}
	void DrawColorEllipse(HDC _hdc, int _x, int _y, int _width, int _height, COLORREF _color, bool _cleanEdge)
	{
		HBRUSH oldBrush, curBrush;
		HGDIOBJ oldPen;
		curBrush = CreateSolidBrush(_color);
		oldBrush = (HBRUSH)SelectObject(_hdc, curBrush);
		SelectObject(_hdc, curBrush);

		if (_cleanEdge)
			oldPen = SelectObject(_hdc, GetStockObject(NULL_PEN));

		Ellipse(_hdc, _x, _y, _x + _width, _y + _height);

		SelectObject(_hdc, oldBrush);
		if (_cleanEdge)
			SelectObject(_hdc, oldPen);
		DeleteObject(curBrush);
	}
	void DrawColorEllipse(HDC _hdc, const RECT & _rect, COLORREF _color, bool _cleanEdge)
	{
		HBRUSH oldBrush, curBrush;
		HGDIOBJ oldPen;
		curBrush = CreateSolidBrush(_color);
		oldBrush = (HBRUSH)SelectObject(_hdc, curBrush);
		SelectObject(_hdc, curBrush);

		if (_cleanEdge)
			oldPen = SelectObject(_hdc, GetStockObject(NULL_PEN));

		Ellipse(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		SelectObject(_hdc, oldBrush);
		if (_cleanEdge)
			SelectObject(_hdc, oldPen);
		DeleteObject(curBrush);
	}
	void DrawColorEllipse(HDC _hdc, const IRECT & _rect, COLORREF _color, bool _cleanEdge)
	{
		HBRUSH oldBrush, curBrush;
		HGDIOBJ oldPen;
		curBrush = CreateSolidBrush(_color);
		oldBrush = (HBRUSH)SelectObject(_hdc, curBrush);
		SelectObject(_hdc, curBrush);

		if (_cleanEdge)
			oldPen = SelectObject(_hdc, GetStockObject(NULL_PEN));

		Ellipse(_hdc, _rect.left, _rect.top, _rect.right, _rect.bottom);

		SelectObject(_hdc, oldBrush);
		if (_cleanEdge)
			SelectObject(_hdc, oldPen);
		DeleteObject(curBrush);
	}

	//??Í∑∏Î¶¨Í∏?
	void DrawCircle(HDC _hdc, const Circle & _circle, bool _isTransParent)
	{
		HBRUSH oldBrush, curBrush;
		if (_isTransParent)
			oldBrush = (HBRUSH)SelectObject(_hdc, GetStockObject(NULL_BRUSH));

		Ellipse(_hdc, _circle.p.x - _circle.radius, _circle.p.y - _circle.radius,
			_circle.p.x + _circle.radius, _circle.p.y + _circle.radius);

		if (_isTransParent) 
			DeleteObject(curBrush);
	}
	void DrawColorCircle(HDC _hdc, const Circle & _circle, COLORREF _color, bool _cleanEdge)
	{
		HBRUSH oldBrush, curBrush;
		HGDIOBJ oldPen;
		curBrush = CreateSolidBrush(_color);
		oldBrush = (HBRUSH)SelectObject(_hdc, curBrush);
		SelectObject(_hdc, curBrush);

		if (_cleanEdge)
			oldPen = SelectObject(_hdc, GetStockObject(NULL_PEN));

		Ellipse(_hdc, _circle.p.x - _circle.radius, _circle.p.y - _circle.radius, 
			_circle.p.x + _circle.radius, _circle.p.y + _circle.radius);

		SelectObject(_hdc, oldBrush);
		if (_cleanEdge)
			SelectObject(_hdc, oldPen);
		DeleteObject(curBrush);
	}

	//?çÏä§??Ï∂úÎ†•
	void PrintText(HDC _hdc, char* _str, char * _font, int _destX, int _destY, 
		int _fontSize, COLORREF _fontColor, bool _isBgTransParent, COLORREF _bgColor)
	{
		HFONT curFont, oldFont;
		COLORREF oldBkColor, oldFontColor;
		int len = strlen(_str);
		if (_fontColor != RGB(0, 0, 0))
			oldFontColor = SetTextColor(_hdc, _fontColor);
		if (_bgColor != RGB(255, 255, 255))
			oldBkColor = SetBkColor(_hdc, _bgColor);
		if (_isBgTransParent)
			SetBkMode(_hdc, TRANSPARENT);
		else 
			SetBkMode(_hdc, OPAQUE);

		curFont = CreateFont(_fontSize, 0, 0, 0, FW_DONTCARE,
			FALSE, FALSE, FALSE, DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
			FF_DONTCARE, _font
		);

		oldFont = (HFONT)SelectObject(_hdc, curFont);
		TextOut(_hdc, _destX, _destY, _str, len);
		SelectObject(_hdc, oldFont);

		DeleteObject(curFont);
		if (_fontColor != RGB(0, 0, 0))
			SetTextColor(_hdc, oldFontColor);
		if (_bgColor != RGB(255, 255, 255))
			SetBkColor(_hdc, oldBkColor);		
		if (_isBgTransParent)
			SetBkMode(_hdc, OPAQUE);		
	}

	//?êÍ≥º ??Ï∂©Îèå
	bool isCircleCircleCollision(const Circle& _circle1, const Circle& _circle2) 
	{
		float dist = GetDistance(_circle1.p, _circle2.p);
		if (dist <= _circle1.radius + _circle2.radius)
			return true;
		return false;
	}

	//?êÍ≥º ?¨Í∞Å??Ï∂©Îèå
	bool isCircleRectCollision(const Circle & _circle, RECT _rect)
	{
		_rect.left -= _circle.radius;
		_rect.top -= _circle.radius;
		_rect.right += _circle.radius;
		_rect.bottom += _circle.radius;
		if (_rect.left <= _circle.p.x  && _circle.p.x <= _rect.right)
			if (_rect.top <= _circle.p.y  && _circle.p.y <= _rect.bottom)
				return true;
		return false;
	}
	bool isCircleRectCollision(const Circle & _circle, FRECT _rect)
	{
		_rect.left -= _circle.radius;
		_rect.top -= _circle.radius;
		_rect.right += _circle.radius;
		_rect.bottom += _circle.radius;
		if (_rect.left <= _circle.p.x  && _circle.p.x <= _rect.right)
			if (_rect.top <= _circle.p.y  && _circle.p.y <= _rect.bottom)
				return true;
		return false;
	}
	bool isCircleRectCollision(const Circle & _circle, IRECT _rect)
	{
		_rect.left -= _circle.radius;
		_rect.top -= _circle.radius;
		_rect.right += _circle.radius;
		_rect.bottom += _circle.radius;
		if (_rect.left <= _circle.p.x  && _circle.p.x <= _rect.right)
			if (_rect.top <= _circle.p.y  && _circle.p.y <= _rect.bottom)
				return true;
		return false;
	}
	bool isCirclePointCollision(const Circle & _circle, int _pointX, int _pointY)
	{
		float dist = GetDistance(_circle.p, _pointX, _pointY);
		if (dist <= _circle.radius)
			return true;
		return false;
	}

	//?êÍ≥º ??Ï∂©Îèå
	bool isCirclePointCollision(const Circle & _circle, const POINT& _point)
	{
		float dist = GetDistance(_circle.p, _point);
		if (dist <= _circle.radius)
			return true;
		return false;
	}


	//?¨Í∞Å?ïÍ≥º ?¨Í∞Å??Ï∂©Îèå
	bool isRectRectCollision(const RECT & rect1, const RECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}
	bool isRectRectCollision(const RECT & rect1, const FRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}
	bool isRectRectCollision(const FRECT & rect1, const FRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}
	bool isRectRectCollision(const IRECT & rect1, const IRECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}
	bool isRectRectCollision(const IRECT & rect1, const RECT & rect2)
	{
		if (rect1.left < rect2.right && rect1.right > rect2.left &&
			rect1.top < rect2.bottom && rect1.bottom > rect2.top) {
			return true;
		}
		return false;
	}

	//?¨Í∞Å?ïÍ≥º ??Ï∂©Îèå
	bool isPointRectCollision(const POINT & point, const RECT & rect)
	{
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}
	bool isPointRectCollision(const POINT & point, const FRECT & rect)
	{
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}
	bool isPointRectCollision(const FPOINT & point, const RECT& rect) {
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}
	bool isPointRectCollision(const FPOINT & point, const FRECT& rect) {
		if ((rect.left < point.x && point.x < rect.right) &&
			(rect.top < point.y && point.y < rect.bottom))
			return true;
		return false;
	}
	bool isPointRectCollision(const POINT & point, const IRECT & rect)
	{
		if ((rect.left <= point.x && point.x <= rect.right) &&
			(rect.top <= point.y && point.y <= rect.bottom))
			return true;
		return false;
	}

	//?ΩÏ? Ï∂©Îèå
	bool isPixelColorSame(HDC _targetImgDC, const POINT & _destPos, COLORREF _targetColor)
	{
		COLORREF originColor = GetPixel(_targetImgDC, _destPos.x, _destPos.y);

		if (originColor != _targetColor)
			return false;
		return true;
	}
	bool isPixelColorSame(HDC _targetImgDC, const int _x, const int _y, COLORREF _targetColor)
	{
		COLORREF originColor = GetPixel(_targetImgDC, _x, _y);

		if (originColor != _targetColor)
			return false;
		return true;
	}
	bool isRectColorSame(HDC _targetImgDC, const RECT& rect, int _divisionX, int _divisionY, COLORREF _targetColor)
	{
		assert(_divisionX >= 0);
		assert(_divisionY >= 0);

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		float divisionWidth = width / _divisionX;
		float divisionHeight = height / _divisionY;


		for (float i = rect.left; i <= rect.right; i += divisionWidth) {
			for (float j = rect.top; j <= rect.bottom; j += divisionHeight) {
				COLORREF originColor = GetPixel(_targetImgDC, i, j);
				if (originColor != _targetColor)
					return false;
			}
		}
		return true;
	}
	bool isRectColorSame(HDC _targetImgDC, const IRECT& rect, int _divisionX, int _divisionY, COLORREF _targetColor)
	{
		assert(_divisionX >= 0);
		assert(_divisionY >= 0);

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		float divisionWidth = width / _divisionX;
		float divisionHeight = height / _divisionY;


		for (float i = rect.left; i <= rect.right; i += divisionWidth) {
			for (float j = rect.top; j <= rect.bottom; j += divisionHeight) {
				COLORREF originColor = GetPixel(_targetImgDC, i, j);
				if (originColor != _targetColor)
					return false;
			}
		}
		return true;
	}
}
