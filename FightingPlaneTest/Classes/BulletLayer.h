#ifndef  __com__wangzhen__fightplane__bulletlayer__h__
#define __com__wangzhen__fightplane__bulletlayer__h__

//#include"cocos2d.h"
#include"BulletBase.h"

class BulletLayer : public BulletBase
{
public:
	virtual bool init();
	BulletLayer();
	~BulletLayer();
	static BulletLayer* createBullet();

public:
	void addBullet(float dt);
	void bulletFlyFinish(cocos2d::CCNode* node);
	void removeBullet(cocos2d::CCSprite* bullet);
	void startShoot(float dt = 0.0f);
	void stopShoot();
	CC_SYNTHESIZE(cocos2d::CCArray*, m_allBullets, AllBullets);

private:
	cocos2d::CCSpriteBatchNode* m_bulletBatchNode;
};

#endif