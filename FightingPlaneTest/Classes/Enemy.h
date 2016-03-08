#ifndef  __com__wangzhen__fightplane__enemy__h__
#define __com__wangzhen__fightplane__enemy__h__

#include"cocos2d.h"

class Enemy : public cocos2d::CCNode
{
public:
	Enemy();
	static Enemy* createEnemy();
	void bindSprite(cocos2d::CCSprite* sprite, int life);
	cocos2d::CCSprite* getSprite();
	int getLife();
	void loseLife();
	cocos2d::CCRect getBoundingBox();

private:
	cocos2d::CCSprite* m_sprite;
	int m_life;
};

#endif