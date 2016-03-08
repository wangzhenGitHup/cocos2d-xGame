#include"UFO.h"
#include"SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

UFOLayer* UFOLayer::createUFOLayer()
{
	UFOLayer* ufoLayer = new UFOLayer();
	if(ufoLayer)
	{
		ufoLayer->init();
		ufoLayer->autorelease();
		return ufoLayer;
	}
	CC_SAFE_DELETE(ufoLayer);
	return NULL;
}

UFOLayer::UFOLayer()
{
	m_allMultiBulletArrays = CCArray::create();
	m_allMultiBulletArrays->retain();

	m_allBigBoomArrays = CCArray::create();
	m_allBigBoomArrays->retain();
}

UFOLayer::~UFOLayer()
{
	CC_SAFE_RELEASE_NULL(m_allMultiBulletArrays);
	CC_SAFE_RELEASE_NULL(m_allBigBoomArrays);
}

bool UFOLayer::init()
{
	if(!CCLayer::init())
	{
		return false;
	}
	this->schedule(schedule_selector(UFOLayer::addMultiBullets), 20.0f);
	this->schedule(schedule_selector(UFOLayer::addBigBoom), 20.0f, kCCRepeatForever, 5.0f);

	return true;
}

void UFOLayer::addMultiBullets(float dt)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/out_porp.mp3");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* bullet = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo1.png"));
	CCSize bulletSize = bullet->getContentSize();
	int minPosX = bulletSize.width / 2;
	int maxPosX = winSize.width - bulletSize.width / 2;
	int rangePosX = maxPosX - minPosX;
	int actualPosX = (rand() % rangePosX) + minPosX;

	bullet->setPosition(ccp(actualPosX, winSize.height + bulletSize.height / 2));
	this->addChild(bullet);
	m_allMultiBulletArrays->addObject(bullet);

	CCMoveBy* move1 = CCMoveBy::create(0.5f, CCPointMake(0, -150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f, CCPointMake(0, 100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f, CCPointMake(0, -winSize.height - bulletSize.height / 2));
	CCCallFuncN* moveDone = CCCallFuncN::create(this, callfuncN_selector(UFOLayer::multiBulletsMoveFinished));
	CCSequence* seq = CCSequence::create(move1, move2, move3, moveDone, NULL);
	bullet->runAction(seq);
}

void UFOLayer::multiBulletsMoveFinished(CCNode* node)
{
	CCSprite* bullet = (CCSprite*)node;
	this->removeChild(bullet, true);
	m_allMultiBulletArrays->removeObject(bullet);
}

void UFOLayer::addBigBoom(float dt)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/out_porp.mp3");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite* bigBoom = CCSprite::createWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ufo2.png"));
	CCSize bigBoomSize = bigBoom->getContentSize();
	int minPosX = bigBoomSize.width / 2;
	int maxPosX = winSize.width - bigBoomSize.width / 2;
	int rangePosX = maxPosX - minPosX;
	int actualPosX = (rand() % rangePosX) + minPosX;

	bigBoom->setPosition(ccp(actualPosX, winSize.height - bigBoomSize.height / 2));
	this->addChild(bigBoom);
	m_allBigBoomArrays->addObject(bigBoom);

	CCMoveBy* move1 = CCMoveBy::create(0.5f, CCPointMake(0, -150));
	CCMoveBy* move2 = CCMoveBy::create(0.3f, CCPointMake(0, 100));
	CCMoveBy* move3 = CCMoveBy::create(1.0f, CCPointMake(0, -winSize.height - bigBoomSize.height / 2));
	CCCallFuncN* moveDone = CCCallFuncN::create(this, callfuncN_selector(UFOLayer::bigBoomMoveFinished));
	CCSequence* seq = CCSequence::create(move1, move2, move3, moveDone, NULL);
	bigBoom->runAction(seq);
}

void UFOLayer::bigBoomMoveFinished(CCNode* node)
{
	CCSprite* bigBoom = (CCSprite*)node;
	this->removeChild(bigBoom, true);
	m_allBigBoomArrays->removeObject(bigBoom);
}

void UFOLayer::removeMultiBullets(CCSprite* bullet)
{
	this->removeChild(bullet, true);
	m_allMultiBulletArrays->removeObject(bullet);
}

void UFOLayer::removeBigBoom(CCSprite* bigBoom)
{
	this->removeChild(bigBoom, true);
	m_allBigBoomArrays->removeObject(bigBoom);
}