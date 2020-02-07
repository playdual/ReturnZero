#pragma once
#include "SystemObject/Animation.h"

class Image
{
public:
	enum IMAGE_LOAD_KIND {
		LOAD_RESOURCE,	//���ν� �ε�
		LOAD_FILE,		//���Ϸε�
		LOAD_EMPTY,		//�� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImage {
		DWORD		resID;
		HDC			hMemDC;		//�޸�
		HBITMAP		hBit;		//��Ʈ��
		HBITMAP		hOBit1;		//���� ��Ʈ��
		int			width;		//�̹��� ����
		int			height;		//�̹��� ����
		BYTE		loadType;
		float		x, y;
		int			currentFrameX;
		int			currentFrameY;
		int			maxFrameX;
		int			maxFrameY;
		int			FrameWidth;
		int			FrameHeight;


		tagImage() {
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit1 = NULL;
			x = 0.f;
			y = 0.f;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			FrameWidth = 0;
			FrameHeight = 0;
			width = 0;
			height = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

public:
	Image();
	~Image();
	void release();

public:
	//�̹��� ���Ϸ� �ʱ�ȭ
	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	HRESULT init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	void setTransColor(bool isTrans, COLORREF transColor);

	//�Ϲ� ����
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight);

	//������ ����
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//loop render
	void loopRender(HDC hdc, LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);
	
	//alpha render
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc,int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);
	void frameAlphaRender(HDC hdc, int destX, int destY, int frameX, int frameY, BYTE alpha);

	//animation render
	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	//이미지 핸들러
	HDC getMemDC()			{ return _imageInfo->hMemDC; }
	float getX()			{ return _imageInfo->x; }
	float getY()			{ return _imageInfo->y; }
	int getWidth()			{ return _imageInfo->width; }
	int getHeight()			{ return _imageInfo->height; }
	int getFrameWidth()		{ return _imageInfo->FrameWidth; }
	int getFrameHeight()	{ return _imageInfo->FrameHeight; }
	int getFrameX()			{ return _imageInfo->currentFrameX; }
	int getFrameY()			{ return _imageInfo->currentFrameY; }
	int getMaxFrameX()		{ return _imageInfo->maxFrameX; }
	int getMaxFrameY()		{ return _imageInfo->maxFrameY; }

	void setX(float x)		{ _imageInfo->x = x; }
	void setY(float y)		{ _imageInfo->y = y; }
	void setCenter(float x, float y) 
	{
		_imageInfo->x = x - (_imageInfo->width) / 2;
		_imageInfo->y = y - (_imageInfo->height) / 2;
	}
	void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	void setFrameY(int frameY) 
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	//BoudBox
	RECT getBoundingBox() {
		RECT rc = UTIL::RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char			_fileName[255];	//�̹��� �̸�
	bool			_isTrans;		//���� ������
	COLORREF		_transColor;	//���� ���� RGB

	BLENDFUNCTION	_blendFunc;		//���ĺ���带 ���� ����
	LPIMAGE_INFO	_blendImage;	//���� ����带 ����ϱ� ���� �̹���
};

