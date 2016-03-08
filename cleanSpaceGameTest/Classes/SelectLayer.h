#ifndef  __com__wangzhen__cleanspacegame__selectlayer__h__
#define  __com__wangzhen__cleanspacegame__selectlayer__h__

#include"cocos2d.h"

class SelectLayer : public cocos2d::CCLayer
{
public:
	static cocos2d::CCScene* scene();
	virtual bool init();
	CREATE_FUNC(SelectLayer);
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

public:
	void menuStartCallback(cocos2d::CCObject* obj);
	void menuSetCallback(cocos2d::CCObject* obj);
	void menuExitCallback(cocos2d::CCObject* obj);

};

#endif