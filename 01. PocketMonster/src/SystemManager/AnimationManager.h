#pragma once
#include "SystemObject/Animation.h"

class AnimationManager
{
public:
	HRESULT init();
	void release();
	void update(float _deltatime = -1.f);
	void render();
	void deleteALL();

public:
	//泥섏쓬遺???앷퉴吏
	void addDefAnimation(std::string animationKeyName, char* imageKeyName, int fps, bool reverse = false, bool loop = false);
	//배열에 담아서
	void addAnimation(std::string animationKeyName, char* imageKeyName, int* playArr, int arrLen, float fps, bool loop = false);
	//구간
	void addAnimation(std::string animationKeyName, char* imageKeyName, int start, int end, float fps,bool reverse =  false, bool loop = false);
	Animation* findAnimation(std::string animationKeyName);

public:
	void start(std::string animationKeyName);
	void stop(std::string animationKeyName);
	void pause(std::string animationKeyName);
	void resume(std::string animationKeyName);

private:
	typedef std::map<std::string, Animation*> arrAnimation;
	arrAnimation _animation;

private:
	DECLARE_SINGLE(AnimationManager)
};

#define ANIMANAGER AnimationManager::GetInst()
