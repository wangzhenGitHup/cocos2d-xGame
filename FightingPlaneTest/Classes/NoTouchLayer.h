#ifndef  __com__wangzhen__fightplane__notouchlayer__h__
#define  __com__wangzhen__fightplane__notouchlayer__h__

#include"cocos2d.h"

class NoTouchLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(NoTouchLayer);
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegn(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
};

#endif