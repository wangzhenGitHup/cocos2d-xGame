#ifndef  __com__wangzhen__fightingplane__welcomelayer__h__
#define __com__wangzhen__fightingplane__welcomelayer__h__

#include"cocos2d.h"

class WelcomeLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(WelcomeLayer);

public:
	void loadingDone();
	bool isHaveSaveXml();
	void getHighestHistoryScore();
	void preLoadMusic();
};

#endif