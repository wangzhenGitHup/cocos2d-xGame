#ifndef  __com__wangzhen__fightplane__ufo__h__
#define  __com__wangzhen__fightplane__ufo__h__

#include"cocos2d.h"

class UFOLayer : public cocos2d::CCLayer
{
public:
	UFOLayer();
	~UFOLayer();
	virtual bool init();
	static UFOLayer* createUFOLayer();

public:
	void addMultiBullets(float dt);
	void multiBulletsMoveFinished(cocos2d::CCNode* node);
	void addBigBoom(float dt);
	void bigBoomMoveFinished(cocos2d::CCNode* node);
	void removeMultiBullets(cocos2d::CCSprite* bullet);
	void removeBigBoom(cocos2d::CCSprite* bigBoom);
	CC_SYNTHESIZE(cocos2d::CCArray*, m_allMultiBulletArrays, AllMultiBulletArrays);
	CC_SYNTHESIZE(cocos2d::CCArray*, m_allBigBoomArrays, AllBigBoomArrays);
};
#endif