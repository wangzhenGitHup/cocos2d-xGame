#ifndef  __com__wangzhen__fightplane__controllayer__h__
#define  __com__wangzhen__fightplane__controllayer__h__

#include"cocos2d.h"
#include"NoTouchLayer.h"

class ControlLayer : public cocos2d::CCLayer
{
public:
	ControlLayer();
	~ControlLayer();
	virtual bool init();
	static ControlLayer* createControlLayer();
	void menuCallback(cocos2d::CCObject* obj);
	void updateScore(int score);

private:
	cocos2d::CCLabelBMFont* scoreItem;
	cocos2d::CCMenuItemImage* pPauseItem;
	NoTouchLayer* noTouchLayer;
};

#endif