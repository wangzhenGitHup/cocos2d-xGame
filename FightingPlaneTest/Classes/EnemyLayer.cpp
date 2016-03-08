#include"EnemyLayer.h"
#include"SimpleAudioEngine.h"
#include"GameLayer.h"

using namespace CocosDenshion;

USING_NS_CC;

EnemyLayer* EnemyLayer::createEnemyLayer()
{
	EnemyLayer* enemyLayer = new EnemyLayer();
	if(enemyLayer)
	{
		enemyLayer->init();
		enemyLayer->autorelease();
		return enemyLayer;
	}
	CC_SAFE_DELETE(enemyLayer);
	return NULL;
}

EnemyLayer::EnemyLayer() : m_enemyOneFrame(NULL), m_enemySecondFrame(NULL),
	m_enemyThird_OneFrame(NULL), m_enemyThird_SecondFrame(NULL)
{
	m_enemyOneArrays = CCArray::create();
	m_enemyOneArrays->retain();

	m_enemySecondArrays = CCArray::create();
	m_enemySecondArrays->retain();

	m_enemyThirdArrays = CCArray::create();
	m_enemyThirdArrays->retain();
}

EnemyLayer::~EnemyLayer()
{
	CC_SAFE_RELEASE_NULL(m_enemyOneArrays);
	CC_SAFE_RELEASE_NULL(m_enemySecondArrays);
	CC_SAFE_RELEASE_NULL(m_enemyThirdArrays);
}

bool EnemyLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	m_enemyOneFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1.png");
	m_enemySecondFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2.png");
	m_enemyThird_OneFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n1.png");
	m_enemyThird_SecondFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_n2.png");

	CCAnimation* enemyOneAnimation = CCAnimation::create();
	enemyOneAnimation->setDelayPerUnit(0.1f);
	enemyOneAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down1.png"));
	enemyOneAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down2.png"));
	enemyOneAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down3.png"));
	enemyOneAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy1_down4.png"));

	CCAnimation* enemySecondAnimation = CCAnimation::create();
	enemySecondAnimation->setDelayPerUnit(0.1f);
	enemySecondAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down1.png"));
	enemySecondAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down2.png"));
	enemySecondAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down3.png"));
	enemySecondAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy2_down4.png"));

	CCAnimation* enemyThirdAnimation = CCAnimation::create();
	enemyThirdAnimation->setDelayPerUnit(0.1f);
	enemyThirdAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down1.png"));
	enemyThirdAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down2.png"));
	enemyThirdAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down3.png"));
	enemyThirdAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down4.png"));
	enemyThirdAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down5.png"));
	enemyThirdAnimation->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("enemy3_down6.png"));

	CCAnimationCache::sharedAnimationCache()->addAnimation(enemyOneAnimation, "enemyOneBlowEffect");
	CCAnimationCache::sharedAnimationCache()->addAnimation(enemySecondAnimation, "enemySecondBlowEffect");
	CCAnimationCache::sharedAnimationCache()->addAnimation(enemyThirdAnimation, "enemyThirdBlowEffect");

	this->schedule(schedule_selector(EnemyLayer::addEnemyOne), 0.5);
	this->schedule(schedule_selector(EnemyLayer::addEnemySecond), 3.0);
	this->schedule(schedule_selector(EnemyLayer::addEnemyThird), 6.0);

	return true;
}

int EnemyLayer::getCurrentGameLevel()
{
	return GameLayer::getGameLevel();
}

void EnemyLayer::addEnemy(EnemyType type)
{
	Enemy* enemy = Enemy::createEnemy();
	CCSpriteFrame* frame = (type == ENEMYONE) ? m_enemyOneFrame : ((type == ENEMYSECOND) ? m_enemySecondFrame : m_enemyThird_OneFrame);
	int enemyLife = (type == ENEMYONE) ? ENEMYONE_MAXLIFE : ((type == ENEMYSECOND) ? ENEMYSECOND_MAXLIFE : ENEMYTHIRD_MAXLIFE);
	enemy->bindSprite(CCSprite::createWithSpriteFrame(frame), enemyLife);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize enemySize = enemy->getSprite()->getContentSize();
	int minPosX = enemySize.width / 2;
	int maxPosX = winSize.width - enemySize.width / 2;
	int rangePosX = maxPosX - minPosX;
	int actualPosX = (rand() % rangePosX) + minPosX;

	enemy->setPosition(ccp(actualPosX, winSize.height + enemySize.height / 2));
	this->addChild(enemy);

	if(type == ENEMYONE)
	{
		m_enemyOneArrays->addObject(enemy);
	}
	else if(type == ENEMYSECOND)
	{
		m_enemySecondArrays->addObject(enemy);
	}
	else if(type == ENEMYTHIRD)
	{
		m_enemyThirdArrays->addObject(enemy);
	}

	float minSpeed, maxSpeed;

	switch(this->getCurrentGameLevel())
	{
	case EASY:
		minSpeed = (type == ENEMYONE) ? 2.0f : ((type == ENEMYSECOND) ? 3.0f : 4.0f);
		maxSpeed = (type == ENEMYONE) ? 4.0f : ((type == ENEMYSECOND) ? 6.0f : 8.0f);
		break;

	case MIDDLE:
		minSpeed = (type == ENEMYONE) ? 1.8f : ((type == ENEMYSECOND) ? 2.7f : 3.6f);
		maxSpeed = (type == ENEMYONE) ? 3.6f : ((type == ENEMYSECOND) ? 5.4f : 7.2f);
		break;

	case HARD:
		minSpeed = (type == ENEMYONE) ? 1.6f : ((type == ENEMYSECOND) ? 2.5f : 3.2f);
		maxSpeed = (type == ENEMYONE) ? 3.2f : ((type == ENEMYSECOND) ? 5.0f : 6.4f);
		break;

	default:
		minSpeed = (type == ENEMYONE) ? 2.0f : ((type == ENEMYSECOND) ? 3.0f : 4.0f);
		maxSpeed = (type == ENEMYONE) ? 4.0f : ((type == ENEMYSECOND) ? 6.0f : 8.0f);
		break;
	}

	int rangeSpeed = maxSpeed - minSpeed;
	int actualSpeed = (rand() % rangeSpeed) + minSpeed;
	CCMoveTo* moveTo = CCMoveTo::create(actualSpeed, ccp(actualPosX, -enemySize.height / 2));
	CCCallFuncN* moveDone = NULL;
	if(type == ENEMYONE)
	{
		moveDone = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemyOneMoveFinish));
	}
	else if(type == ENEMYSECOND)
	{
		moveDone = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemySecondMoveFinish));
	}
	else if(type == ENEMYTHIRD)
	{
		moveDone = CCCallFuncN::create(this, callfuncN_selector(EnemyLayer::enemyThirdMoveFinish));
	}

	CCSequence* seq = CCSequence::create(moveTo, moveDone, NULL);
	enemy->runAction(seq);

	if(type == ENEMYTHIRD)
	{
		CCAnimation* animation = CCAnimation::create();
		animation->addSpriteFrame(m_enemyThird_OneFrame);
		animation->addSpriteFrame(m_enemyThird_SecondFrame);

		CCAnimate* animate = CCAnimate::create(animation);
		enemy->getSprite()->runAction(CCRepeatForever::create(animate));
	}
}

void EnemyLayer::enemyMoveFinish(EnemyType type, CCNode* node)
{
	Enemy* enemy = (Enemy*)node;

	this->removeChild(enemy, true);
	if(type == ENEMYONE)
	{
		m_enemyOneArrays->removeObject(enemy);
	}
	else if(type == ENEMYSECOND)
	{
		m_enemySecondArrays->removeObject(enemy);
	}
	else if(type == ENEMYTHIRD)
	{
		m_enemySecondArrays->removeObject(enemy);
	}
}

void EnemyLayer::enemyBlowEffect(EnemyType type, Enemy* enemy)
{
	const char* enemyMusicPath = (type == ENEMYONE) ? "sound/enemy1_down.mp3" : ((type == ENEMYSECOND) ? "sound/enemy2_down.mp3" : "sound/enemy3_down.mp3");
	const char* enemyBlowEffectName = (type == ENEMYONE) ? "enemyOneBlowEffect" : ((type == ENEMYSECOND) ? "enemySecondBlowEffect" : "enemyThirdBlowEffect");
	
	SimpleAudioEngine::sharedEngine()->playEffect(enemyMusicPath);
	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(enemyBlowEffectName);
	CCAnimate* animate = CCAnimate::create(animation);
	CCCallFuncND* execDone = NULL;
	if(type == ENEMYONE)
	{
		execDone = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemyOne), (void*)enemy);
	}
	else if(type == ENEMYSECOND)
	{
		execDone = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemySecond), (void*)enemy);
	}
	else if(type == ENEMYTHIRD)
	{
		execDone = CCCallFuncND::create(this, callfuncND_selector(EnemyLayer::removeEnemyThird), (void*)enemy);
	}
	CCSequence* seq = CCSequence::create(animate, execDone, NULL);
	enemy->getSprite()->runAction(seq);
}

void EnemyLayer::addEnemyOne(float dt)
{
	this->addEnemy(ENEMYONE);
}

void EnemyLayer::enemyOneMoveFinish(CCNode* node)
{
	this->enemyMoveFinish(ENEMYONE, node);
}

void EnemyLayer::enemyOneBlowEffect(Enemy* enemy)
{
	this->enemyBlowEffect(ENEMYONE, enemy);
}

void EnemyLayer::removeEnemyOne(CCNode* node, void* data)
{
	Enemy* enemy = (Enemy*)data;
	m_enemyOneArrays->removeObject(enemy, true);
	this->removeChild(enemy, true);
}

void EnemyLayer::removeAllEnemyOne()
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_enemyOneArrays, obj)
	{
		Enemy* enemy = (Enemy*)obj;
		if(enemy->getLife() > 0)
		{
			this->enemyOneBlowEffect(enemy);
		}
	}
}

void EnemyLayer::addEnemySecond(float dt)
{
	this->addEnemy(ENEMYSECOND);
}

void EnemyLayer::enemySecondMoveFinish(CCNode* node)
{
	this->enemyMoveFinish(ENEMYSECOND, node);
}

void EnemyLayer::enemySecondBlowEffect(Enemy*enemy)
{
	this->enemyBlowEffect(ENEMYSECOND, enemy);
}

void EnemyLayer::removeEnemySecond(CCNode* node, void* data)
{
	Enemy* enemy = (Enemy*)data;
	m_enemySecondArrays->removeObject(enemy, true);
	this->removeChild(enemy, true);
}

void EnemyLayer::removeAllEnemySecond()
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_enemySecondArrays, obj)
	{
		Enemy* enemy = (Enemy*)obj;
		if(enemy->getLife() > 0)
		{
			this->enemySecondBlowEffect(enemy);
		}
	}
}

void EnemyLayer::addEnemyThird(float dt)
{
	this->addEnemy(ENEMYTHIRD);
}

void EnemyLayer::enemyThirdMoveFinish(CCNode* node)
{
	this->enemyMoveFinish(ENEMYTHIRD, node);
}

void EnemyLayer::enemyThirdBlowEffect(Enemy* enemy)
{
	this->enemyBlowEffect(ENEMYTHIRD, enemy);
}

void EnemyLayer::removeEnemyThird(CCNode* node, void* data)
{
	Enemy* enemy = (Enemy*)data;
	m_enemyThirdArrays->removeObject(enemy, true);
	this->removeChild(enemy, true);
}

void EnemyLayer::removeAllEnemyThird()
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(m_enemyThirdArrays, obj)
	{
		Enemy* enemy = (Enemy*)obj;
		if(enemy->getLife() > 0)
		{
			this->enemyThirdBlowEffect(enemy);
		}
	}
}