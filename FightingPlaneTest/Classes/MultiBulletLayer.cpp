#include"MultiBulletLayer.h"
#include"PlaneLayer.h"
#include"SimpleAudioEngine.h"
#include"global.h"

using namespace CocosDenshion;
USING_NS_CC;

MultiBulletLayer::MultiBulletLayer()
{
	m_allBullets = CCArray::create();
	m_allBullets->retain();
	m_multiBulletBatchNode = NULL;
}

MultiBulletLayer::~MultiBulletLayer()
{
	CC_SAFE_RELEASE_NULL(m_allBullets);
}

bool MultiBulletLayer::init()
{
	m_multiBulletBatchNode = CCSpriteBatchNode::create("shoot.png");
	this->addChild(m_multiBulletBatchNode);
	return true;
}

MultiBulletLayer* MultiBulletLayer::createBullet()
{
	MultiBulletLayer* bullet = new MultiBulletLayer();
	if(bullet)
	{
		bullet->init();
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return NULL;
}

void MultiBulletLayer::addBullet(float dt)
{
	SimpleAudioEngine::sharedEngine()->playEffect("sound/bullet.mp3");
	CCSprite* bulletLeft = CCSprite::createWithSpriteFrameName("bullet2.png");
	CCSprite* bulletRight = CCSprite::createWithSpriteFrameName("bullet2.png");

	m_multiBulletBatchNode->addChild(bulletLeft);
	m_multiBulletBatchNode->addChild(bulletRight);
	m_allBullets->addObject(bulletLeft);
	m_allBullets->addObject(bulletRight);

	PlaneLayer* plane = (PlaneLayer*)PlaneLayer::sharedPlaneLayer()->getChildByTag(AIR_TAG);
	CCPoint planePos = plane->getPosition();
	CCSize planeSize = plane->getContentSize();
	CCPoint bulletLeftPos = ccp(planePos.x - 33, planePos.y + 35);
	CCPoint bulletRightPos = ccp(planePos.x + 33, planePos.y + 35);

	bulletLeft->setPosition(bulletLeftPos);
	bulletRight->setPosition(bulletRightPos);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	float flyDistance =  winSize.height + bulletLeft->getContentSize().height / 2 - planePos.y;
	float flySpeed = 320;
	float flyTime = flyDistance / flySpeed;

	CCMoveTo* moveToLeft = CCMoveTo::create(flyTime, ccp(bulletLeftPos.x, winSize.height + bulletLeft->getContentSize().height / 2));
	CCMoveTo* moveToRight = CCMoveTo::create(flyTime, ccp(bulletRightPos.x, winSize.height + bulletRight->getContentSize().height / 2));
	CCCallFuncN* flyDone = CCCallFuncN::create(this, callfuncN_selector(MultiBulletLayer::bulletFlyFinish));
	CCSequence* seqLeft = CCSequence::create(moveToLeft, flyDone, NULL);
	CCSequence* seqRight = CCSequence::create(moveToRight, flyDone, NULL);

	bulletLeft->runAction(seqLeft);
	bulletRight->runAction(seqRight);
}

void MultiBulletLayer::bulletFlyFinish(CCNode* node)
{
	CCSprite* bullet = (CCSprite*)node;
	this->removeBullet(bullet);
}

void MultiBulletLayer::removeBullet(CCSprite* bullet)
{
	if(bullet)
	{
		m_multiBulletBatchNode->removeChild(bullet, true);
		m_allBullets->removeObject(bullet);
	}
}

void MultiBulletLayer::startShoot()
{
	this->schedule(schedule_selector(MultiBulletLayer::addBullet), 0.2f, 30, 0.0f);
}

void MultiBulletLayer::stopShoot()
{
	this->unschedule(schedule_selector(MultiBulletLayer::addBullet));
}