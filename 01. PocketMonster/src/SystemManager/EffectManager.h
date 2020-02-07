#pragma once
//ÀÌÆåÆ® Å¬·¡½º Àü¹æ¼±¾ğ
class Effect;

class EffectManager
{
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC _hdc);

	//ÀÌÆåÆ® Ãß°¡(Å°°ª, ÀÌ¹ÌÁö ÀÌ¸§, ÀÌ¹ÌÁö °¡·Î, ¼¼·Î, ÇÑÇÁ·¹ÀÓ °¡·Î, ¼¼·Î, FPS, ¼Óµµ, ¹öÆÛ°¹¼ö)
	void addEffect(std::string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);
	void play(std::string effectKey, int x, int y);
	bool getIsPlay();

private:
	//ÀÌÆåÆ® Å¬·¡½º ´ãÀº ³à¼®
	typedef std::vector<Effect*>vEffect;
	typedef std::vector<Effect*>::iterator viEffect;
	//ÀÌÆåÆ® Å¬·¡½º°¡ ´ã°ÜÁ® ÀÖ´Â º¤ÅÍ¸¦ ´ãÀº ³à¼®
	typedef std::map<std::string, vEffect> mEffect;
	typedef std::map<std::string, vEffect>::iterator miEffect;
	//¸ğµç ÀÌÆåÆ®¸¦ °ü¸®ÇÒ ³à¼®
	typedef std::vector<mEffect> vTotalEffect;
	typedef std::vector<mEffect>::iterator viTotalEffect;

	//½ÇÁ¦ ¸ğµç ÀÌÆåÆ®°¡ ´ã°ÜÁ® ÀÖ´Â ³à¼®
	vTotalEffect m_vTotalEffect;

	//í•˜ë‚˜ì˜ ì´íŒ©íŠ¸ê°€ êº¼ì§€ëŠ”ì§€ë¥¼ í™•ì¸í•´ì£¼ëŠ”ë° ì‚¬ìš©í•˜ëŠ” ë³€ìˆ˜
	viEffect vArrIterIsPlay;

private:
	DECLARE_SINGLE(EffectManager)
};

#define EFFECTMANAGER EffectManager::GetInst()