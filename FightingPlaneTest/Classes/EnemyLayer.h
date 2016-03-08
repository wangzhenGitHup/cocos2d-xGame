#ifndef  __com__wangzhen__fightplane__enemylayer__h__
#define __com__wangzhen__fightplane__enemylayer__h__

#include"cocos2d.h"
#include"Enemy.h"
#include"global.h"

class EnemyLayer : public cocos2d::CCLayer
{
public:
	EnemyLayer();
	~EnemyLayer();
	virtual bool init();
	static EnemyLayer* createEnemyLayer();

public:
	void addEnemy(EnemyType type);
	void enemyMoveFinish(EnemyType type, cocos2d::CCNode* node);
	void enemyBlowEffect(EnemyType type, Enemy* enemy);

	void addEnemyOne(float dt);
	void enemyOneMoveFinish(cocos2d::CCNode* node);
	void enemyOneBlowEffect(Enemy* enemy);
	void removeEnemyOne(cocos2d::CCNode* node, void* data);
	void removeAllEnemyOne();

	void addEnemySecond(float dt);
	void enemySecondMoveFinish(cocos2d::CCNode* node);
	void enemySecondBlowEffect(Enemy*enemy);
	void removeEnemySecond(cocos2d::CCNode* node, void* data);
	void removeAllEnemySecond();

	void addEnemyThird(float dt);
	void enemyThirdMoveFinish(cocos2d::CCNode* node);
	void enemyThirdBlowEffect(Enemy* enemy);
	void removeEnemyThird(cocos2d::CCNode* node, void* data);
	void removeAllEnemyThird();
	int getCurrentGameLevel();

	CC_SYNTHESIZE(cocos2d::CCArray*, m_enemyOneArrays, EnemyOneArrays);
	CC_SYNTHESIZE(cocos2d::CCArray*, m_enemySecondArrays, EnemySecondArrays);
	CC_SYNTHESIZE(cocos2d::CCArray*, m_enemyThirdArrays, EnemyThirdArrays);

private:
	cocos2d::CCSpriteFrame* m_enemyOneFrame;
	cocos2d::CCSpriteFrame* m_enemySecondFrame;
	cocos2d::CCSpriteFrame* m_enemyThird_OneFrame;
	cocos2d::CCSpriteFrame* m_enemyThird_SecondFrame;
};

#endif