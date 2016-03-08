#ifndef  __com__wangzhen__cleanspacegame__settinglayer__h__
#define  __com__wangzhen__cleanspacegame__settinglayer__h__

#include"cocos2d.h"

class SettingLayer : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(SettingLayer);

	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

public:
	void menuMusicCallback(cocos2d::CCObject* obj);
	void menuSoundCallback(cocos2d::CCObject* obj);
	void menuBackCallback(cocos2d::CCObject* obj);
};

#endif