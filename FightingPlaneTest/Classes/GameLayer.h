#ifndef  __com__wangzhen__fightplane__gamelayer__h__
#define __com__wangzhen__fightplane__gamelayer__h__

#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"PlaneLayer.h"
#include"BulletLayer.h"
#include"EnemyLayer.h"
#include"Enemy.h"
#include"MultiBulletLayer.h"
#include"UFO.h"
#include"ControlLayer.h"

class GameLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene();
	CREATE_FUNC(GameLayer);
	virtual void update(float dt);
	virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent);
	virtual void registerWithTouchDispatcher();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();

public:
	static int getGameLevel();
	void initData();
	void moveBackground(float dt);
	CC_SYNTHESIZE(int, m_gameScore, GameScore);
	void checkNormalBulletCollisionToEnemy(BulletType type);
	void actorCollisionToEnemy();
	void actorDeadDone(Enemy* enmey, cocos2d::CCRect actorRect);
	void actorCollisionToSupplyTools();
	void actorCollisionToBigBoom();
	void updateBigBoomItem();
	void menuBombCallback(cocos2d::CCObject* obj);
	
private:
	cocos2d::CCMenu* bombMenu;
	cocos2d::CCLabelBMFont* bombLabel;
	cocos2d::CCSprite* m_bgSp1;
	cocos2d::CCSprite* m_bgSp2;
	PlaneLayer* m_plane;
	BulletLayer* m_bullet;
	EnemyLayer* m_enemyLayer;
	ControlLayer* m_controlLayer;
	MultiBulletLayer* m_multiBullet;
	UFOLayer* m_ufoLayer;
	static int m_gameLevel;
	int bigBoomCount;
};

#endif