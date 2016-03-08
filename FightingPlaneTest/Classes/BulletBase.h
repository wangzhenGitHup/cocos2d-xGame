#ifndef  __com__wangzhen__fightplane__bulletbase__h__
#define __com__wangzhen__fightplane__bulletbase__h__

#include"cocos2d.h"

class BulletBase : public cocos2d::CCNode
{
public:
	BulletBase();
	~BulletBase();
	virtual bool init();
	virtual void addBullet(float dt);
	virtual void startShoot(float dt = 0.0f);
	virtual void stopShoot();
	virtual void bulletFlyFinish(cocos2d::CCNode* node);
	virtual void removeBullet(cocos2d::CCSprite* bullet);
	CC_SYNTHESIZE(cocos2d::CCArray*, m_allBullets, AllBullets);
};

#endif