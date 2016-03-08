#ifndef  __com__wangzhen__fightplane__multibulletlayer__h__
#define __com__wangzhen__fightplane__multibulletlayer__h__

//#include"cocos2d.h"
#include"BulletBase.h"

class MultiBulletLayer : public BulletBase
{
public:
	virtual bool init();
	MultiBulletLayer();
	~MultiBulletLayer();
	static MultiBulletLayer* createBullet();
	void addBullet(float dt);
	void startShoot();
	void stopShoot();
	void bulletFlyFinish(cocos2d::CCNode* node);
	void removeBullet(cocos2d::CCSprite* bullet);
	CC_SYNTHESIZE(cocos2d::CCArray*, m_allBullets, AllBullets);

private:
	cocos2d::CCSpriteBatchNode* m_multiBulletBatchNode;
};

#endif